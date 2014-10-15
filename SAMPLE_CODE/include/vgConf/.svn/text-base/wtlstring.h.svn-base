// Windows Template Library - WTL version 7.1
// Copyright (C) 1997-2003 Microsoft Corporation
// All rights reserved.
//
// This file is a part of the Windows Template Library.
// The code and information is provided "as-is" without
// warranty of any kind, either expressed or implied.

#ifndef WTLSTRING_H
#define WTLSTRING_H

#include <crtdbg.h>
#include <malloc.h>
#include <limits.h>
#include <stdio.h>

#pragma message("including wtlstring.h")

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#pragma warning(disable : 4710)		// not inlined
#pragma warning(push)
#pragma warning(disable : 4127)		// conditional expression is constant
#pragma warning(disable : 4996)		// disable bogus deprecation warning

#ifdef _DEBUG
void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
void  operator delete(void* p, LPCSTR lpszFileName, int nLine);
#undef DEBUG_NEW
#define DEBUG_NEW new("wtlstring.h", __LINE__)
#undef new
#define new DEBUG_NEW
#endif	//_DEBUG

///////////////////////////////////////////////////////////////////////////////
// CWTLString - String class

struct CWTLStringData
{
	long nRefs;     // reference count
	int nDataLength;
	int nAllocLength;
	// TCHAR data[nAllocLength]

	TCHAR* data()
	{ return (TCHAR*)(this + 1); }
};

// Globals

// For an empty string, m_pchData will point here
// (note: avoids special case of checking for NULL m_pchData)
// empty string data (and locked)
_declspec(selectany) int X_rgInitData[] = { -1, 0, 0, 0 };
_declspec(selectany) CWTLStringData* _atltmpXtmpDataNil = (CWTLStringData*)&X_rgInitData;
_declspec(selectany) LPCTSTR _atltmpXtmpPchNil = (LPCTSTR)(((BYTE*)&X_rgInitData) + sizeof(CWTLStringData));

class CWTLString
{
public:
// Constructors
	CWTLString();
	CWTLString(const CWTLString& stringSrc);
	CWTLString(TCHAR ch, int nRepeat = 1);
	CWTLString(LPCSTR lpsz);
	CWTLString(LPCWSTR lpsz);
	CWTLString(LPCSTR lpch, int nLength);
	CWTLString(LPCWSTR lpch, int nLength);
	CWTLString(const unsigned char* psz);

// Attributes & Operations
	// as an array of characters
	int GetLength() const;
	BOOL IsEmpty() const;
	void Empty();                       // free up the data

	TCHAR GetAt(int nIndex) const;      // 0 based
	TCHAR operator [](int nIndex) const; // same as GetAt
	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;           // as a C string

	// overloaded assignment
	const CWTLString& operator =(const CWTLString& stringSrc);
	const CWTLString& operator =(TCHAR ch);
#ifdef _UNICODE
	const CWTLString& operator =(char ch);
#endif
	const CWTLString& operator =(LPCSTR lpsz);
	const CWTLString& operator =(LPCWSTR lpsz);
	const CWTLString& operator =(const unsigned char* psz);

	// string concatenation
	const CWTLString& operator +=(const CWTLString& string);
	const CWTLString& operator +=(TCHAR ch);
#ifdef _UNICODE
	const CWTLString& operator +=(char ch);
#endif
	const CWTLString& operator +=(LPCTSTR lpsz);

	friend CWTLString __stdcall operator +(const CWTLString& string1, const CWTLString& string2);
	friend CWTLString __stdcall operator +(const CWTLString& string, TCHAR ch);
	friend CWTLString __stdcall operator +(TCHAR ch, const CWTLString& string);
#ifdef _UNICODE
	friend CWTLString __stdcall operator +(const CWTLString& string, char ch);
	friend CWTLString __stdcall operator +(char ch, const CWTLString& string);
#endif
	friend CWTLString __stdcall operator +(const CWTLString& string, LPCTSTR lpsz);
	friend CWTLString __stdcall operator +(LPCTSTR lpsz, const CWTLString& string);

	// string comparison
	int Compare(LPCTSTR lpsz) const;         // straight character
	int CompareNoCase(LPCTSTR lpsz) const;   // ignore case
	int Collate(LPCTSTR lpsz) const;         // NLS aware
	int CollateNoCase(LPCTSTR lpsz) const;   // ignore case

	// simple sub-string extraction
	CWTLString Mid(int nFirst, int nCount) const;
	CWTLString Mid(int nFirst) const;
	CWTLString Left(int nCount) const;
	CWTLString Right(int nCount) const;

	CWTLString SpanIncluding(LPCTSTR lpszCharSet) const;
	CWTLString SpanExcluding(LPCTSTR lpszCharSet) const;

	// upper/lower/reverse conversion
	void MakeUpper();
	void MakeLower();
	void MakeReverse();

	// trimming whitespace (either side)
	void TrimRight();
	void TrimLeft();
	void Trim();

	// remove continuous occurrences of chTarget starting from right
	void TrimRight(TCHAR chTarget);
	// remove continuous occcurrences of characters in passed string,
	// starting from right
	void TrimRight(LPCTSTR lpszTargets);
	// remove continuous occurrences of chTarget starting from left
	void TrimLeft(TCHAR chTarget);
	// remove continuous occcurrences of characters in
	// passed string, starting from left
	void TrimLeft(LPCTSTR lpszTargets);

	// advanced manipulation
	// replace occurrences of chOld with chNew
	int Replace(TCHAR chOld, TCHAR chNew);
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
	int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew);
	// remove occurrences of chRemove
	int Remove(TCHAR chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, TCHAR ch);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, LPCTSTR pstr);
	// delete nCount characters starting at zero-based index
	int Delete(int nIndex, int nCount = 1);

	// searching (return starting index, or -1 if not found)
	// look for a single character match
	int Find(TCHAR ch) const;                     // like "C" strchr
	int ReverseFind(TCHAR ch) const;
	int Find(TCHAR ch, int nStart) const;         // starting at index
	int FindOneOf(LPCTSTR lpszCharSet) const;

	// look for a specific sub-string
	int Find(LPCTSTR lpszSub) const;        // like "C" strstr
	int Find(LPCTSTR lpszSub, int nStart) const;  // starting at index

	// Concatentation for non strings
	const CWTLString& Append(int n)
	{
		const int cchBuff = 12;
		TCHAR szBuffer[cchBuff];
		wsprintf(szBuffer,_T("%d"),n);
		ConcatInPlace(SafeStrlen(szBuffer), szBuffer);
		return *this;
	}

	// simple formatting
	BOOL __cdecl Format(LPCTSTR lpszFormat, ...);
	BOOL __cdecl Format(UINT nFormatID, ...);
	BOOL FormatV(LPCTSTR lpszFormat, va_list argList);

	// formatting for localization (uses FormatMessage API)
	BOOL __cdecl FormatMessage(LPCTSTR lpszFormat, ...);
	BOOL __cdecl FormatMessage(UINT nFormatID, ...);

	// Windows support
	BOOL LoadString(UINT nID);          // load from string resource (255 chars max.)

#ifndef _UNICODE
	// ANSI <-> OEM support (convert string in place)
	void AnsiToOem();
	void OemToAnsi();
#endif

	// Access to string implementation buffer as "C" character array
	LPTSTR GetBuffer(int nMinBufLength);
	void ReleaseBuffer(int nNewLength = -1);
	LPTSTR GetBufferSetLength(int nNewLength);
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn refcounting off
	LPTSTR LockBuffer();
	void UnlockBuffer();

