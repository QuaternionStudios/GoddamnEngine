// ==========================================================================================
// Copyright (C) Goddamn Industries 2015. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

/*!
 * @file GoddamnEngine/Core/System/Graphics/GraphicsDirect3D11/GraphicsDirect3D11FormatDXGI.h
 * File contains export interface for Direct3D 11 Implementation of the graphics interface: DXGI format tables.
 */
#pragma once

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Engine/Interface/Graphics/GraphicsFormat.h>

#if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL
#	include <dxgiformat.h>
#endif	// if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL

GD_NAMESPACE_BEGIN

#if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL
	DXGI_FORMAT static const IGraphicsDirect3D11FormatsTableDXGI[IGRAPHICS_FORMATS_COUNT] = {
		// ..Generic formats..
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/* IGRAPHICS_FORMAT_R32G32B32A32_FLOAT */ DXGI_FORMAT_R32G32B32A32_FLOAT,
		/* IGRAPHICS_FORMAT_R32G32B32A32_UINT  */ DXGI_FORMAT_R32G32B32A32_UINT,
		/* IGRAPHICS_FORMAT_R32G32B32A32_SINT  */ DXGI_FORMAT_R32G32B32A32_SINT,
		/* IGRAPHICS_FORMAT_R32G32B32_FLOAT    */ DXGI_FORMAT_R32G32B32_FLOAT,
		/* IGRAPHICS_FORMAT_R32G32B32_UINT     */ DXGI_FORMAT_R32G32B32_FLOAT,
		/* IGRAPHICS_FORMAT_R32G32B32_SINT     */ DXGI_FORMAT_R32G32B32_SINT,
		/* IGRAPHICS_FORMAT_R32G32_FLOAT       */ DXGI_FORMAT_R32G32_FLOAT,
		/* IGRAPHICS_FORMAT_R32G32_UINT        */ DXGI_FORMAT_R32G32_UINT,
		/* IGRAPHICS_FORMAT_R32G32_SINT        */ DXGI_FORMAT_R32G32_SINT,
		/* IGRAPHICS_FORMAT_R32_FLOAT          */ DXGI_FORMAT_R32_FLOAT,
		/* IGRAPHICS_FORMAT_R32_UINT           */ DXGI_FORMAT_R32_UINT,
		/* IGRAPHICS_FORMAT_R32_SINT           */ DXGI_FORMAT_R32_SINT,
	//	/* IGRAPHICS_FORMAT_R16G16B16A16_FLOAT */ DXGI_FORMAT_R16G16B16A16_FLOAT, 
		/* IGRAPHICS_FORMAT_R16G16B16A16_UNORM */ DXGI_FORMAT_R16G16B16A16_UNORM,
		/* IGRAPHICS_FORMAT_R16G16B16A16_NORM  */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16G16B16A16_UINT  */ DXGI_FORMAT_R16G16B16A16_UINT,
		/* IGRAPHICS_FORMAT_R16G16B16A16_SINT  */ DXGI_FORMAT_R16G16B16A16_SINT,
	//	/* IGRAPHICS_FORMAT_R16G16B16_FLOAT    */ DXGI_FORMAT_R16G16B16_FLOAT, 
		/* IGRAPHICS_FORMAT_R16G16B16_UNORM    */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16G16B16_NORM     */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16G16B16_UINT     */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16G16B16_SINT     */ DXGI_FORMAT(0),
	//	/* IGRAPHICS_FORMAT_R16G16_FLOAT       */ DXGI_FORMAT_R16G16_FLOAT, 
		/* IGRAPHICS_FORMAT_R16G16_UNORM       */ DXGI_FORMAT_R16G16_UNORM,
		/* IGRAPHICS_FORMAT_R16G16_NORM        */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16G16_UINT        */ DXGI_FORMAT_R16G16_UINT,
		/* IGRAPHICS_FORMAT_R16G16_SINT        */ DXGI_FORMAT_R16G16_SINT,
	//	/* IGRAPHICS_FORMAT_R16_FLOAT          */ DXGI_FORMAT_R16_FLOAT, 
		/* IGRAPHICS_FORMAT_R16_UNORM          */ DXGI_FORMAT_R16_UNORM,
		/* IGRAPHICS_FORMAT_R16_NORM           */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R16_UINT           */ DXGI_FORMAT_R16_UINT,
		/* IGRAPHICS_FORMAT_R16_SINT           */ DXGI_FORMAT_R16_SINT,
	//	/* IGRAPHICS_FORMAT_R8G8B8A8_FLOAT     */ DXGI_FORMAT_R8G8B8A8_FLOAT, 
		/* IGRAPHICS_FORMAT_R8G8B8A8_UNORM     */ DXGI_FORMAT_R8G8B8A8_UNORM,
		/* IGRAPHICS_FORMAT_R8G8B8A8_NORM      */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8G8B8A8_UINT      */ DXGI_FORMAT_R8G8B8A8_UINT,
		/* IGRAPHICS_FORMAT_R8G8B8A8_SINT      */ DXGI_FORMAT_R8G8B8A8_SINT,
	//	/* IGRAPHICS_FORMAT_R8G8B8_FLOAT       */ DXGI_FORMAT_R8G8B8_FLOAT, 
		/* IGRAPHICS_FORMAT_R8G8B8_UNORM       */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8G8B8_NORM        */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8G8B8_UINT        */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8G8B8_SINT        */ DXGI_FORMAT(0),
	//	/* IGRAPHICS_FORMAT_R8G8_FLOAT         */ DXGI_FORMAT_R8G8_FLOAT, 
		/* IGRAPHICS_FORMAT_R8G8_UNORM         */ DXGI_FORMAT_R8G8_UNORM,
		/* IGRAPHICS_FORMAT_R8G8_NORM          */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8G8_UINT          */ DXGI_FORMAT_R8G8_UINT,
		/* IGRAPHICS_FORMAT_R8G8_SINT          */ DXGI_FORMAT_R8G8_SINT,
	//	/* IGRAPHICS_FORMAT_R8_FLOAT           */ DXGI_FORMAT_R8_FLOAT,
		/* IGRAPHICS_FORMAT_R8_UNORM           */ DXGI_FORMAT_R8_UNORM,
		/* IGRAPHICS_FORMAT_R8_NORM            */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_R8_UINT            */ DXGI_FORMAT_R8_UINT,
		/* IGRAPHICS_FORMAT_R8_SINT            */ DXGI_FORMAT_R8_SINT,

		// ..Depth formats..
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/* IGRAPHICS_FORMAT_DEPTH32_FLOAT      */ DXGI_FORMAT_D32_FLOAT, 
		/* IGRAPHICS_FORMAT_DEPTH32_UINT       */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_DEPTH32_INT        */ DXGI_FORMAT(0),
	//	/* IGRAPHICS_FORMAT_DEPTH16_FLOAT      */ DXGI_FORMAT(0), 
		/* IGRAPHICS_FORMAT_DEPTH16_UINT       */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_DEPTH16_INT        */ DXGI_FORMAT(0),
	//	/* IGRAPHICS_FORMAT_DEPTH8_FLOAT       */ DXGI_FORMAT_D8_FLOAT, 
		/* IGRAPHICS_FORMAT_DEPTH8_UINT        */ DXGI_FORMAT(0),
		/* IGRAPHICS_FORMAT_DEPTH8_INT         */ DXGI_FORMAT(0),

		// ..Additional invalid format..
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		/* IGRAPHICS_FORMAT_UNKNOWN            */ DXGI_FORMAT(0),
	};
#endif	// if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL

#if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL
	// ------------------------------------------------------------------------------------------
	//! Returns the DXGI format that this format value represents.
	//! @param gfxFormat the format value to process.
	//! @returns The DXGI format that this format value represents.
	GDINL static DXGI_FORMAT IGraphicsDirect3D11FormatConvertDXGI(IGraphicsFormat const gfxFormat)
	{
		return IGraphicsDirect3D11FormatsTableDXGI[IGraphicsFormatGetIndex(gfxFormat)];
	}
#endif	// if GD_IGRAPHICS_DIRECT3D1X_IMPL || GD_IGRAPHICS_DIRECT3D12_IMPL || GD_IGRAPHICS2D_DIRECT2D_IMPL

GD_NAMESPACE_END