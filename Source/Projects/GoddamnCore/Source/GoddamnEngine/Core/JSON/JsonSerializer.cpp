// ==========================================================================================
// Copyright (C) Goddamn Industries 2015. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

//! @file GoddamnEngine/Core/JSON/JsonParser.cpp
//! JavaScript Object Notation data parsing.
#include <GoddamnEngine/Core/JSON/Json.h>
#include <GoddamnEngine/Core/UniquePtr.h>
#include <GoddamnEngine/Core/IO/Stream/Stream.h>
#include <GoddamnEngine/Core/Containers/StringBuilder.h>

GD_NAMESPACE_BEGIN

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// JSON Reader.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// ------------------------------------------------------------------------------------------
	//! Represents type of the JSON token.
	enum class JsonTokenType : UInt8
	{
		Error,
		EndOfStream,
		Number,
		String,
		Literal,
		Punctuation,
	};	// enum class JsonTokenType

	// ------------------------------------------------------------------------------------------
	//! Represents the single JSON token.
	struct JsonToken
	{
		JsonTokenType TokenType;
		String        TokenData;
		union {
			bool      TokenBool;
			Float64   TokenNumber;
			Char      TokenPunctiation;
		};	// anonymous union. 
	};	// struct JsonToken

	// ------------------------------------------------------------------------------------------
	//! Parses next token from the input stream.
	//! @param stream Input stream with possible JSON data.
	//! @returns Next token parsed from the input stream.
	GDINT static JsonToken JsonGetNextToken(InputStream* const stream)
	{
#if GD_COMPILER_MSVC
#	pragma warning(push)
#	pragma warning(disable : 4244)
#endif	// if GD_COMPILER_MSVC

		// Skipping all the space characters inside the stream.
		Int16 nextCharacter;
		do
		{
			nextCharacter = stream->Read();
		} while (CChar::IsSpace(static_cast<Char>(nextCharacter)) && nextCharacter != -1);
		if (nextCharacter == -1) return{ JsonTokenType::EndOfStream };

		JsonToken nextToken = {};
		if(CChar::IsDigit(nextCharacter) || CString::Strchr("+-.", nextCharacter) != nullptr)
		{
			// Numeric constant. Is should be written like a "cast-able" to double constant in C++.
			nextToken.TokenType = JsonTokenType::Number;
			while ((CChar::IsDigit(nextCharacter) || CChar::IsAlphabetic(nextCharacter)
				|| CString::Strchr("+-.", nextCharacter) != nullptr) && nextCharacter != -1)
			{
				nextToken.TokenData.Append(nextCharacter);
				nextCharacter = stream->Read();
			}
			stream->Seek(-1);

			// Testing whether all the token content is a valid number.
			CStr numberString = nextToken.TokenData.CStr();
			nextToken.TokenNumber = CString::Strtof64(numberString, &numberString);
			if (*numberString != '\0')
				return{ JsonTokenType::Error, String::Format("Invalid numeric constant \"%s\" in the input stream.", nextToken.TokenData.CStr()) };
		}
		else if (CChar::IsAlphabetic(nextCharacter))
		{
			// Literal. Is should be one of the following: "null", "true" or "false".
			nextToken.TokenType = JsonTokenType::Literal;
			nextToken.TokenBool = nextCharacter == 't';
			while ((CChar::IsDigit(nextCharacter) || CChar::IsAlphabetic(nextCharacter)) && nextCharacter != -1)
			{
				nextToken.TokenData.Append(nextCharacter);
				nextCharacter = stream->Read();
			}
			stream->Seek(-1);

			// All literals except "null", "true" and "false" are treated as errors.
			if (nextToken.TokenData != "null" && nextToken.TokenData != "true" && nextToken.TokenData != "false")
				return{ JsonTokenType::Error, String::Format("Invalid literal \"%s\" in the input stream.", nextToken.TokenData.CStr()) };
		}
		else if (nextCharacter == '\"')
		{
			// String constant. It should be a character sequence with the limited support of the escape sequences.
			nextToken.TokenType = JsonTokenType::String;
			nextCharacter = stream->Read();
			while ((CChar::IsDigit(nextCharacter) || CChar::IsAlphabetic(nextCharacter) || CChar::IsPunctuation(nextCharacter) || CChar::IsSpace(nextCharacter))
				&& nextCharacter != '\"' && nextCharacter != '\n' && nextCharacter != '\r' && nextCharacter != -1)
			{
				if (!nextToken.TokenData.IsEmpty() && *nextToken.TokenData.ReverseBegin() == '\\')
				{
					// Escape sequence. Replacing last character (\) with the special one.
					auto& prevCharacter = *nextToken.TokenData.ReverseBegin();
					switch (nextCharacter)
					{
					case 'a': prevCharacter = '\a'; break; case 'b': prevCharacter = '\b'; break; case 'f': prevCharacter = '\f'; break; case 'n': prevCharacter = '\n'; break;
					case 'r': prevCharacter = '\r'; break; case 't': prevCharacter = '\r'; break; case '"': prevCharacter = '\"'; break; 
					case '\'': prevCharacter = '\''; break; case '\\': prevCharacter = '\\'; break;
					default:
						return{ JsonTokenType::Error, String::Format("Invalid escape sequence \"\\%c\" in the input stream.", nextCharacter) };
					}
				}
				else
				{
					nextToken.TokenData.Append(nextCharacter);
				}
				nextCharacter = stream->Read();
			}
			// No need to unget last character - it is '"' and should be skipped.

			// No line breaks are allowed inside string constants, as soon as unfinished string constants.
			if (nextCharacter == '\n' || nextCharacter == '\r') return{ JsonTokenType::Error, "Unexpected line break while parsing string constant." };
			if (nextCharacter == -1)                            return{ JsonTokenType::Error, "Unexpected end of stream while parsing string constant." };
		}
		else if (CString::Strchr(",:[]{}", static_cast<Char>(nextCharacter)) != nullptr)
		{
			// Punctuation character. "," - for values separation, ":" - fields, "{}" - objects and "[]" - arrays.
			nextToken.TokenType = JsonTokenType::Punctuation;
			nextToken.TokenData.Append(nextCharacter);
			nextToken.TokenPunctiation = static_cast<Char>(nextCharacter);
		}
		else
		{
			nextToken.TokenType = JsonTokenType::Error;
			nextToken.TokenData = String::Format("Invalid character %c in the input stream.", static_cast<Char>(nextCharacter));
		}

		return nextToken;

#if GD_COMPILER_MSVC
#	pragma warning(pop)
#endif	// if GD_COMPILER_MSVC
	}

	GDINT static JsonResult<JsonObject> JsonParseObject(InputStream* const stream, JsonToken& nextToken);
	GDINL static JsonResult<JsonObject> JsonParseObject(InputStream* const stream)
	{
		auto firstToken = JsonGetNextToken(stream);
		return JsonParseObject(stream, firstToken);
	}

	GDINT static JsonResult<JsonValue> JsonParseValue(InputStream* const stream, JsonToken& nextToken);
	GDINL static JsonResult<JsonValue> JsonParseValue(InputStream* const stream)
	{
		auto firstToken = JsonGetNextToken(stream);
		return JsonParseValue(stream, firstToken);
	}

	// ------------------------------------------------------------------------------------------
	//! Parses next JSON value from the input stream.
	//! @param stream Input stream with possible JSON data.
	//! @param nextToken First token of the expression.
	//! @returns Pointer to the JSON value or error description.
	GDINT static JsonResult<JsonValue> JsonParseValue(InputStream* const stream, JsonToken& nextToken)
	{
		switch (nextToken.TokenType)
		{
			// Number and string constants are valid JSON values.
			case JsonTokenType::Number: 
				return{ GD_NEW(JsonValueNumber, nextToken.TokenNumber) };
			case JsonTokenType::String: 
				return{ GD_NEW(JsonValueString, nextToken.TokenData) };

			// Boolean and null literals are also valid.
			case JsonTokenType::Literal: 
				return{ *nextToken.TokenData.CStr() == 'n'
					? static_cast<JsonValue*>(GD_NEW(JsonValueNull))
					: static_cast<JsonValue*>(GD_NEW(JsonValueBool, nextToken.TokenBool)) };

			// Punctuation token may mean only JSON object or array.
			case JsonTokenType::Punctuation: 
				if (nextToken.TokenPunctiation == '{')
				{
					// Trying to read next object from stream and treat is a JSON value.
					auto const jsonObject = JsonParseObject(stream);
					if (!jsonObject.ErrorDesc.IsEmpty()) return{ nullptr, jsonObject.ErrorDesc };
					return{ GD_NEW(JsonValueObject, jsonObject.Result) };
				}
				if (nextToken.TokenPunctiation == '[')
				{
					// Trying to read the array from stream.
					UniquePtr<JsonValueArray> jsonArray(GD_NEW(JsonValueArray));
					for (;;)
					{
						nextToken = JsonGetNextToken(stream);
						if (nextToken.TokenType == JsonTokenType::Punctuation && nextToken.TokenPunctiation == ']')
							return{ jsonArray.Release() };

						// Reading next element of the array..
						auto const jsonValue = JsonParseValue(stream, nextToken);
						if (!jsonValue.ErrorDesc.IsEmpty()) return jsonValue;
						jsonArray->ValueArray.InsertLast(jsonValue.Result);

						// And expecting "," as value separator or "]" as array closing.
						nextToken = JsonGetNextToken(stream);
						if (nextToken.TokenType == JsonTokenType::Punctuation)
						{
							if (nextToken.TokenPunctiation == ']') return{ SharedPtr<JsonValue>(jsonArray.Release()) };
							if (nextToken.TokenPunctiation == ',') continue;
						}
						return{ nullptr, "Unexpected token in the array declaration, ',' or ']' expected." };
					}
				}
				fallthrough;

			// All other types of tokens could not be treated as values.
			default: 
				return{ nullptr, "Unexpected token in the array declaration, value expected." };
		}
	}

	// ------------------------------------------------------------------------------------------
	//! Parses next JSON object from the input stream.
	//! @param stream Input stream with possible JSON data.
	//! @param nextToken First token of the object after '{'.
	//! @returns Pointer to the JSON object or error description.
	GDINT static JsonResult<JsonObject> JsonParseObject(InputStream* const stream, JsonToken& nextToken)
	{
		UniquePtr<JsonObject> jsonObject(GD_NEW(JsonObject));

		// This may possibly be the empty object.
		if (nextToken.TokenType == JsonTokenType::Punctuation && nextToken.TokenPunctiation == '}')
			return{ jsonObject.Release() };

		for (;;)
		{
			// Reading the string constant token that represents name of the field.
			if (nextToken.TokenType != JsonTokenType::String)
				return{ nullptr, "Unexpected token in the object field name, string constant expected." };

			auto const jsonObjectFieldName = nextToken.TokenData;
			
			// Reading the field-value separator semicolon.
			nextToken = JsonGetNextToken(stream);
			if (nextToken.TokenType != JsonTokenType::Punctuation || nextToken.TokenPunctiation != ':')
				return{ nullptr, "Unexpected token in the object field, ':' expected." };

			auto const jsonObjectFieldValue = JsonParseValue(stream);
			if (!jsonObjectFieldValue.ErrorDesc.IsEmpty()) return{ nullptr, jsonObjectFieldValue.ErrorDesc };

			// Inserting our field into the object.
			jsonObject->AddField(jsonObjectFieldName, jsonObjectFieldValue.Result);

			// And expecting "," as field separator or "}" as object closing.
			nextToken = JsonGetNextToken(stream);
			if (nextToken.TokenType == JsonTokenType::Punctuation)
			{
				if (nextToken.TokenPunctiation == '}') return{ jsonObject.Release() };
				if (nextToken.TokenPunctiation == ',')
				{
					nextToken = JsonGetNextToken(stream);
					continue;
				}
			}
			return{ nullptr, "Unexpected token in the object declaration, ',' or '}' expected." };
		}
	}

	// ------------------------------------------------------------------------------------------
	//! Parses JSON data from the input stream.
	//! @param stream Input stream with possible JSON data.
	//! @returns Pointer to the JSON m_RootNode object or error description.
	GDAPI JsonDocument JsonSerializer::Parse(InputStream* const stream)
	{
		// Expecting beginning of the m_RootNode object.
		auto nextToken = JsonGetNextToken(stream);
		if (nextToken.TokenType != JsonTokenType::Punctuation || nextToken.TokenPunctiation != '{')
			return{ nullptr, "Unexpected token in the m_RootNode object declaration, '{' expected." };

		// Parsing the m_RootNode object.
		auto const jsonObject = JsonParseObject(stream);
		return jsonObject;
	}

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// JSON Writer.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GDINT static void JsonWriteValue(SharedPtr<JsonValue> const jsonValue, StringBuilder& builder, UInt32 const depth = 0);
	GDINT static void JsonWriteObject(SharedPtr<JsonObject> const jsonObject, StringBuilder& builder, UInt32 const depth = 0);