// Implementation
public:
	~CWTLString();
	int GetAllocLength() const;

	static BOOL __stdcall _IsValidString(LPCWSTR lpsz, int nLength = -1)
	{
		if(lpsz == NULL)
			return FALSE;
		return !::IsBadStringPtrW(lpsz, nLength);
	}

	static BOOL __stdcall _IsValidString(LPCSTR lpsz, int nLength = -1)
	{
		if(lpsz == NULL)
			return FALSE;
		return !::IsBadStringPtrA(lpsz, nLength);
	}

protected:
	LPTSTR m_pchData;   // pointer to ref counted string data

	// implementation helpers
	CWTLStringData* GetData() const;
	void Init();
	void AllocCopy(CWTLString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	BOOL AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);
	BOOL ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data);
	void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData);
	void CopyBeforeWrite();
	BOOL AllocBeforeWrite(int nLen);
	void Release();
	static void PASCAL Release(CWTLStringData* pData);
	static int PASCAL SafeStrlen(LPCTSTR lpsz);

	static int __stdcall _LoadString(UINT /*nID*/, LPTSTR /*lpszBuf*/, UINT /*nMaxBuf*/)
	{
		return 0;
	}

	static const CWTLString& __stdcall _GetEmptyString()
	{
		return *(CWTLString*)&_atltmpXtmpPchNil;
	}

// CWTLString conversion helpers
	static int __cdecl _wcstombsz(char* mbstr, const wchar_t* wcstr, size_t count)
	{
		if (count == 0 && mbstr != NULL)
			return 0;

		int result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1, mbstr, (int)count, NULL, NULL);
		_ASSERTE(mbstr == NULL || result <= (int)count);
		if (result > 0)
			mbstr[result - 1] = 0;
		return result;
	}

	static int __cdecl _mbstowcsz(wchar_t* wcstr, const char* mbstr, size_t count)
	{
		if (count == 0 && wcstr != NULL)
			return 0;

		int result = ::MultiByteToWideChar(CP_ACP, 0, mbstr, -1, wcstr, (int)count);
		_ASSERTE(wcstr == NULL || result <= (int)count);
		if (result > 0)
			wcstr[result - 1] = 0;
		return result;
	}

// Helpers to avoid CRT startup code
	static TCHAR* _cstrchr(const TCHAR* p, TCHAR ch)
	{
		return (TCHAR*)_tcschr(p, ch);
	}

	static TCHAR* _cstrrchr(const TCHAR* p, TCHAR ch)
	{
		return (TCHAR*)_tcsrchr(p, ch);
	}

	static TCHAR* _cstrrev(TCHAR* pStr)
	{
		return (TCHAR*)_tcsrev(pStr);
	}

	static TCHAR* _cstrstr(const TCHAR* pStr, const TCHAR* pCharSet)
	{
		return (TCHAR*)_tcsstr(pStr, pCharSet);
	}

	static int _cstrspn(const TCHAR* pStr, const TCHAR* pCharSet)
	{
		return (int)_tcsspn(pStr, pCharSet);
	}

	static int _cstrcspn(const TCHAR* pStr, const TCHAR* pCharSet)
	{
		return (int)_tcscspn(pStr, pCharSet);
	}

	static TCHAR* _cstrpbrk(const TCHAR* p, const TCHAR* lpszCharSet)
	{
		return (TCHAR*)_tcspbrk(p, lpszCharSet);
	}

	static int _cstrisdigit(TCHAR ch)
	{
		return _istdigit(ch);
	}

	static int _cstrisspace(TCHAR ch)
	{
		return _istspace((_TUCHAR)ch);
	}

	static int _cstrcmp(const TCHAR* pstrOne, const TCHAR* pstrOther)
	{
		return _tcscmp(pstrOne, pstrOther);
	}

	static int _cstrcmpi(const TCHAR* pstrOne, const TCHAR* pstrOther)
	{
		return _tcsicmp(pstrOne, pstrOther);
	}

	static int _cstrcoll(const TCHAR* pstrOne, const TCHAR* pstrOther)
	{
		return _tcscoll(pstrOne, pstrOther);
	}

	static int _cstrcolli(const TCHAR* pstrOne, const TCHAR* pstrOther)
	{
		return _tcsicoll(pstrOne, pstrOther);
	}

	static int _cstrtoi(const TCHAR* nptr)
	{
		return _ttoi(nptr);
	}

	static TCHAR* _cstrchr_db(const TCHAR* p, TCHAR ch1, TCHAR ch2)
	{
		const TCHAR* lpsz = NULL;
		while (*p != 0)
		{
			if (*p == ch1 && *(p + 1) == ch2)
			{
				lpsz = p;
				break;
			}
			p = ::CharNext(p);
		}
		return (TCHAR*)lpsz;
	}
};

// Compare helpers
bool __stdcall operator ==(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator ==(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator ==(LPCTSTR s1, const CWTLString& s2);
bool __stdcall operator !=(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator !=(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator !=(LPCTSTR s1, const CWTLString& s2);
bool __stdcall operator <(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator <(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator <(LPCTSTR s1, const CWTLString& s2);
bool __stdcall operator >(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator >(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator >(LPCTSTR s1, const CWTLString& s2);
bool __stdcall operator <=(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator <=(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator <=(LPCTSTR s1, const CWTLString& s2);
bool __stdcall operator >=(const CWTLString& s1, const CWTLString& s2);
bool __stdcall operator >=(const CWTLString& s1, LPCTSTR s2);
bool __stdcall operator >=(LPCTSTR s1, const CWTLString& s2);


///////////////////////////////////////////////////////////////////////////////
// CWTLString Implementation

inline CWTLStringData* CWTLString::GetData() const
{
	_ASSERTE(m_pchData != NULL);
	return ((CWTLStringData*)m_pchData) - 1;
}

inline void CWTLString::Init()
{ m_pchData = _GetEmptyString().m_pchData; }

inline CWTLString::CWTLString(const unsigned char* lpsz)
{
	Init();
	*this = (LPCSTR)lpsz;
}

inline const CWTLString& CWTLString::operator =(const unsigned char* lpsz)
{
	*this = (LPCSTR)lpsz;
	return *this;
}

#ifdef _UNICODE
inline const CWTLString& CWTLString::operator +=(char ch)
{
	*this += (TCHAR)ch;
	return *this;
}

inline const CWTLString& CWTLString::operator =(char ch)
{
	*this = (TCHAR)ch;
	return *this;
}

inline CWTLString __stdcall operator +(const CWTLString& string, char ch)
{ return string + (TCHAR)ch; }

inline CWTLString __stdcall operator +(char ch, const CWTLString& string)
{ return (TCHAR)ch + string; }
#endif //_UNICODE

inline int CWTLString::GetLength() const
{ return GetData()->nDataLength; }

inline int CWTLString::GetAllocLength() const
{ return GetData()->nAllocLength; }

inline BOOL CWTLString::IsEmpty() const
{ return GetData()->nDataLength == 0; }

inline CWTLString::operator LPCTSTR() const
{ return m_pchData; }

inline int PASCAL CWTLString::SafeStrlen(LPCTSTR lpsz)
{ return (lpsz == NULL) ? 0 : lstrlen(lpsz); }

// CWTLString support (windows specific)
inline int CWTLString::Compare(LPCTSTR lpsz) const
{ return _cstrcmp(m_pchData, lpsz); }    // MBCS/Unicode aware

inline int CWTLString::CompareNoCase(LPCTSTR lpsz) const
{ return _cstrcmpi(m_pchData, lpsz); }   // MBCS/Unicode aware

inline TCHAR CWTLString::GetAt(int nIndex) const
{
	_ASSERTE(nIndex >= 0);
	_ASSERTE(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}

inline TCHAR CWTLString::operator [](int nIndex) const
{
	// same as GetAt
	_ASSERTE(nIndex >= 0);
	_ASSERTE(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}

inline bool __stdcall operator ==(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) == 0; }

inline bool __stdcall operator ==(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) == 0; }

inline bool __stdcall operator ==(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) == 0; }

inline bool __stdcall operator !=(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) != 0; }

inline bool __stdcall operator !=(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) != 0; }

inline bool __stdcall operator !=(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) != 0; }

inline bool __stdcall operator <(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) < 0; }

inline bool __stdcall operator <(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) < 0; }

inline bool __stdcall operator <(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) > 0; }

inline bool __stdcall operator >(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) > 0; }

inline bool __stdcall operator >(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) > 0; }

inline bool __stdcall operator >(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) < 0; }

