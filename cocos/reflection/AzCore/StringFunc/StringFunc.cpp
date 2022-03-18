/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include <ctype.h>

#include <functional>
#include <string>
#include <array>
//#include <AzCore/std/containers/fixed_vector.h>
#include <AzCore/Memory/Memory.h>
//#include <AzCore/Memory/OSAllocator.h>
//#include <AzCore/Memory/SystemAllocator.h>
//#include <AzCore/IO/Path/Path.h>
#include <AzCore/StringFunc/StringFunc.h>
#include <AzCore/std/string/conversions.h>
//cjh #include <AzCore/Math/Vector2.h>
//#include <AzCore/Math/Vector3.h>
//#include <AzCore/Math/Vector4.h>
//#include <AzCore/AzCore_Traits_Platform.h>

namespace AZ::StringFunc::Internal
{


    template<typename StringType>
    bool Replace(StringType& inout, const char replaceA, const char withB, bool bCaseSensitive = false, bool bReplaceFirst = false, bool bReplaceLast = false)
    {
        bool bSomethingWasReplaced = false;
        size_t pos = 0;

        if (!bReplaceFirst && !bReplaceLast)
        {
            //replace all
            if (bCaseSensitive)
            {
                bSomethingWasReplaced = false;
                while ((pos = inout.find(replaceA, pos)) != StringType::npos)
                {
                    bSomethingWasReplaced = true;
                    inout.replace(pos, 1, 1, withB);
                    pos++;
                }
            }
            else
            {
                StringType lowercaseIn(inout);
                AZStd::to_lower(lowercaseIn.begin(), lowercaseIn.end());

                char lowercaseReplaceA = (char)tolower(replaceA);

                while ((pos = lowercaseIn.find(lowercaseReplaceA, pos)) != StringType::npos)
                {
                    bSomethingWasReplaced = true;
                    inout.replace(pos, 1, 1, withB);
                    pos++;
                }
            }
        }
        else
        {
            if (bCaseSensitive)
            {
                if (bReplaceFirst)
                {
                    //replace first
                    if ((pos = inout.find_first_of(replaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, 1, 1, withB);
                    }
                }

                if (bReplaceLast)
                {
                    //replace last
                    if ((pos = inout.find_last_of(replaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, 1, 1, withB);
                    }
                }
            }
            else
            {
                StringType lowercaseIn(inout);
                AZStd::to_lower(lowercaseIn.begin(), lowercaseIn.end());

                char lowercaseReplaceA = (char)tolower(replaceA);

                if (bReplaceFirst)
                {
                    //replace first
                    if ((pos = lowercaseIn.find_first_of(lowercaseReplaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, 1, 1, withB);
                        if (bReplaceLast)
                        {
                            lowercaseIn.replace(pos, 1, 1, withB);
                        }
                    }
                }

                if (bReplaceLast)
                {
                    //replace last
                    if ((pos = lowercaseIn.find_last_of(lowercaseReplaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, 1, 1, withB);
                    }
                }
            }
        }

        return bSomethingWasReplaced;
    }

    template<typename StringType>
    bool Replace(StringType& inout, const char* replaceA, const char* withB, bool bCaseSensitive = false, bool bReplaceFirst = false, bool bReplaceLast = false)
    {
        if (!replaceA) //withB can be nullptr
        {
            return false;
        }

        size_t lenA = strlen(replaceA);
        if (!lenA)
        {
            return false;
        }

        const char* emptystring = "";
        if (!withB)
        {
            withB = emptystring;
        }

        size_t lenB = strlen(withB);

        bool bSomethingWasReplaced = false;

        size_t pos = 0;

        if (!bReplaceFirst && !bReplaceLast)
        {
            //replace all
            if (bCaseSensitive)
            {
                while ((pos = inout.find(replaceA, pos)) != StringType::npos)
                {
                    bSomethingWasReplaced = true;
                    inout.replace(pos, lenA, withB, lenB);
                    pos += lenB;
                }
            }
            else
            {
                StringType lowercaseIn(inout);
                AZStd::to_lower(lowercaseIn.begin(), lowercaseIn.end());

                StringType lowercaseReplaceA(replaceA);
                AZStd::to_lower(lowercaseReplaceA.begin(), lowercaseReplaceA.end());

                while ((pos = lowercaseIn.find(lowercaseReplaceA, pos)) != StringType::npos)
                {
                    bSomethingWasReplaced = true;
                    lowercaseIn.replace(pos, lenA, withB, lenB);
                    inout.replace(pos, lenA, withB, lenB);
                    pos += lenB;
                }
            }
        }
        else
        {
            if (bCaseSensitive)
            {
                if (bReplaceFirst)
                {
                    //replace first
                    if ((pos = inout.find(replaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, lenA, withB, lenB);
                    }
                }

                if (bReplaceLast)
                {
                    //replace last
                    if ((pos = inout.rfind(replaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, lenA, withB, lenB);
                    }
                }
            }
            else
            {
                StringType lowercaseIn(inout);
                AZStd::to_lower(lowercaseIn.begin(), lowercaseIn.end());

                StringType lowercaseReplaceA(replaceA);
                AZStd::to_lower(lowercaseReplaceA.begin(), lowercaseReplaceA.end());

                if (bReplaceFirst)
                {
                    //replace first
                    if ((pos = lowercaseIn.find(lowercaseReplaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, lenA, withB, lenB);
                        if (bReplaceLast)
                        {
                            lowercaseIn.replace(pos, lenA, withB, lenB);
                        }
                    }
                }

                if (bReplaceLast)
                {
                    //replace last
                    if ((pos = lowercaseIn.rfind(lowercaseReplaceA)) != StringType::npos)
                    {
                        bSomethingWasReplaced = true;
                        inout.replace(pos, lenA, withB, lenB);
                    }
                }
            }
        }

        return bSomethingWasReplaced;
    }

}

namespace AZ::StringFunc
{
    bool Replace(AZStd::string& inout, const char replaceA, const char withB, bool bCaseSensitive, bool bReplaceFirst, bool bReplaceLast)
    {
        return Internal::Replace(inout, replaceA, withB, bCaseSensitive, bReplaceFirst, bReplaceLast);
    }

    bool Replace(AZStd::string& inout, const char* replaceA, const char* withB, bool bCaseSensitive, bool bReplaceFirst, bool bReplaceLast)
    {
        return Internal::Replace(inout, replaceA, withB, bCaseSensitive, bReplaceFirst, bReplaceLast);
    }


} // namespace AZ::StringFunc
