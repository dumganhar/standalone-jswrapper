/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/std/typetraits/integral_constant.h>

namespace AZStd
{

template<class B>
struct negation : bool_constant<!bool(B::value)> { };

template<class B>
constexpr bool negation_v = negation<B>::value;
}