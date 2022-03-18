/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <type_traits>
#include <AzCore/std/utils.h> // AZStd::addressof
#include <AzCore/std/typetraits/is_array.h>


namespace AZStd
{
    //! Implements the C++20 version of destroy_at
    //! If the element type T is not an array type it invokes the destructor on that object
    //! Otherwise it recursively destructs the elements of the array as if by calling
    //! AZStd::destroy(AZStd::begin(*ptr), AZStd::end(*ptr))
    template <typename T>
    constexpr void destroy_at(T* ptr)
    {
        if constexpr (AZStd::is_array_v<T>)
        {
            for (auto& element : *ptr)
            {
                AZStd::destroy_at(AZStd::addressof(element));
            }
        }
        else
        {
            ptr->~T();
        }
    }
    //! Implements the C++17 destroy function which works on a range of elements
    //! The functions accepts a first and last iterator
    //! and invokes the destructor on all element in the iterator range
    template <typename ForwardIt>
    constexpr void destroy(ForwardIt first, ForwardIt last)
    {
        for (; first != last; ++first)
        {
            AZStd::destroy_at(AZStd::addressof(*first));
        }
    }

    //! Implements the C++17 destroy_n function
    //! The function accepts a forward iterator and a number of elements
    //! and invokes the destructor on all the elements in the range
    //! Returns an iterator past the last element destructed
    template <typename ForwardIt, size_t N>
    constexpr ForwardIt destroy_n(ForwardIt first, size_t numElements)
    {
        for (; numElements > 0; ++first, --numElements)
        {
            AZStd::destroy_at(AZStd::addressof(*first));
        }
        return first;
    }
}

namespace AZStd
{
    //! C++20 implementation of construct_at
    //! Invokes placement new on the supplied address
    //! Constraints: Only available when the expression
    //! `new (declval<void*>()) T(declval<Args>()...)` is well-formed
    template <typename T, typename... Args>
    constexpr auto construct_at(T* ptr, Args&&... args)
        -> enable_if_t<AZStd::is_void_v<AZStd::void_t<decltype(new (AZStd::declval<void*>()) T(AZStd::forward<Args>(args)...))>>, T*>
    {
        return ::new (ptr) T(AZStd::forward<Args>(args)...);
    }
}



