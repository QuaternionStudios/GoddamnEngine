/// ==========================================================================================
/// StringBuilder.h: Mutable string interface.
/// Copyright (C) $(GODDAMN_DEV) 2011 - Present. All Rights Reserved.
/// 
/// History:
///		* 16.06.2014 - Created by James Jhuighuy.
/// ==========================================================================================

#pragma once
#ifndef GD_CORE_TEXT_STRINGBUILDER_STRINGBUILDER
#define GD_CORE_TEXT_STRINGBUILDER_STRINGBUILDER

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Core/Utility.h>
#include <GoddamnEngine/Core/Text/String/String.h>
#include <GoddamnEngine/Core/Containers/Vector/Vector.h>

GD_NAMESPACE_BEGIN

	/// Represents mutable sequence of characters.
	template<typename CharType>
	class BaseStringBuilder final
	{
	private:
		Vector<CharType> MutableString;

	public:
		GDINL  BaseStringBuilder(BaseStringBuilder&& Other) : MutableString(Move(Other.MutableString)) { }
		GDINL  BaseStringBuilder() { this->MutableString.PushLast(CharType('\0')); }
		GDINL ~BaseStringBuilder() { }

		/// Returns pointer on content of this builder.
		GDINL CharType const* GetPointer() const { return &this->MutableString[0]; }
		GDINL CharType      * GetPointer()       { return &this->MutableString[0]; }

		/// Returns length of this buffer.
		GDINL size_t GetLength() const { return this->MutableString.GetLength() - 1; }

		/// Returns number of characters this builder may include without reallocation.
		GDINL size_t GetCapacity() const { return this->MutableString.GetCapacity() - 1; }

		/// Resizes buffer.
		GDINL void Resize(size_t const NewSize) { this->MutableString.Resize(NewSize + 1); }

		/// Resizes buffer that it could store enough data without reallocation.
		GDINL void Reserve(size_t const NewCapacity) { this->MutableString.Reserve(NewCapacity + 1); }

		/// Appends string to this string builder.
		/// @param Format Standart printf-like format.
		/// @return Self.
		inline BaseStringBuilder& AppendFormat(CharType const* const Format, ...);
		inline BaseStringBuilder& Append(CharType const* const String, size_t const Length);
		inline BaseStringBuilder& Append(CharType const* const String);
		inline BaseStringBuilder& Append(String const& TheString);
		inline BaseStringBuilder& Append(CharType const Character);
		template <size_t const Count>
		inline BaseStringBuilder& Append(CharType const(&Array)[Count]);
		
		/// Converts this builder to normal string.
		GDINL String ToString() const;

		GDINL BaseStringBuilder& operator= (BaseStringBuilder&& Other) 
		{ 
			this->MutableString = Move(Other.MutableString); 
			return (*this);
		}
	};	// class BaseStringBuilder

	typedef BaseStringBuilder<Char> StringBuilder;

GD_NAMESPACE_END

#include <GoddamnEngine/Core/Text/StringBuilder/StringBuilder.inl>

#endif