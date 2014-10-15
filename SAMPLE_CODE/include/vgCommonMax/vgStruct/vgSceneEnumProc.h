
#ifndef _VGSCENEENUMPROC_H_INCLUDED_
#define _VGSCENEENUMPROC_H_INCLUDED_

#include "vgStableHeaders.h"

#include <vgStruct/vgSceneObjectEntry.h>
#include <vgStruct/vgMeshMtlList.h>

#if	IMPORT_MAX_LIB

class SceneEntry;
class MeshMtlList;

class SceneEnumProc /*: public ITreeEnumProc*/ {
public:
	Interface	*i;
	SceneEntry *head;
	SceneEntry *tail;
	//IScene		*theScene;
	int			count;
	MeshMtlList *mtlList;
	TimeValue	time;
	SceneEnumProc(/*IScene *scene,TimeValue t, */INode* pRootNode
		,Interface *i, MeshMtlList *ml
		,bool exportSelected);

	SceneEnumProc( vector<INode*>* pRootNodes
		,Interface *i, MeshMtlList *ml
		,bool exportSelected);

	SceneEnumProc(Interface *i, MeshMtlList *ml
		,bool exportSelected);

	~SceneEnumProc();
	int			Count() { return count; }
	void		Append(INode *node, Object *obj, int type);
	int			callback( INode *node );
	Box3		Bound();
	SceneEntry *Find(INode *node);
	//		SceneEntry *operator[](int index);
	void BuildNames();

public:
	void		enumScene(INode *node);

protected:
	bool exportSelected;
};

#endif	//_VGSCENEENUMPROC_H_INCLUDED_
#endif
