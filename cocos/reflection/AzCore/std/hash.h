/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#ifndef AZSTD_HASH_H
#define AZSTD_HASH_H 1

#include <limits>
#include <type_traits>

#include "typetraits/has_member_function.h"

namespace AZStd
{

/// define your own struct AZStd::hash<T> and HasherInvocable<T>::type will be AZStd::true_type
AZ_HAS_STATIC_MEMBER(DefaultHash, OnlyUnspecializedTypesShouldHaveThis, bool, ());

template<class T, bool isConstructible = AZStd::is_constructible<T>::value && !AZStd::is_abstract<T>::value>
struct IsNumber
{
    static constexpr bool value = false;
};

template <typename T>
struct IsNumber<T, true>
{
    static constexpr bool value = std::numeric_limits<T>::is_specialized;
};

template<typename KeyType>
using HasherInvocable = AZStd::conjunction
    < AZStd::disjunction<AZStd::negation<HasDefaultHash<hash<KeyType>>>, IsNumber<KeyType>, AZStd::is_enum<KeyType>>
    , AZStd::is_default_constructible<hash<KeyType>>
    , AZStd::is_invocable_r<size_t, hash<KeyType>, const KeyType&>>;

template<typename KeyType>
inline constexpr bool HasherInvocable_v = HasherInvocable<KeyType>::value;

    template <class T>
    constexpr void hash_combine(AZStd::size_t& seed, T const& v)
    {
        hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    template <class T1, class T2, class... RestTypes>
    constexpr void hash_combine(AZStd::size_t& seed, const T1& firstElement, const T2& secondElement, const RestTypes&... restElements)
    {
        hash_combine(seed, firstElement);
        hash_combine(seed, secondElement, restElements...);
    }
}

#endif // AZSTD_HASH_H
#pragma once
