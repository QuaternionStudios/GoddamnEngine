/// ==========================================================================================
/// Assembly.h: Common interface for assembly definition.
/// Copyright (C) Goddamn Industries 2011 - Present. All Rights Reserved.
/// 
/// History:
///		* 07.04.2014 - Created by James Jhuighuy
/// ==========================================================================================

#pragma once
#ifndef GD_CORE_REFLECTION_ASSEMBLY
#define GD_CORE_REFLECTION_ASSEMBLY

#include <GoddamnEngine/Include.h>
#include <GoddamnEngine/Core/Containers/String.h>
#include <GoddamnEngine/Core/Containers/Vector.h>

GD_NAMESPACE_BEGIN

	class IClassInfo;
	class AssemblyManifest final
	{};

	/// Representation of compiled separately block of code, either executable or dynamically linked library.
	class Assembly final
	{
	private:
		GD_CLASS_UNASSIGNABLE(Assembly);
		GD_CLASS_UNCOPIABLE(Assembly);

		Vector<IClassInfo const*> DefinedTypes;
		AssemblyManifest const* (*ManifestGetterPtr)() = nullptr;
		void (*ReflectionInitializationProcPtr)() = nullptr;

		handle NativePointer;
		String Path;

	public:
		/// Returns assembly that contains this class
		GDAPI static Assembly const* GetCurrentAssembly();

		/// Returns assembly that is currently executing
		GDAPI static Assembly const* GetExecutingAssembly();

		/// Loads assembly from path
		GDAPI static Assembly const* LoadAssemblyFromPath(String const& Path) { return new Assembly(Path); }

		GDAPI Assembly(String const& FileName);
		GDAPI virtual ~Assembly();

	public:
		/// Returns true if Assembly was successfully loaded
		GDINL bool WasSuccessfullyLoaded() const { return (this->NativePointer != nullptr); }
		
		/// Returns true if this assembly is executable
		GDAPI bool IsExecutableAssembly() const;

		/// Returns true if this assembly is library
		GDAPI bool IsLibraryAssembly() const;

		/// Returns true if this assembly is linked to system dynamically
		GDAPI bool IsLinkedDynamically() const;

		/// Returns collection of types that are defined in this assembly
		GDAPI Vector<IClassInfo const*> const& GetTypes() const;

		/// Returns pointer of native method that is located in this assembly or nullptr if it was not found
		GDAPI chandle GetNativeMethod(String const& MethodName) const;
	};	// class Assembly 

GD_NAMESPACE_END

#endif