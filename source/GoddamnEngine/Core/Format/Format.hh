#ifndef GD_CORE_FORMAT_FORMAT
#define GD_CORE_FORMAT_FORMAT

#include <GoddamnEngine/Include.hh>

#define GD_FORMAT_TYPE_MASK					((Format)0xFF00)
#define GD_FORMAT_TYPE_EXTRACT(format)		((FormatType)((format & GD_FORMAT_TYPE_MASK) >> 8))
#define GD_FORMAT_TYPE_PACK(Type)			((UInt64)(((UInt64)Type << 8) & GD_FORMAT_TYPE_MASK)) 

#define GD_FORMAT_SIZE_UNKNOWN				(Format(0 ))
#define GD_FORMAT_SIZE_8BITS				(Format(8 ))
#define GD_FORMAT_SIZE_16BITS				(Format(16))
#define GD_FORMAT_SIZE_32BITS				(Format(32))
#define GD_FORMAT_SIZE_64BITS				(Format(64))
#if   (defined(GD_PLATFORM_64BIT))
#	define GD_FORMAT_SIZE_CURRENT			GD_FORMAT_SIZE_64BITS
#elif (defined(GD_PLATFORM_32BIT))
#	define GD_FORMAT_SIZE_CURRENT			GD_FORMAT_SIZE_32BITS
#endif
#define GD_FORMAT_SIZE_MAX					((Format)8)
#define GD_FORMAT_SIZE_MASK					((Format)0x00F0)
#define GD_FORMAT_SIZE_EXTRACT(format)		((Format)((((format & GD_FORMAT_SIZE_MASK) >> 4) + 1) * 4))
#define GD_FORMAT_SIZE_PACK(Size)			((UInt64)(((((UInt64)Size / 4) - 1) << 4) & GD_FORMAT_SIZE_MASK)) 

#define GD_FORMAT_COUNT_MAX					((Format)4)
#define GD_FORMAT_COUNT_MASK				((Format)0x000F)
#define GD_FORMAT_COUNT_EXTRACT(format)		((Format)((format & GD_FORMAT_COUNT_MASK) >> 0))
#define GD_FORMAT_COUNT_PACK(Count)			((UInt64)(((UInt64)Count << 0) & GD_FORMAT_COUNT_MASK)) 

#define GD_FORMAT_MAKE(Type, Size, Count)	(Format(GD_FORMAT_TYPE_PACK(Type) | GD_FORMAT_SIZE_PACK(Size) | GD_FORMAT_COUNT_PACK(Count)))
#define GD_FORMAT_SIZEOF(Format)			((GD_FORMAT_SIZE_EXTRACT(Format) * GD_FORMAT_COUNT_EXTRACT(Format)) / 8)

#define FormatEnumeration Format

