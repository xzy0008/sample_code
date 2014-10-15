#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <vgCellGridCtrl.h>

using namespace std;

typedef vector<string> DependenceVec;
typedef map<string, DependenceVec*> DependenceMap;

typedef vector<string> LibStrVec;

typedef struct VersionDef_t 
{
	string versionTitleName;
	LibStrVec* incld;
}VersionDef;

typedef vector<VersionDef> VersionInfoVec;

extern DependenceMap gs_libMap;
extern VersionInfoVec gs_versionVec;

// 读入依赖关系
int vgInitDependenceVec();

// 清理依赖关系MAP
int vgCleanUpDependenceVec();

// 根据依赖关系初始化Grid
int vgInitDependenceGrid(CCellTypesGridCtrl &gridCtrl);

// 检查并修正版本选择
int vgCheckVersionGrid(int curSel, CCellTypesGridCtrl &gridGtrl);

int vgCheckLibItem(string libName, CCellTypesGridCtrl &gridGtrl);

int vgUnCheckLibItem(string libName, CCellTypesGridCtrl &gridGtrl);


