// ==========================================================================================
// Copyright (C) Goddamn Industries 2016. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

/*! 
 * @file GoddamnEngine/Core/System/Threading/CriticalSection.h
 * File contains generic critical section implementation.
 */
#pragma once
#define GD_INSIDE_CRITICALSECTION_H

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Core/System/Platform.h>

GD_NAMESPACE_BEGIN

	// **~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**
	//! Generic critical section class.
	// **~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**
	struct CriticalSectionGeneric : public TNonCopyable
	{
	public:

		/*!
		 * Locks the Critical Section.
		 */
		// ReSharper disable once CppMemberFunctionMayBeStatic
		GDINL void Enter() const
		{
		}

		/*!
		 * Unlocks the Critical Section.
		 */ 
		 // ReSharper disable once CppMemberFunctionMayBeStatic
		GDINL void Leave() const
		{
		}

	};	// struct CriticalSectionGeneric

GD_NAMESPACE_END

#include GD_PLATFORM_API_INCLUDE(GoddamnEngine/Core/System/Threading, CriticalSection)
#undef GD_INSIDE_ATOMICS_H

GD_NAMESPACE_BEGIN

	// **~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**
	//! RAII object that locks specified object.
	// **~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~**
	struct ScopedCriticalSection final : TNonCopyable
	{
	private:
		CriticalSection const& m_CriticalSection;

	public:

		/*!
		 * Initializes scoped lock and locks sync object.
		 * @param criticalSection Object which would be locked.
		 */
		GDINL explicit ScopedCriticalSection(CriticalSection const& criticalSection)
			: m_CriticalSection(criticalSection)
		{
			m_CriticalSection.Enter();
		}

		/*!
		 * Deinitializes scoped lock and unlocks sync object.
		 */
		GDINL ~ScopedCriticalSection()
		{
			m_CriticalSection.Leave();
		}

	};	// struct ScopedCriticalSection

GD_NAMESPACE_END