GD_NAMESPACE_BEGIN

	/// ==========================================================================================
	/// ==========================================================================================
	/// Enumeration describing base type of some scalar variable
	///	E.g: 'GD_FORMAT_R64G64_SINT' format type is 'GD_FORMAT_TYPE_SINT' 
	enum FormatType : UInt8
	{
		GD_FORMAT_TYPE_UINT = 1,	///< Unsigned integer value
		GD_FORMAT_TYPE_SINT,		///< Signed integer value
		GD_FORMAT_TYPE_FLOAT,		///< Floating-point value
		GD_FORMAT_TYPE_STRING,		///< String value
		GD_FORMAT_TYPE_OBJECT,		///< Object pointer
		GD_FORMAT_TYPE_HRI_TEXTURE,		///< Texture pointer
		GD_FORMAT_TYPE_UNKNOWN		///< Unknown 
	};

	struct FormatDesc final
	{
		FormatType DescFormatType;
		unsigned   DescElementSize  : 4;
		unsigned   DescElementCount : 2;
		unsigned   DescSeed			: 2;
	};

	/// ==========================================================================================
	/// ==========================================================================================
	/// Enumeration describing type of vertex semantic
	/// Common structure is:
	/// +--------------- 8 bits ---------------+---------- 4 bits --------+--------- 4 bits -------+
	/// | Type of this format: int, float, ... | (element's bits - 1) / 4 |   number of elements   |
	/// +---------------------------------------- 16 bits -----------------------------------------|
	/// 8 Bits - Seed,
	/// 8 bits - Type of this format
	/// 8 bits - Size of element in bytes
	/// 8 Bits - Number of elements
	/// @note For string and object types bits count of element is 0, such as number of elements
	enum Format : UInt64
	{
		GD_FORMAT_R8_UINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_8BITS,  1),
		GD_FORMAT_R16_UINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_16BITS, 1),
		GD_FORMAT_R32_UINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_32BITS, 1),
		GD_FORMAT_R64_UINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_64BITS, 1),

		GD_FORMAT_R8G8_UINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_8BITS,  2),
		GD_FORMAT_R16G16_UINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_16BITS, 2),
		GD_FORMAT_R32G32_UINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_32BITS, 2),
		GD_FORMAT_R64G64_UINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_64BITS, 2),

		GD_FORMAT_R8G8B8_UINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_8BITS,  3),
		GD_FORMAT_R16G16B16_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_16BITS, 3),
		GD_FORMAT_R32G32B32_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_32BITS, 3),
		GD_FORMAT_R64G64B64_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_64BITS, 3),

		GD_FORMAT_R8G8B8A8_UINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_8BITS,  4),
		GD_FORMAT_R16G16B16A16_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_16BITS, 4),
		GD_FORMAT_R32G32B32A32_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_32BITS, 4),
		GD_FORMAT_R64G64B64A64_UINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_UINT,  GD_FORMAT_SIZE_64BITS, 4),

		GD_FORMAT_R8_SINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_8BITS,  1),
		GD_FORMAT_R16_SINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_16BITS, 1),
		GD_FORMAT_R32_SINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_32BITS, 1),
		GD_FORMAT_R64_SINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_64BITS, 1),

		GD_FORMAT_R8G8_SINT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_8BITS,  2),
		GD_FORMAT_R16G16_SINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_16BITS, 2),
		GD_FORMAT_R32G32_SINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_32BITS, 2),
		GD_FORMAT_R64G64_SINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_64BITS, 2),

		GD_FORMAT_R8G8B8_SINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_8BITS,  3),
		GD_FORMAT_R16G16B16_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_16BITS, 3),
		GD_FORMAT_R32G32B32_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_32BITS, 3),
		GD_FORMAT_R64G64B64_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_64BITS, 3),

		GD_FORMAT_R8G8B8A8_SINT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_8BITS,  4),
		GD_FORMAT_R16G16B16A16_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_16BITS, 4),
		GD_FORMAT_R32G32B32A32_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_32BITS, 4),
		GD_FORMAT_R64G64B64A64_SINT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_SINT,  GD_FORMAT_SIZE_64BITS, 4),

		GD_FORMAT_R8_FLOAT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_8BITS,  1),
		GD_FORMAT_R16_FLOAT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_16BITS, 1),
		GD_FORMAT_R32_FLOAT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_32BITS, 1),
		GD_FORMAT_R64_FLOAT			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_64BITS, 1),

		GD_FORMAT_R8G8_FLOAT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_8BITS,  2),
		GD_FORMAT_R16G16_FLOAT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_16BITS, 2),
		GD_FORMAT_R32G32_FLOAT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_32BITS, 2),
		GD_FORMAT_R64G64_FLOAT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_64BITS, 2),

		GD_FORMAT_R8G8B8_FLOAT		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_8BITS,  3),
		GD_FORMAT_R16G16B16_FLOAT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_16BITS, 3),
		GD_FORMAT_R32G32B32_FLOAT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_32BITS, 3),
		GD_FORMAT_R64G64B64_FLOAT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_64BITS, 3),

		GD_FORMAT_R8G8B8A8_FLOAT	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_8BITS,  4),
		GD_FORMAT_R16G16B16A16_FLOAT = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_16BITS, 4),
		GD_FORMAT_R32G32B32A32_FLOAT = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_32BITS, 4),
		GD_FORMAT_R64G64B64A64_FLOAT = GD_FORMAT_MAKE(GD_FORMAT_TYPE_FLOAT, GD_FORMAT_SIZE_64BITS, 4),

		GD_FORMAT_STRING			 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_STRING, 0, 0),
		GD_FORMAT_OBJECT_POINTER	 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_OBJECT, GD_FORMAT_SIZE_CURRENT, 1),

		GD_FORMAT_HRI_TEXTURE2D		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_HRI_TEXTURE, GD_FORMAT_SIZE_CURRENT, 1),
		GD_FORMAT_HRI_TEXTURE3D		 = GD_FORMAT_MAKE(GD_FORMAT_TYPE_HRI_TEXTURE, GD_FORMAT_SIZE_CURRENT, 1),

		GD_FORMAT_UNKNOWN			 = (0xFFFF)
	};

GD_NAMESPACE_END

#endif
