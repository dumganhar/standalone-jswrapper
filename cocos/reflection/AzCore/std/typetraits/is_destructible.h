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

    template< class T >
    constexpr bool is_destructible_v = is_destructible<T>::value;

    template< class T >
    constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;

    template< class T >
    constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;

    template<class T>
    /*concept*/ constexpr bool destructible = is_nothrow_destructible_v<T>;
}
