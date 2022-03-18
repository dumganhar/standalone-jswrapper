/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once


#include <AzCore/std/string/string.h>
#include <set>
#include <vector>
#include <optional>
#include <AzCore/Casting/numeric_cast.h>

//---------------------------------------------------------------------
// FILENAME CONSTRAINTS
//---------------------------------------------------------------------

#if AZ_TRAIT_OS_USE_WINDOWS_FILE_PATHS
#   define AZ_CORRECT_FILESYSTEM_SEPARATOR '\\'
#   define AZ_CORRECT_FILESYSTEM_SEPARATOR_STRING "\\"
#   define AZ_DOUBLE_CORRECT_FILESYSTEM_SEPARATOR "\\\\"
#   define AZ_WRONG_FILESYSTEM_SEPARATOR '/'
#   define AZ_WRONG_FILESYSTEM_SEPARATOR_STRING "/"
#   define AZ_NETWORK_PATH_START "\\\\"
#   define AZ_NETWORK_PATH_START_SIZE 2
#   define AZ_CORRECT_AND_WRONG_FILESYSTEM_SEPARATOR "/\\"
#else
#   define AZ_CORRECT_FILESYSTEM_SEPARATOR '/'
#   define AZ_CORRECT_FILESYSTEM_SEPARATOR_STRING "/"
#   define AZ_DOUBLE_CORRECT_FILESYSTEM_SEPARATOR "//"
#   define AZ_WRONG_FILESYSTEM_SEPARATOR '\\'
#   define AZ_WRONG_FILESYSTEM_SEPARATOR_STRING "\\"
#   define AZ_NETWORK_PATH_START "\\\\"
#   define AZ_NETWORK_PATH_START_SIZE 2
#   define AZ_CORRECT_AND_WRONG_FILESYSTEM_SEPARATOR "/\\"
#endif
#define AZ_FILESYSTEM_EXTENSION_SEPARATOR '.'
#define AZ_FILESYSTEM_WILDCARD '*'
#define AZ_FILESYSTEM_DRIVE_SEPARATOR ':'
#define AZ_FILESYSTEM_INVALID_CHARACTERS "><|\"?*\r\n"

#define AZ_FILENAME_ALLOW_SPACES
#define AZ_SPACE_CHARACTERS " \t"
#define AZ_MATCH_ALL_FILES_WILDCARD_PATTERN  "*"
#define AZ_FILESYSTEM_SEPARATOR_WILDCARD AZ_CORRECT_FILESYSTEM_SEPARATOR_STRING AZ_MATCH_ALL_FILES_WILDCARD_PATTERN

//These do not change per platform they relate to how we represent paths in our database
//which is not dependent on platform file system
#define AZ_CORRECT_DATABASE_SEPARATOR '/'
#define AZ_CORRECT_DATABASE_SEPARATOR_STRING "/"
#define AZ_DOUBLE_CORRECT_DATABASE_SEPARATOR "//"
#define AZ_WRONG_DATABASE_SEPARATOR '\\'
#define AZ_WRONG_DATABASE_SEPARATOR_STRING "\\"
#define AZ_CORRECT_AND_WRONG_DATABASE_SEPARATOR "/\\"
#define AZ_DATABASE_EXTENSION_SEPARATOR '.'
#define AZ_DATABASE_INVALID_CHARACTERS "><|\"?*\r\n"
//////////////////////////////////////////////////////////////////////////

//! Namespace for string functions.
/*!
The StringFunc namespace is where we put string functions that extend some std::string functionality
to regular c-strings, make easier implementations of common but complex AZStd::strings routines,
implement features that are not in std (or not yet in std), and a host of functions to more easily
manipulate file paths. Some simply do additional error checking on top of the std, or make it more
readable.
*/
namespace AZ
{
    namespace StringFunc
    {


        //! Replace
        /*! Replace the first, last or all character(s) or substring(s) in a AZStd::string with
         *! case sensitivity.
         Example: Case Insensitive Replace all 'o' characters with 'a' character
         StringFunc::Replace(s = "Hello World", 'o', 'a'); s == "Hella Warld"
         Example: Case Sensitive Replace all 'o' characters with 'a' character
         StringFunc::Replace(s = "HellO World", 'O', 'o'); s == "Hello World"
         */
        bool Replace(AZStd::string& inout, const char replaceA, const char withB, bool bCaseSensitive = false, bool bReplaceFirst = false, bool bReplaceLast = false);
        bool Replace(AZStd::string& inout, const char* replaceA, const char* withB, bool bCaseSensitive = false, bool bReplaceFirst = false, bool bReplaceLast = false);


    } // namespace StringFunc
} // namespace AzFramework
