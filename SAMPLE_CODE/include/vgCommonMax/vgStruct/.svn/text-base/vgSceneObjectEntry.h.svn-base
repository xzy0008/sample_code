
#ifndef _VGSCENEOBJECTENTRY_H_INCLUDED_
#define _VGSCENEOBJECTENTRY_H_INCLUDED_

#include "vgStableHeaders.h"

#include <vgStruct/vgSceneEnumProc.h>

#if	IMPORT_MAX_LIB

#define OBTYPE_MESH 0
#define OBTYPE_CAMERA 1
#define OBTYPE_OMNILIGHT 2
#define OBTYPE_SPOTLIGHT 3
#define OBTYPE_DUMMY 5
#define OBTYPE_CTARGET 6
#define OBTYPE_LTARGET 7


class SceneEnumProc;


class SceneEntry {
public:
	string name;
	INode *node,*tnode;
	Object *obj;
	int type;		// See above
	int id;
	SceneEntry *next;
	SceneEntry(INode *n, Object *o, int t);
	void SetID(int id) { this->id = id; }
};

// We need to maintain a list of the unique objects in the scene
class ObjectEntry {
public:
	TriObject *tri;
	SceneEntry *entry;
	ObjectEntry *next;
	ObjectEntry(SceneEntry *e) { entry = e; next = NULL;  tri = NULL; }
};


class ObjectList {
public:
	ObjectEntry *head;
	ObjectEntry *tail;
	int			count;
	ObjectList(SceneEnumProc &scene);
	~ObjectList();
	int			Count() { return count; }
	void		Append(SceneEntry *e);
	ObjectEntry *Contains(Object *obj);
	ObjectEntry *Contains(INode *node);
	ObjectEntry *FindLookatNode(INode *node);
};

class FindDepNodeEnum: public DependentEnumProc {
public:
	ReferenceTarget *targ;
	ReferenceTarget *me;
	INode *depNode;
	FindDepNodeEnum() { targ = me = NULL; depNode = NULL; }
	// proc should return 1 when it wants enumeration to halt.
	virtual	int proc(ReferenceMaker *rmaker);
};

class ObjName {
public:
	string name;
	ObjName *next;
	ObjName(string n) { name = n; next = NULL; }
};

class ObjNameList {
public:
	ObjName *head;
	ObjName *tail;
	int			count;
	ObjNameList() { head = tail = NULL; count = 0; }
	~ObjNameList();
	int			Count() { return count; }
	int			Contains(string &n);
	void		Append(string &n);
	void		MakeUnique(string &n);
};

class Memory {
	void *ptr;
public:
	Memory() { ptr = NULL; }
	Memory(int amount, BOOL zero = FALSE) { ptr = NULL; Alloc(amount, zero); }
	~Memory() { Free(); }
	void *			Ptr() { return ptr; }
	void *			Realloc(int amount);
	void *			Alloc(int amount, BOOL zero = FALSE);
	void			Free() { if(ptr) free(ptr); ptr = NULL; }
};






#endif	//_VGSCENEOBJECTENTRY_H_INCLUDED_
#endif
