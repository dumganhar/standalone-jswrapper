cmake_minimum_required(VERSION 3.8)

project(reflection CXX)

set(module_name ccreflection)

set(reflection_source)


list(APPEND reflection_source
    test_main.h
    test_main.cpp
    AzCore/StringFunc/StringFunc.h
    AzCore/StringFunc/StringFunc.cpp

    AzCore/Memory/Memory.h
    AzCore/PlatformDef.h
    AzCore/PlatformRestrictedFileDef.h
    AzCore/PlatformIncl.h
    AzCore/std/utils.h
    AzCore/std/typetraits/is_class.h
    AzCore/std/typetraits/function_traits.h
    AzCore/std/typetraits/is_member_function_pointer.h
    AzCore/std/typetraits/remove_cvref.h
    AzCore/std/typetraits/is_unsigned.h
    AzCore/std/typetraits/is_member_pointer.h
    AzCore/std/typetraits/is_array.h
    AzCore/std/typetraits/is_object.h
    AzCore/std/typetraits/is_base_of.h

    AzCore/std/typetraits/is_member_object_pointer.h
    AzCore/std/typetraits/is_same.h
    AzCore/std/typetraits/is_convertible.h
    AzCore/std/typetraits/typetraits.h
    AzCore/std/typetraits/config.h
    AzCore/std/typetraits/disjunction.h
    AzCore/std/typetraits/is_union.h
    AzCore/std/typetraits/is_reference.h
    AzCore/std/typetraits/invoke_traits.h
    AzCore/std/typetraits/is_const.h
    AzCore/std/typetraits/void_t.h
    AzCore/std/typetraits/is_swappable.h
    AzCore/std/typetraits/negation.h
    AzCore/std/typetraits/internal/type_sequence_traits.h
    AzCore/std/typetraits/is_signed.h
    AzCore/std/typetraits/is_abstract.h
    AzCore/std/typetraits/is_assignable.h
    AzCore/std/typetraits/is_volatile.h
    AzCore/std/typetraits/is_fundamental.h
    AzCore/std/typetraits/is_lvalue_reference.h
    AzCore/std/typetraits/is_destructible.h
    AzCore/std/typetraits/is_void.h
    AzCore/std/typetraits/is_enum.h
    AzCore/std/typetraits/is_trivially_copyable.h
    AzCore/std/typetraits/is_trivial.h
    AzCore/std/typetraits/is_function.h
    AzCore/std/typetraits/is_rvalue_reference.h
    AzCore/std/typetraits/is_arithmetic.h
    AzCore/std/typetraits/has_member_function.h
    AzCore/std/typetraits/is_empty.h
    AzCore/std/typetraits/is_polymorphic.h
    AzCore/std/typetraits/is_floating_point.h
    AzCore/std/typetraits/is_scalar.h
    AzCore/std/typetraits/is_pointer.h
    AzCore/std/typetraits/is_integral.h
    AzCore/std/typetraits/is_pod.h
    AzCore/std/typetraits/conjunction.h
    AzCore/std/typetraits/is_constructible.h
    AzCore/std/typetraits/integral_constant.h
    AzCore/std/typetraits/is_compound.h

    AzCore/std/config.h
    AzCore/std/smart_ptr/scoped_ptr.h
    AzCore/std/smart_ptr/intrusive_ptr.h

    AzCore/std/smart_ptr/shared_array.h
    AzCore/std/smart_ptr/intrusive_refcount.h
    AzCore/std/smart_ptr/checked_delete.h
    AzCore/std/smart_ptr/intrusive_base.h
    AzCore/std/smart_ptr/sp_convertible.h
    AzCore/std/smart_ptr/scoped_array.h
    AzCore/std/smart_ptr/shared_count.h

    AzCore/std/function/invoke.h
    AzCore/std/allocator_static.h
    AzCore/std/createdestroy.h
    AzCore/std/reference_wrapper.h
    AzCore/std/string/conversions.h
    AzCore/std/string/tokenize.h
    AzCore/std/string/string.cpp
    AzCore/std/string/string.h
    AzCore/std/hash.h
    AzCore/std/base.h
    AzCore/Outcome/Outcome.h
    AzCore/Outcome/Internal/OutcomeStorage.h
    AzCore/Outcome/Internal/OutcomeImpl.h
    AzCore/Math/Crc.cpp

    AzCore/Math/Uuid.h
    AzCore/Math/Crc.h
    AzCore/Math/Guid.h
    AzCore/Math/DocsMath.h
    AzCore/Math/Uuid.cpp
    AzCore/Math/Crc.inl
    AzCore/Math/Sha1.h
    AzCore/Math/MathUtils.cpp
    AzCore/Math/Random.h
    AzCore/Math/MathUtils.h

    AzCore/Script/ScriptContextAttributes.h
    AzCore/RTTI/BehaviorContextAttributes.inl
    AzCore/RTTI/RTTI.h
    AzCore/RTTI/AttributeReader.h
    AzCore/RTTI/AzStdOnDemandReflectionSpecializations.cpp
    AzCore/RTTI/BehaviorContext.h
    AzCore/RTTI/BehaviorContextUtilities.cpp
    AzCore/RTTI/BehaviorContext.cpp
    AzCore/RTTI/TypeInfoSimple.h
    AzCore/RTTI/AzStdOnDemandReflection.inl
    AzCore/RTTI/AzStdOnDemandPrettyName.inl
    AzCore/RTTI/ReflectionManager.h
    AzCore/RTTI/ReflectContext.h
    AzCore/RTTI/BehaviorInterfaceProxy.h
    AzCore/RTTI/BehaviorContextUtilities.h
    AzCore/RTTI/ReflectContext.cpp
    AzCore/RTTI/TypeInfo.h
    AzCore/RTTI/ReflectionManager.cpp
    AzCore/RTTI/TypeSafeIntegral.h
    AzCore/Casting/lossy_cast.h
    AzCore/Casting/numeric_cast_internal.h
    AzCore/Casting/numeric_cast.h
    AzCore/Debug/MemoryProfiler.h

    AzCore/Debug/Trace.cpp
    AzCore/Debug/Trace.h
    AzCore/Debug/Profiler.h
    AzCore/base.h
    AzCore/variadic.h
)

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} PREFIX "Source Files" FILES ${reflection_source})

add_library(${module_name} ${reflection_source})

target_include_directories(${module_name} SYSTEM PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

