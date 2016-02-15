// ==========================================================================================
// Copyright (C) Goddamn Industries 2015. All Rights Reserved.
// 
// This software or any its part is distributed under terms of Goddamn Industries End User
// License Agreement. By downloading or using this software or any its part you agree with 
// terms of Goddamn Industries End User License Agreement.
// ==========================================================================================

/*!
 * @file GoddamnEngine/Engine/Interface/Graphics/Graphics.h
 * File contains export interface for the engine graphics subsystem.
 */
#pragma once

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Engine/Interface/UniqueInterface.h>
#include <GoddamnEngine/Engine/Interface/Graphics/GraphicsFormat.h>

#include <GoddamnEngine/Core/Math/Geometry.h>
#include <GoddamnEngine/Core/Templates/Singleton.h>
#include <GoddamnEngine/Core/Containers/Vector.h>

GD_NAMESPACE_BEGIN

	enum IGraphicsDriver : UInt8
	{
		IGRAPHICS_DRIVER_MANTLE,
		IGRAPHICS_DRIVER_METAL,
		IGRAPHICS_DRIVER_DIRECTX12,
		IGRAPHICS_DRIVER_VULKAN,
		IGRAPHICS_DRIVER_DIRECTX11,
		IGRAPHICS_DRIVER_OPENGL,
		IGRAPHICS_DRIVER_OPENGLES,
		IGRAPHICS_DRIVER_EMPTY,
		IGRAPHICS_DRIVER_UNKNOWN,
	};	// enum IGraphicsDriver

	enum IGraphicsTopologyType : UInt8
	{
		IGRAPHICS_TOPOLOGY_TYPE_TRAINGLELIST,
		IGRAPHICS_TOPOLOGY_TYPE_UNKNOWN,
	};	// enum IGraphicsTopologyType

	// ==========================================================================================
	// IGraphics interface.
	// ==========================================================================================

	typedef IInterface IGraphicsInterface;
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL_BASE(IGraphics, IRuntimeUniqueInterface);

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Canvas output.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines the list of the supported canvas output modes.
	 */
	enum IGraphicsCanvasMode : UInt8
	{
		IGRAPHICS_OUTPUT_MODE_WINDOWED,
		IGRAPHICS_OUTPUT_MODE_PSEUDO_FULLSCREEN,
		IGRAPHICS_OUTPUT_MODE_FULLSCREEN,
		IGRAPHICS_OUTPUT_MODE_UNKNOWN,
	};	// enum IGraphicsCanvasMode

	/*!
	 * Defines the list of the supported canvas vsync modes.
	 */
	enum IGraphicsCanvasVsyncMode : UInt8
	{
		IGRAPHICS_OUTPUT_VSYNC_DISABLED,
		IGRAPHICS_OUTPUT_VSYNC_30FPS,
		IGRAPHICS_OUTPUT_VSYNC_60FPS,
		IGRAPHICS_OUTPUT_VSYNC_UNKNOWN,
	};	// enum IGraphicsCanvasVsyncMode 

	/*!
	 * Adds canvas output support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithCanvas, IGraphics)
	{
	public:
		
		/*!
		 * Retrieves the mode in which graphics canvas device is running. 
		 */
		GDAPI virtual IGraphicsCanvasMode Canvas_GetMode() const GD_PURE_VIRTUAL;

		/*!
		 * Changes the mode in which the graphics canvas device is running. 
		 *
		 * @param gfxCanvasMode The new canvas mode that would be set.
		 * @param gfxForcelyReapply Do forcedly reapply mode, even if device is running is the same mode.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Canvas_SetMode(IGraphicsCanvasMode const gfxCanvasMode, bool const gfxForcelyReapply = false) GD_PURE_VIRTUAL;

#if 0
		/*!
		 * Returns mode, in which graphics device is performing vertical sync.
		 */
		GDAPI virtual IGraphicsCanvasVsyncMode Canvas_GetVsyncMode() const GD_PURE_VIRTUAL;

		/*!
		 * Changes mode, in which graphics device is performing vertical sync.
		 *
		 * @param gfxVsyncMode The mode in which graphics device is performing vertical sync.
		 * @param gfxForcelyReapply Do forcedly reapply mode, even if vsync is running is the same mode.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Canvas_SetVsyncEnabled(IGraphicsCanvasVsyncMode const gfxVsyncMode, bool const gfxForcelyReapply = false) GD_PURE_VIRTUAL;
#endif	// if 0

		//! @todo Do something with pointer here. It is not very safe.

		/*!
		 * Returns a vector reference with all supported resolution descriptors.
		 */
		GDAPI virtual GeomResolution const* Canvas_GetSupportedResolutions() const GD_PURE_VIRTUAL;
	
		/*!
		 * Returns pointer to the resolution descriptor that is currently set.
		 */
		GDAPI virtual GeomResolution const* Canvas_GetResolution() const GD_PURE_VIRTUAL;

		/*!
		 * Changes resolution in which graphics canvas device is rendering and resize several frame
		 * buffers (those, that have a corresponding flag specified).
		 *
		 * @param gfxResolution Pointer to the resolution descriptor that would be set.
		 * @param gfxForcelyReapply Do forcedly resolution mode, even if device is running is the same resolution.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Canvas_SetResolution(GeomResolution const* const gfxResolution, bool const gfxForcelyReapply = false) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithCanvas

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Command lists.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines an interface for the GPU commands list.
	 */
	uinterface IGraphicsCommandList : public IGraphicsInterface
	{
		//! @todo Implement command lists here.
	};	// uinterface IGraphicsCommandList

	/*!
	 * Adds command lists support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithCommandLists, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU command list with specified parameters.
		 *
		 * @param gfxCommandListPtr Pointer for output.
		 * @param gfxCommandListCreationInfo Pointer to the command list creation information.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_CommandListCreate(IGraphicsCommandList** const gfxCommandListPtr, void const* const gfxCommandListCreationInfo) GD_PURE_VIRTUAL;

		/*!
		 * Clears current render target depth buffer.
		 * @param gfxCommandList Command list into which this command would be written.
		 */
		GDAPI virtual void GfxCmd_RenderTargetClearDepth(IGraphicsCommandList* const gfxCommandList) GD_PURE_VIRTUAL;

		/*!
		 * Clear current render target with a specified color.
		 *
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxClearColor Color that would be used to fill the render target.
		 */
		GDAPI virtual void GfxCmd_RenderTargetClearColor(IGraphicsCommandList* const gfxCommandList, GeomColor const gfxClearColor) GD_PURE_VIRTUAL;

		//! @todo Implement command lists here.

	};	// uinterface IGraphicsBase_WithCommandLists

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Buffers.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines types of supported buffer objects.
	 */
	enum IGraphicsBufferType : UInt8
	{
		IGRAPHICS_BUFFER_TYPE_VERTEX,
		IGRAPHICS_BUFFER_TYPE_INDEX,
		IGRAPHICS_BUFFER_TYPE_UNIFORM,
		IGRAPHICS_BUFFER_TYPE_UNKNOWN,
		IGRAPHICS_BUFFER_TYPES_COUNT,
	};	// enum IGraphicsBufferType

	/*!
	 * Defines the flags for the GPU buffer.
	 */
	//! @{
	enum IGraphicsBufferFlags : UInt8
	{
		IGRAPHICS_BUFFER_FLAGS_NONE          = 0,
		IGRAPHICS_BUFFER_FLAGS_DYNAMIC_READ  = GD_BIT(0),
		IGRAPHICS_BUFFER_FLAGS_DYNAMIC_WRITE = GD_BIT(1),
	};	// enum IGraphicsBufferFlags
	GD_ENUM_DEFINE_FLAG_OPERATORS(IGraphicsBufferFlags);
	//! @}

	/*!
	 * Structure that contains information that is required to create a GPU buffer.
	 */
	struct IGraphicsBufferCreationInfo final
	{
	public:
		IGraphicsBufferType  gfxBufferType;		//!< Type of the buffer: vertex, m_Index, uniform or etc buffer.
		SizeTp               gfxBufferSize;		//!< Size of the buffer in bytes.
		IGraphicsBufferFlags gfxBufferFlags;	//!< Flags of the buffer to create.
	};	// struct BufferCreationInfo

	/*!
	 * GPU buffer interface. Engine's graphics abstraction layer provides no separation for
	 * buffers of different type.
	 */
	uinterface IGraphicsBuffer : public IGraphicsInterface
	{
	public:
		IGraphicsBufferCreationInfo const gfxBufferCreationInfo;

	protected:
		GDINL explicit IGraphicsBuffer(IGraphicsBufferCreationInfo const* const gfxBufferCreationInfo) : gfxBufferCreationInfo(*gfxBufferCreationInfo) {}
	
	public:

		/*!
		 * Maps all GPU's buffer data on the CPU memory.
		 *
		 * @param gfxMappedWOMemory Pointer to the write-only memory Handle.
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Imm_MapForWriting(Handle* const gfxMappedWOMemory) GD_PURE_VIRTUAL;

		/*!
		 * Maps all GPU's buffer data on the CPU memory.
		 *
		 * @param gfxMappedROMemory Pointer to the read-only memory Handle.
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Imm_MapForReading(CHandle* const gfxMappedROMemory) GD_PURE_VIRTUAL;

		/*!
		 * Unmaps the buffer from the CPU memory.
		 * @param gfxBuffer Buffer that would be unmapped.
		 */
		GDAPI virtual void Imm_Unmap() GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBuffer

	/*!
	 * Adds buffers support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithBuffers, IGraphics)
	{
	public:
		
		/*!
		 * Creates a GPU buffer with specified parameters.
		 *
		 * @param gfxBufferPtr Pointer for output.
		 * @param gfxBufferCreationInfo Pointer to the buffer creation information.
		 * @param gfxBufferInitialData Initial data of the buffer. Can be null pointer for en empty buffer.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_BufferCreate(IGraphicsBuffer** const gfxBufferPtr, IGraphicsBufferCreationInfo const* const gfxBufferCreationInfo, CHandle const gfxBufferInitialData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithBuffers

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Vertex array objects.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines the list of supported vertex/shader flow semantics.
	 */
	enum IGraphicsSemanticType : UInt8
	{
		IGRAPHICS_SEMANTIC_POSITION,
		IGRAPHICS_SEMANTIC_NORMAL,
		IGRAPHICS_SEMANTIC_TANGENT,
		IGRAPHICS_SEMANTIC_BINORMAL,
		IGRAPHICS_SEMANTIC_TEXCOORD,
		IGRAPHICS_SEMANTIC_BLENDINDICES,
		IGRAPHICS_SEMANTIC_BLENDWEIGHT,
		IGRAPHICS_SEMANTIC_COLOR,
		IGRAPHICS_SEMANTIC_UNKNOWN,
		IGRAPHICS_SEMANTICS_COUNT
	};	// enum IGraphicsSemanticType

	/*!
	 * Defines a list of the supported vertex slots classes.
	 */
	enum IGraphicsInputSlotClass : UInt8
	{
		IGRAPHICS_INPUT_SLOT_CLASS_PER_VERTEX,
		IGRAPHICS_INPUT_SLOT_CLASS_PER_INSTANCE,
		IGRAPHICS_INPUT_SLOT_CLASS_PER_UNKNOWN,
		IGRAPHICS_INPUT_SLOT_CLASSES_COUNT,
	};	// enum IGraphicsInputSlotClass

	/*!
	 * Helper struct that describes the single slot of the vertex array input data.
	 */
	struct IGraphicsVertexArrayLayoutSlot final
	{
	public:
		IGraphicsFormat         SlotFormat;			//!< Format of the slot data.
		IGraphicsSemanticType   SlotSemantic;		//!< The semantic of the slot.
		Int32					SlotSemanticIndex;	//!< m_Index of the semantic.	
		IGraphicsInputSlotClass SlotClass;			//!< Class of this slot: per vertex or instance, etc.
		UInt32					SlotDataStepRate;	//!< Number of the instances using same per-instance data.
	};	// struct IGraphicsVertexArrayLayoutSlot

	/*!
	 * Layout for the shader input/vertex array data.
	 */
	struct IGraphicsVertexArrayLayout final
	{
	public:
		IGraphicsVertexArrayLayoutSlot const* LayoutSlots;	//!< All slots of our input layout.
		SizeTp                           LayoutSlotsCount;	//!< Number of the slots, used by this layout.
	};	// struct IGraphicsVertexArrayLayout 

	/*!
	 * Structure that contains information that is required to create a GPU vertex array.
	 */
	GD_DSTRUCT(CopyFields)
	struct IGraphicsVertexArrayCreationInfo final
	{
	public:
		IGraphicsVertexArrayLayout const* VertexArrayLayout;		//!< The layout of the current input data.
		IGraphicsBuffer const* const*	  ArrayVertexBuffers;	//!< Vertex buffers list of the current input data.
		IGraphicsBuffer const*	          ArrayIndexBuffer;		//!< Index buffer of the current input data.
	};	// struct IGraphicsVertexArrayCr eationInfo

	/*!
	 * GPU input data interface.
	 */
	uinterface IGraphicsVertexArray : public IGraphicsInterface
	{
	public:
		IGraphicsVertexArrayCreationInfo const gfxVertexArrayCreationInfo;

	protected:
		GDINL explicit IGraphicsVertexArray(IGraphicsVertexArrayCreationInfo const* const gfxVertexArrayCreationInfo) : gfxVertexArrayCreationInfo(*gfxVertexArrayCreationInfo) {}
	
	public:
		// No public interface functions here..
	};	// uinterface IGraphicsVertexArray
	
	/*!
	 * Adds vertex arrays support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithVertexArrays, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU vertex array with specified parameters.
		 *
		 * @param gfxVertexArrayPtr Pointer for output.
		 * @param gfxVertexArrayCreationInfo Pointer to the vertex array creation information.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_VertexArrayCreate(IGraphicsVertexArray** const gfxVertexArrayPtr, IGraphicsVertexArrayCreationInfo const* const gfxVertexArrayCreationInfo) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithVertexArrays

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Sampler state objects.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines the Wrap mode for some dimension of the texture.
	 */
	enum IGraphicsTextureAddressMode : UInt8
	{
		IGRAPHICS_TEXTURE_ADDRESS_MODE_CLAMP_TO_EDGE,
		IGRAPHICS_TEXTURE_ADDRESS_MODE_CLAMP_TO_ZERO,
		IGRAPHICS_TEXTURE_ADDRESS_MODE_REPEAT,
		IGRAPHICS_TEXTURE_ADDRESS_MODE_MIRROR,
		IGRAPHICS_TEXTURE_ADDRESS_MODE_UNKNOWN,
		IGRAPHICS_TEXTURE_ADDRESS_MODES_COUNT,
	};	// enum IGraphicsTextureAddressMode 

	/*!
	 * Defines the minification and magnification filtering modes.
	 */
	enum IGraphicsTextureMinMagFilter : UInt8
	{
		IGRAPHICS_TEXTURE_MINMAG_FILTER_NEAREST,
		IGRAPHICS_TEXTURE_MINMAG_FILTER_LINEAR,
		IGRAPHICS_TEXTURE_MINMAG_FILTER_UNKNOWN,
		IGRAPHICS_TEXTURE_MINMAG_FILTERS_COUNT,
	};	// enum IGraphicsTextureMinMagFilter

	/*!
	 * Structure that contains information that is required to create a GPU sampler state.
	 */
	struct IGraphicsSamplerStateCreationInfo final
	{
	public:
		IGraphicsTextureAddressMode  SamplerAddressModeU /*S*/;	//!< Wrap mode for the U(S) dimension of the texture.
		IGraphicsTextureAddressMode  SamplerAddressModeV /*T*/;	//!< Wrap mode for the V(T) dimension of the texture.
		IGraphicsTextureAddressMode  SamplerAddressModeW /*R*/;	//!< Wrap mode for the W(R) dimension of the texture (for 3D textures).
		IGraphicsTextureMinMagFilter SamplerMinFilter;			//!< Minification filtering.
		IGraphicsTextureMinMagFilter SamplerMagFilter;			//!< Magnification filtering.
		Float32                      SamplerLODMinClamp;		//!< @todo Document this.
		Float32                      SamplerLODMaxClamp;		//!< @todo Document this.
		GeomColor                    SamplerBorderColor;		//!< @todo Document this.
		UInt32	                     SamplerMaxAnisotropy;		//!< Max anisotropy filtering level.
	};	// struct IGraphicsSamplerStateCreationInfo

	/*!
	 * GPU sampler state interface.
	 */
	uinterface IGraphicsSamplerState : public IGraphicsInterface
	{
	public:
		IGraphicsSamplerStateCreationInfo const gfxSamplerStateCreationInfo;

	protected:
		GDINL explicit IGraphicsSamplerState(IGraphicsSamplerStateCreationInfo const* const gfxSamplerStateCreationInfo) : gfxSamplerStateCreationInfo(*gfxSamplerStateCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsSamplerState;

	/*!
	 * Adds sampler states support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithSamplerStates, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU sampler state with specified parameters.
		 *
		 * @param gfxSamplerStatePtr Pointer for output.
		 * @param gfxSamplerStateCreationInfo Pointer to the sampler state creation information.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_SamplerStateCreate(IGraphicsSamplerState** gfxSamplerStatePtr, IGraphicsSamplerStateCreationInfo const* const gfxSamplerStateCreationInfo) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithSamplerStates

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Shader Resources common.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines types of the supported shader resources.
	 */
	enum IGraphicsResourceType : UInt8
	{
		IGRAPHICS_RESOURCE_TYPE_TEXTURE_2D,
		IGRAPHICS_RESOURCE_TYPE_TEXTURE_3D,
		IGRAPHICS_RESOURCE_TYPE_TEXTURE_CUBE,
		IGRAPHICS_RESOURCE_TYPE_UNKNOWN,
		IGRAPHICS_RESOURCE_TYPES_COUNT,
	};	// enum IGraphicsResourceType

	/*!
	 * A GPU shader resource view interface.
	 */
	uinterface IGraphicsShaderResourceView : public IGraphicsInterface
	{
	public:
		// No public interface functions here..
	};	// uinterface IGraphicsShaderResourceView
	
	/*!
	 * A base GPU resource interface.
	 */
	uinterface IGraphicsResource : public IGraphicsInterface
	{
	public:

		/*!
		 * Queries the shader resource for current resource.
		 * @returns Pointer to the shader resource view. Should be released manually.
		 */
		GDAPI virtual IGraphicsShaderResourceView const* CPU_GetShaderResourceView() const GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsResource
	
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 2D Textures.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines flags for the 2D texture.
	 */
	//! @{
	enum IGraphicsTexture2DFlags : UInt8
	{
		IGRAPHICS_TEXTURE_2D_DYNAMIC_READ     = GD_BIT(0),
		IGRAPHICS_TEXTURE_2D_DYNAMIC_WRITE    = GD_BIT(1),
		IGRAPHICS_TEXTURE_2D_GENERATE_MIPMAPS = GD_BIT(2),
	};	// enum IGraphicsTexture2DFlags
	GD_ENUM_DEFINE_FLAG_OPERATORS(IGraphicsTexture2DFlags);
	//! @}

	/*!
	 * Defines the natively compression mode for 2D textures data.
	 */
	enum IGraphicsTexture2DCompressionMode : UInt8
	{
		IGRAPHICS_TEXTURE_2D_COMPRESSION_RAW,
		IGRAPHICS_TEXTURE_2D_COMPRESSION_DXT1,
		IGRAPHICS_TEXTURE_2D_COMPRESSION_DXT3,
		IGRAPHICS_TEXTURE_2D_COMPRESSION_DXT5,
		IGRAPHICS_TEXTURE_2D_COMPRESSION_UNKNOWN,
		IGRAPHICS_TEXTURE_2D_COMPRESSIONS_COUNT,
	};	// enum IGraphicsTexture2DCompressionMode

	/*!
	 * Structure that contains information that is required to create a GPU 2D texture.
	 */
	struct IGraphicsTexture2DCreationInfo final
	{
	public:
		UInt32							  TextureWidth;				//!< Width of the texture data.
		UInt32							  TextureHeight;			//!< Height of the texture data.
		IGraphicsFormat                   TexturePixelFormat;		//!< Pixel format of the texture data.
		IGraphicsTexture2DCompressionMode TextureCompressionMode;	//!< Compression mode of the texture. If value is specified, then pixel format value is ignored.
		UInt32							  TextureMipMapsCount;		//!< Amount of the mipmaps levels of the texture.
		IGraphicsTexture2DFlags			  TextureFlags;
	};	// struct IGraphicsTexture2DCreationInfo
		
	/*!
	 * Structure that contains 2D texture data information.
	 */
	struct IGraphicsTexture2DData final
	{
	public:
		CHandle TextureData; //!< Pointer to the texture data.
	};	// struct IGraphicsTexture2DData

	/*!
	 * GPU 2D texture interface.
	 */
	uinterface IGraphicsTexture2D : public IGraphicsResource
	{
	public:
		IGraphicsTexture2DCreationInfo const gfxTexture2DCreationInfo;

	protected:
		GDINL explicit IGraphicsTexture2D(IGraphicsTexture2DCreationInfo const* const gfxTexture2DCreationInfo) : gfxTexture2DCreationInfo(*gfxTexture2DCreationInfo) {}

	public:

		/*!
		 * Updates data stored inside texture.
		 *
		 * @param gfxTexture2DData New data that would be uploaded to GPU.
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Imm_UpdateData(IGraphicsTexture2DData const* const gfxTexture2DData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsTexture2D
	
	/*!
	 * Adds 2D textures support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithTextures2D, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU 2D texture with specified parameters.
		 *
		 * @param gfxTexture2DPtr Pointer for output.
		 * @param gfxTexture2DCreationInfo Pointer to the 2D texture creation information.
		 * @param gfxTexture2DInitialData Initial data for our texture.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_Texture2DCreate(IGraphicsTexture2D** const gfxTexture2DPtr, IGraphicsTexture2DCreationInfo const* const gfxTexture2DCreationInfo
			, IGraphicsTexture2DData const* const gfxTexture2DInitialData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithTextures2D

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Cube map textures.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Structure that contains information that is required to create a GPU cube texture.
	 */
	typedef IGraphicsTexture2DCreationInfo IGraphicsTextureCubeCreationInfo;

	/*!
	 * Structure that contains cube texture data information.
	 */
	struct IGraphicsTextureCubeData final
	{
	public:
		IGraphicsTexture2DData TexureCubeSides[6];	//!< Creation data for the side of the cube.
	};	// struct IGraphicsTextureCubeData

	/*!
	 * GPU Cube texture interface.
	 */
	uinterface IGraphicsTextureCube : public IGraphicsResource
	{
	public:
		IGraphicsTexture2DCreationInfo const gfxTextureCubeCreationInfo;

	protected:
		GDINL explicit IGraphicsTextureCube(IGraphicsTextureCubeCreationInfo const* const gfxTextureCubeCreationInfo) : gfxTextureCubeCreationInfo(*gfxTextureCubeCreationInfo) {}
	
	public:

		/*!
		 * Updates data stored inside texture.
		 *
		 * @param gfxTextureCubeData New data that would be uploaded to GPU.
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Imm_UpdateData(IGraphicsTextureCubeData const* const gfxTextureCubeData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsTextureCube

	/*!
	 * Adds Cube textures support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithTexturesCube, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU Cube texture with specified parameters.
		 *
		 * @param gfxTextureCubePtr Pointer for output.
		 * @param gfxTextureCubeCreationInfo Pointer to the Cube texture creation information.
		 * @param gfxTextureInitialCubeData Initial data for our texture.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_TextureCubeCreate(IGraphicsTextureCube** const gfxTextureCubePtr, IGraphicsTextureCubeCreationInfo const* const gfxTextureCubeCreationInfo
			, IGraphicsTextureCubeData const* const gfxTextureInitialCubeData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithTextures2D

#if GD_FALSE

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// 3D Textures.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Structure that contains information that is required to create a GPU 3D texture.
	 */
	struct IGraphicsTexture3DCreationInfo final
	{
	public:
		UInt32          TextureWidth;			//!< Width of the texture data.
		UInt32          TextureHeight;			//!< Height of the texture data.
		UInt32          TextureDepth;			//!< Depth of the texture data.
		IGraphicsFormat TexturePixelFormat;		//!< Pixel format of the texture data.
		UInt32          TextureMipMapsCount;	//!< Amount of the mipmaps levels of the texture.
	};	// struct IGraphicsTexture3DCreationInfo

	/*!
	 * Structure that contains 3D texture data information.
	 */
	struct IGraphicsTexture3DData final
	{
	public:
	//	IGraphicsTexture3DCompressionMode TextureCompressionMode;	//!< Compression mode of the texture.
		CHandle                           TextureData;				//!< Pointer to the texture data.
	};	// struct IGraphicsTexture3DData

	/*!
	 * GPU 3D texture interface.
	 */
	uinterface IGraphicsTexture3D : public IGraphicsResource
	{
	public:
		IGraphicsTexture3DCreationInfo const gfxTexture3DCreationInfo;

	protected:
		GDINL explicit IGraphicsTexture3D(IGraphicsTexture3DCreationInfo const* const gfxTexture3DCreationInfo) : gfxTexture3DCreationInfo(*gfxTexture3DCreationInfo) {}

	public:

		/*!
		 * Updates data stored inside texture.
		 *
		 * @param gfxTexture3DData New data that would be uploaded to GPU.
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult Imm_UpdateData(IGraphicsTexture3DData const* const gfxTexture3DData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsTexture3D

	/*!
	 * Adds 3D textures support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithTextures3D, IGraphics)
	{
	public:

		/*!
		 * Creates a GPU 3D texture with specified parameters.
		 *
		 * @param gfxTexture3DPtr Pointer for output.
		 * @param gfxTexture3DCreationInfo Pointer to the 3D texture creation information.
		 * @param gfxTexture3DInitialData Initial data for our texture.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_Texture3DCreate(IGraphicsTexture3D** const gfxTexture3DPtr, IGraphicsTexture3DCreationInfo const* const gfxTexture3DCreationInfo
			, IGraphicsTexture3DData const* const gfxTexture3DInitialData) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithTextures3D

#endif	// if GD_FALSE

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Base shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Defines a list of the supported shader types.
	 */
	enum IGraphicsShaderType : UInt32
	{
		IGRAPHICS_SHADER_TYPE_VERTEX,
		IGRAPHICS_SHADER_TYPE_PIXEL,
		IGRAPHICS_SHADER_TYPE_GEOMETRY,
		IGRAPHICS_SHADER_TYPE_HULL,
		IGRAPHICS_SHADER_TYPE_DOMAIN,
		IGRAPHICS_SHADER_TYPE_COMPUTE,
		IGRAPHICS_SHADER_TYPE_UNKNOWN,
		IGRAPHICS_SHADER_TYPES_COUNT,
	};	// enum IGraphicsShaderType
	
	/*!
	 * Defines the flags for the GPU shader.
	 */
	//! @{
	enum IGraphicsShaderFlags : Int32
	{
		IGRAPHICS_SHADER_FLAGS_DEBUG_COMPILE_FROM_SOURCE = GD_BIT(0),
	};	// enum IGraphicsShaderFlags
	GD_ENUM_DEFINE_FLAG_OPERATORS(IGraphicsShaderFlags)
	//! @}

	/*!
	 * Structure that contains information that is required to create a GPU shader.
	 */
	struct IGraphicsShaderCreationInfo
	{
	public:
		CHandle				 ShaderByteCode;		//!< Pointer to the data of the shader Byte code.
		SizeTp				 ShaderByteCodeLength;	//!< Length of the shader Byte code data in bytes.
		IGraphicsShaderFlags ShaderFlags;			//!< Flags of the shader.
		IGraphicsShaderType  ShaderType;			//!< Shader type. Could be unspecified, internal usage.
	};	// struct IGraphicsShaderCreationInfo

	/*!
	 * GPU shader interface.
	 */
	GD_DINTERFACE()
	uinterface IGraphicsShader : public IGraphicsInterface
	{
	public:
		IGraphicsShaderCreationInfo const gfxShaderCreationInfo;

	protected:
		GDINL explicit IGraphicsShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : gfxShaderCreationInfo(*gfxShaderCreationInfo) {}
	
	public:
		// No public interface functions here..
	};	// uinterface IGraphicsShader

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Vertex shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * GPU Vertex shader interface.
	 */
	uinterface IGraphicsVertexShader : public IGraphicsShader
	{
	protected:
		GDINL explicit IGraphicsVertexShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : IGraphicsShader(gfxShaderCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsVertexShader
	
	/*!
	 * Adds Vertex shaders support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithVertexShaders, IGraphics)
	{
	public:
		
		/*!
		 * Creates a new Vertex GPU shader with specified parameters and specifies the input layout
		 * of the Vertex GPU shader.
		 *
		 * @param gfxVertexShaderPtr Pointer for output.
		 * @param gfxShaderCreationInfo Creation information for the Vertex shader.
		 * @param gfxVertexArrayLayout input layout of the vertex shader input data.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_VertexShaderCreate(IGraphicsVertexShader** const gfxVertexShaderPtr, IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo
			, IGraphicsVertexArrayLayout const* const gfxVertexArrayLayout) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified uniform buffers into Vertex shader input. Layout of the buffers in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxUniformBuffers Pointer to the uniform buffers list.
		 * @param gfxUniformBuffersCount Number of the uniform buffers to bind.
		 */
		GDAPI virtual void GfxCmd_VertexShaderBindUniformBuffers(IGraphicsCommandList* const gfxCommandList, IGraphicsBuffer const* const* const gfxUniformBuffers
			, SizeTp const gfxUniformBuffersCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified resources into Vertex shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxResources Pointer to the resources list.
		 * @param gfxResourcesCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_VertexShaderBindResources(IGraphicsCommandList* const gfxCommandList, IGraphicsShaderResourceView const* const* const gfxResources
			, SizeTp const gfxResourcesCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified samplers into Vertex shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxSamplers Pointer to the samplers list.
		 * @param gfxSamplersCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_VertexShaderBindSamplers(IGraphicsCommandList* const gfxCommandList, IGraphicsSamplerState const* const* const gfxSamplerStates
			, SizeTp const gfxSamplerStatesCount) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithVertexShaders

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Pixel shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * GPU Pixel shader interface.
	 */
	uinterface IGraphicsPixelShader : public IGraphicsShader
	{
	protected:
		GDINL explicit IGraphicsPixelShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : IGraphicsShader(gfxShaderCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsPixelShader
	
	/*!
	 * Adds Pixel shaders support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithPixelShaders, IGraphics)
	{
	public:
		
		/*!
		 * Creates a new Pixel GPU shader with specified parameters and specifies the input layout
		 * of the Pixel GPU shader.
		 *
		 * @param gfxPixelShaderPtr Pointer for output.
		 * @param gfxShaderCreationInfo Creation information for the Pixel shader.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_PixelShaderCreate(IGraphicsPixelShader** const gfxPixelShaderPtr, IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified uniform buffers into Pixel shader input. Layout of the buffers in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxUniformBuffers Pointer to the uniform buffers list.
		 * @param gfxUniformBuffersCount Number of the uniform buffers to bind.
		 */
		GDAPI virtual void GfxCmd_PixelShaderBindUniformBuffers(IGraphicsCommandList* const gfxCommandList, IGraphicsBuffer const* const* const gfxUniformBuffers
			, SizeTp const gfxUniformBuffersCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified resources into Pixel shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxResources Pointer to the resources list.
		 * @param gfxResourcesCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_PixelShaderBindResources(IGraphicsCommandList* const gfxCommandList, IGraphicsShaderResourceView const* const* const gfxResources
			, SizeTp const gfxResourcesCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified samplers into Pixel shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxSamplers Pointer to the samplers list.
		 * @param gfxSamplersCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_PixelShaderBindSamplers(IGraphicsCommandList* const gfxCommandList, IGraphicsSamplerState const* const* const gfxSamplerStates
			, SizeTp const gfxSamplerStatesCount) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithPixelShaders

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Geometry shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * GPU Geometry shader interface.
	 */
	uinterface IGraphicsGeometryShader : public IGraphicsShader
	{
	protected:
		GDINL explicit IGraphicsGeometryShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : IGraphicsShader(gfxShaderCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsGeometryShader
	
	/*!
	 * Adds Geometry shaders support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithGeometryShaders, IGraphics)
	{
	public:
		
		/*!
		 * Creates a new Geometry GPU shader with specified parameters and specifies the input layout
		 * of the Geometry GPU shader.
		 *
		 * @param gfxGeometryShaderPtr Pointer for output.
		 * @param gfxShaderCreationInfo Creation information for the Geometry shader.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_GeometryShaderCreate(IGraphicsGeometryShader** const gfxGeometryShaderPtr, IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified uniform buffers into Geometry shader input. Layout of the buffers in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxUniformBuffers Pointer to the uniform buffers list.
		 * @param gfxUniformBuffersCount Number of the uniform buffers to bind.
		 */
		GDAPI virtual void GfxCmd_GeometryShaderBindUniformBuffers(IGraphicsCommandList* const gfxCommandList, IGraphicsBuffer const* const* const gfxUniformBuffers
			, SizeTp const gfxUniformBuffersCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified resources into Geometry shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxResources Pointer to the resources list.
		 * @param gfxResourcesCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_GeometryShaderBindResources(IGraphicsCommandList* const gfxCommandList, IGraphicsShaderResourceView const* const* const gfxResources
			, SizeTp const gfxResourcesCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified samplers into Geometry shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxSamplers Pointer to the samplers list.
		 * @param gfxSamplersCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_GeometryShaderBindSamplers(IGraphicsCommandList* const gfxCommandList, IGraphicsSamplerState const* const* const gfxSamplerStates
			, SizeTp const gfxSamplerStatesCount) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithGeometryShaders

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Hull shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#if GD_FALSE

	/*!
	 * GPU Hull shader interface.
	 */
	uinterface IGraphicsHullShader : public IGraphicsShader
	{
	protected:
		GDINL explicit IGraphicsHullShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : IGraphicsShader(gfxShaderCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsHullShader
	
	/*!
	 * Adds Hull shaders support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithHullShaders, IGraphics)
	{
	public:
		
		/*!
		 * Creates a new Hull GPU shader with specified parameters and specifies the input layout
		 * of the Hull GPU shader.
		 *
		 * @param gfxHullShaderPtr Pointer for output.
		 * @param gfxShaderCreationInfo Creation information for the Hull shader.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_HullShaderCreate(IGraphicsHullShader** const gfxHullShaderPtr, IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified uniform buffers into Hull shader input. Layout of the buffers in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxUniformBuffers Pointer to the uniform buffers list.
		 * @param gfxUniformBuffersCount Number of the uniform buffers to bind.
		 */
		GDAPI virtual void GfxCmd_HullShaderBindUniformBuffers(IGraphicsCommandList* const gfxCommandList, IGraphicsBuffer const* const* const gfxUniformBuffers
			, SizeTp const gfxUniformBuffersCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified resources into Hull shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxResources Pointer to the resources list.
		 * @param gfxResourcesCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_HullShaderBindResources(IGraphicsCommandList* const gfxCommandList, IGraphicsShaderResourceView const* const* const gfxResources
			, SizeTp const gfxResourcesCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified samplers into Hull shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxSamplers Pointer to the samplers list.
		 * @param gfxSamplersCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_HullShaderBindSamplers(IGraphicsCommandList* const gfxCommandList, IGraphicsSamplerState const* const* const gfxSamplerStates
			, SizeTp const gfxSamplerStatesCount) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithHullShaders

#endif	// if GD_FALSE

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Domain shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#if GD_FALSE

	/*!
	 * GPU Domain shader interface.
	 */
	uinterface IGraphicsDomainShader : public IGraphicsShader
	{
	protected:
		GDINL explicit IGraphicsDomainShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) : IGraphicsShader(gfxShaderCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsDomainShader
	
	/*!
	 * Adds Domain shaders support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithDomainShaders, IGraphics)
	{
	public:
		
		/*!
		 * Creates a new Domain GPU shader with specified parameters and specifies the input layout
		 * of the Domain GPU shader.
		 *
		 * @param gfxDomainShaderPtr Pointer for output.
		 * @param gfxShaderCreationInfo Creation information for the Domain shader.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_DomainShaderCreate(IGraphicsDomainShader** const gfxDomainShaderPtr, IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified uniform buffers into Domain shader input. Layout of the buffers in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxUniformBuffers Pointer to the uniform buffers list.
		 * @param gfxUniformBuffersCount Number of the uniform buffers to bind.
		 */
		GDAPI virtual void GfxCmd_DomainShaderBindUniformBuffers(IGraphicsCommandList* const gfxCommandList, IGraphicsBuffer const* const* const gfxUniformBuffers
			, SizeTp const gfxUniformBuffersCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified resources into Domain shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxResources Pointer to the resources list.
		 * @param gfxResourcesCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_DomainShaderBindResources(IGraphicsCommandList* const gfxCommandList, IGraphicsShaderResourceView const* const* const gfxResources
			, SizeTp const gfxResourcesCount) GD_PURE_VIRTUAL;

		/*!
		 * Binds specified samplers into Domain shader input. Layout of the resources in
		 * shader and in parameters should be preserved.
		 * 
		 * @param gfxCommandList Command list into which this command would be written.
		 * @param gfxSamplers Pointer to the samplers list.
		 * @param gfxSamplersCount Number of the resources to bind.
		 */
		GDAPI virtual void GfxCmd_DomainShaderBindSamplers(IGraphicsCommandList* const gfxCommandList, IGraphicsSamplerState const* const* const gfxSamplerStates
			, SizeTp const gfxSamplerStatesCount) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithDomainShaders

#endif	// if GD_FALSE

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Compute shaders.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#if GD_FALSE

	// ------------------------------------------------------------------------------------------
	//! GPU Compute shader interface.
	GD_DINTERFACE()
	uinterface IGraphicsComputeShader : public IGraphicsShader
	{
		GD_DEFINE_CLASS_INFORMATION(IGraphicsComputeShader, IGraphicsShader);
	protected:
		GD_DCTOR()
		GDINL explicit IGraphicsComputeShader(IGraphicsShaderCreationInfo const* const gfxShaderCreationInfo)
			: IGraphicsShader(gfxShaderCreationInfo) {}
	public:
		// No public interface functions here..
	};	// uinterface IGraphicsComputeShader

	// ------------------------------------------------------------------------------------------
	//! Adds Compute shaders support to the zero IGraphics interface.
	GD_DINTERFACE()
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithComputeShaders, IGraphics)
	{
	public:
		// No public interface functions here..
		//! @todo Provide functionality for compute shaders.
	};	// uinterface IGraphicsBase_WithComputeShaders

#endif	// if GD_FALSE

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Pipeline state object.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * Structure that contains information that is required to create a GPU pipeline.
	 */
	struct IGraphicsPipelineStateCreationInfo
	{
	public:
		IGraphicsVertexShader   const* PipelineVertexShader;	//!< Vertex shader of this pipeline.
		IGraphicsPixelShader    const* PipelinePixelShader;		//!< Pixel shader of this pipeline.
		IGraphicsGeometryShader const* PipelineGeometryShader;	//!< Geometry shader of this pipeline.
#if GD_FALSE
		IGraphicsHullShader     const* PipelineHullShader;		//!< Hull shader of this pipeline.
		IGraphicsDomainShader   const* PipelineDomainShader;	//!< Domain shader of this pipeline.
#endif	// if GD_FALSE
	};	// struct IGraphicsPipelineStateCreationInfo

	/*!
	 * GPU pipeline interface.
	 */
	uinterface IGraphicsPipelineState : public IGraphicsInterface
	{
	public:
		IGraphicsPipelineStateCreationInfo const gfxPipelineStateCreationInfo;

	protected:
		GDINL explicit IGraphicsPipelineState(IGraphicsPipelineStateCreationInfo const* const gfxPipelineStateCreationInfo) : gfxPipelineStateCreationInfo(*gfxPipelineStateCreationInfo) {}

	public:
		// No public interface functions here..
	};	// uinterface IGraphicsPipelineState
	
	/*!
	 * Adds command lists support to the zero IGraphics interface.
	 */
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphicsBase_WithPipelineStates, IGraphics)
	{
	public:

		/*!
		 * Creates a new GPU pipeline with specified parameters.
		 *
		 * @param gfxPipelinePtr Pointer for output.
		 * @param gfxPipelineCreationInfo Creation information for the pipeline.
		 *
		 * @returns Non-negative value if the operation succeeded.
		 */
		GDAPI virtual IResult GfxImm_PipelineCreate(IGraphicsPipelineState** const gfxPipelinePtr, IGraphicsPipelineStateCreationInfo const* const gfxPipelineCreationInfo) GD_PURE_VIRTUAL;

	};	// uinterface IGraphicsBase_WithPipelineStates

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Global interface.
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	/*!
	 * GPU-accelerated graphics interface.
	 */
	GD_DINTERFACE()
	GD_UNIQUE_INTERFACE_DEFINE_PARTIAL(IGraphics, IGraphics), public Singleton<IGraphics>
	{
	protected:
		IGraphicsCanvasMode         m_GfxCanvasMode = IGRAPHICS_OUTPUT_MODE_UNKNOWN;
		IGraphicsCanvasVsyncMode	m_GfxVsyncMode  = IGRAPHICS_OUTPUT_VSYNC_UNKNOWN;
		GeomResolution const*		m_GfxResolutionSelected = nullptr;
		Vector<GeomResolution>		m_GfxResolutionsList;
	};	// uinterface IGraphics

	// ------------------------------------------------------------------------------------------
	//! Global graphics interface pointer.
	GD_DSTATIC_VARIABLE()
	GDAPI extern IUniqueInterfacePointer<IGraphics> Graphics;

GD_NAMESPACE_END

GDINL bool FFF() { return true; }
#define GD_IGRAPHICS_CHECK_ARGS(Operation) FFF() //GD_GLUE(Check_, Operation)

#include <GoddamnEngine/Core/System/Platform.h>
#if GD_PLATFORM_API_LIBSDL1 || GD_PLATFORM_API_LIBSDL2
#	include GD_PLATFORM_API_INCLUDE(GoddamnEngine/Engine/Interface/Graphics, Graphics)
#else // if GD_PLATFORM_API_LIBSDL1 || GD_PLATFORM_API_LIBSDL2
#	include GD_PLATFORM_INCLUDE(GoddamnEngine/Engine/Interface/Graphics, Graphics)
#endif	// if GD_PLATFORM_API_LIBSDL1 || GD_PLATFORM_API_LIBSDL2