inline bool __stdcall operator <=(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) <= 0; }

inline bool __stdcall operator <=(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) <= 0; }

inline bool __stdcall operator <=(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) >= 0; }

inline bool __stdcall operator >=(const CWTLString& s1, const CWTLString& s2)
{ return s1.Compare(s2) >= 0; }

inline bool __stdcall operator >=(const CWTLString& s1, LPCTSTR s2)
{ return s1.Compare(s2) >= 0; }

inline bool __stdcall operator >=(LPCTSTR s1, const CWTLString& s2)
{ return s2.Compare(s1) <= 0; }

inline CWTLString::CWTLString()
{
	Init();
}

inline CWTLString::CWTLString(const CWTLString& stringSrc)
{
	_ASSERTE(stringSrc.GetData()->nRefs != 0);
	if (stringSrc.GetData()->nRefs >= 0)
	{
		_ASSERTE(stringSrc.GetData() != _atltmpXtmpDataNil);
		m_pchData = stringSrc.m_pchData;
		InterlockedIncrement(&GetData()->nRefs);
	}
	else
	{
		Init();
		*this = stringSrc.m_pchData;
	}
}

inline BOOL CWTLString::AllocBuffer(int nLen)
// always allocate one extra character for '\0' termination
// assumes [optimistically] that data length will equal allocation length
{
	_ASSERTE(nLen >= 0);
	_ASSERTE(nLen <= INT_MAX - 1);    // max size (enough room for 1 extra)

	if (nLen == 0)
	{
		Init();
	}
	else
	{
		CWTLStringData* pData = NULL;
		pData = (CWTLStringData*)new BYTE[sizeof(CWTLStringData) + (nLen + 1) * sizeof(TCHAR)];
		if(pData == NULL)
			return FALSE;

		pData->nRefs = 1;
		pData->data()[nLen] = '\0';
		pData->nDataLength = nLen;
		pData->nAllocLength = nLen;
		m_pchData = pData->data();
	}

	return TRUE;
}

inline void CWTLString::Release()
{
	if (GetData() != _atltmpXtmpDataNil)
	{
		_ASSERTE(GetData()->nRefs != 0);
		if (InterlockedDecrement(&GetData()->nRefs) <= 0)
			delete[] (BYTE*)GetData();
		Init();
	}
}

inline void PASCAL CWTLString::Release(CWTLStringData* pData)
{
	if (pData != _atltmpXtmpDataNil)
	{
		_ASSERTE(pData->nRefs != 0);
		if (InterlockedDecrement(&pData->nRefs) <= 0)
			delete[] (BYTE*)pData;
	}
}

inline void CWTLString::Empty()
{
	if (GetData()->nDataLength == 0)
		return;

	if (GetData()->nRefs >= 0)
		Release();
	else
		*this = _T("");

	_ASSERTE(GetData()->nDataLength == 0);
	_ASSERTE(GetData()->nRefs < 0 || GetData()->nAllocLength == 0);
}

inline void CWTLString::CopyBeforeWrite()
{
	if (GetData()->nRefs > 1)
	{
		CWTLStringData* pData = GetData();
		Release();
		if(AllocBuffer(pData->nDataLength))
			memcpy(m_pchData, pData->data(), (pData->nDataLength + 1) * sizeof(TCHAR));
	}
	_ASSERTE(GetData()->nRefs <= 1);
}

inline BOOL CWTLString::AllocBeforeWrite(int nLen)
{
	BOOL bRet = TRUE;
	if (GetData()->nRefs > 1 || nLen > GetData()->nAllocLength)
	{
		Release();
		bRet = AllocBuffer(nLen);
	}
	_ASSERTE(GetData()->nRefs <= 1);
	return bRet;
}

inline CWTLString::~CWTLString()
//  free any attached data
{
	if (GetData() != _atltmpXtmpDataNil)
	{
		if (InterlockedDecrement(&GetData()->nRefs) <= 0)
			delete[] (BYTE*)GetData();
	}
}

inline void CWTLString::AllocCopy(CWTLString& dest, int nCopyLen, int nCopyIndex,
	 int nExtraLen) const
{
	// will clone the data attached to this string
	// allocating 'nExtraLen' characters
	// Places results in uninitialized string 'dest'
	// Will copy the part or all of original data to start of new string

	int nNewLen = nCopyLen + nExtraLen;
	if (nNewLen == 0)
	{
		dest.Init();
	}
	else
	{
		if(dest.AllocBuffer(nNewLen))
			memcpy(dest.m_pchData, m_pchData + nCopyIndex, nCopyLen * sizeof(TCHAR));
	}
}

inline CWTLString::CWTLString(LPCTSTR lpsz)
{
	Init();
	if (lpsz != NULL && HIWORD(lpsz) == NULL)
	{
		UINT nID = LOWORD((DWORD_PTR)lpsz);
		if (!LoadString(nID))
		{
			//TRACE(_T("Warning: implicit LoadString(%u) in CWTLString failed\n"), nID);
		}
	}
	else
	{
		int nLen = SafeStrlen(lpsz);
		if (nLen != 0)
		{
			if(AllocBuffer(nLen))
				memcpy(m_pchData, lpsz, nLen * sizeof(TCHAR));
		}
	}
}

#ifdef _UNICODE
inline CWTLString::CWTLString(LPCSTR lpsz)
{
	Init();
	int nSrcLen = (lpsz != NULL) ? lstrlenA(lpsz) : 0;
	if (nSrcLen != 0)
	{
		if(AllocBuffer(nSrcLen))
		{
			_mbstowcsz(m_pchData, lpsz, nSrcLen + 1);
			ReleaseBuffer();
		}
	}
}
#else //_UNICODE
inline CWTLString::CWTLString(LPCWSTR lpsz)
{
	Init();
	int nSrcLen = (lpsz != NULL) ? (int)wcslen(lpsz) : 0;
	if (nSrcLen != 0)
	{
		if(AllocBuffer(nSrcLen * 2))
		{
			_wcstombsz(m_pchData, lpsz, (nSrcLen * 2) + 1);
			ReleaseBuffer();
		}
	}
}
#endif //!_UNICODE

// Assignment operators
//  All assign a new value to the string
//      (a) first see if the buffer is big enough
//      (b) if enough room, copy on top of old buffer, set size and type
//      (c) otherwise free old string data, and create a new one
//
//  All routines return the new string (but as a 'const CWTLString&' so that
//      assigning it again will cause a copy, eg: s1 = s2 = "hi there".
//

inline void CWTLString::AssignCopy(int nSrcLen, LPCTSTR lpszSrcData)
{
	if(AllocBeforeWrite(nSrcLen))
	{
		memcpy(m_pchData, lpszSrcData, nSrcLen * sizeof(TCHAR));
		GetData()->nDataLength = nSrcLen;
		m_pchData[nSrcLen] = '\0';
	}
}

