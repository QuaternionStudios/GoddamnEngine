// ==========================================================================================
// Copyright (C) Goddamn Industries 2015. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

//! @file GoddamnEngine/Core/Containers/InitializerList.h
//! Initializer list class.
#pragma once

#include <GoddamnEngine/Include.h>
#include <initializer_list>	// for std::initializer_list

GD_NAMESPACE_BEGIN

	//! Workaround of standard initializer list with Goddamn-Like naming conversion.
	//! @todo Possibly write a wrapper m_Container class with Goddamn-Like methods naming.
	template<typename TElement>
	using InitializerList = ::std::initializer_list<TElement>;

#if !GD_DOCUMENTATION
	namespace std { enum { initializer_list }; }
#endif	// if !GD_DOCUMENTATION

GD_NAMESPACE_END
