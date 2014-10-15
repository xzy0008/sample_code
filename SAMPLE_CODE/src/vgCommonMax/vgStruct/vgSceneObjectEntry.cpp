
#include "vgStableHeaders.h"
#include <vgStruct/vgSceneObjectEntry.h>

#if	IMPORT_MAX_LIB

SceneEntry::SceneEntry(INode *n, Object *o, int t) { 
	node = n; obj = o; type = t; next = NULL; 
	tnode = n->GetTarget();
}

ObjectList::ObjectList(SceneEnumProc &scene) {
	head = tail = NULL;
	count = 0;
	// Zip thru the object list and record all unique objects (Some may be used by more than one node)
	int scount = scene.Count();
	for(SceneEntry *se = scene.head; se!=NULL; se = se->next) {
		// can't multiple instance lights and cameras in 3DS  
		// so make them all unique--DS 4/6/96
		if ( (se->type!=OBTYPE_MESH)|| !Contains(se->obj))
			Append(se);
	}
}

ObjectList::~ObjectList() {
	while(head) {
		ObjectEntry *next = head->next;
		delete head;
		head = next;
	}
	head = tail = NULL;
	count = 0;	
}

ObjectEntry *ObjectList::Contains(Object *obj) {
	ObjectEntry *e;
	for (e=head; e!=NULL; e = e->next) {
		if(e->entry->obj == obj)
			return e;
	}
	return NULL;
}



int FindDepNodeEnum::proc(ReferenceMaker *rmaker) {
	if (rmaker == me) return DEP_ENUM_CONTINUE;
	if (rmaker->SuperClassID()!=BASENODE_CLASS_ID) return DEP_ENUM_CONTINUE;
	INode* node = (INode *)rmaker;
	if (node->GetTarget()==targ) {
		depNode = node;
		return DEP_ENUM_HALT;
	}
	return DEP_ENUM_SKIP;
}

ObjectEntry *ObjectList::FindLookatNode(INode *node) {
	FindDepNodeEnum	 finder;
	ObjectEntry *e;
	for (e=head; e!=NULL; e = e->next) {
		finder.targ = node;
		finder.me = e->entry->node;
		e->entry->node->DoEnumDependents(&finder);
		if (finder.depNode) return e;
	}
	return NULL;
}


ObjectEntry *ObjectList::Contains(INode *node) {
	ObjectEntry *e;
	for (e=head; e!=NULL; e = e->next) {
		if(e->entry->node == node)
			return e;
	}
	return NULL;
}

void ObjectList::Append(SceneEntry *e) {
	ObjectEntry *entry = new ObjectEntry(e);
	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}


ObjNameList::~ObjNameList() {
	while(head) {
		ObjName *next = head->next;
		delete head;
		head = next;
	}
	head = tail = NULL;
	count = 0;	
}

int ObjNameList::Contains(string &n) {
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

void ObjNameList::Append(string &n) {
	ObjName *entry = new ObjName(n);
	if(tail)
		tail->next = entry;
	tail = entry;
	if(!head)
		head = entry;
	count++;	
}

void ObjNameList::MakeUnique(string &n) {
	// First make it less than 10 chars.
	if (n.size()>10) 
		n.substr(0,10);

	if(Contains(n) < 0) {
		Append(n);
		return;
	}
	// Make it unique and keep it 10 chars or less
	for(int i = 0; i < 100000; ++i) {
		char buf[12];
		sprintf_s(buf, sizeof(buf), "%d",i);
		string num(buf);
		string work = n;
		int totlen = num.size() + work.size();
		if(totlen > 10)
			work = work.substr(0,10 - (totlen - 10));
		work = work + num;
		if(Contains(work) < 0) {
			Append(work);
			n = work;
			return;
		}
	}
	// Forget it!
}



void *Memory::Realloc(int amount) {
	if(ptr)
		ptr = realloc(ptr, amount);
	else
		ptr = malloc(amount);
	return ptr;
}

void *Memory::Alloc(int amount, BOOL zero) {
	Free();
	ptr = malloc(amount);
	if(ptr && zero) {
		char *p = (char *)ptr;
		for(int i = 0; i < amount; ++i)
			*p++ = 0;
	}
	return ptr;
}


#endif