inline const CWTLString& CWTLString::operator =(const CWTLString& stringSrc)
{
	if (m_pchData != stringSrc.m_pchData)
	{
		if ((GetData()->nRefs < 0 && GetData() != _atltmpXtmpDataNil) || stringSrc.GetData()->nRefs < 0)
		{
			// actual copy necessary since one of the strings is locked
			AssignCopy(stringSrc.GetData()->nDataLength, stringSrc.m_pchData);
		}
		else
		{
			// can just copy references around
			Release();
			_ASSERTE(stringSrc.GetData() != _atltmpXtmpDataNil);
			m_pchData = stringSrc.m_pchData;
			InterlockedIncrement(&GetData()->nRefs);
		}
	}
	return *this;
}

inline const CWTLString& CWTLString::operator =(LPCTSTR lpsz)
{
	_ASSERTE(lpsz == NULL || _IsValidString(lpsz));
	AssignCopy(SafeStrlen(lpsz), lpsz);
	return *this;
}

#ifdef _UNICODE
inline const CWTLString& CWTLString::operator =(LPCSTR lpsz)
{
	int nSrcLen = (lpsz != NULL) ? lstrlenA(lpsz) : 0;
	if(AllocBeforeWrite(nSrcLen))
	{
		_mbstowcsz(m_pchData, lpsz, nSrcLen + 1);
		ReleaseBuffer();
	}
	return *this;
}
#else //!_UNICODE
inline const CWTLString& CWTLString::operator =(LPCWSTR lpsz)
{
	int nSrcLen = (lpsz != NULL) ? (int)wcslen(lpsz) : 0;
	if(AllocBeforeWrite(nSrcLen * 2))
	{
		_wcstombsz(m_pchData, lpsz, (nSrcLen * 2) + 1);
		ReleaseBuffer();
	}
	return *this;
}
#endif  //!_UNICODE

// Concatenation
// NOTE: "operator +" is done as friend functions for simplicity
//      There are three variants:
//          CWTLString + CWTLString
// and for ? = TCHAR, LPCTSTR
//          CWTLString + ?
//          ? + CWTLString

inline BOOL CWTLString::ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data,
	int nSrc2Len, LPCTSTR lpszSrc2Data)
{
  // -- master concatenation routine
  // Concatenate two sources
  // -- assume that 'this' is a new CWTLString object

	BOOL bRet = TRUE;
	int nNewLen = nSrc1Len + nSrc2Len;
	if (nNewLen != 0)
	{
		bRet = AllocBuffer(nNewLen);
		if (bRet)
		{
			memcpy(m_pchData, lpszSrc1Data, nSrc1Len * sizeof(TCHAR));
			memcpy(m_pchData + nSrc1Len, lpszSrc2Data, nSrc2Len * sizeof(TCHAR));
		}
	}
	return bRet;
}

inline CWTLString __stdcall operator +(const CWTLString& string1, const CWTLString& string2)
{
	CWTLString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, string2.GetData()->nDataLength, string2.m_pchData);
	return s;
}

inline CWTLString __stdcall operator +(const CWTLString& string, LPCTSTR lpsz)
{
	_ASSERTE(lpsz == NULL || CWTLString::_IsValidString(lpsz));
	CWTLString s;
	s.ConcatCopy(string.GetData()->nDataLength, string.m_pchData, CWTLString::SafeStrlen(lpsz), lpsz);
	return s;
}

inline CWTLString __stdcall operator +(LPCTSTR lpsz, const CWTLString& string)
{
	_ASSERTE(lpsz == NULL || CWTLString::_IsValidString(lpsz));
	CWTLString s;
	s.ConcatCopy(CWTLString::SafeStrlen(lpsz), lpsz, string.GetData()->nDataLength, string.m_pchData);
	return s;
}

inline void CWTLString::ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData)
{
	//  -- the main routine for += operators

	// concatenating an empty string is a no-op!
	if (nSrcLen == 0)
		return;

	// if the buffer is too small, or we have a width mis-match, just
	//   allocate a new buffer (slow but sure)
	if (GetData()->nRefs > 1 || GetData()->nDataLength + nSrcLen > GetData()->nAllocLength)
	{
		// we have to grow the buffer, use the ConcatCopy routine
		CWTLStringData* pOldData = GetData();
		if (ConcatCopy(GetData()->nDataLength, m_pchData, nSrcLen, lpszSrcData))
		{
			_ASSERTE(pOldData != NULL);
			CWTLString::Release(pOldData);
		}
	}
	else
	{
		// fast concatenation when buffer big enough
		memcpy(m_pchData + GetData()->nDataLength, lpszSrcData, nSrcLen * sizeof(TCHAR));
		GetData()->nDataLength += nSrcLen;
		_ASSERTE(GetData()->nDataLength <= GetData()->nAllocLength);
		m_pchData[GetData()->nDataLength] = '\0';
	}
}

inline const CWTLString& CWTLString::operator +=(LPCTSTR lpsz)
{
	_ASSERTE(lpsz == NULL || _IsValidString(lpsz));
	ConcatInPlace(SafeStrlen(lpsz), lpsz);
	return *this;
}

inline const CWTLString& CWTLString::operator +=(TCHAR ch)
{
	ConcatInPlace(1, &ch);
	return *this;
}

inline const CWTLString& CWTLString::operator +=(const CWTLString& string)
{
	ConcatInPlace(string.GetData()->nDataLength, string.m_pchData);
	return *this;
}

inline LPTSTR CWTLString::GetBuffer(int nMinBufLength)
{
	_ASSERTE(nMinBufLength >= 0);

	if (GetData()->nRefs > 1 || nMinBufLength > GetData()->nAllocLength)
	{
		// we have to grow the buffer
		CWTLStringData* pOldData = GetData();
		int nOldLen = GetData()->nDataLength;   // AllocBuffer will tromp it
		if (nMinBufLength < nOldLen)
			nMinBufLength = nOldLen;

		if(!AllocBuffer(nMinBufLength))
			return NULL;

		memcpy(m_pchData, pOldData->data(), (nOldLen + 1) * sizeof(TCHAR));
		GetData()->nDataLength = nOldLen;
		CWTLString::Release(pOldData);
	}
	_ASSERTE(GetData()->nRefs <= 1);

	// return a pointer to the character storage for this string
	_ASSERTE(m_pchData != NULL);
	return m_pchData;
}

inline void CWTLString::ReleaseBuffer(int nNewLength)
{
	CopyBeforeWrite();  // just in case GetBuffer was not called

	if (nNewLength == -1)
		nNewLength = lstrlen(m_pchData); // zero terminated

	_ASSERTE(nNewLength <= GetData()->nAllocLength);
	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
}

inline LPTSTR CWTLString::GetBufferSetLength(int nNewLength)
{
	_ASSERTE(nNewLength >= 0);

	if(GetBuffer(nNewLength) == NULL)
		return NULL;

	GetData()->nDataLength = nNewLength;
	m_pchData[nNewLength] = '\0';
	return m_pchData;
}

inline void CWTLString::FreeExtra()
{
	_ASSERTE(GetData()->nDataLength <= GetData()->nAllocLength);
	if (GetData()->nDataLength != GetData()->nAllocLength)
	{
		CWTLStringData* pOldData = GetData();
		if(AllocBuffer(GetData()->nDataLength))
		{
			memcpy(m_pchData, pOldData->data(), pOldData->nDataLength * sizeof(TCHAR));
			_ASSERTE(m_pchData[GetData()->nDataLength] == '\0');
			CWTLString::Release(pOldData);
		}
	}
	_ASSERTE(GetData() != NULL);
}

inline LPTSTR CWTLString::LockBuffer()
{
	LPTSTR lpsz = GetBuffer(0);
	if(lpsz != NULL)
		GetData()->nRefs = -1;
	return lpsz;
}

inline void CWTLString::UnlockBuffer()
{
	_ASSERTE(GetData()->nRefs == -1);
	if (GetData() != _atltmpXtmpDataNil)
		GetData()->nRefs = 1;
}

inline int CWTLString::Find(TCHAR ch) const
{
	return Find(ch, 0);
}

