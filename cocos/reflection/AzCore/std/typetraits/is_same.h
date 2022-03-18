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
    template <class T, class U>
    constexpr bool is_same_v = is_same<T, U>::value;

    // models the same_as concept
    template <class T, class U>
    /*concept*/ constexpr bool same_as = is_same_v<T, U>;
}
