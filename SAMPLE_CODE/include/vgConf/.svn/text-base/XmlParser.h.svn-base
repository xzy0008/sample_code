// XmlParser.h: interface for the CXmlParser class.

#ifndef XMLPARSER_H
#define XMLPARSER_H

//#ifdef __AFX_H__
//#define CWTLString CString
//#else
#include "wtlstring.h"
//#endif // __AFX_H__

#include "CLinkedList.h"

class CXmlElement;
typedef CLinkedList<CXmlElement> CXmlList;
typedef CLinkedListElement<CXmlElement> CXmlListElement;

//=============================================================================
class CXmlElement
//=============================================================================
{
public:
	CXmlElement() 
	{
		//TRACE(_T("in CXmlElement\n"));
		m_posFind = NULL;
		m_pParentElement = NULL;
	};

	virtual ~CXmlElement() 
	{
		//TRACE(_T("in ~CXmlElement <%s>\n"), m_strName);
		CXmlListElement *pos = m_ChildElements.GetFirst();
		while (pos != NULL && !pos->IsRoot())
		{
			CXmlListElement *posnext = pos->GetNext();
			pos->DeleteRemove();
			pos = posnext;
		}
	};

	CWTLString GetValue(LPCTSTR attribute);

	CWTLString			m_strName;
	CWTLString			m_strAttributes;
	CWTLString			m_strData;
	CWTLString			m_strFind;

	CXmlList			m_ChildElements;
	CXmlListElement *	m_posFind;
	CXmlElement *		m_pParentElement;
};

//=============================================================================
class CXmlParser
//=============================================================================
{
public:
	CXmlParser();
	virtual ~CXmlParser();

	BOOL Parse(LPCTSTR lpszString);

	// must be the same as CXmlProfile
	enum ENCODING { Default = 0, Ansi, Unicode };

	BOOL Load(LPCTSTR lpszFileName, ENCODING eEncoding = Default);
	BOOL Save(LPCTSTR lpszFileName, ENCODING eEncoding = Default);
	CXmlElement *GetFirstChild(CXmlElement *pElement);
	CXmlElement *GetRootElement() { return &m_RootElement; }
	CXmlElement * CXmlParser::GetNextSibling(CXmlElement *pElement);
	
	CXmlElement *FindElement(CXmlElement *pElement, LPCTSTR lpszName);
	CXmlElement *FindNextElement(CXmlElement *pElement);

	CXmlElement *AddElement(CXmlElement *pElement, 
							LPCTSTR lpszName, 
							LPCTSTR lpszAttributes = NULL,
							LPCTSTR lpszData = NULL);

	void DeleteContents();

protected:
	int ValidateTag(CWTLString& strTag, CWTLString& strResult);
	BOOL CreateTag(CXmlElement *pElement, CWTLString& strTag);
	CWTLString Generate(BOOL bUnicode);

	int				m_nLevel;
	CWTLString		m_strXml;
	CXmlElement		m_RootElement;
	CXmlElement *	m_pCurElement;
};

#endif //XMLPARSER_H
