﻿/***
*mbtohira.c - Convert character from katakana to hiragana (Japanese).
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _jtohira() - convert character to hiragana.
*
*******************************************************************************/
#ifndef _MBCS
    #error This file should only be compiled with _MBCS defined
#endif

#include <corecrt_internal_mbstring.h>
#include <locale.h>


/***
*unsigned int _mbctohira(c) - Converts character to hiragana.
*
*Purpose:
*       Converts the character c from katakana to hiragana, if possible.
*
*Entry:
*       unsigned int c - Character to convert.
*
*Exit:
*       Returns the converted character.
*
*Exceptions:
*
*******************************************************************************/

#if WindowsTargetPlatformMinVersion < WindowsTargetPlatformWindows6
extern "C" unsigned int __cdecl _mbctohira_l(
        unsigned int c,
        _locale_t plocinfo
        )
{
        if (_ismbckata_l(c, plocinfo) && c <= 0x8393) {
                if (c < 0x837f)
                        c -= 0xa1;
                else
                        c -= 0xa2;
        }
        return(c);
}

_LCRT_DEFINE_IAT_SYMBOL(_mbctohira_l);
#endif

#if 0
extern "C" unsigned int __cdecl _mbctohira(unsigned int c)
{
    return _mbctohira_l(c, nullptr);
}
#endif
