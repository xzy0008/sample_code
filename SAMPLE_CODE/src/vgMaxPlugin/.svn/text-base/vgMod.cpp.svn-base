#include <vgStableHeaders.h>
/**********************************************************************
*<
vgMod.cpp:	与模型几何信息相关的数据结构定义
主要内容是： class ObjNameList、class ObjectList和class SceneEnumProc的定义
*>	
**********************************************************************/
#include "vgMod.h"

//BOOL exportSelected;

//////////////////////////////////////////////////////////////////////////
//	class ObjNameList
ObjNameList::~ObjNameList() 
{
	while(head) {
		ObjName *next = head->next;
		delete head;
		head = next;
	}
	head = tail = NULL;
	count = 0;	
}

int ObjNameList::Contains(TSTR &n) 
{
	ObjName *e = head;
	int index = 0;
	while(e) {
		if(e->name == n)
			return index;
		e = e->next;
		index++;
	}
	return -1;
}

void ObjNameList::Append(TSTR &n) 
{
	ObjName *entry = new ObjName(n);
	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}


// 2008年1月22日15:20:45 刘寿生 修改——物体名字长度可含18个字节（18个数字字母或9个汉字）
void ObjNameList::MakeUnique(TSTR &str) 
{
	// First make it less than 20 chars.
	int sizeTemp ,iNum;

	sizeTemp = str.Length();
	
	if (str.Length()>OBJ_NAME_LENGTH) 
		str.Resize(OBJ_NAME_LENGTH);

	if(Contains(str) < 0) 
	{
		Append(str);
		return;
	}
	// Make it unique and keep it 20 chars or less
	for( iNum = 0; iNum < 100000; ++iNum) 
	{
		std::string prefixName = createPrefixName(str, iNum);
#if 1
		if ( iNum == 0 && containPrefix(prefixName) )
		{
			iNum += strRepeat[prefixName];
			continue;
		}
#endif 
		TSTR newName(prefixName.data());
		
		std::ostringstream appendixName;
		appendixName << iNum;
	
		newName += appendixName.str().data();

		if(Contains(newName) < 0) 
		{
			appendPrefix(prefixName, iNum);
			Append(newName);
			str = newName;
			return;
		}
	}
}
TSTR ObjNameList::createNewName(TSTR str, int id) 
{
	char bufNum[5];
	bufNum[0] = '\0';
	sprintf_s(bufNum,5,"%c%d%c",'0',id+1,'\0');
	TSTR num(bufNum);
	
	TSTR newName = str;
	
	int totlen = num.Length() + newName.Length();
	if(totlen > OBJ_NAME_LENGTH)
		newName.Resize(OBJ_NAME_LENGTH - (totlen - OBJ_NAME_LENGTH));
	newName = newName + num;

	return newName;
}
std::string ObjNameList::createPrefixName(TSTR str, int id) 
{
	std::ostringstream oStr;
	oStr << id;

	std::string tempStr(str.data());

	int totlen = tempStr.length() + oStr.str().length();
	if(totlen > OBJ_NAME_LENGTH)
		tempStr.resize(OBJ_NAME_LENGTH*2 - totlen);
	
	return tempStr;
}

bool ObjNameList::containPrefix( string& str )
{
	StrRepeatMapItr itr = strRepeat.find( str );
	if ( itr != strRepeat.end() )
	{
		return	true;
	}
	else
	{
		return	false;
	}
}

void ObjNameList::appendPrefix( string& str , int id)
{
	if ( containPrefix(str) )
	{
		if ( strRepeat[str] < id )
		{
			strRepeat[str] = id;
		}
		return;
	}

	strRepeat.insert( StrRepeatPair(str, id) );
}
///////////////////////////////////////////////////	class ObjNameList
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	class ObjectList
ObjectList::ObjectList(SceneEnumProc &scene) 
{
	head = tail = NULL;
	count = 0;

	int scount = scene.Count();
	for(SceneEntry *se = scene.head; se!=NULL; se = se->next) 
	{
		if ( (se->type!=OBTYPE_MESH)|| !Contains(se->obj))
			Append(se);
	}
}

ObjectList::~ObjectList() 
{
	while(head) {
		ObjectEntry *next = head->next;
		delete head;
		head = next;
	}
	head = tail = NULL;
	count = 0;	
}

ObjectEntry *ObjectList::Contains(Object *obj) 
{
	ObjectEntry *e;
	for (e=head; e!=NULL; e = e->next) {
		if(e->entry->obj == obj)
			return e;
	}
	return NULL;
}

ObjectEntry *ObjectList::Contains(INode *node) 
{
	ObjectEntry *e;
	for (e=head; e!=NULL; e = e->next) {
		if(e->entry->node == node)
			return e;
	}
	return NULL;
}

void ObjectList::Append(SceneEntry *e) 
{
	ObjectEntry *entry = new ObjectEntry(e);
	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}
/////////////////////////////////////////////////////	class ObjectList
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//	class SceneEnumProc
SceneEnumProc::SceneEnumProc(IScene *scene, TimeValue t, 
							 Interface *i, MeshMtlList *ml,
							 bool	bExportSelected) 
							 :exportSelected(bExportSelected)
{
	time = t;
	theScene = scene;
	count = 0;
	head = tail = NULL;
	this->i = i;
	mtlList = ml;
	theScene->EnumTree(this);
}

SceneEnumProc::~SceneEnumProc() 
{
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
	//static	int   nodeNumber;

	//nodeNumber ++;

	if( exportSelected && node->Selected() == FALSE)
		return TREE_CONTINUE;

	Object *obj = node->EvalWorldState(time).obj;

	if (obj && obj->CanConvertToType(triObjectClassID)) 
	{
		Append(node, obj, OBTYPE_MESH);
		mtlList->AddMtl(node->GetMtl());
		return TREE_CONTINUE;
	}
// 	if (node->IsTarget()) {
// 		INode* ln = node->GetLookatNode();
// 		if (ln) {
// 			Object *lobj = ln->EvalWorldState(time).obj;
// 			switch(lobj->SuperClassID()) {
// 				case LIGHT_CLASS_ID:  Append(node, obj, OBTYPE_LTARGET); break;
// 				case CAMERA_CLASS_ID: Append(node, obj, OBTYPE_CTARGET); break;
// 			}
// 		}
// 		return TREE_CONTINUE;
// 	}
	switch (obj->SuperClassID()) { 

		case CAMERA_CLASS_ID:
			/*if (obj->ClassID()==Class_ID(LOOKAT_CAM_CLASS_ID,0))*/
				Append(node, obj, OBTYPE_CAMERA);
			break;
	}

	return TREE_CONTINUE;
}

void SceneEnumProc::Append(INode *node, Object *obj, int type) 
{
	SceneEntry *entry = new SceneEntry(node, obj, type);

	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}

Box3 SceneEnumProc::Bound() 
{
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

SceneEntry *SceneEnumProc::Find(INode *node) 
{
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

	while (ptr) 
	{
		ptr->name = ptr->node->GetName();
		nameList.MakeUnique(ptr->name);		
		ptr = ptr->next;
	}
}