#pragma once

enum EStaticEntryType
{
	STATIC_ENTRY_ROOT,
	STATIC_ENTRY_MODEL,
	STATIC_ENTRY_CAMERA,
	STATIC_ENTRY_EFFECT,
	STATIC_ENTRY_ANIMATION,
	STATIC_ENTRY_SOUND,		
	STATIC_ENTRY_SPECIFIC_ANALYSIS,
	STATIC_ENTRY_SHAPEFILE,
	STATIC_ENTRY_COUNT			= 8
};

enum EDynamicEntryType
{
	MODEL_VGM,
	MODEL_MOD,
	CAMERA_VIEW,

	EFFECT_BILLBOARD_PLANT		= 3,

	EFFECT_PARTICLE_FOUNTAIN	= 4,
	EFFECT_PARTICLE_FIRE,
	EFFECT_PARTICLE_SMOKE,
	EFFECT_PARTICLE_FLAG,

	EFFECT_MOD_WATER			= 8,
	EFFECT_MOD_GLASS,
	EFFECT_MOD_MIRROR,
	EFFECT_MOD_METAL,
	EFFECT_MOD_FLOOR,
	EFFECT_MOD_AVI,
	EFFECT_MOD_SKYBOX,
	EFFECT_MOD_DYNAMIC			= 15,

	EFFECT_MOD_TRIGGER,
	EFFECT_MOD_AUTOBUILD,

	ANIMATION_KEYFRAME			= 18,
	ANIMATION_MS3D,
	ANIMATION_VCR,
	
	SOUND_3D					= 21,		

	SPECIFIC_ANALYSIS_ROAD_GEN,

	SHAPEFILE,

	DYNAMIC_ENTRY_COUNT			= 24
};

struct tagEntryRoot 
{
	EDynamicEntryType	_type;
	HTREEITEM			_root;
};

typedef std::map<int, HTREEITEM>	StaticEntryRootMap;
typedef std::map<int, HTREEITEM>	DynamicEntryRootMap;

typedef std::pair<int, HTREEITEM> EntryRoot_Pair;

class EntryRootManager
{
public:
	EntryRootManager();

	~EntryRootManager();
	
public:
	HTREEITEM	getEntryRootByType(EDynamicEntryType entryType);
	HTREEITEM	getEntryRootByType(EStaticEntryType entryType);

	void	initializeEntryRoots();

	void	appendEntryRootItem(EDynamicEntryType entryType, HTREEITEM item);
	void	appendEntryRootItem(EStaticEntryType entryType, HTREEITEM item);

private:
	//EntryRootVec	_entryRoots;
	StaticEntryRootMap	_entryRootsStatic;
	DynamicEntryRootMap	_entryRootsDynamic;

};