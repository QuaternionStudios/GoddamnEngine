/// ==========================================================================================
/// Quaternion.h: quternion class.
/// Copyright (C) $(GODDAMN_DEV) 2011 - Present. All Rights Reserved.
/// 
/// History:
///		* 07.06.2014  - Rewritten from scratch by James Jhuighuy,
/// ==========================================================================================

#pragma once
#ifndef GD_CORE_MATH_QUATERNION
#define GD_CORE_MATH_QUATERNION

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Core/TypeTraits.h>
#include <GoddamnEngine/Core/Math/Vector3.h>
#include <GoddamnEngine/Core/Math/Vector3Fast.h>
#include <GoddamnEngine/Core/Math/Float32x4Intrinsics/Float32x4Intrinsics.h>

GD_NAMESPACE_BEGIN

	/// Generic quaternion class.
	template<typename ElementType>
	struct Quaternion_t final
	{
	public:
		static_assert(TypeTraits::IsFloatingPoint<ElementType>::Value, "'Quaternion_t<T>' error: T should be floating point");
		typedef typename Conditional<TypeTraits::IsPodType<ElementType>::Value, ElementType, ElementType const&>::Type ElementTypeConstRef;
		ElementType x, y, z, w;

	public /* Constructors */:
		GDINL Quaternion_t(ElementTypeConstRef const QuaternionValue0, ElementTypeConstRef const QuaternionValue1, ElementTypeConstRef const QuaternionValue2, ElementTypeConstRef const QuaternionValue3)
			: x(QuaternionValue0)
			, y(QuaternionValue1)
			, z(QuaternionValue2)
			, w(QuaternionValue3)
		{
		}

		GDINL Quaternion_t(Quaternion_t const& Other)
			: x(Other.x)
			, y(Other.y)
			, z(Other.z)
			, w(Other.w)
		{
		}

		GDINL Quaternion_t()
			: x(ElementType(0))
			, y(ElementType(0))
			, z(ElementType(0))
			, w(ElementType(1))
		{
		}

		GDINL ~Quaternion_t()
		{
		}

	public /* Class API */:
		inline Vector3t<ElementType> GetEulerRadians() const
		{
			ElementType const y = ElementType(asin (ElementType(-2) * (this->x * this->z - this->w * this->y)));
			ElementType const x = ElementType(atan2(ElementType( 2) * (this->y * this->z + this->w * this->x), this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z));
			ElementType const z = ElementType(atan2(ElementType( 2) * (this->x * this->y + this->w * this->z), this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z));

			return Vector3t<ElementType>(x, y, z);
		}

		inline Quaternion_t& SetEulerRadians(Vector3t<ElementType> const& Radians)
		{
			ElementType const CosZ = cos(Radians.z * ElementType(0.5f)), CosY = cos(Radians.y * ElementType(0.5f)), CosX = cos(Radians.x * ElementType(0.5f));
			ElementType const SinZ = sin(Radians.z * ElementType(0.5f)), SinY = sin(Radians.y * ElementType(0.5f)), SinX = sin(Radians.x * ElementType(0.5f));

			this->x = SinX * CosY * CosZ - CosX * SinY * SinZ;
			this->y = CosX * SinY * CosZ + SinX * CosY * SinZ;
			this->z = CosX * CosY * SinZ - SinX * SinY * CosZ;
			this->w = CosX * CosY * CosZ + SinX * SinY * SinZ;
			return (*this);
		}

		inline Quaternion_t RotateRadians(ElementTypeConstRef const Angle, Vector3t<ElementType> const& Vector) const
		{
			Vector3t<ElementType> const Axis = Vector.Normalize();
			ElementType const s = sin(Angle * ElementType(0.5f));
			ElementType const c = cos(Angle * ElementType(0.5f));
			return ((*this) * Quaternion_t(Axis.x * s, Axis.y * c, Axis.z * s, c));
		}

		GDINL Vector3t<ElementType> GetEulerDegrees() const
		{
			return this->GetEulerRadians() * ElementType(180.0f / M_PI);
		}

		GDINL Quaternion_t& SetEulerDegrees(Vector3t<ElementType> const& Degrees)
		{
			return this->SetEulerRadians(Degrees * ElementType(M_PI / 180.0f));
		}

		GDINL Quaternion_t RotateDegrees(ElementType const Angle, Vector3t<ElementType> const& Vector) const
		{
			return this->RotateRadians(Angle * ElementType(M_PI / 180.0f), Vector);
		}

	public /* Operators */:
		inline Quaternion_t operator* (Quaternion_t const& Other) const
		{
			return Quaternion_t(
				this->w * Other.x + this->x * Other.w + this->y * Other.z - this->z * Other.y,
				this->w * Other.y + this->y * Other.w + this->z * Other.x - this->x * Other.z,
				this->w * Other.z + this->z * Other.w + this->x * Other.y - this->y * Other.x,
				this->w * Other.w - this->x * Other.x - this->y * Other.y - this->z * Other.z
			);
		}

		inline Vector3t<ElementType> operator* (Vector3t<ElementType> const& Vector) const
		{
			ElementType static const Two = ElementType(2);

			Vector3t<ElementType> QuatVector(this->x, this->y, this->z);
			Vector3t<ElementType>  UV = QuatVector.Cross(Vector) * this->w * Two;
			Vector3t<ElementType> UUV = QuatVector.Cross(UV) * Two;
			
			return Vector + UV + UUV;
		}

		GDINL Quaternion_t operator*= (Quaternion_t const& Other)
		{
			return ((*this) = ((*this) * Other));
		}

		GDINL Quaternion_t operator= (Quaternion_t const& Other)
		{
			this->x = Other.x;
			this->y = Other.y;
			this->z = Other.z;
			this->w = Other.w;
			return (*this);
		}
	};	// struct Quaternion_t

