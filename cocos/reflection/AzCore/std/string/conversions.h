/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/std/string/string.h>
//#include <AzCore/std/string/fixed_string.h>

#include <ctype.h>
#include <wctype.h>

//////////////////////////////////////////////////////////////////////////
// utf8 cpp lib
//#include <AzCore/std/string/utf8/unchecked.h>
//////////////////////////////////////////////////////////////////////////

//# define AZSTD_USE_OLD_RW_STL

#if !defined(AZSTD_USE_OLD_RW_STL)
#   include <locale>
#endif

namespace AZStd
{
    // 21.5: numeric conversions
    template<class Allocator>
    int stoi(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, AZStd::size_t* idx = 0, int base = 10)
    {
        char* ptr;
        const char* sChar = str.c_str();
        int result = (int)strtol(sChar, &ptr, base);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    template<class Allocator>
    long stol(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, AZStd::size_t* idx = 0, int base = 10)
    {
        char* ptr;
        const char* sChar = str.c_str();
        long result = strtol(sChar, &ptr, base);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    template<class Allocator>
    unsigned long stoul(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, AZStd::size_t* idx = 0, int base = 10)
    {
        char* ptr;
        const char* sChar = str.c_str();
        unsigned long result = strtoul(sChar, &ptr, base);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    template<class Allocator>
    long long stoll(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, size_t* idx = 0, int base = 10)
    {
        char* ptr;
        const char* sChar = str.c_str();
        long long result = strtoll(sChar, &ptr, base);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    template<class Allocator>
    unsigned long long stoull(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, size_t* idx = 0, int base = 10)
    {
        char* ptr;
        const char* sChar = str.c_str();
        unsigned long long result = strtoull(sChar, &ptr, base);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }

    template<class Allocator>
    float stof(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, AZStd::size_t* idx = 0)
    {
        char* ptr;
        const char* sChar = str.c_str();
        float result = (float)strtod(sChar, &ptr);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    template<class Allocator>
    double stod(const AZStd::basic_string<AZStd::string::value_type, AZStd::string::traits_type, Allocator>& str, AZStd::size_t* idx = 0)
    {
        char* ptr;
        const char* sChar = str.c_str();
        double result = strtod(sChar, &ptr);
        if (idx)
        {
            *idx = ptr - sChar;
        }
        return result;
    }
    /*
    template<class Allocator>
    long double stold(const AZStd::basic_string<string::value_type,string::traits_type,Allocator>& str, size_t *idx = 0)
    {
        char* ptr;
        const char * sChar = str.c_str();
        long double result = strtold(sChar,&ptr);
        if(idx)
            *idx = ptr - sChar;
        return result;
    }*/

    // Standard is messy when it comes to custom string. Let's say we have a string with different allocator ???
    // so we have our (custom) implementations here and wrappers so we are compatible with the standard.
    template<class Str>
    void to_string(Str& str, int value)
    {
        char buf[16];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%d", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, unsigned int value)
    {
        char buf[16];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%u", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, float value)
    {
        char buf[64];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%f", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, double value)
    {
        char buf[64];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%f", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, long value)
    {
        char buf[32];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%ld", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, unsigned long value)
    {
        char buf[32];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%lu", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, long long value)
    {
        char buf[32];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%lld", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, unsigned long long value)
    {
        char buf[32];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%llu", value);
        str = buf;
    }
    template<class Str>
    void to_string(Str& str, long double value)
    {
        char buf[128];
        azsnprintf(buf, AZ_ARRAY_SIZE(buf), "%Lf", value);
        str = buf;
    }



    // Convert a range of chars to lower case

    // C standard requires that is_alpha and all the other below functions should be passed a positive integer
    // (it will error if a negative value is passed in such as -128), which is what happens if you pass a char
    // from the extended character set, without first converting it to an unsigned char, because it will
    // automatically convert it to an int (-128) instead of to its ascii value (127), which is what these functions expect.
    AZ_FORCE_INLINE bool is_alnum(char ch)          { return isalnum((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_alpha(char ch)          { return isalpha((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_cntrl(char ch)          { return iscntrl((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_digit(char ch)          { return isdigit((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_graph(char ch)          { return isgraph((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_lower(char ch)          { return islower((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_print(char ch)          { return isprint((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_punct(char ch)          { return ispunct((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_space(char ch)          { return isspace((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_upper(char ch)          { return isupper((unsigned char)ch) != 0; }
    AZ_FORCE_INLINE bool is_xdigit(char ch)         { return isxdigit((unsigned char)ch) != 0; }

    AZ_FORCE_INLINE bool is_alnum(wchar_t ch)       { return iswalnum(ch) != 0; }
    AZ_FORCE_INLINE bool is_alpha(wchar_t ch)       { return iswalpha(ch) != 0; }
    AZ_FORCE_INLINE bool is_cntrl(wchar_t ch)       { return iswcntrl(ch) != 0; }
    AZ_FORCE_INLINE bool is_digit(wchar_t ch)       { return iswdigit(ch) != 0; }
    AZ_FORCE_INLINE bool is_graph(wchar_t ch)       { return iswgraph(ch) != 0; }
    AZ_FORCE_INLINE bool is_lower(wchar_t ch)       { return iswlower(ch) != 0; }
    AZ_FORCE_INLINE bool is_print(wchar_t ch)       { return iswprint(ch) != 0; }
    AZ_FORCE_INLINE bool is_punct(wchar_t ch)       { return iswpunct(ch) != 0; }
    AZ_FORCE_INLINE bool is_space(wchar_t ch)       { return iswspace(ch) != 0; }
    AZ_FORCE_INLINE bool is_upper(wchar_t ch)       { return iswupper(ch) != 0; }
    AZ_FORCE_INLINE bool is_xdigit(wchar_t ch)      { return iswxdigit(ch) != 0; }


    template<class Iterator>
    void to_lower(Iterator first, Iterator last, const std::locale& loc = std::locale())
    {
        for (; first != last; ++first)
        {
            *first = std::tolower(*first, loc);
        }
    }

    // Convert a range of chars to upper case
    template<class Iterator>
    void to_upper(Iterator first, Iterator last, const std::locale& loc = std::locale())
    {
        for (; first != last; ++first)
        {
            *first = std::toupper(*first, loc);
        }
    }
    // Add case insensitive compares
}
