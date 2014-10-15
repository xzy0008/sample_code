// pja_format.cpp - implementation file for the CFormat class
//
// Copyright (c) 2006 PJ Arends
//
// This file is provided "AS-IS". Use and/or abuse it in any way you feel fit.
//
#include <vgStableHeaders.h>
#include "pja_format.h"
#include <crtdbg.h>            // for _ASSERT

using namespace pja;

// ReservedMarkers is used by the AddMarker and RemoveMarker functions
const TCHAR ReservedMarkers[] = _T("%nt123456789");

CFormat::CFormat(unsigned int Precision /* = 6 */) :
precision(Precision)
{
    markermap[_T('%')] = _T("%");
    markermap[_T('n')] = _T("\r\n");
    markermap[_T('t')] = _T("\t");
}

unsigned int CFormat::SetPrecision(unsigned int p)
{
    unsigned int ret = precision;
    precision = p;
    return ret;
}

std::tstring CFormat::AddMarker(TCHAR Marker, std::tstring ReplaceWith)
{
    _ASSERT(_tcschr(ReservedMarkers, Marker) == 0);
    _ASSERT (!ReplaceWith.empty());

    if (_tcschr(ReservedMarkers, Marker) == 0 && !ReplaceWith.empty())
    {
        return markermap[Marker] = ReplaceWith;
    }
    return _T("");
}

std::tstring CFormat::RemoveMarker(TCHAR Marker)
{
    _ASSERT(_tcschr(ReservedMarkers, Marker) == 0);

    if (_tcschr(ReservedMarkers, Marker) == 0 && markermap.find(Marker) != markermap.end())
    {
        std::tstring ret = markermap[Marker];
        markermap.erase(Marker);
        return ret;
    }

    return _T("");
}

#ifdef _WINDOWS_
// The file windows.h declares the HMODULE type and the GetModuleHandle, LoadString and
// OutputDebugString APIs so it has to be included in your project in order to use this
// overridden version of MakeMessage

std::tstring CFormat::MakeMessage(HMODULE hModule,
                                  unsigned long FormatStringID,
                                  unsigned int ParameterCount /* = 0 */,
                                  ...)
{
    _ASSERT(FormatStringID != 0);

    std::tstring ret = _T("");
    va_list valist;
    va_start(valist, ParameterCount);

    if (hModule == NULL)
    {
        hModule = ::GetModuleHandle(NULL);
        _ASSERT(hModule != NULL);
    }

    // following code based on CString::LoadString
    int size = 0;
    int len = 256;
    TCHAR *buffer = NULL;

    try
    {
        while (len && len > size - 2)
        {
            size += 256;
            len = 0;
            delete[] buffer;
            buffer = new TCHAR[size];
            if (hModule && FormatStringID && buffer)
            {
                len = ::LoadString(hModule, FormatStringID, buffer, size);
            }
        }
    }
    catch (std::bad_alloc &)
    {
        len = 0;
    }

    if (len)
    {
        ret = _make(buffer, ParameterCount, valist);
    }
    else
    {
#ifdef _DEBUG
        std::tostringstream error;
        error << _T("Unable to load string resource: ") << FormatStringID;
        error << _T(", GetLastError() returns: ") << GetLastError() << std::endl;
        OutputDebugString(error.str().c_str());
        _ASSERT(0);
#endif // _DEBUG

        // maybe substitute this text for a more meaningful error text,
        // or possibly leave the ret value empty
        ret = _T("<< ? ? ? >>");
    }

    delete[] buffer;
    return ret;
}

#endif // _WINDOWS_

std::tstring CFormat::MakeMessage(const TCHAR * FormatString,
                                  unsigned int ParameterCount /* = 0 */,
                                  ...)
{
    va_list valist;
    va_start(valist, ParameterCount);

    return _make(FormatString, ParameterCount, valist);
}

std::tstring CFormat::MakeMessage(std::tstring FormatString,
                                  unsigned int ParameterCount /* = 0 */,
                                  ...)
{
    va_list valist;
    va_start(valist, ParameterCount);

    return _make(FormatString, ParameterCount, valist);
}

std::tstring CFormat::_make(std::tstring FormatString,
                            unsigned int ParameterCount,
                            va_list valist)
{
    _ASSERT(ParameterCount < 10);

    // only handle a maximum of nine variables ( %1 to %9 )
    if (ParameterCount > 9)
    {
        ParameterCount = 9;
    }

    // here we grab the variables from the variable argument list and
    // store them in the marker map for quick and easy access later.
    // They should all be std::tstring
    unsigned int LoopCounter = 0;
    for (; LoopCounter < ParameterCount; ++LoopCounter)
    {
        std::tstring Variable = va_arg(valist, std::tstring);
        markermap[_T('1') + static_cast<TCHAR>(LoopCounter)] = Variable;
    }

    // remove any variables that may be left over from a previous call to _make.
    for (; LoopCounter < 10; ++LoopCounter)
    {
        markermap.erase(_T('1') + static_cast<TCHAR>(LoopCounter));
    }

    va_end(valist);

    // Scan the format string for insertion markers, and replace any found
    // with the corresponding text stored in the marker map.
    //
    // I am using the tostringstream insertion operator to build the final string,
    // not the tstring::replace function because I am hoping to be able to have the
    // marker map be able to map insertion markers to any type that has an ostream
    // insertion operator defined rather than simply a static text. But at the
    // moment I am unsure how to declare the map to take multiple data types.
    size_t LastPosition = 0;
    size_t Position = LastPosition;
    std::tostringstream FinalString;

    while (Position != std::tstring::npos)
    {
        Position = FormatString.find(_T('%'), Position);
        if (Position != std::tstring::npos)
        {
            FinalString << FormatString.substr(LastPosition, Position - LastPosition);
            TCHAR marker = FormatString[Position + 1];

            // if the format string ends with a single '%', marker will be the terminating NULL
            if (marker != NULL)
            {
                if (markermap.find(marker) != markermap.end())
                {
                    FinalString << markermap[marker];
                }
                ++Position;
            }

            ++Position;
            LastPosition = Position;
        }
    }

    if (LastPosition != 0)
    {
        FinalString << FormatString.substr(LastPosition);
        FormatString = FinalString.str();
    }

    return FormatString;
}
