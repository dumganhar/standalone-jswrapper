/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#ifndef AZSTD_UTILS_H
#define AZSTD_UTILS_H 1

#include <type_traits>
#include <utility>

#ifdef AZStd
#define AZStd std
#endif

namespace AZStd
{
     template<class T, bool isEnum = AZStd::is_enum<T>::value>
    struct RemoveEnum
    {
        typedef typename AZStd::underlying_type<T>::type type;
    };

    template<class T>
    struct RemoveEnum<T, false>
    {
        typedef T type;
    };

    template<class T>
    using RemoveEnumT = typename RemoveEnum<T>::type;

    template<class T>
    struct HandleLambdaPointer;

    template<class R, class L, class... Args>
    struct HandleLambdaPointer<R(L::*)(Args...)>
    {
        typedef R(type)(Args...);
    };

    template<class R, class L, class... Args>
    struct HandleLambdaPointer<R(L::*)(Args...) const>
    {
        typedef R(type)(Args...);
    };

    template<class T>
    struct RemoveFunctionConst
    {
        typedef typename HandleLambdaPointer<decltype(&T::operator())>::type type; // lambda matching handling
    };

    template<class R, class... Args>
    struct RemoveFunctionConst<R(Args...)>
    {
        typedef R(type)(Args...);
    };

#if __cpp_noexcept_function_type
    // C++17 makes exception specifications as part of the type in paper P0012R1
    // Therefore noexcept overloads must distinguished from non-noexcept overloads
    template<class R, class... Args>
    struct RemoveFunctionConst<R(Args...) noexcept>
    {
        typedef R(type)(Args...) noexcept;
    };
#endif

    template<class R, class C, class... Args>
    struct RemoveFunctionConst<R(C::*)(Args...)>
    {
        using type = R(C::*)(Args...);
    };

#if __cpp_noexcept_function_type
    // C++17 makes exception specifications as part of the type in paper P0012R1
    // Therefore noexcept overloads must distinguished from non-noexcept overloads
    template<class R, class C, class... Args>
    struct RemoveFunctionConst<R(C::*)(Args...) noexcept>
    {
        using type = R(C::*)(Args...) noexcept;
    };
#endif

    template<class R, class C, class... Args>
    struct RemoveFunctionConst<R(C::*)(Args...) const>
    {
        using type = R(C::*)(Args...);
    };

#if __cpp_noexcept_function_type
    // C++17 makes exception specifications as part of the type in paper P0012R1
    // Therefore noexcept overloads must distinguished from non-noexcept overloads
    template<class R, class C, class... Args>
    struct RemoveFunctionConst<R(C::*)(Args...) const noexcept>
    {
        using type = R(C::*)(Args...) noexcept;
    };
#endif


}

#endif // AZSTD_UTILS_H
#pragma once