#if (defined(GD_HAS_FLOAT32X4INTRINSICS) && (!defined(GD_DOCUMENTATION)))
	template<>
	struct GD_ALIGN_MSVC(16) Quaternion_t<Float32> final
	{
		union {
			Float32x4Intrinsics::VectorRegisterType ElementsVector;
			struct { Float32 x, y, z, w; };
		};	// anonymous union

	public /* Constructors */:
		GDINL Quaternion_t()
			: ElementsVector(Float32x4Intrinsics::VectorMake(0.0f, 0.0f, 0.0f, 1.0f))
		{
		}

		GDINL Quaternion_t(Float32 const QuaternionValue0, Float32 const QuaternionValue1, Float32 const QuaternionValue2, Float32 const QuaternionValue3)
			: ElementsVector(Float32x4Intrinsics::VectorMake(QuaternionValue0, QuaternionValue1, QuaternionValue2, QuaternionValue3))
		{
		}

		GDINL Quaternion_t(Float32x4Intrinsics::VectorRegisterType const ElementsVector)
			: ElementsVector(ElementsVector)
		{
		}

		GDINL Quaternion_t(Quaternion_t const& Other)
			: ElementsVector(Other.ElementsVector)
		{
		}

		GDINL ~Quaternion_t()
		{
		}

	public /* Class API */:

		/// ------------------------------------------------------------------------------------------
		/// *** EulerRadians ***
		/// ------------------------------------------------------------------------------------------

		inline Vector3Fast GetEulerRadians() const
		{
			Float32 const y = Float32(asin (Float32(-2) * (this->x * this->z - this->w * this->y)));
			Float32 const x = Float32(atan2(Float32( 2) * (this->y * this->z + this->w * this->x), this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z));
			Float32 const z = Float32(atan2(Float32( 2) * (this->x * this->y + this->w * this->z), this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z));

			return Vector3Fast(x, y, z, Float32(1.0f));
		}

		inline Quaternion_t& SetEulerRadians(Vector3Fast const& Radians)
		{
			Float32 const CosZ = cos(Radians.z * Float32(0.5f)), CosY = cos(Radians.y * Float32(0.5f)), CosX = cos(Radians.x * Float32(0.5f));
			Float32 const SinZ = sin(Radians.z * Float32(0.5f)), SinY = sin(Radians.y * Float32(0.5f)), SinX = sin(Radians.x * Float32(0.5f));

			this->x = SinX * CosY * CosZ - CosX * SinY * SinZ;
			this->y = CosX * SinY * CosZ + SinX * CosY * SinZ;
			this->z = CosX * CosY * SinZ - SinX * SinY * CosZ;
			this->w = CosX * CosY * CosZ + SinX * SinY * SinZ;
			return (*this);
		}

		inline Quaternion_t RotateRadians(Float32 const Angle, Vector3Fast const& Vector) const
		{
			Vector4t<Float32> const Axis = Vector.Normalize();
			Float32 const s = sin(Angle * Float32(0.5f));
			Float32 const c = cos(Angle * Float32(0.5f));
			return ((*this) * Quaternion_t(Axis.x * s, Axis.y * c, Axis.z * s, c));
		}

		GDINL Vector4t<Float32> GetEulerDegrees() const
		{
			return this->GetEulerRadians() * Float32(180.0f / M_PI);
		}

		GDINL Quaternion_t& SetEulerDegrees(Vector3Fast const& Degrees)
		{
			return this->SetEulerRadians(Degrees * Float32(M_PI / 180.0f));
		}

		GDINL Quaternion_t RotateDegrees(Float32 const Angle, Vector3Fast const& Vector) const
		{
			return this->RotateRadians(Angle * Float32(M_PI / 180.0f), Vector);
		}

	public /* Operators */:
		inline Quaternion_t operator* (Quaternion_t const& Other) const
		{
			using namespace Float32x4Intrinsics;
			VectorRegisterType static const SignMask0 = VectorMake( 1.0f, -1.0f,  1.0f, -1.0f);
			VectorRegisterType static const SignMask1 = VectorMake( 1.0f,  1.0f, -1.0f, -1.0f);
			VectorRegisterType static const SignMask2 = VectorMake(-1.0f,  1.0f,  1.0f, -1.0f);

			VectorRegisterType Result = VectorMul(VectorReplicate(this->ElementsVector, 3), Other.ElementsVector);
			Result = VectorMulAdd(VectorMul(VectorReplicate(this->ElementsVector, 0), VectorSwizzle(Other.ElementsVector, 3, 2, 1, 0)), SignMask0, Result);
			Result = VectorMulAdd(VectorMul(VectorReplicate(this->ElementsVector, 1), VectorSwizzle(Other.ElementsVector, 2, 3, 0, 1)), SignMask1, Result);
			Result = VectorMulAdd(VectorMul(VectorReplicate(this->ElementsVector, 2), VectorSwizzle(Other.ElementsVector, 1, 0, 3, 2)), SignMask2, Result);

			return Quaternion_t(Result);
		}

		inline Vector3Fast operator* (Vector3Fast const& Vector) const
		{
			Vector4t<Float32> const QuatVector(this->x, this->y, this->z, 1.0f);
			Vector4t<Float32> const Temp0 = QuatVector.Cross(Vector) * this->w * 2.0f;
			Vector4t<Float32> const Temp1 = QuatVector.Cross(Temp0) * 2.0f;

			return Vector + Temp0 + Temp1;
		}

		GDINL Quaternion_t operator*= (Quaternion_t const& Other)
		{
			return ((*this) = ((*this) * Other));
		}

		GDINL Quaternion_t operator= (Quaternion_t const& Other)
		{
			this->ElementsVector = Other.ElementsVector;
			return (*this);
		}
	} GD_ALIGN_GCC(16);	// Quaternion_t<Float32>
#endif	// if (defined(GD_HAS_FLOAT32X4INTRINSICS) && (!defined(GD_DOCUMENTATION)))

	typedef Quaternion_t<float> Quaternion;

GD_NAMESPACE_END

#endif