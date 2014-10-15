
#include "vgStableHeaders.h"
#include <vgStruct/vgSceneEnumProc.h>

#if	IMPORT_MAX_LIB

SceneEnumProc::SceneEnumProc(/*IScene *scene, TimeValue t,*/ INode* pRootNode
							 , Interface *i
							 , MeshMtlList *ml
							 , bool exportSelected) {
	time = i->GetTime();
	//theScene = scene;
	count = 0;
	head = tail = NULL;
	this->i = i;
	mtlList = ml;
	this->exportSelected = exportSelected;
	
	enumScene(pRootNode);
}

SceneEnumProc::SceneEnumProc(vector<INode*>* pRootNodes
							 , Interface *i
							 , MeshMtlList *ml
							 , bool exportSelected) 
{
	time = i->GetTime();
	count = 0;
	head = tail = NULL;
	this->i = i;
	mtlList = ml;
	this->exportSelected = exportSelected;

	for (vector<INode*>::iterator itr = pRootNodes->begin();
		itr != pRootNodes->end(); itr ++)
	{
		callback( *itr );
	}
}


SceneEnumProc::SceneEnumProc(Interface *i
							 , MeshMtlList *ml
							 , bool exportSelected) 
{
	time = i->GetTime();
	count = 0;
	head = tail = NULL;
	this->i = i;
	mtlList = ml;
	this->exportSelected = exportSelected;

	enumScene( i->GetRootNode() );
}


SceneEnumProc::~SceneEnumProc() {
	while(head) {
		SceneEntry *next = head->next;
		delete head;
		head = next;
	}
	head = tail = NULL;
	count = 0;	
}

int SceneEnumProc::callback(INode *node) 
{
	if(exportSelected && node->Selected() == FALSE)
		return TREE_CONTINUE;
	Object *obj = node->EvalWorldState(time).obj;
	if (obj == NULL)
	{
		return TREE_CONTINUE;
	}
	if (obj->CanConvertToType(triObjectClassID)) {
		Append(node, obj, OBTYPE_MESH);
		mtlList->AddMtl(node->GetMtl());
		return TREE_CONTINUE;
	}
	if (node->IsTarget()) {
		INode* ln = node->GetLookatNode();
		if (ln) {
			Object *lobj = ln->EvalWorldState(time).obj;
			switch(lobj->SuperClassID()) {
				case LIGHT_CLASS_ID:  Append(node, obj, OBTYPE_LTARGET); break;
				case CAMERA_CLASS_ID: Append(node, obj, OBTYPE_CTARGET); break;
			}
		}
		return TREE_CONTINUE;
	}
	switch (obj->SuperClassID()) { 
		/*case HELPER_CLASS_ID:
			if ( obj->ClassID()==Class_ID(DUMMY_CLASS_ID,0)) 
				Append(node, obj, OBTYPE_DUMMY);
			break;*/
		case LIGHT_CLASS_ID: {
			//TCHAR buf[SCHAR_MAX];
			if (obj->ClassID()==Class_ID(OMNI_LIGHT_CLASS_ID,0))
				Append(node, obj, OBTYPE_OMNILIGHT);
			if (obj->ClassID()==Class_ID(SPOT_LIGHT_CLASS_ID,0)) 
				Append(node, obj, OBTYPE_SPOTLIGHT);
			if (obj->ClassID()==Class_ID(DIR_LIGHT_CLASS_ID,0)) {
				//sprintf(buf, vgModUtility::GetString(IDS_DIR_LIGHT), node->GetName());
				//AddToMsgList(msgList, buf);
				//Append(node, obj, OBTYPE_SPOTLIGHT);
			}
			if (obj->ClassID()==Class_ID(FSPOT_LIGHT_CLASS_ID,0)) {
				//sprintf(buf, vgModUtility::GetString(IDS_FSPOT_LIGHT), node->GetName());
				//AddToMsgList(msgList, buf);
				//Append(node, obj, OBTYPE_SPOTLIGHT);
			}
			break;
							 }
		case CAMERA_CLASS_ID:
			if (obj->ClassID()==Class_ID(LOOKAT_CAM_CLASS_ID,0))
				Append(node, obj, OBTYPE_CAMERA);
			break;
	}
	return TREE_CONTINUE;	// Keep on enumeratin'!
}



void SceneEnumProc::Append(INode *node, Object *obj, int type) {
	SceneEntry *entry = new SceneEntry(node, obj, type);

	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}



Box3 SceneEnumProc::Bound() {
	Box3 bound;
	bound.Init();
	SceneEntry *e = head;
	ViewExp *vpt = i->GetViewport(NULL);
	while(e) {
		Box3 bb;
		e->obj->GetWorldBoundBox(time, e->node, vpt, bb);
		bound += bb;
		e = e->next;
	}
	return bound;
}

SceneEntry *SceneEnumProc::Find(INode *node) {
	SceneEntry *e = head;
	while(e) {
		if(e->node == node)
			return e;
		e = e->next;
	}
	return NULL;
}


void SceneEnumProc::BuildNames()
{
	ObjNameList nameList;
	SceneEntry *ptr = head;

	while (ptr) {
		//		if (ptr->node->IsTarget()) {
		//			ptr->name = _T("");
		//			}
		//		else {
		ptr->name = ptr->node->GetName();
		nameList.MakeUnique(ptr->name);		
		//			}
		ptr = ptr->next;
	}
}

void SceneEnumProc::enumScene( INode *node )
{
	int numChildren = node->NumberOfChildren();
	
	if (numChildren == 0)
	{
		callback(node);
	}
	else
	{
		for(int i=0; i<numChildren; i++)
			enumScene(node->GetChildNode(i));
	}

}

#endif