inline int CWTLString::Find(TCHAR ch, int nStart) const
{
	int nLength = GetData()->nDataLength;
	if (nStart >= nLength)
		return -1;

	// find first single character
	LPTSTR lpsz = _cstrchr(m_pchData + nStart, (_TUCHAR)ch);

	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

inline int CWTLString::FindOneOf(LPCTSTR lpszCharSet) const
{
	_ASSERTE(_IsValidString(lpszCharSet));
	LPTSTR lpsz = _cstrpbrk(m_pchData, lpszCharSet);
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

inline void CWTLString::MakeUpper()
{
	CopyBeforeWrite();
	CharUpper(m_pchData);
}

inline void CWTLString::MakeLower()
{
	CopyBeforeWrite();
	CharLower(m_pchData);
}

inline void CWTLString::MakeReverse()
{
	CopyBeforeWrite();
	_cstrrev(m_pchData);
}

inline void CWTLString::SetAt(int nIndex, TCHAR ch)
{
	_ASSERTE(nIndex >= 0);
	_ASSERTE(nIndex < GetData()->nDataLength);

	CopyBeforeWrite();
	m_pchData[nIndex] = ch;
}

#ifndef _UNICODE
inline void CWTLString::AnsiToOem()
{
	CopyBeforeWrite();
	::AnsiToOem(m_pchData, m_pchData);
}

inline void CWTLString::OemToAnsi()
{
	CopyBeforeWrite();
	::OemToAnsi(m_pchData, m_pchData);
}
#endif //_UNICODE

inline CWTLString::CWTLString(TCHAR ch, int nLength)
{
	_ASSERTE(!_istlead(ch));    // can't create a lead byte string
	Init();
	if (nLength >= 1)
	{
		if(AllocBuffer(nLength))
		{
#ifdef _UNICODE
			for (int i = 0; i < nLength; i++)
				m_pchData[i] = ch;
#else
			memset(m_pchData, ch, nLength);
#endif
		}
	}
}

inline CWTLString::CWTLString(LPCTSTR lpch, int nLength)
{
	Init();
	if (nLength != 0)
	{
		if(AllocBuffer(nLength))
			memcpy(m_pchData, lpch, nLength * sizeof(TCHAR));
	}
}

#ifdef _UNICODE
inline CWTLString::CWTLString(LPCSTR lpsz, int nLength)
{
	Init();
	if (nLength != 0)
	{
		if(AllocBuffer(nLength))
		{
			int n = ::MultiByteToWideChar(CP_ACP, 0, lpsz, nLength, m_pchData, nLength + 1);
			ReleaseBuffer((n >= 0) ? n : -1);
		}
	}
}
#else //_UNICODE
inline CWTLString::CWTLString(LPCWSTR lpsz, int nLength)
{
	Init();
	if (nLength != 0)
	{
		if(AllocBuffer(nLength * 2))
		{
			int n = ::WideCharToMultiByte(CP_ACP, 0, lpsz, nLength, m_pchData, (nLength * 2) + 1, NULL, NULL);
			ReleaseBuffer((n >= 0) ? n : -1);
		}
	}
}
#endif //!_UNICODE

inline const CWTLString& CWTLString::operator =(TCHAR ch)
{
	_ASSERTE(!_istlead(ch));    // can't set single lead byte
	AssignCopy(1, &ch);
	return *this;
}

inline CWTLString __stdcall operator +(const CWTLString& string1, TCHAR ch)
{
	CWTLString s;
	s.ConcatCopy(string1.GetData()->nDataLength, string1.m_pchData, 1, &ch);
	return s;
}

inline CWTLString __stdcall operator +(TCHAR ch, const CWTLString& string)
{
	CWTLString s;
	s.ConcatCopy(1, &ch, string.GetData()->nDataLength, string.m_pchData);
	return s;
}

inline CWTLString CWTLString::Mid(int nFirst) const
{
	return Mid(nFirst, GetData()->nDataLength - nFirst);
}

inline CWTLString CWTLString::Mid(int nFirst, int nCount) const
{
	// out-of-bounds requests return sensible things
	if (nFirst < 0)
		nFirst = 0;
	if (nCount < 0)
		nCount = 0;

	if (nFirst + nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength - nFirst;
	if (nFirst > GetData()->nDataLength)
		nCount = 0;

	CWTLString dest;
	AllocCopy(dest, nCount, nFirst, 0);
	return dest;
}

inline CWTLString CWTLString::Right(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	else if (nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength;

	CWTLString dest;
	AllocCopy(dest, nCount, GetData()->nDataLength-nCount, 0);
	return dest;
}

inline CWTLString CWTLString::Left(int nCount) const
{
	if (nCount < 0)
		nCount = 0;
	else if (nCount > GetData()->nDataLength)
		nCount = GetData()->nDataLength;

	CWTLString dest;
	AllocCopy(dest, nCount, 0, 0);
	return dest;
}

// strspn equivalent
inline CWTLString CWTLString::SpanIncluding(LPCTSTR lpszCharSet) const
{
	_ASSERTE(_IsValidString(lpszCharSet));
	return Left(_cstrspn(m_pchData, lpszCharSet));
}

// strcspn equivalent
inline CWTLString CWTLString::SpanExcluding(LPCTSTR lpszCharSet) const
{
	_ASSERTE(_IsValidString(lpszCharSet));
	return Left(_cstrcspn(m_pchData, lpszCharSet));
}

inline int CWTLString::ReverseFind(TCHAR ch) const
{
	// find last single character
	LPTSTR lpsz = _cstrrchr(m_pchData, (_TUCHAR)ch);

	// return -1 if not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

// find a sub-string (like strstr)
inline int CWTLString::Find(LPCTSTR lpszSub) const
{
	return Find(lpszSub, 0);
}

inline int CWTLString::Find(LPCTSTR lpszSub, int nStart) const
{
	_ASSERTE(_IsValidString(lpszSub));

	int nLength = GetData()->nDataLength;
	if (nStart > nLength)
		return -1;

	// find first matching substring
	LPTSTR lpsz = _cstrstr(m_pchData + nStart, lpszSub);

	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}

inline BOOL CWTLString::FormatV(LPCTSTR lpszFormat, va_list argList)
{
	_ASSERTE(_IsValidString(lpszFormat));

	enum _FormatModifiers
	{
		FORCE_ANSI =	0x10000,
		FORCE_UNICODE =	0x20000,
		FORCE_INT64 =	0x40000
	};

	va_list argListSave = argList;

	// make a guess at the maximum length of the resulting string
	int nMaxLen = 0;
	for (LPCTSTR lpsz = lpszFormat; *lpsz != '\0'; lpsz = ::CharNext(lpsz))
	{
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(lpsz = ::CharNext(lpsz)) == '%')
		{
			// this is instead of _tclen()
#if !defined(_UNICODE) && defined(_MBCS)
			nMaxLen += (int)(::CharNext(lpsz) - lpsz);
#else
			nMaxLen++;
#endif
			continue;
		}

		int nItemLen = 0;

		// handle '%' character with format
		int nWidth = 0;
		for (; *lpsz != '\0'; lpsz = ::CharNext(lpsz))
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLen += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' || *lpsz == ' ')
				;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)
		{
			// width indicated by
			nWidth = _cstrtoi(lpsz);
			for (; *lpsz != '\0' && _cstrisdigit(*lpsz); lpsz = ::CharNext(lpsz))
				;
		}
		_ASSERTE(nWidth >= 0);

		int nPrecision = 0;
		if (*lpsz == '.')
		{
			// skip past '.' separator (width.precision)
			lpsz = ::CharNext(lpsz);

			// get precision and skip it
			if (*lpsz == '*')
			{
				nPrecision = va_arg(argList, int);
				lpsz = ::CharNext(lpsz);
			}
			else
			{
				nPrecision = _cstrtoi(lpsz);
				for (; *lpsz != '\0' && _cstrisdigit(*lpsz); lpsz = ::CharNext(lpsz))
					;
			}
			_ASSERTE(nPrecision >= 0);
		}

		// should be on type modifier or specifier
		int nModifier = 0;
		if(lpsz[0] == _T('I') && lpsz[1] == _T('6') && lpsz[2] == _T('4'))
		{
			lpsz += 3;
			nModifier = FORCE_INT64;
		}
		else
		{
			switch (*lpsz)
			{
			// modifiers that affect size
			case 'h':
				nModifier = FORCE_ANSI;
				lpsz = ::CharNext(lpsz);
				break;
			case 'l':
				nModifier = FORCE_UNICODE;
				lpsz = ::CharNext(lpsz);
				break;

			// modifiers that do not affect size
			case 'F':
			case 'N':
			case 'L':
				lpsz = ::CharNext(lpsz);
				break;
			}
		}

		// now should be on specifier
		switch (*lpsz | nModifier)
		{
		// single characters
		case 'c':
		case 'C':
			nItemLen = 2;
			va_arg(argList, TCHAR);
			break;
		case 'c' | FORCE_ANSI:
		case 'C' | FORCE_ANSI:
			nItemLen = 2;
			va_arg(argList, char);
			break;
		case 'c' | FORCE_UNICODE:
		case 'C' | FORCE_UNICODE:
			nItemLen = 2;
			va_arg(argList, WCHAR);
			break;

		// strings
		case 's':
		{
			LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);
			if (pstrNextArg == NULL)
			{
				nItemLen = 6;  // "(null)"
			}
			else
			{
				nItemLen = lstrlen(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
			break;
		}

		case 'S':
		{
#ifndef _UNICODE
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
			if (pstrNextArg == NULL)
			{
				nItemLen = 6;  // "(null)"
			}
			else
			{
				nItemLen = (int)wcslen(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
#else //_UNICODE
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
			if (pstrNextArg == NULL)
			{
				nItemLen = 6; // "(null)"
			}
			else
			{
				nItemLen = lstrlenA(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
#endif //_UNICODE
			break;
		}

		case 's' | FORCE_ANSI:
		case 'S' | FORCE_ANSI:
		{
			LPCSTR pstrNextArg = va_arg(argList, LPCSTR);
			if (pstrNextArg == NULL)
			{
				nItemLen = 6; // "(null)"
			}
			else
			{
				nItemLen = lstrlenA(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
			break;
		}

		case 's' | FORCE_UNICODE:
		case 'S' | FORCE_UNICODE:
		{
			LPWSTR pstrNextArg = va_arg(argList, LPWSTR);
			if (pstrNextArg == NULL)
			{
				nItemLen = 6; // "(null)"
			}
			else
			{
				nItemLen = (int)wcslen(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
			break;
		}
		}

		// adjust nItemLen for strings
		if (nItemLen != 0)
		{
			nItemLen = max(nItemLen, nWidth);
			if (nPrecision != 0)
				nItemLen = min(nItemLen, nPrecision);
		}
		else
		{
			switch (*lpsz)
			{
			// integers
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
				if (nModifier & FORCE_INT64)
					va_arg(argList, __int64);
				else
					va_arg(argList, int);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth + nPrecision);
				break;

			case 'e':
			case 'E':
			case 'g':
			case 'G':
				va_arg(argList, double);
				nItemLen = 128;
				nItemLen = max(nItemLen, nWidth + nPrecision);
				break;
			case 'f':
				{
					double f;
					LPTSTR pszTemp;

					// 312 == strlen("-1+(309 zeroes).")
					// 309 zeroes == max precision of a double
					// 6 == adjustment in case precision is not specified,
					//   which means that the precision defaults to 6
					pszTemp = (LPTSTR)_alloca(max(nWidth, 312 + nPrecision + 6));

					f = va_arg(argList, double);
					_stprintf(pszTemp, _T( "%*.*f" ), nWidth, nPrecision + 6, f);
					nItemLen = _tcslen(pszTemp);
				}
				break;

			case 'p':
				va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth + nPrecision);
				break;

			// no output
			case 'n':
				va_arg(argList, int*);
				break;

			default:
				_ASSERTE(FALSE);  // unknown formatting option
				break;
			}
		}

		// adjust nMaxLen for output nItemLen
		nMaxLen += nItemLen;
	}

	if(GetBuffer(nMaxLen) == NULL)
		return FALSE;
	int nRet = _vstprintf(m_pchData, lpszFormat, argListSave);
	nRet;   // ref
	_ASSERTE(nRet <= GetAllocLength());
	ReleaseBuffer();

	va_end(argListSave);
	return TRUE;
}

// formatting (using wsprintf style formatting)
inline BOOL __cdecl CWTLString::Format(LPCTSTR lpszFormat, ...)
{
	_ASSERTE(_IsValidString(lpszFormat));

	va_list argList;
	va_start(argList, lpszFormat);
	BOOL bRet = FormatV(lpszFormat, argList);
	va_end(argList);
	return bRet;
}

inline BOOL __cdecl CWTLString::Format(UINT nFormatID, ...)
{
	CWTLString strFormat;
	BOOL bRet = strFormat.LoadString(nFormatID);
	_ASSERTE(bRet != 0);

	va_list argList;
	va_start(argList, nFormatID);
	bRet = FormatV(strFormat, argList);
	va_end(argList);
	return bRet;
}

// formatting (using FormatMessage style formatting)
inline BOOL __cdecl CWTLString::FormatMessage(LPCTSTR lpszFormat, ...)
{
	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, lpszFormat);
	LPTSTR lpszTemp;
	BOOL bRet = TRUE;

	if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			lpszFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 || lpszTemp == NULL)
		bRet = FALSE;

	// assign lpszTemp into the resulting string and free the temporary
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
	return bRet;
}

inline BOOL __cdecl CWTLString::FormatMessage(UINT /*nFormatID*/, ...)
{
	// LoadString not implemented
	return false;
#if 0  // -----------------------------------------------------------
	// get format string from string table
	CWTLString strFormat;
	BOOL bRetTmp = strFormat.LoadString(nFormatID);
	bRetTmp;   // ref
	_ASSERTE(bRetTmp != 0);

	// format message into temporary buffer lpszTemp
	va_list argList;
	va_start(argList, nFormatID);
	LPTSTR lpszTemp;
	BOOL bRet = TRUE;

	if (::FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			strFormat, 0, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 || lpszTemp == NULL)
		bRet = FALSE;

	// assign lpszTemp into the resulting string and free lpszTemp
	*this = lpszTemp;
	LocalFree(lpszTemp);
	va_end(argList);
	return bRet;
#endif // -----------------------------------------------------------
}

inline void CWTLString::Trim()
{
	TrimLeft();
	TrimRight();
}

inline void CWTLString::TrimRight()
{
	CopyBeforeWrite();

	// find beginning of trailing spaces by starting at beginning (DBCS aware)
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;
	while (*lpsz != '\0')
	{
		if (_cstrisspace(*lpsz))
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
		{
			lpszLast = NULL;
		}
		lpsz = ::CharNext(lpsz);
	}

	if (lpszLast != NULL)
	{
		// truncate at trailing space start
		*lpszLast = '\0';
		GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
	}
}

inline void CWTLString::TrimLeft()
{
	CopyBeforeWrite();

	// find first non-space character
	LPCTSTR lpsz = m_pchData;
	while (_cstrisspace(*lpsz))
		lpsz = ::CharNext(lpsz);

	// fix up data and length
	int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
	memmove(m_pchData, lpsz, (nDataLength + 1) * sizeof(TCHAR));
	GetData()->nDataLength = nDataLength;
}

inline void CWTLString::TrimRight(LPCTSTR lpszTargetList)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)

	CopyBeforeWrite();
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;

	while (*lpsz != '\0')
	{
		TCHAR* pNext = ::CharNext(lpsz);
		if(pNext > lpsz + 1)
		{
			if (_cstrchr_db(lpszTargetList, *lpsz, *(lpsz + 1)) != NULL)
			{
				if (lpszLast == NULL)
					lpszLast = lpsz;
			}
			else
			{
				lpszLast = NULL;
			}
		}
		else
		{
			if (_cstrchr(lpszTargetList, *lpsz) != NULL)
			{
				if (lpszLast == NULL)
					lpszLast = lpsz;
			}
			else
			{
				lpszLast = NULL;
			}
		}

		lpsz = pNext;
	}

	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
	}
}

inline void CWTLString::TrimRight(TCHAR chTarget)
{
	// find beginning of trailing matches
	// by starting at beginning (DBCS aware)

	CopyBeforeWrite();
	LPTSTR lpsz = m_pchData;
	LPTSTR lpszLast = NULL;

	while (*lpsz != '\0')
	{
		if (*lpsz == chTarget)
		{
			if (lpszLast == NULL)
				lpszLast = lpsz;
		}
		else
			lpszLast = NULL;
		lpsz = ::CharNext(lpsz);
	}

	if (lpszLast != NULL)
	{
		// truncate at left-most matching character
		*lpszLast = '\0';
		GetData()->nDataLength = (int)(DWORD_PTR)(lpszLast - m_pchData);
	}
}

inline void CWTLString::TrimLeft(LPCTSTR lpszTargets)
{
	// if we're not trimming anything, we're not doing any work
	if (SafeStrlen(lpszTargets) == 0)
		return;

	CopyBeforeWrite();
	LPCTSTR lpsz = m_pchData;

	while (*lpsz != '\0')
	{
		TCHAR* pNext = ::CharNext(lpsz);
		if(pNext > lpsz + 1)
		{
			if (_cstrchr_db(lpszTargets, *lpsz, *(lpsz + 1)) == NULL)
				break;
		}
		else
		{
			if (_cstrchr(lpszTargets, *lpsz) == NULL)
				break;
		}
		lpsz = pNext;
	}

	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength + 1) * sizeof(TCHAR));
		GetData()->nDataLength = nDataLength;
	}
}

inline void CWTLString::TrimLeft(TCHAR chTarget)
{
	// find first non-matching character

	CopyBeforeWrite();
	LPCTSTR lpsz = m_pchData;

	while (chTarget == *lpsz)
		lpsz = ::CharNext(lpsz);

	if (lpsz != m_pchData)
	{
		// fix up data and length
		int nDataLength = GetData()->nDataLength - (int)(DWORD_PTR)(lpsz - m_pchData);
		memmove(m_pchData, lpsz, (nDataLength + 1) * sizeof(TCHAR));
		GetData()->nDataLength = nDataLength;
	}
}

inline int CWTLString::Delete(int nIndex, int nCount /* = 1 */)
{
	if (nIndex < 0)
		nIndex = 0;
	int nLength = GetData()->nDataLength;
	if (nCount > 0 && nIndex < nLength)
	{
		if((nIndex + nCount) > nLength)
			nCount = nLength - nIndex;
		CopyBeforeWrite();
		int nBytesToCopy = nLength - (nIndex + nCount) + 1;

		memmove(m_pchData + nIndex, m_pchData + nIndex + nCount, nBytesToCopy * sizeof(TCHAR));
		nLength -= nCount;
		GetData()->nDataLength = nLength;
	}

	return nLength;
}

inline int CWTLString::Insert(int nIndex, TCHAR ch)
{
	CopyBeforeWrite();

	if (nIndex < 0)
		nIndex = 0;

	int nNewLength = GetData()->nDataLength;
	if (nIndex > nNewLength)
		nIndex = nNewLength;
	nNewLength++;

	if (GetData()->nAllocLength < nNewLength)
	{
		CWTLStringData* pOldData = GetData();
		LPTSTR pstr = m_pchData;
		if(!AllocBuffer(nNewLength))
			return -1;
		memcpy(m_pchData, pstr, (pOldData->nDataLength + 1) * sizeof(TCHAR));
		CWTLString::Release(pOldData);
	}

	// move existing bytes down
	memmove(m_pchData + nIndex + 1, m_pchData + nIndex, (nNewLength - nIndex) * sizeof(TCHAR));
	m_pchData[nIndex] = ch;
	GetData()->nDataLength = nNewLength;

	return nNewLength;
}

inline int CWTLString::Insert(int nIndex, LPCTSTR pstr)
{
	if (nIndex < 0)
		nIndex = 0;

	int nInsertLength = SafeStrlen(pstr);
	int nNewLength = GetData()->nDataLength;
	if (nInsertLength > 0)
	{
		CopyBeforeWrite();
		if (nIndex > nNewLength)
			nIndex = nNewLength;
		nNewLength += nInsertLength;

		if (GetData()->nAllocLength < nNewLength)
		{
			CWTLStringData* pOldData = GetData();
			LPTSTR pstr = m_pchData;
			if(!AllocBuffer(nNewLength))
				return -1;
			memcpy(m_pchData, pstr, (pOldData->nDataLength + 1) * sizeof(TCHAR));
			CWTLString::Release(pOldData);
		}

		// move existing bytes down
		memmove(m_pchData + nIndex + nInsertLength, m_pchData + nIndex, (nNewLength - nIndex - nInsertLength + 1) * sizeof(TCHAR));
		memcpy(m_pchData + nIndex, pstr, nInsertLength * sizeof(TCHAR));
		GetData()->nDataLength = nNewLength;
	}

	return nNewLength;
}

inline int CWTLString::Replace(TCHAR chOld, TCHAR chNew)
{
	int nCount = 0;

	// short-circuit the nop case
	if (chOld != chNew)
	{
		// otherwise modify each character that matches in the string
		CopyBeforeWrite();
		LPTSTR psz = m_pchData;
		LPTSTR pszEnd = psz + GetData()->nDataLength;
		while (psz < pszEnd)
		{
			// replace instances of the specified character only
			if (*psz == chOld)
			{
				*psz = chNew;
				nCount++;
			}
			psz = ::CharNext(psz);
		}
	}
	return nCount;
}

inline int CWTLString::Replace(LPCTSTR lpszOld, LPCTSTR lpszNew)
{
	// can't have empty or NULL lpszOld

	int nSourceLen = SafeStrlen(lpszOld);
	if (nSourceLen == 0)
		return 0;
	int nReplacementLen = SafeStrlen(lpszNew);

	// loop once to figure out the size of the result string
	int nCount = 0;
	LPTSTR lpszStart = m_pchData;
	LPTSTR lpszEnd = m_pchData + GetData()->nDataLength;
	LPTSTR lpszTarget;
	while (lpszStart < lpszEnd)
	{
		while ((lpszTarget = _cstrstr(lpszStart, lpszOld)) != NULL)
		{
			nCount++;
			lpszStart = lpszTarget + nSourceLen;
		}
		lpszStart += lstrlen(lpszStart) + 1;
	}

	// if any changes were made, make them
	if (nCount > 0)
	{
		CopyBeforeWrite();

		// if the buffer is too small, just
		//   allocate a new buffer (slow but sure)
		int nOldLength = GetData()->nDataLength;
		int nNewLength =  nOldLength + (nReplacementLen - nSourceLen) * nCount;
		if (GetData()->nAllocLength < nNewLength || GetData()->nRefs > 1)
		{
			CWTLStringData* pOldData = GetData();
			LPTSTR pstr = m_pchData;
			if(!AllocBuffer(nNewLength))
				return -1;
			memcpy(m_pchData, pstr, pOldData->nDataLength * sizeof(TCHAR));
			CWTLString::Release(pOldData);
		}
		// else, we just do it in-place
		lpszStart = m_pchData;
		lpszEnd = m_pchData + GetData()->nDataLength;

		// loop again to actually do the work
		while (lpszStart < lpszEnd)
		{
			while ( (lpszTarget = _cstrstr(lpszStart, lpszOld)) != NULL)
			{
				int nBalance = nOldLength - ((int)(DWORD_PTR)(lpszTarget - m_pchData) + nSourceLen);
				memmove(lpszTarget + nReplacementLen, lpszTarget + nSourceLen, nBalance * sizeof(TCHAR));
				memcpy(lpszTarget, lpszNew, nReplacementLen * sizeof(TCHAR));
				lpszStart = lpszTarget + nReplacementLen;
				lpszStart[nBalance] = '\0';
				nOldLength += (nReplacementLen - nSourceLen);
			}
			lpszStart += lstrlen(lpszStart) + 1;
		}
		_ASSERTE(m_pchData[nNewLength] == '\0');
		GetData()->nDataLength = nNewLength;
	}

	return nCount;
}

inline int CWTLString::Remove(TCHAR chRemove)
{
	CopyBeforeWrite();

	LPTSTR pstrSource = m_pchData;
	LPTSTR pstrDest = m_pchData;
	LPTSTR pstrEnd = m_pchData + GetData()->nDataLength;

	while (pstrSource < pstrEnd)
	{
		if (*pstrSource != chRemove)
		{
			*pstrDest = *pstrSource;
			pstrDest = ::CharNext(pstrDest);
		}
		pstrSource = ::CharNext(pstrSource);
	}
	*pstrDest = '\0';
	int nCount = (int)(DWORD_PTR)(pstrSource - pstrDest);
	GetData()->nDataLength -= nCount;

	return nCount;
}

#ifdef _UNICODE
  #define CHAR_FUDGE 1    // one TCHAR unused is good enough
#else
  #define CHAR_FUDGE 2    // two BYTES unused for case of DBC last char
#endif

inline BOOL CWTLString::LoadString(UINT /*nID*/)
{
	// LoadString not implemented
	return false;
#if 0  // -----------------------------------------------------------
	// try fixed buffer first (to avoid wasting space in the heap)
	TCHAR szTemp[256];
	int nCount =  sizeof(szTemp) / sizeof(szTemp[0]);
	int nLen = _LoadString(nID, szTemp, nCount);
	if (nCount - nLen > CHAR_FUDGE)
	{
		*this = szTemp;
		return (nLen > 0);
	}

	// try buffer size of 512, then larger size until entire string is retrieved
	int nSize = 256;
	do
	{
		nSize += 256;
		LPTSTR lpstr = GetBuffer(nSize - 1);
		if(lpstr == NULL)
		{
			nLen = 0;
			break;
		}
		nLen = _LoadString(nID, lpstr, nSize);
	} while (nSize - nLen <= CHAR_FUDGE);
	ReleaseBuffer();

	return (nLen > 0);
#endif // -----------------------------------------------------------
}

///////////////////////////////////////////////////////////////////////////////
// Global function for compacting a path by replacing parts with ellipsis

// helper for multi-byte character sets
inline bool _IsDBCSTrailByte(LPCTSTR lpstr, int nChar)
{
#ifndef _UNICODE
	int i = nChar;
	for( ; i > 0; i--)
	{
		if(!::IsDBCSLeadByte(lpstr[i - 1]))
			break;
	}
	return ((nChar > 0) && (((nChar - i) & 1) != 0));
#else //_UNICODE
	lpstr; nChar;
	return false;
#endif //_UNICODE
}

inline bool AtlCompactPath(LPTSTR lpstrOut, LPCTSTR lpstrIn, int cchLen)
{
	_ASSERTE(lpstrOut != NULL);
	_ASSERTE(lpstrIn != NULL);
	_ASSERTE(cchLen > 0);

	LPCTSTR szEllipsis = _T("...");
	const int cchEndEllipsis = 3;
	const int cchMidEllipsis = 4;

	if(lstrlen(lpstrIn) + 1 < cchLen)
		return (lstrcpy(lpstrOut, lpstrIn) != NULL);

	lpstrOut[0] = 0;

	// check if the separator is a slash or a backslash
	TCHAR chSlash = _T('\\');
	for(LPTSTR lpstr = (LPTSTR)lpstrIn; *lpstr != 0; lpstr = ::CharNext(lpstr))
	{
		if((*lpstr == _T('/')) || (*lpstr == _T('\\')))
			chSlash = *lpstr;
	}

	// find the filename portion of the path
	LPCTSTR lpstrFileName = lpstrIn;
	for(LPCTSTR pPath = lpstrIn; *pPath; pPath = ::CharNext(pPath))
	{
		if((pPath[0] == _T('\\') || pPath[0] == _T(':') || pPath[0] == _T('/'))
				&& pPath[1] && pPath[1] != _T('\\') && pPath[1] != _T('/'))
			lpstrFileName = pPath + 1;
	}
	int cchFileName = lstrlen(lpstrFileName);

	// handle just the filename without a path
	if(lpstrFileName == lpstrIn && cchLen > cchEndEllipsis)
	{
		bool bRet = (lstrcpyn(lpstrOut, lpstrIn, cchLen - cchEndEllipsis) != NULL);
		if(bRet)
		{
#ifndef _UNICODE
			if(_IsDBCSTrailByte(lpstrIn, cchLen - cchEndEllipsis))
				lpstrOut[cchLen - cchEndEllipsis - 1] = 0;
#endif //_UNICODE
			bRet = (lstrcat(lpstrOut, szEllipsis) != NULL);
		}
		return bRet;
	}

	// handle just ellipsis
	if((cchLen < (cchMidEllipsis + cchEndEllipsis)))
	{
		for(int i = 0; i < cchLen - 1; i++)
			lpstrOut[i] = ((i + 1) == cchMidEllipsis) ? chSlash : _T('.');
		lpstrOut[cchLen - 1] = 0;
		return true;
	}

	// calc how much we have to copy
	int cchToCopy = cchLen - (cchMidEllipsis + cchFileName);

	if(cchToCopy < 0)
		cchToCopy = 0;

#ifndef _UNICODE
	if(cchToCopy > 0 && _IsDBCSTrailByte(lpstrIn, cchToCopy))
		cchToCopy--;
#endif //_UNICODE

	bool bRet = (lstrcpyn(lpstrOut, lpstrIn, cchToCopy) != NULL);
	if(!bRet)
		return false;

	// add ellipsis
	bRet = (lstrcat(lpstrOut, szEllipsis) != NULL);
	if(!bRet)
		return false;
	TCHAR szSlash[2] = { chSlash, 0 };
	bRet = (lstrcat(lpstrOut, szSlash) != NULL);
	if(!bRet)
		return false;

	// add filename (and ellipsis, if needed)
	if(cchLen > (cchMidEllipsis + cchFileName))
	{
		bRet = (lstrcat(lpstrOut, lpstrFileName) != NULL);
	}
	else
	{
		cchToCopy = cchLen - cchMidEllipsis - cchEndEllipsis;
#ifndef _UNICODE
		if(cchToCopy > 0 && _IsDBCSTrailByte(lpstrFileName, cchToCopy))
			cchToCopy--;
#endif //_UNICODE
		bRet = (lstrcpyn(&lpstrOut[cchMidEllipsis], lpstrFileName, cchToCopy) != NULL);
		if(bRet)
			bRet = (lstrcat(lpstrOut, szEllipsis) != NULL);
	}

	return bRet;
}

#pragma warning(pop)

#endif // WTLSTRING_H

