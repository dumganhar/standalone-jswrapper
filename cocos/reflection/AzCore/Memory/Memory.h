/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/base.h>


    #define aznew           new
    #define aznewex(_Name)  aznew



#define AZ_PAGE_SIZE AZ_TRAIT_OS_DEFAULT_PAGE_SIZE
#define AZ_DEFAULT_ALIGNMENT (sizeof(void*))

// define unlimited allocator limits (scaled to real number when we check if there is enough memory to allocate)
#define AZ_CORE_MAX_ALLOCATOR_SIZE AZ_TRAIT_OS_MEMORY_MAX_ALLOCATOR_SIZE
