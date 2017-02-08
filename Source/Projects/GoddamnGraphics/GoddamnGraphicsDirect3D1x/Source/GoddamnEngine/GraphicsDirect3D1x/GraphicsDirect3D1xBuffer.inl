// ==========================================================================================
// Copyright (C) Goddamn Industries 2015. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

#define GD_IGRAPHICS_DIRECT3D1X_IMPL 1

/*!
 * @file GoddamnEngine/Core/System/Graphics/GraphicsDirect3D1x/GraphicsDirect3D1xBuffers.cpp
 * File contains Implementation for Direct3D1x 4.3 Implementation of the graphics interface: buffer objects.
 */
#include <GoddamnEngine/Core/System/Graphics/GraphicsDirect3D1x/GraphicsDirect3D1x.h>
#if GD_PLATFORM_API_MICROSOFT

GD_NAMESPACE_BEGIN

	// ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Buffers.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GD_IMPLEMENT_CLASS_INFORMATION_NOT_CONSTRUCTIBLE(IGraphicsDirect3D1xBuffer);

	// ------------------------------------------------------------------------------------------
	//! Creates a GPU buffer with specified parameters.
	//! @param gfxBufferCreationInfo Pointer to the buffer creation information.
	//! @param gfxBufferInitialData Initial data of the buffer. Can be null pointer for en empty buffer.
	GDAPI IGraphicsDirect3D1xBuffer::IGraphicsDirect3D1xBuffer(IGraphicsBufferCreationInfo const* const gfxBufferCreationInfo, CHandle const gfxBufferInitialData)
		: IGraphicsBuffer(gfxBufferCreationInfo), D3DBuffer(nullptr), D3DBufferMappedMemory(nullptr)
	{
		D3D1x_(BUFFER_DESC) d3dBufferDesc = {};
		d3dBufferDesc.ByteWidth = static_cast<UINT>(gfxBufferCreationInfo->gfxBufferSize);
		d3dBufferDesc.BindFlags = IGraphicsDirect3D1xBufferTypesTable[gfxBufferCreationInfo->gfxBufferType];
		if (gfxBufferCreationInfo->gfxBufferFlags != 0)
		{
			d3dBufferDesc.Usage = D3D1x_(USAGE_IMMUTABLE);
			if ((gfxBufferCreationInfo->gfxBufferFlags & IGRAPHICS_BUFFER_FLAGS_DYNAMIC_READ ) != 0) d3dBufferDesc.CPUAccessFlags |= D3D10_CPU_ACCESS_READ;
			if ((gfxBufferCreationInfo->gfxBufferFlags & IGRAPHICS_BUFFER_FLAGS_DYNAMIC_WRITE) != 0) d3dBufferDesc.CPUAccessFlags |= D3D10_CPU_ACCESS_WRITE;
		}

		D3D1x_(SUBRESOURCE_DATA) d3dBufferSubresource = {}, *d3dBufferSubresourcePtr = nullptr;
		if (gfxBufferInitialData != nullptr)
		{
			d3dBufferSubresourcePtr = &d3dBufferSubresource;
			d3dBufferSubresource.pSysMem = gfxBufferInitialData;
		}

		ThrowIfFailed(GD_IGRAPHICS_DIRECT3D1X->D3DDevice->CreateBuffer(&d3dBufferDesc, d3dBufferSubresourcePtr, &D3DBuffer.p));
	}

	// ------------------------------------------------------------------------------------------
	//! Deletes current GPU buffer.
	GDAPI IGraphicsDirect3D1xBuffer::~IGraphicsDirect3D1xBuffer()
	{
		Imm_Unmap();
		D3DBuffer.Release();
	}

	// ------------------------------------------------------------------------------------------
	//! Maps all GPU's buffer data on the CPU memory.
	//! @param gfxMappedWOMemory Pointer to the write-only memory Handle.
	//! @returns Non-negative value if the operation succeeded.
	GDAPI IResult IGraphicsDirect3D1xBuffer::Imm_MapForWriting(Handle* const gfxMappedWOMemory)
	{
#if GD_DEBUG
		if (!GD_IGRAPHICS_CHECK_ARGS(Imm_MapForWriting(gfxMappedWOMemory)))
			return IResult::InvalidArguments;
#endif	// if GD_DEBUG

		if (D3DBufferMappedMemory == nullptr)
		{
#if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11			
			ThrowIfFailed(GD_IGRAPHICS_DIRECT3D1X->D3DDeviceContext->Map(D3DBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &D3DBufferMappedSubresource));
#else	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
			ThrowIfFailed(D3DBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, const_cast<void**>(&D3DBufferMappedMemory)));
#endif	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
		}
		*gfxMappedWOMemory = D3DBufferMappedMemory;
		return IResult::Ok;
	}

	// ------------------------------------------------------------------------------------------
	//! Maps all GPU's buffer data on the CPU memory.
	//! @param gfxMappedROMemory Pointer to the read-only memory Handle.
	//! @returns Non-negative value if the operation succeeded.
	GDAPI IResult IGraphicsDirect3D1xBuffer::Imm_MapForReading(CHandle* const gfxMappedROMemory)
	{
#if GD_DEBUG
		if (!GD_IGRAPHICS_CHECK_ARGS(Imm_MapForReading(gfxMappedROMemory)))
			return IResult::InvalidArguments;
#endif	// if GD_DEBUG

		if (D3DBufferMappedMemory == nullptr)
		{
#if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11			
			ThrowIfFailed(GD_IGRAPHICS_DIRECT3D1X->D3DDeviceContext->Map(D3DBuffer, 0, D3D11_MAP_READ, 0, &D3DBufferMappedSubresource));
#else	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
			ThrowIfFailed(D3DBuffer->Map(D3D10_MAP_READ, 0, const_cast<void**>(&D3DBufferMappedMemory)));
#endif	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
		}
		*gfxMappedROMemory = D3DBufferMappedMemory;
		return IResult::Ok;
	}

	// ------------------------------------------------------------------------------------------
	//! Unmaps the buffer from the CPU memory.
	//! @param gfxBuffer Buffer that would be unmapped.
	GDAPI void IGraphicsDirect3D1xBuffer::Imm_Unmap()
	{
#if GD_DEBUG
		if (!GD_IGRAPHICS_CHECK_ARGS(Imm_Unmap(gfxBuffer)))
			return;
#endif	// if GD_DEBUG

		if (D3DBufferMappedMemory != nullptr)
		{
#if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11			
			GD_IGRAPHICS_DIRECT3D1X->D3DDeviceContext->Unmap(D3DBuffer, 0);
			D3DBufferMappedSubresource = {};
#else	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
			D3DBuffer->Unmap();
			D3DBufferMappedMemory = nullptr;
#endif	// if GD_IGRAPHICS_DIRECT3D1X_VERSION >= 11
		}
	}

	// ------------------------------------------------------------------------------------------
	//! Creates a GPU buffer with specified parameters.
	//! @param gfxBufferPtr Pointer for output.
	//! @param gfxBufferCreationInfo Pointer to the buffer creation information.
	//! @param gfxBufferInitialData Initial data of the buffer. Can be null pointer for en empty buffer.
	//! @returns Non-negative value if the operation succeeded.
	GDAPI IResult IGraphicsDirect3D1xWithBuffers::GfxImm_BufferCreate(IGraphicsBuffer** const gfxBufferPtr
		, IGraphicsBufferCreationInfo const* const gfxBufferCreationInfo, CHandle const gfxBufferInitialData)
	{
#if GD_DEBUG
		if (!GD_IGRAPHICS_CHECK_ARGS(GfxImm_BufferCreate(gfxBufferPtr, gfxBufferCreationInfo, gfxBufferInitialData)))
			return IResult::InvalidArguments;
#endif	// if GD_DEBUG

		*gfxBufferPtr = GD_NEW(IGraphicsDirect3D1xBuffer, gfxBufferCreationInfo, gfxBufferInitialData);
		return IResult::Ok;
	}

	// ReSharper restore CppNonInlineFunctionDefinitionInHeaderFile

GD_NAMESPACE_END

#endif	// if GD_PLATFORM_API_MICROSOFT