/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#ifndef AZSTD_TYPE_TRAITS_CONFIG_INCLUDED
#define AZSTD_TYPE_TRAITS_CONFIG_INCLUDED


#ifndef AZStd
#define std
#endif
//#include <AzCore/std/base.h>

// Compilers are more consistent with the traits, since AZStd doesn't have the goal or design need
// to control that we are pulling std one into AZStd till we have all tests pass and have consisten syntax
// across compilers
#include <type_traits>

//
// define AZSTD_TYPE_TRAITS_TEST_MS_FUNC_SIGS
// when we want to test __stdcall etc function types with is_function etc
//
#if defined(_MSC_EXTENSIONS)
    #define AZSTD_TYPE_TRAITS_TEST_MS_FUNC_SIGS
#else
    #define AZSTD_DISABLE_WIN32
#endif

//
// whenever we have a conversion function with elipses
// it needs to be declared __cdecl to suppress compiler
// warnings from MS
#if defined(AZ_COMPILER_MSVC) && !defined(AZSTD_DISABLE_WIN32)
    #define AZSTD_TYPE_TRAITS_DECL __cdecl
#else
    #define AZSTD_TYPE_TRAITS_DECL /**/
#endif


#endif // AZSTD_TYPE_TRAITS_CONFIG_INCLUDED
#pragma once

