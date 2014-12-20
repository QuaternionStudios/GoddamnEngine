/// ==========================================================================================
/// RefPtr.h - unique reference-contable pointer interface/implementation.
/// Copyright (C) $(GODDAMN_DEV) 2011 - Present. All Rights Reserved.
/// 
/// History:
///		* 13.05.2014 - Created by James Jhuighuy
/// ==========================================================================================

#pragma once
#ifndef GD_CORE_CONTAINERS_REF_PTR
#define GD_CORE_CONTAINERS_REF_PTR

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Core/Object/Object.h>

GD_NAMESPACE_BEGIN

	/// Provides automatic reference counting on object-derived objects.
	template<typename ObjectType>
	class RefPtr final
	{
	private /* Class members */:
		ObjectType* Pointer;

	public /* Constructors / Destructors. */:
		/// Initializes smart pointer with existing object.
		/// Reference counter is not incremented.
		GDINL RefPtr(ObjectType* const Pointer = nullptr)
			: Pointer(Pointer)
		{
			SafeObtain(this->Pointer);
		}

		/// Initializes smart pointer with other pointer.
		/// Reference counter is incremented.
		GDINL RefPtr(RefPtr const& Other)
			: Pointer(Other.Pointer)
		{
			SafeObtain(this->Pointer);
		}

		/// Moves other smart pointer to this new object.
		/// Reference counter is not incremented.
		GDINL RefPtr(RefPtr&& Other)
			: Pointer(Other.Pointer)
		{
			Other.Pointer = nullptr;
		}

		GDINL ~RefPtr()
		{
			SafeRelease(this->Pointer);
		}

	public /*Class API*/:
		/// Returns native pointer stored in this object.
		GDINL ObjectType* GetPointer() const
		{
			return this->Pointer;
		}

		/// Releases ownership on this pointer, by returning it`s value and replacing it with nullptr.
		GDINL ObjectType* Release()
		{
			ObjectType* Pointer = this->Pointer;
			this->Pointer = nullptr;
			return Pointer;
		}

	public /*Operators*/:
		GDINL ObjectType& operator*  () const { return  (*this->GetPointer()); }
		GDINL ObjectType* operator-> () const { return  ( this->GetPointer()); }

		GDINL bool operator== (       ObjectType  const* const OtherPointer) const { return (this->GetPointer() == OtherPointer); }
		GDINL bool operator== (RefPtr<ObjectType> const&       OtherPointer) const { return (this->GetPointer() == OtherPointer.GetPointer()); }

		GDINL bool operator!= (       ObjectType  const* const OtherPointer) const { return !(*this == OtherPointer); }
		GDINL bool operator!= (RefPtr<ObjectType> const&       OtherPointer) const { return !(*this == OtherPointer); }

		GDINL RefPtr& operator= (RefPtr&& Other)
		{
			if ((&Other) != this)
			{
				SafeRelease(this->Pointer);
				this->Pointer = Other.Pointer;
				Other.Pointer = nullptr;
			}

			return (*this);
		}

		GDINL RefPtr& operator= (RefPtr const& Other)
		{
			if ((&Other) != this)
			{
				SafeRelease(this->Pointer);
				SafeObtain(this->Pointer = Other.Pointer);
			}

			return (*this);
		}

		GDINL RefPtr& operator= (ObjectType* const Other)
		{
			if (this->Pointer != Other)
			{
				SafeRelease(this->Pointer);
				SafeObtain(this->Pointer = Other);
			}

			return (*this);
		}

		template<typename OtherObjectType>
		GDINL explicit operator RefPtr<OtherObjectType>() const
		{
			SafeObtain(this->Pointer);
			return object_cast<OtherObjectType*>(this->GetPointer());
		}

		GDINL operator RefPtr<ObjectType const>() const
		{
			SafeObtain(this->Pointer);
			return static_cast<ObjectType const*>(this->GetPointer());
		}

	private:
		GDINL friend void Swap(RefPtr& First, RefPtr& Second)
		{	using GD Swap;
			Swap(First.Pointer, Second.Pointer);
		}
	};	// class RefPtr

#if (!defined(GD_DOCUMENTATION))
	template<typename ObjectType, typename ThisObjectType>
	auto IterateChildObjects(RefPtr<ThisObjectType> const& TheObject) -> decltype(IterateChildObjects<ObjectType>(TheObject.GetPointer()))
	{	// Returning object wrapped with iteration adapter.
		return IterateChildObjects<ObjectType>(TheObject.GetPointer());
	}
#endif	// if (!defined(GD_DOCUMENTATION))

GD_NAMESPACE_END

#endif