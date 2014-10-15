// pja_format.h - header file for the CFormat class
//
// Copyright (c) 2006 PJ Arends
//
// This file is provided "AS-IS". Use and/or abuse it in any way you feel fit.
//

#ifndef _PJA_FORMAT_H_INCLUDED_
#define _PJA_FORMAT_H_INCLUDED_

#pragma once

#pragma warning(disable: 4786) // identifier was truncated to '255' characters in the debug information

#ifndef _CONSOLE
#include <windows.h>
#endif

#include <map>
#include <sstream>
#include <stdarg.h>
#include <tchar.h>
#include "tstl.h"

namespace pja
{
    class CFormat
    {
    private:
        unsigned int precision;
        std::map<TCHAR, std::tstring> markermap;
        std::tstring _make(std::tstring FormatString, unsigned int ParameterCount, va_list valist);
    public:
        CFormat(unsigned int Precision = 6);

        unsigned int SetPrecision(unsigned int p);

        std::tstring AddMarker(TCHAR Marker, std::tstring ReplaceWith);
        std::tstring RemoveMarker(TCHAR Marker);

    #ifdef _WINDOWS_
        // The file windows.h declares the HMODULE type
        std::tstring MakeMessage(HMODULE hModule, unsigned long FormatStringID, unsigned int ParameterCount = 0, ...);
    #endif // _WINDOWS_

        std::tstring MakeMessage(std::tstring FormatString, unsigned int ParameterCount = 0, ...);
        std::tstring MakeMessage(const TCHAR * FormatString, unsigned int ParameterCount = 0, ...);

        // default implementation of the TS function
        // convert any type to a string using the inserter << operator
        template <class T> const std::tstring TS (const T &t)
        {
            std::tostringstream s;
            s.setf(std::tios::fixed | std::tios::boolalpha);
            s.precision(precision);
            s << t;
            return s.str();
        }
    };
}

#endif // _PJA_FORMAT_H_INCLUDED_
