/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/std/typetraits/config.h>

namespace AZStd
{
    template< class T, class... Args >
    constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

    template< class T, class... Args >
    constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

    template< class T, class... Args >
    constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;


    template< class T >
    constexpr bool is_default_constructible_v = is_default_constructible<T>::value;

    template< class T >
    constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;

    template< class T >
    constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;

    template< class T >
    constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;

    template< class T >
    constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;

    template< class T >
    constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;

    template< class T >
    constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

    template< class T >
    constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;

    template< class T >
    constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;
}
