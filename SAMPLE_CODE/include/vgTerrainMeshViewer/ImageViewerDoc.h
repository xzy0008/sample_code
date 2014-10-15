/****************************************************************************
ImageViewerDoc.h : Header file for the CImageViewerDoc class
written by PJ Arends
pja@telus.net

For updates check http://www.codeproject.com/tools/imageviewer.asp

-----------------------------------------------------------------------------
This code is provided as is, with no warranty as to it's suitability or usefulness
in any application in which it may be used.

This code may be used in any way you desire. This file may be redistributed by any
means as long as it is not sold for profit, and providing that this notice and the
author's name are included. Any modifications not made by the original author should
be clearly marked as such to remove any confusion between the original version and
any other versions.

If any bugs are found and fixed, a note to the author explaining the problem and
fix would be nice.
-----------------------------------------------------------------------------
****************************************************************************/

#pragma once

#include "ImageData.h"
#include <vector>

#include <vgTerritory/vgVgtrFile.h>

class CDeletedImageData : public CObject
{
    // Used by CImageViewerDoc::DeleteImageData() to inform the it's
    // CImageViewerView views what images have been deleted. A pointer
    // to an instance of this class is used as the pHint variable
    // in CDocument::UpdateAllViews() and CView::OnUpdate().
public:
    size_t StartRange;  // first image deleted
    size_t EndRange;    // last image deleted
    size_t CountLeft;   // count of images still in the document

    CDeletedImageData() { StartRange = 0; EndRange = 0; CountLeft = 0; }
};

class CImageViewerDoc : public CDocument
{
protected: // create from serialization only
    CImageViewerDoc();
    DECLARE_DYNCREATE(CImageViewerDoc)

// Attributes
protected:
    typedef std::vector<CImageData> ImageDataVector;

    ImageDataVector Images;
    std::tstring Caption;
    DWORD ProcessID;

    bool IsImageFile;
// Operations
public:

// Overrides
public:
    virtual BOOL OnNewDocument();
    virtual void OnCloseDocument();
    virtual void Serialize(CArchive& ar);
    virtual void DeleteContents();

// Implementation
public:
    virtual ~CImageViewerDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
    std::tstring GetModuleBaseName(HANDLE hProcess, HMODULE hModule) const;
    bool LoadImageFile(CString FilePath);

	bool LoadLodImageFile( const vgTerritory::VgtrFilePtr vgtr , const long& lod );

    afx_msg void OnFileSaveAs();
    afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
    DECLARE_MESSAGE_MAP()

public:
    void AddImageData(const CImageData &ImagaData);
    CImageData *GetImageData(size_t Index);
    size_t GetImageDataCount() const;
    void DeleteImageData(size_t First, size_t Last = 0);

    void SetCaption(DWORD ID);
    std::tstring GetCaption() { return Caption; }
};


