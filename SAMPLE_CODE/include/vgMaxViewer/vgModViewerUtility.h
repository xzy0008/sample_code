
#ifndef __VGMODVIEWERUTILITY__H
#define __VGMODVIEWERUTILITY__H

#include "vgStableHeaders.h"
#include "vgMaxViewer.h"


//extern ClassDesc* GetCollectionDesc();
//extern UtilityObj* GetCollectionUtility();

class vgModViewerUtility
{
public:
	static	bool	exportMODAndSave();
	static	bool	exportMODAndView();
	static	bool	exportMODThenView();
	static	bool	exportMODAndCollect();

public:
	static	bool	getFlagPromptDisable();
	static	uint	getExportOption();
	static	void	setFlagPromptDisable(bool bPromptDisable);
	static	void	setExportOption(uint uiExportOption);
	static	void	appendExportOption(uint uiExportOption);

	static	bool	getFlagSelectedOnly();
	static	void	setFlagSelectedOnly(bool bSelected);
	static	void	configSelectedOnlyDefault();

	//static	ClassDesc* getCollectionDesc();
	//static	void	setCollectionDesc(CollectionClassDesc* desc);
	static	Collection* getCollectionUtility();
	static	void	setCollectionUtility(Collection* uti);

public:
	static	void	calculateBoxBySelf();

protected:
	static  bool	exportMODCommon();
	static void TraverseNode(INode* node, TimeValue t);
	static void SelectAllNode(INode* node, TimeValue time);
	static  bool	exportByMax(string filepath);

private:
	static	bool	_bPromptDisable;// true: means setting options by oneself, will not utility default option 
	static	uint	_uiExportOption;
	static	bool	_bSelectedOnly;
	static  Class_ID _class_ID;

	static  CollectionClassDesc*	_classDesc;
	static  Collection*				_utiObj;

};//class vgModViewerUtility


#endif//__VGMODVIEWERUTILITY__H