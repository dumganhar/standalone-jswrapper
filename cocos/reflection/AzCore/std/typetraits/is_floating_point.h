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
    constexpr bool is_floating_point_v = is_floating_point<T>::value;

    template<class T>
    /*concept*/ constexpr bool floating_point = is_floating_point_v<T>;
}