#if 0
	// ------------------------------------------------------------------------------------------
	//! Writes following JSON string constant directly into the string builder.
	//! @param jsonString JSON string constant to write.
	//! @param builder Output buffer.
	GDINL static void JsonWriteString(String const& jsonString, StringBuilder& builder)
	{
		builder.Append('\"');
		for (auto jsonChar : jsonString)
		{
			// Parsing the escape sequences inside string constants.
			switch (jsonChar)
			{
				case '\a': builder.Append("\\a"); break; case '\b': builder.Append("\\b"); break; case '\f': builder.Append("\\f"); break; 
				case '\r': builder.Append("\\r"); break; case '\t': builder.Append("\\r"); break; case '\n': builder.Append("\\n"); break;
				case '\"': builder.Append("\\\""); break; case '\'': builder.Append("\\'"); break; case '\\': builder.Append("\\\\"); break;
				default: builder.Append(jsonChar); break;
			}
		}
		builder.Append('\"');
	}
#endif	// if 0

	// ------------------------------------------------------------------------------------------
	//! Writes following JSON value directly into the string builder.
	//! @param jsonValue JSON value to write.
	//! @param builder Output buffer.
	//! @param depth If positive, depth of object insets (so pretty printing may be supported).
	GDINT static void JsonWriteValue(SharedPtr<JsonValue> const jsonValue, StringBuilder& builder, UInt32 const depth)
	{
		switch (jsonValue->GetType())
		{
			// Numbers and literals can be safely written as raw string.
			case JsonValueType::Null:
			case JsonValueType::Bool:
			case JsonValueType::Number:
			{
				String value;
				jsonValue->TryGetString(value);
				builder.Append(value);
			} break;

			// We have a separate function to write string constants.
			case JsonValueType::String:
			{
				auto const jsonValueString = static_cast<JsonValueString*>(jsonValue.GetPointer());
				builder.AppendFormat("\"%s\"", jsonValueString->ValueString.WrapEscapeSequences().CStr());
			} break;

			// We have a separate function to write objects.
			case JsonValueType::Object:
			{
				auto const jsonValueObject = static_cast<JsonValueObject*>(jsonValue.GetPointer());
				JsonWriteObject(jsonValueObject->ValueObject, builder, depth);
			} break;

			// Writing the array.
			case JsonValueType::Array:
			{
				auto const jsonValueArray = static_cast<JsonValueArray*>(jsonValue.GetPointer());

				builder.Append('[');
				if (!jsonValueArray->ValueArray.IsEmpty())
				{
					String identations(depth, '\t');
					for (auto jsonArrayIter = jsonValueArray->ValueArray.Begin(); jsonArrayIter != jsonValueArray->ValueArray.End() - 1; ++jsonArrayIter)
					{
						// Writing all array elements except the last one with comma delimiter..
						builder.AppendFormat("\n\t%s", identations.CStr());
						JsonWriteValue(*jsonArrayIter, builder, depth);
						builder.Append(", ");
					}

					// Writing the last array element..
					builder.AppendFormat("\n\t%s", identations.CStr());
					JsonWriteValue(jsonValueArray->ValueArray.GetLast(), builder, depth);
					builder.AppendFormat("\n%s]", identations.CStr());
				}
				else
				{
					builder.Append(" ]");
				}
			} break;

			default: 
				GD_DEBUG_ASSERT_FALSE("Invalid JSON value type.");
		}
	}

	// ------------------------------------------------------------------------------------------
	//! Writes following JSON object directly into the string builder.
	//! @param jsonValue JSON object to write.
	//! @param builder Output buffer.
	//! @param depth If positive, depth of object insets (so pretty printing may be supported).
	GDINT static void JsonWriteObject(SharedPtr<JsonObject> const jsonObject, StringBuilder& builder, UInt32 const depth)
	{
		builder.Append('{');
		if (!jsonObject->GetFields().IsEmpty())
		{
			String identations(depth, '\t');
			for (auto jsonFieldIter = jsonObject->GetFieldsOrder().Begin(); jsonFieldIter != jsonObject->GetFieldsOrder().End() - 1; ++jsonFieldIter)
			{
				auto const& jsonFieldName = *jsonFieldIter;
				auto const jsonFieldValue = jsonObject->GetField(jsonFieldName);

				// Writing all object fields except the last one with comma delimiter..
				builder.AppendFormat("\n\t%s\"%s\" : ", identations.CStr(), jsonFieldName.WrapEscapeSequences().CStr());
				JsonWriteValue(jsonFieldValue, builder, depth + 1);
				builder.Append(", ");
			}

			// Writing the last object field..
			auto const& jsonLastFieldName = jsonObject->GetFieldsOrder().GetLast();
			auto const jsonLastFieldValue = jsonObject->GetField(jsonLastFieldName);

			builder.AppendFormat("\n\t%s\"%s\" : ", identations.CStr(), jsonLastFieldName.WrapEscapeSequences().CStr());
			JsonWriteValue(jsonLastFieldValue, builder, depth + 1);
			builder.AppendFormat("\n%s}", identations.CStr());
		}
		else
		{
			builder.Append(" }" );
		}
	}

	GDAPI void JsonSerializer::Write(SharedPtr<JsonObject> const json, class OutputStream* const stream)
	{
		StringBuilder builder;
		JsonWriteObject(json, builder);
		builder.Append('\n');
	}

GD_NAMESPACE_END
