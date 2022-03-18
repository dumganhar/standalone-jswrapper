/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <string>
#include <AzCore/PlatformDef.h>
#include <type_traits>

#ifndef AZStd
#define AZStd std
#endif


namespace AZStd {


string format_string(const char* formatStr, ...);

template <typename char_type>
static constexpr bool eq(char_type left, char_type right) noexcept { return left == right; }

template <typename char_type>
static constexpr bool lt(char_type left, char_type right) noexcept { return left < right; }

template <typename char_type>
static constexpr int string_compare(const char_type* s1, const char_type* s2, size_t count) noexcept
{
    // In GCC versions , __builtin_memcmp fails in valid checks in constexpr evaluation
//cjh #if !defined(AZ_COMPILER_GCC)
//    if constexpr (AZStd::is_same_v<char_type, char>)
//    {
//        return __builtin_memcmp(s1, s2, count);
//    }
//    else if constexpr (AZStd::is_same_v<char_type, wchar_t>)
//    {
//        return __builtin_wmemcmp(s1, s2, count);
//    }
//    else
//#endif
    {
        if (az_builtin_is_constant_evaluated())
        {
            for (; count; --count, ++s1, ++s2)
            {
                if (lt(*s1, *s2))
                {
                    return -1;
                }
                else if (lt(*s2, *s1))
                {
                    return 1;
                }
            }
            return 0;
        }
        else
        {
            return ::memcmp(s1, s2, count * sizeof(char_type));
        }
    }
}

// ends_with
static inline constexpr bool string_ends_with(const string& str, const string& suffix)
{
    return str.size() >= suffix.size() && string_compare(str.data() + (str.size() - suffix.size()), suffix.data(), suffix.size()) == 0;
}

template<class Element, class Traits, class Allocator, class Predicate>
decltype(auto) erase_if(basic_string<Element, Traits, Allocator>& container, Predicate predicate)
{
    auto iter = AZStd::remove_if(container.begin(), container.end(), predicate);
    auto removedCount = AZStd::distance(iter, container.end());
    container.erase(iter, container.end());
    return removedCount;
}

}
