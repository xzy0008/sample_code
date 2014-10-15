// vgFrameWorkView.cpp : implementation of the CvgFrameWorkView class
//


 
#include <vgStableHeaders.h>
#include "res.h"
#include "vgFrameWork.h"
#include "vgFrameWorkDoc.h"
#include "vgFrameWorkView.h"
#include "vgUIController/vgUIController.h"
#include "vgEntry/vgBaseEntry.h"


#include "vgEntry/vgTerrainEntry.h"


#include <sys/timeb.h>
#include <MainFrm.h>


#include <vgKernel/vgkOpenGLSupport.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgGlobal/vggGlobalFacade.h>
#include <vgGlobal/vggGlobalConsole.h>
#include <vgKernel/vgkRenderer.h>

#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkSelectManager.h>

#include <vgKernel/vgkStringUtility.h>

#include <vgDlgTestMultisample.h>

#include <vgKernel/vgkAbstractTreeFacMgr.h>
#include <vgTree/vgtTreeFactory.h>

#include <vgMesh/vgmFileHandleVgm.h>

#include <vgCam/vgcaCamManager.h>
#include "vgEntry/vgEntryFactory.h"

#include <vgCam/vgcaCameraRecord.h>

#include "vgTree/vgtTreeFactory.h"
#include <vgKernel/vgkRendererManager.h>

#include <vgEffect/vgAviNode.h>
#include <vgDlgAviNode.h>


#include <vgOcc/vgoOcclusion.h>


#include <vgTerritory/vgtTerrainManager.h>
#include <vgTerritory/vgtElevationFilter.h>

#include "DlgAbout.h"
#include "DlgTranslateAll.h"
#include "DlgTranslateVector.h"
//#include "DlgShpToDBEx.h"
#include <vgShape/DlgShpToDBEx.h>

//Utiltity for separate code of view
#include <vgGlobal/vggGlobalUtility.h>
#include <vgGlobal/vggSoundUtility.h>
#include <vgGlobal/vggEffectUtility.h>
#include <vgGlobal/vggEditUtility.h>
#include <vgGlobal/vggGisUtility.h>
#include <vgGlobal/vggVgcamUtility.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggVgmeshUtility.h>
#include <vgGlobal/vggVgshpUtility.h>

#include <vgConf/vgcoExeConfigRegProxy.h>
#include <vgConf/vgcoExeConfig.h>
#include <vgConf/vgcoProjectConfig.h>
#include <vgConf/vgcoProjectConfigRegProxy.h>


#include <vgDatabase/vgdDatabaseManager.h>
#include <vgDatabase/vgdOracleConnector.h>
#include <vgDatabase/vgdBasedConnector.h>

#include <vgDatabase/vgDlgDBConnect.h>
#include <vgDatabase/vgDlgCondition.h>

#include <vgVisualEffects/vgviBackgroundManager.h>
//#include <vgScript/vgscScriptManager.h>


#include <vgScript/vgscScriptManager.h>
#include <vgGlobal/vggSystemFacade.h>
#include <vgGlobal/vggSceneFileUtility.h>

#include <vgTerritory/vgtTerrainCenterManager.h>
//#include <vgMod/vgModTerrainManager.h>

//#include "vgDlgSun.h"
#include <vgaviexportdialog.h>
#include <vgExportBMPDialog.h>


#include <vgTerritory/vgtCutSurfaceLevelling.h>


#include <vgImage/vgiCximageWrapper.h>

#include <vgShape/vgshShapeManager.h>
#include "vgVcrHeightDlg.h"
//#include "vgShapeDataSourceEntry.h"

//#include "vgShapeLayerEntry.h"

#include <vgAutoBuild/vgAutoBuildNode.h>
#include <vgAutoBuild/vgvAutoBuildManager.h>
#include <vgShape/vgshSpecialPolygon.h>
#include <vgShape/vgshPolygon.h>


#include "DlgAutoBuildInput.h"
#include "DlgAutoIn.h"
#include <vgLogo/vgloLogoManager.h>
#include "DlgTriggerConfig.h"
#include "vgDlgDynamicTexNode.h"
#include <vgPlan/vgPlanmanager.h>
#include <vgDlgTreeSet.h>
#include <DlgFindObject.h>
#include <DlgSelectFlash.h>


#include <vgKernel/vgkDynamicLibraryUtility.h>

#include "vgUserScriptSystem.h"
#include "vgUserScriptOtherModules.h"

#include <vgMod/vgTriggerManager.h>
#include <vgMod/vgModMisc.h>
#include <vgMovingManager.h>


#include <vgKernel/vgkClassFactoryManager.h>

#include <vgModel/vgmoFileHandleVmd.h>
#include <vgModel/vgmoModelManager.h>


#include <vgMod/vgGisRoadMatch.h>
#include <vgDlgGismatch.h>

#include <vgKernel/vgkPluginManager.h>

#include <vgSolar/vgsoDefinition.h>
#include <vgDatabase/vgdDefinition.h>
#include <vgKernel/vgkRenderCommandManager.h>

#include "vgClientRenderCommand.h"
#include <vgKernel/vgkPropertyManager.h>
#include "vgLogonDialog.h"

using std::list;
using std::vector;
using namespace vgDatabase;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VG_MSG_RENDER WM_USER + 100


#define VGMSGBOX2(A) {\
	this->SetTimer(1, 150, NULL);\
	A; \
	this->SetTimer(1, 15, NULL);}

// ---------------------------------------------------------

// CvgFrameWorkView

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CvgFrameWorkView, CView)

BEGIN_MESSAGE_MAP(CvgFrameWorkView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	
	ON_COMMAND(NID_VGM_IMPORT_VGM, &CvgFrameWorkView::OnVgmImportVgm)
	ON_COMMAND(NID_VGI_IMPORT_VGI, &CvgFrameWorkView::OnVgiImportVgi)
	ON_COMMAND(NID_VGM_SAVE_VGM, &CvgFrameWorkView::OnVgmSaveVgm)
	ON_COMMAND(NID_VGMI_SAVE_VGM_VGI, &CvgFrameWorkView::OnVgmiSaveVgmVgi)
	
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	
	ON_COMMAND(NID_VGTERRAIN_WIREFRAME, &CvgFrameWorkView::OnVgterrainWireframe)
	ON_COMMAND(NID_VGTERRAIN_NOWIREFRAME, &CvgFrameWorkView::OnVgterrainNowireframe)
	ON_COMMAND(NID_VGTERRAIN_TURNON, &CvgFrameWorkView::OnVgterrainTurnon)
	ON_WM_ACTIVATEAPP()

	//ON_MESSAGE(VG_MSG_RENDER, &CvgFrameWorkView::OnRender)
	ON_COMMAND(NID_VGTERRAIN_CONVERT_DEM_TO_VGTR, &CvgFrameWorkView::OnVgterrainConvertDemToVgtr)
	ON_COMMAND(NID_VGTERRAIN_CONVERT_VGTR_HEIGHTMAP, &CvgFrameWorkView::OnVgterrainConvertVgtrHeightmap)
	//ON_COMMAND(ID_TTTTTTEST, &CvgFrameWorkView::OnTtttttest)
	ON_COMMAND(NID_FILE_IMPORT_MOD, &CvgFrameWorkView::OnFileImportMod)
	//ON_COMMAND(ID_CAMERA_CAPTURE, &CvgFrameWorkView::OnCameraCapture)
	
	ON_COMMAND(ID_CREATCAM, &CvgFrameWorkView::OnCreatcam)
	ON_COMMAND(ID_ANI_Start, &CvgFrameWorkView::OnAniStart)
	ON_COMMAND(ID_ANI_END, &CvgFrameWorkView::OnAniEnd)
	ON_COMMAND(ID_ANI_PLAY, &CvgFrameWorkView::OnAniPlay)
	ON_COMMAND(ID_ANI_RESUME, &CvgFrameWorkView::OnAniResume)
	ON_COMMAND(ID_CREATCAM, &CvgFrameWorkView::OnCreatcam)
	ON_COMMAND(ID_ANI_STOP, &CvgFrameWorkView::OnAniStop)

	ON_COMMAND(ID_SWITCHCAM, &CvgFrameWorkView::OnSwitchcam)
	ON_COMMAND(ID_POSITIONTOOBJ, &CvgFrameWorkView::OnPositiontoobj)

	ON_COMMAND(ID_SE_FOUNTAIN, &CvgFrameWorkView::OnSeFountain)
	ON_COMMAND(ID_FIRE_ADD, &CvgFrameWorkView::OnFireAdd)
	ON_COMMAND(ID_SE_SMOKE, &CvgFrameWorkView::OnSeSmoke)
	ON_COMMAND(ID_ADDFLAG, &CvgFrameWorkView::OnAddflag)
	ON_COMMAND(ID_WATER_CONVERT, &CvgFrameWorkView::OnWaterConvert)
	ON_COMMAND(ID_GLASS_CONVERT, &CvgFrameWorkView::OnGlassConvert)
	ON_COMMAND(ID_AVI_NODE_CONVERT, &CvgFrameWorkView::OnAviNodeConvert)
	ON_COMMAND(ID_SKYBOX_CONVERT, &CvgFrameWorkView::OnSkyboxConvert)
	ON_COMMAND(ID_WATER_DIRECTION, &CvgFrameWorkView::OnWaterDirection)
	//ON_COMMAND(ID_BEGINPLANT, &CvgFrameWorkView::OnBeginplant)

	ON_COMMAND(ID_RAIN, &CvgFrameWorkView::OnRain)
	ON_COMMAND(ID_SNOW, &CvgFrameWorkView::OnSnow)
	ON_COMMAND(ID_RAIN_DEL, &CvgFrameWorkView::OnRainDel)
	ON_COMMAND(ID_SNOW_DEL, &CvgFrameWorkView::OnSnowDel)
	ON_COMMAND(ID_SE_FOG_DEL, &CvgFrameWorkView::OnFogDel)
	ON_COMMAND(ID_SE_FOG, &CvgFrameWorkView::OnSeFog)
	ON_COMMAND(ID_MIRROR_CONVERT, &CvgFrameWorkView::OnMirrorConvert)
	ON_COMMAND(ID_METAL_CONVERT, &CvgFrameWorkView::OnMetalConvert)
	ON_COMMAND(ID_CONVERT_BRIGTHFLOOR, &CvgFrameWorkView::OnConvertBrigthfloor)
	ON_COMMAND(ID_3DSOUND_ADD, &CvgFrameWorkView::On3dsoundAdd)
	ON_COMMAND(ID_BACKSOUND_SET, &CvgFrameWorkView::OnBacksoundSet)
	ON_COMMAND(ID_FILE_IMPORT_MS3D, &CvgFrameWorkView::OnFileImportMs3d)

	ON_COMMAND(ID_ADDANIMATION, &CvgFrameWorkView::OnAddanimation)
	ON_COMMAND(ID_SETTREE, &CvgFrameWorkView::OnSettree)
	//ON_COMMAND(ID_SELECT, &CvgFrameWorkView::OnSelect)
	//ON_COMMAND(ID_PLANTINLINE, &CvgFrameWorkView::OnPlantinline)
	ON_COMMAND(ID_VGTERRAIN_NEW_VTR, &CvgFrameWorkView::OnVgterrainNewVtr)

	ON_COMMAND(IDM_Zuobiao, &CvgFrameWorkView::OnZuobiao)
	ON_COMMAND(IDM_Juli, &CvgFrameWorkView::OnJuli)
	ON_COMMAND(IDM_Mianji, &CvgFrameWorkView::OnMianji)
	ON_COMMAND(IDM_Tiji, &CvgFrameWorkView::OnTiji)
	ON_COMMAND(ID_TOOL_MAKER_VGM, &CvgFrameWorkView::OnToolMakerVgm)
	ON_COMMAND(ID_TOOL_MAKER_VGI, &CvgFrameWorkView::OnToolMakerVgi)
	ON_COMMAND(ID_SCENE_READ, &CvgFrameWorkView::OnSceneRead)
	ON_COMMAND(ID_SCENE_SAVE, &CvgFrameWorkView::OnSceneSave)
	ON_COMMAND(ID_PUBLISH_COLLECT, &CvgFrameWorkView::OnPublishCollect)
	ON_COMMAND(ID_33014, &CvgFrameWorkView::OnShapefileDb)//YXDB

	ON_COMMAND(ID_TOOL_MAKER_DDS, &CvgFrameWorkView::OnToolMakerDds)


	ON_COMMAND(ID_EDIT_SELECT, &CvgFrameWorkView::OnEditSelect)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CvgFrameWorkView::OnEditSelectAll)
	ON_COMMAND(ID_EDIT_SELECT_CLEAR, &CvgFrameWorkView::OnEditSelectClear)
	ON_COMMAND(ID_EDIT_FIND_OBJ, &CvgFrameWorkView::OnFindObj)
	ON_COMMAND(ID_EDIT_SELECT_RECT, &CvgFrameWorkView::OnSelectShapeRect)
	ON_COMMAND(ID_EDIT_SELECT_POLYGON, &CvgFrameWorkView::OnSelectShapePolygon)
	ON_COMMAND(ID_EDIT_SELECT_REGION_NEW, &CvgFrameWorkView::OnSelectRegionNew)
	ON_COMMAND(ID_EDIT_SELECT_REGION_ADD, &CvgFrameWorkView::OnSelectRegionAdd)
	ON_COMMAND(ID_EDIT_SELECT_REGION_SUBTRACT, &CvgFrameWorkView::OnSelectRegionSubtract)
	ON_COMMAND(ID_EDIT_SELECT_REGION_INTERSECT, &CvgFrameWorkView::OnSelectRegionIntersect)
	ON_COMMAND(ID_EDIT_SELECT_MODE_INCLUDE, &CvgFrameWorkView::OnSelectModeInclude)
	ON_COMMAND(ID_EDIT_SELECT_MODE_INTERSECT, &CvgFrameWorkView::OnSelectModeIntersect)

	ON_COMMAND(NID_FILE_IMPORT_KFM, &CvgFrameWorkView::OnFileImportKfm)
	ON_COMMAND(ID_EDIT_TRANSLATE, &CvgFrameWorkView::OnEditTranslate)
	ON_COMMAND(ID_EDIT_ROTATE, &CvgFrameWorkView::OnEditRotate)
	ON_COMMAND(ID_EDIT_SCALE, &CvgFrameWorkView::OnEditScale)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TRANSLATE, &CvgFrameWorkView::OnUpdateEditTranslate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATE, &CvgFrameWorkView::OnUpdateEditRotate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SCALE, &CvgFrameWorkView::OnUpdateEditScale)
	ON_COMMAND(ID_CHANNEL_1, &CvgFrameWorkView::OnChannel1)
	ON_COMMAND(ID_CHANNEL_0, &CvgFrameWorkView::OnChannel0)
	ON_COMMAND(ID_CHANNEL_m1, &CvgFrameWorkView::OnChannelm1)
	ON_COMMAND(ID_APP_ABOUT, &CvgFrameWorkView::OnAppAbout)

	ON_COMMAND(ID_OCC_SWITCH, &CvgFrameWorkView::OnOccSwitch)
	ON_COMMAND(ID_FILE_IMPORT, &CvgFrameWorkView::OnFileImport)
	ON_COMMAND(IDM_GISMATCH, &CvgFrameWorkView::OnGismatch)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_FILE_EXPORT, &CvgFrameWorkView::OnFileExport)
	ON_COMMAND(ID_UNDO, &CvgFrameWorkView::OnUndo)
	ON_COMMAND(ID_REDO, &CvgFrameWorkView::OnRedo)
	ON_COMMAND(ID_MESH_OR_LINE, &CvgFrameWorkView::OnMeshOrLine)
	ON_UPDATE_COMMAND_UI(ID_MESH_OR_LINE, &CvgFrameWorkView::OnUpdateMeshOrLine)
	ON_UPDATE_COMMAND_UI(ID_OCC_SWITCH, &CvgFrameWorkView::OnUpdateOccSwitch)
	ON_COMMAND(ID_EDIT_TRANALL, &CvgFrameWorkView::OnEditTranall)
	//ON_COMMAND(ID_SHOW_MODELS, &CvgFrameWorkView::OnShowModels)
	//ON_UPDATE_COMMAND_UI(ID_SHOW_MODELS, &CvgFrameWorkView::OnUpdateShowModels)

	ON_COMMAND(ID_VGT_ATTACH, &CvgFrameWorkView::OnVgtAttach)
	ON_COMMAND(ID_TERRAIN_COLLISION_DETECT, &CvgFrameWorkView::OnTerrainCollisionDetect)
	ON_UPDATE_COMMAND_UI(ID_TERRAIN_COLLISION_DETECT, &CvgFrameWorkView::OnUpdateTerrainCollisionDetect)
	ON_COMMAND(ID_32972, &CvgFrameWorkView::On32972)
	ON_UPDATE_COMMAND_UI(ID_32972, &CvgFrameWorkView::OnUpdate32972)
	ON_COMMAND(ID_32973, &CvgFrameWorkView::On32973)
	ON_UPDATE_COMMAND_UI(ID_32973, &CvgFrameWorkView::OnUpdate32973)
	ON_COMMAND(ID_32974, &CvgFrameWorkView::On32974)
	ON_UPDATE_COMMAND_UI(ID_32974, &CvgFrameWorkView::OnUpdate32974)
	ON_COMMAND(ID_VGT_VISIBILITY, &CvgFrameWorkView::OnVgtVisibility)
	ON_UPDATE_COMMAND_UI(ID_VGT_ATTACH, &CvgFrameWorkView::OnUpdateVgtAttach)
	ON_UPDATE_COMMAND_UI(ID_VGT_VISIBILITY, &CvgFrameWorkView::OnUpdateVgtVisibility)


	ON_COMMAND(ID_HIDE_VEC, &CvgFrameWorkView::OnHideVec)
	ON_COMMAND(ID_NOSEL_VEC, &CvgFrameWorkView::OnNoselVec)
	//ON_UPDATE_COMMAND_UI(ID_TERRAIN_LEVELING, &CvgFrameWorkView::OnUpdateTerrainLeveling)
	ON_COMMAND(ID_VGT_CUT_ANALYSIS2, &CvgFrameWorkView::OnVgtCutAnalysis2)
	ON_UPDATE_COMMAND_UI(ID_VGT_CUT_ANALYSIS2, &CvgFrameWorkView::OnUpdateVgtCutAnalysis2)
	ON_COMMAND(ID_VGT_TERRAIN_SAVE, &CvgFrameWorkView::OnVgtTerrainSave)
	ON_UPDATE_COMMAND_UI(ID_VGT_TERRAIN_SAVE, &CvgFrameWorkView::OnUpdateVgtTerrainSave)
	ON_COMMAND(ID_VGT_BLEND, &CvgFrameWorkView::OnVgtBlend)
	ON_UPDATE_COMMAND_UI(ID_VGT_BLEND, &CvgFrameWorkView::OnUpdateVgtBlend)
	//ON_COMMAND(ID_VGT_VISIBILITY2, &CvgFrameWorkView::OnVgtVisibility2)
	//ON_UPDATE_COMMAND_UI(ID_VGT_VISIBILITY2, &CvgFrameWorkView::OnUpdateVgtVisibility2)
	//ON_COMMAND(ID_VGT_CUTAREA, &CvgFrameWorkView::OnVgtCutarea)
	//ON_UPDATE_COMMAND_UI(ID_VGT_CUTAREA, &CvgFrameWorkView::OnUpdateVgtCutarea)
	ON_COMMAND(ID_NDB_CONNECT, &CvgFrameWorkView::OnNdbConnect)
	ON_COMMAND(ID_NDB_CONDITION, &CvgFrameWorkView::OnNdbCondition)
	ON_COMMAND(ID_COLLISION_ONOFF, &CvgFrameWorkView::OnCollisionOnoff)
	ON_UPDATE_COMMAND_UI(ID_COLLISION_ONOFF, &CvgFrameWorkView::OnUpdateCollisionOnoff)
	ON_COMMAND(ID_VGT_MAPPING_ORIGIN, &CvgFrameWorkView::OnVgtMappingOrigin)
	ON_UPDATE_COMMAND_UI(ID_VGT_MAPPING_ORIGIN, &CvgFrameWorkView::OnUpdateVgtMappingOrigin)
	ON_COMMAND(ID_VECTOR_SHP_EXPORT2DB, &CvgFrameWorkView::OnVectorShpExport2db)


	ON_COMMAND(ID_VGVI_BG_CONFIG, &CvgFrameWorkView::OnVgviBgConfig)
	ON_COMMAND(ID_NDB_DISCONNECT, &CvgFrameWorkView::OnNdbDisconnect)
	ON_COMMAND(ID_SCRIPT_RUNFILE, &CvgFrameWorkView::OnScriptRunfile)
	ON_COMMAND(ID_SCRIPT_TESTSCRIPT, &CvgFrameWorkView::OnScriptTestscript)
	ON_COMMAND(ID_SCRIPT_TESTMENU, &CvgFrameWorkView::OnScriptTestmenu)
	ON_COMMAND(ID_SCRIPT_CONSOLE, &CvgFrameWorkView::OnScriptConsole)
	ON_COMMAND(ID_PUBLISH_PACKAGE_EXE, &CvgFrameWorkView::OnPublishPackageExe)
	ON_COMMAND(ID_SCENE_RESET, &CvgFrameWorkView::OnSceneReset)
	ON_COMMAND(ID_33109, &CvgFrameWorkView::Onterraintesting)
	ON_UPDATE_COMMAND_UI(ID_33109, &CvgFrameWorkView::OnUpdate33109)

	ON_COMMAND(ID_VGSC_USER_SCRIPT_CONFIG, &CvgFrameWorkView::OnVgscUserScriptConfig)
	ON_COMMAND(ID_GIS_SUN, &CvgFrameWorkView::OnGisSun)
	ON_COMMAND(ID_TANSLATE_SELECTED, &CvgFrameWorkView::OnTanslateSelected)
	ON_COMMAND(ID_EXP_AVI, &CvgFrameWorkView::OnExpAvi)
	ON_COMMAND(ID_EXP_BMP, &CvgFrameWorkView::OnExpBmp)
	ON_COMMAND(ID_VGSHAPE_QUERY_GREEN_RATIO, &CvgFrameWorkView::OnVectorShpGreenRatio)
	ON_COMMAND(ID_VGSHAPE_READSHPFILE, &CvgFrameWorkView::OnVgshapeReadshpfile)
	ON_COMMAND(ID_VGSHAPE_SELECTSHPAREA, &CvgFrameWorkView::OnVgshapeSelectshparea)
	ON_COMMAND(ID_CAM_REHEIGHT, &CvgFrameWorkView::OnCamReheight)

	ON_COMMAND(ID_EDIT_SET_TRANSPARENT, &CvgFrameWorkView::OnEditSetTransparent)
	ON_COMMAND(ID_EDIT_SET_UNTRANSPARENT, &CvgFrameWorkView::OnEditSetUnTransparent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SET_TRANSPARENT, &CvgFrameWorkView::OnUpdateEditSetTransparent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SET_UNTRANSPARENT, &CvgFrameWorkView::OnUpdateEditSetUntransparent)

	ON_COMMAND(ID_AUTOBUILD, &CvgFrameWorkView::OnAutobuild)
	ON_COMMAND(ID_VGSHAPE_READGRIDSHPFILE, &CvgFrameWorkView::OnVgshapeReadgridshpfile)
	ON_UPDATE_COMMAND_UI(ID_VGSHAPE_SELECTSHPAREA, &CvgFrameWorkView::OnUpdateVgshapeSelectshparea)
	ON_COMMAND(ID_AUTOBUILD_CLONE, &CvgFrameWorkView::OnAutobuildClone)
	ON_COMMAND(ID_EDIT_SINGLE_FACE_RENDER_SEL, &CvgFrameWorkView::OnEditSingleFaceRenderSel)
	ON_COMMAND(ID_EDIT_SINGLE_FACE_RENDER_ALL, &CvgFrameWorkView::OnEditSingleFaceRenderAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SINGLE_FACE_RENDER_SEL, &CvgFrameWorkView::OnUpdateEditSingleFaceRenderSelect)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SINGLE_FACE_RENDER_ALL, &CvgFrameWorkView::OnUpdateEditSingleFaceRenderAll)

	ON_COMMAND(ID_TRIGGER_SET_AS, &CvgFrameWorkView::OnTriggerSetAs)
	ON_COMMAND(ID_VGSHAPE_IMPORTTEXT, &CvgFrameWorkView::OnVgshapeImporttext)

	ON_COMMAND(ID_VGSHAPE_CACULATEPOSITION, &CvgFrameWorkView::OnVgshapeCaculateposition)
	ON_COMMAND(ID_VGSHAPE_CLEARPLAN, &CvgFrameWorkView::OnVgshapeClearplan)
	ON_COMMAND(ID_VGSHAPE_GENERATESELECTED, &CvgFrameWorkView::OnVgshapeGenerateselected)
	ON_COMMAND(ID_VGSHAPE_IMPORTINFOFROMTXT, &CvgFrameWorkView::OnVgshapeImportinfofromtxt)
	ON_COMMAND(ID_AUTOBUILDING_CLOSEINFOFILE, &CvgFrameWorkView::OnAutobuildingCloseinfofile)
	ON_COMMAND(ID_TRIGGER_CONFIG, &CvgFrameWorkView::OnTriggerConfig)
	ON_COMMAND(ID_QUERYPLANINFO_QUERYPLOTRATIO, &CvgFrameWorkView::OnQueryplaninfoQueryplotratio)
	ON_UPDATE_COMMAND_UI(ID_QUERYPLANINFO_QUERYPLOTRATIO, &CvgFrameWorkView::OnUpdateQueryplaninfoQueryplotratio)
	ON_COMMAND(ID_DYNTEXTURE_CONVERT, &CvgFrameWorkView::OnDyntextureConvert)
	ON_COMMAND(ID_VGPLAN_ADDGROUND, &CvgFrameWorkView::OnVgplanAddground)
	ON_COMMAND(ID_VGPLAN_ADDSECNE, &CvgFrameWorkView::OnVgplanAddsecne)
	ON_COMMAND(ID_VGSHADOW_TURNONSHADOW, &CvgFrameWorkView::OnVgshadowTurnonshadow)
	ON_COMMAND(ID_VGSHADOW_SELECTSHADOWCASTOBJECTS, &CvgFrameWorkView::OnVgshadowSelectshadowcastobjects)
	ON_COMMAND(ID_VGPLAN_SETPARAMETER, &CvgFrameWorkView::OnVgplanSetparameter)
	ON_COMMAND(ID_VGSHADOW_CHANGE, &CvgFrameWorkView::OnVgshadowChange)
	ON_COMMAND(ID_VGSHADOW_TURNOFFSHADOW, &CvgFrameWorkView::OnVgshadowTurnoffshadow)
	ON_COMMAND(ID_VGSHADOW_SOLARANALYSIS, &CvgFrameWorkView::OnVgshadowSolaranalysis)
	ON_UPDATE_COMMAND_UI(ID_VGSHADOW_SOLARANALYSIS, &CvgFrameWorkView::OnUpdateVgshadowSolaranalysis)
	ON_UPDATE_COMMAND_UI(ID_VGSHADOW_TURNONSHADOW, &CvgFrameWorkView::OnUpdateVgshadowTurnonshadow)
	ON_COMMAND(ID_TESTTEST_SELECTCHANGECOLOR, &CvgFrameWorkView::OnTesttestSelectchangecolor)
	ON_COMMAND(ID_VGPLAN_ADDSTREETLINE, &CvgFrameWorkView::OnVgplanAddstreetline)
	ON_COMMAND(ID_PLAN_EXPORTSCENE, &CvgFrameWorkView::OnPlanExportscene)
	ON_COMMAND(ID_VGPLAN_GENERATEPLANMAP, &CvgFrameWorkView::OnVgplanGenerateplanmap)
	ON_COMMAND(ID_VGPLAN_ADDREGION, &CvgFrameWorkView::OnVgplanAddregion)
	ON_COMMAND(ID_VGPLAN_ADDNEW, &CvgFrameWorkView::OnVgplanAddnew)
	ON_COMMAND(ID_VGPLAN_CGRID, &CvgFrameWorkView::OnVgplanCgrid)
	ON_COMMAND(ID_VGPLAN_CALGRID, &CvgFrameWorkView::OnVgplanCalgrid)
	ON_COMMAND(ID_VGPLAN_GENPLAN, &CvgFrameWorkView::OnVgplanGenplan)
	ON_COMMAND(ID_VGPLAN_OUTPUT, &CvgFrameWorkView::OnVgplanOutput)

	ON_COMMAND(ID_VMD_IMPORT, &CvgFrameWorkView::OnVmdImport)
//  	ON_MESSAGE(WM_DELETE_DLG_EXE,OnDelDlgMsg)
	// ON_COMMAND(ID_LOAD_VTR_DLL, &CvgFrameWorkView::OnLoadVtrDll)
	// ON_COMMAND(ID_UNLOAD_VTR_DLL, &CvgFrameWorkView::OnUnloadVtrDll)
	ON_UPDATE_COMMAND_UI(ID_VGTERRAIN_NEW_VTR, &CvgFrameWorkView::OnUpdateVgterrainNewVtr)
	ON_COMMAND(ID_SCENE_PUBLISH, &CvgFrameWorkView::OnScenePublish)
	ON_UPDATE_COMMAND_UI(IDM_Zuobiao, &CvgFrameWorkView::OnUpdateZuobiao)
	ON_UPDATE_COMMAND_UI(IDM_Juli, &CvgFrameWorkView::OnUpdateJuli)
	ON_UPDATE_COMMAND_UI(IDM_Mianji, &CvgFrameWorkView::OnUpdateMianji)
	ON_COMMAND(ID_VGSO_LOAD_DLL, &CvgFrameWorkView::OnVgsoLoadDll)
	ON_COMMAND(ID_VGSO_UNLOAD_DLL, &CvgFrameWorkView::OnVgsoUnloadDll)
	ON_UPDATE_COMMAND_UI(ID_SCENE_PUBLISH, &CvgFrameWorkView::OnUpdateScenePublish)

	ON_COMMAND(ID_VCR_ACCE, &CvgFrameWorkView::OnVcrAcce)
	ON_COMMAND(ID_VCR_DEACCE, &CvgFrameWorkView::OnVcrDeacce)
	ON_COMMAND(ID_CONFIGDYNBILLBOARD, &CvgFrameWorkView::OnConfigdynbillboard)
	ON_COMMAND(ID_DYNAMICBILLBOARD, &CvgFrameWorkView::OnDynamicbillboard)

	ON_COMMAND(ID_SAVE_CUT_BLOCK, &CvgFrameWorkView::OnSaveCutBlock)
	ON_COMMAND(ID_SWITCH_TO_TOP_VIEW, &CvgFrameWorkView::OnSwitchToTopView)
	ON_COMMAND(ID_SWITCH_TO_PERSPECT_VIEW, &CvgFrameWorkView::OnSwitchToPerspectView)

	ON_COMMAND(ID_AXONOVIEW_NORTHWEST, &CvgFrameWorkView::OnAxonoViewNorthWest)
	ON_COMMAND(ID_AXONOVIEW_SOUTHWEST, &CvgFrameWorkView::OnAxonoViewSouthWest)
	ON_COMMAND(ID_AXONOVIEW_NORTHEAST, &CvgFrameWorkView::OnAxonoViewNorthEast)
	ON_COMMAND(ID_AXONOVIEW_SOUTHEAST, &CvgFrameWorkView::OnAxonoViewSouthEast)

	ON_COMMAND(ID_BEGIN_CUT_BLOCK, &CvgFrameWorkView::OnBeginCutBlock)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_SOLIDBUILD, &CvgFrameWorkView::OnSolidBuild)
	ON_UPDATE_COMMAND_UI(ID_SOLIDBUILD, &CvgFrameWorkView::OnUpdateSolidBuild)
	ON_COMMAND(ID_INFORMATION_MARK, &CvgFrameWorkView::OnLandMarkBuild)
	ON_UPDATE_COMMAND_UI(ID_INFORMATION_MARK, &CvgFrameWorkView::OnUpdateLandMark)
	ON_COMMAND(ID_ENABLE_ALLMARK, &CvgFrameWorkView::OnEnableAllMark)
	ON_UPDATE_COMMAND_UI(ID_ENABLE_ALLMARK, &CvgFrameWorkView::OnUpdateAllMark)

	ON_COMMAND(ID_COMPASS, &CvgFrameWorkView::OnCompass)
	ON_UPDATE_COMMAND_UI(ID_COMPASS, &CvgFrameWorkView::OnUpdateCompass)
	ON_COMMAND(ID_Hawkeye, &CvgFrameWorkView::OnHawkeye)
	ON_UPDATE_COMMAND_UI(ID_Hawkeye, &CvgFrameWorkView::OnUpdateHawkeye)
	ON_COMMAND(ID_OUTPUTIAMGE, &CvgFrameWorkView::OnOutputiamge)
	ON_COMMAND(ID_TEST_ADDUPDATE, &CvgFrameWorkView::OnTestAddupdate)
	ON_COMMAND(ID_TEST_V, &CvgFrameWorkView::OnTestV)
	ON_COMMAND(ID_CONNET, &CvgFrameWorkView::OnConnet)
	ON_COMMAND(ID_DUSTSUN_INI, &CvgFrameWorkView::OnDustsunIni)
	ON_COMMAND(ID_DUSTSUN_SET, &CvgFrameWorkView::OnDustsunSet)
	ON_COMMAND(ID_EDIT_SELECT_REVERSE2, &CvgFrameWorkView::OnEditSelectReverse2)
	END_MESSAGE_MAP()

// MFC消息

CvgFrameWorkView::CvgFrameWorkView()
: m_pDC(NULL)
{
	initializeSock();

	createClientRecvSocket();
}

CvgFrameWorkView::~CvgFrameWorkView()
{
	finalizeSock();

	if (m_updateVgimgPath.length() == 0)
	{
		return ;
	}

	vgCore::ArchiveManager::getSingleton().clear();

	// BOOL reDel = DeleteFile(m_oldVgPath.c_str());
	BOOL reDel = DeleteFile(m_oldVgimgPath.c_str());

	BOOL reMove = MoveFile(m_updateVgimgPath.c_str(), m_oldVgimgPath.c_str());
	// reMove = MoveFile(m_updataVgPath.c_str(), m_oldVgPath.c_str());

}

BOOL CvgFrameWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


// CvgFrameWorkView drawing
void CvgFrameWorkView::OnDraw(CDC* /*pDC*/)
{
	CvgFrameWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


// CvgFrameWorkView printing
void CvgFrameWorkView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CvgFrameWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CvgFrameWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}

void CvgFrameWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}



void CvgFrameWorkView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
}

void CvgFrameWorkView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CView::OnShowWindow(bShow, nStatus);
}


// CvgFrameWorkView diagnostics
#ifdef _DEBUG
void CvgFrameWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CvgFrameWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CvgFrameWorkDoc* CvgFrameWorkView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CvgFrameWorkDoc)));
	return (CvgFrameWorkDoc*)m_pDocument;
}
#endif //_DEBUG

void CvgFrameWorkView::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	CView::OnWindowPosChanging(lpwndpos);

	CRect rect;

	GetWindowRect(&rect);

	int nCenterX = rect.TopLeft().x+ rect.Width()/2;
	int nCenterY = rect.TopLeft().y+ rect.Height()/2;
	//vgCam::CamManager::getSingleton().setCenterOfScreen(nCenterX, nCenterY);
	vgGlobal::CamUtility::setCenterOfScreen(nCenterX, nCenterY);

	// TODO: 在此处添加消息处理程序代码
}

BOOL CvgFrameWorkView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}



//OpenGL 环境
void CvgFrameWorkView::renderScene(void)
{

	if (m_needUpdate)
	{
		m_needUpdate = false;

		vgKernel::StringVector vec;
		vec.push_back(m_newModPath);

		FILE *fp = fopen(m_newModPath.c_str(), "r");
		
		if (fp != NULL)
		{
			fclose(fp);

			AfxMessageBox("收到远程更新指令. 场景已更新");

			vgGlobal::ModUtility::importModFile(m_newModPath);
		}
		else
		{
			string outString = "收到远程更新指令.";
			outString += m_newModPath;

			AfxMessageBox(outString.c_str());
		}
	}

	VGK_CHECK_OPENGL_ERROR();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	
	
	// 按优先级渲染所有插件
	vgKernel::RenderCommandFacade::RenderAll();

	HDC handledevice = m_pDC->GetSafeHdc();

	if ( handledevice == INVALID_HANDLE_VALUE )
	{
		assert( 0 );
	}

	SwapBuffers( handledevice );

	vgKernel::OpenGLSupport::makeErrorStackEmpty();

	try
	{
		VGK_CHECK_OPENGL_ERROR();
	}
	catch (...)
	{
		int dff=0;

		::MessageBox( NULL , "SwapBuffers 出错!" , "ERROR" , MB_OK );
	}

	vgGlobal::GlobalConsole::getSingleton().showFps();

	VGK_CHECK_OPENGL_ERROR();
}



bool CvgFrameWorkView::initGLContext(void)
{
	GLuint PixelFormat;	

	static PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
		1,                                // 版本号 
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
		PFD_DOUBLEBUFFER,                 // 双缓存模式 
		PFD_TYPE_RGBA,                    // RGBA 颜色模式 
		24,                               // 24 位颜色深度 
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
		1,                                // 没有非透明度缓存 
		0,                                // 忽略移位位 
		0,                                // 无累加缓存 
		0, 0, 0, 0,                       // 忽略累加位 
		32,                               // 32 位深度缓存     
		8,                                // 无模板缓存 //改动阴影
		0,                                // 无辅助缓存 
		PFD_MAIN_PLANE,                   // 主层 
		0,                                // 保留 
		0, 0, 0                           // 忽略层,可见性和损毁掩模 
	};

	HWND hWND = this->GetSafeHwnd();
	HDC hDC = ::GetDC(hWND);
	m_pDC = new CClientDC(this);
	// 选择合适的Device Context像素点格式
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{							
		::MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if ( *(((CMainFrame *)GetParent())->test_multisample_dlg)._parbMultisampleSupported )
	{
		PixelFormat = *((((CMainFrame *)GetParent())->test_multisample_dlg)._parbMultisampleFormat);
	}



	// 设置新的Device Context像素点格式
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		::MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 根据当前的Device Context得到rending context
	if (!(this->m_hGLContext=wglCreateContext(hDC)))	// Are We Able To Get A Rendering Context?
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}
	// 设置当前Device context 的rendering context
	if(!wglMakeCurrent(hDC,this->m_hGLContext))			// Try To Activate The Rendering Context
	{
		//KillGLWindow();								// Reset The Display
		::MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.5f,0.6f,0.8f,1.0f);					// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	return true;
}

void CvgFrameWorkView::releaseGLContext(void)
{
	if (this->m_hGLContext)										// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))							// Are We Able To Release The DC And RC Contexts?
		{
			::MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(this->m_hGLContext))				// Are We Able To Delete The RC?
		{
			::MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		this->m_hGLContext=NULL;								// Set RC To NULL
	}

	if (m_pDC)
		delete m_pDC;
}

int  CvgFrameWorkView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	this->initGLContext();

	vgKernel::OpenGLSupport::initialiseOpenGLExtension();


	HWND hWND = this->GetSafeHwnd();

	vgMod::ModMisc::getSingleton().initialize( hWND);

	//------------------------------------------
	// 设定用户script
	//------------------------------------------
	vgScript::ScriptManager::getSingleton().addUserScriptFunc( 
		vgUser::exportSystemModule );

	vgScript::ScriptManager::getSingleton().addUserScriptFunc( 
		vgUser::exportOtherModules );

	std::ostringstream o;

	o << "\n"
		<< "import vgCam"		<< "\n"
		<< "import vgSystem"		<< "\n"
		<< "import vgKernel"		<< "\n"
		<< "import vgVector"		<< "\n"
		<< "import vgTerritory"		<< "\n"
		<< "import vgVisualEffects"		<< "\n"
		<< "import vgScript"		<< "\n"
		<< "import vgSprite"		<< "\n"
		<< "import vgConf"		<< "\n"
		<< "import vgMusic"		<< "\n"
		<< "import vgAsyn"		<< "\n"
		;

	


	//----------------------------------------------------------------


	vgGlobal::GlobalConsole::getSingleton().initAfterOpenGLSetup();

	this->SetTimer(1, 15, NULL);

	vgKernel::SelectManager::getSingleton();

	//vgCam::CamManager::getSingleton().setAviRecordCnt(0);
	vgGlobal::CamUtility::setAviRecordCnt(0);


	vgScript::ScriptManager::getSingleton().runScriptString( o.str() );


	//vgGlobal::GlobalFacade::getSingleton();

	VGK_TRACE(
		vgKernel::ClassFactoryManager::getSingleton().getDetails() );



	pClientRenderCmd = new ClientRenderMngRender;
	vgKernel::RenderCommandFacade::AddCommand(pClientRenderCmd);

	vgKernel::SelectManager::getSingleton().registerObserver(this);

	return 0;
}

void CvgFrameWorkView::OnDestroy()
{
	vgKernel::RenderCommandFacade::RemoveCommand(pClientRenderCmd);

	CView::OnDestroy();

	vgGlobal::GlobalConsole::getSingleton().uninitBeforeOpenGLDestroy();
	
	this->releaseGLContext();
	
	vgKernel::SelectManager::getSingleton().removeObserver(this);

}

void CvgFrameWorkView::onEvent(unsigned int eventId, void *param)
{

	return ;

	string sceneImgPath = vgGlobal::SceneFileUtility::getCurrentSceneVgimgPath();

	vgKernel::RendererQueue &renderQueue 
		= vgKernel::SelectManager::getSingleton().getSelectedItems();
	
	
	vgMod::NodeAbsPtrVec nodeAbsVec;
	vgCore::TextureNameMap textureNameMap;

	vgMod::ModUtility::generateNodeIndexFromRender(renderQueue, &nodeAbsVec);
	
	vgMod::ModUtility::generateSelectTexNameVec(&nodeAbsVec, &textureNameMap);
	
	vgCore::TextureNameMap::iterator iter = textureNameMap.begin();
	vgCore::TextureNameMap::iterator iter_end = textureNameMap.end();
	
	stringstream outStringBuffer;
	vector<vgCore::MetaFile> metaVec = vgCore::ModUtility::getMetaFileInfo();

	string outFileFloder = "f:\\";

	FILE *vgimgFile = fopen(sceneImgPath.c_str(), "rb");

	if (vgimgFile == NULL)
	{
		return ;
	}

	while (iter != iter_end)
	{
		for (int i=0; i<metaVec.size(); i++)
		{
			if ( *(iter->first) == metaVec[i].mFilename )
			{
				outStringBuffer << iter->first->c_str() 
					<< " - " 
					<< iter->second->c_str() << "\n";

				VGK_SHOW(outStringBuffer.str());
				
				string outFileName = outFileFloder + metaVec[i].mFilename;

				FILE *fp = fopen(outFileName.c_str(), "wb+");
			
				fseek(vgimgFile, metaVec[i].mStoragePos, SEEK_SET);
				char *buffer = new char[metaVec[i].mFileSize];
				fread(buffer, metaVec[i].mFileSize, 1, vgimgFile);
				fwrite(buffer, metaVec[i].mFileSize, 1, fp);
				fclose(fp);
				
				delete [] buffer;

				outStringBuffer.str("");
			}
		}

		iter ++;
	}

	fclose(vgimgFile);
}

void CvgFrameWorkView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int height = cy;
	int width = cx;

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	//vgLogo::LogoManager::getSingleton().getMenuLogoPtr()->resetCorner();
	// vgKernel::SelectManager::getSingleton().SetViewSize(cx, cy);

	// vgCam::CamManager::getSingleton().setAspectRatioByWindowSize(cx, cy);


	vgKernel::UnTypedPropertyPtr prop; 
	prop = vgKernel::PropertyManager::getSingleton().getProperty("PROP_SCREEN_SIZE");
	
	if (prop != NULL)
	{
		vgKernel::Property<vgKernel::Vec2>* pScreenProp 
			= (vgKernel::Property<vgKernel::Vec2>*)prop;

		assert(pScreenProp != NULL);
		pScreenProp->setValue(vgKernel::Vec2(cx, cy));
	}
	else
	{
		vgKernel::Property<vgKernel::Vec2> *pScreenProp
			= new vgKernel::Property<vgKernel::Vec2>("PROP_SCREEN_SIZE", vgKernel::Vec2(cx, cy));

		vgKernel::PropertyManager::getSingleton().addProperty(pScreenProp);
	}

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


void CvgFrameWorkView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		VGK_CHECK_OPENGL_ERROR();
		renderScene();
		VGK_CHECK_OPENGL_ERROR();
	}
	CView::OnTimer(nIDEvent);
}


// vgm
void CvgFrameWorkView::OnVgmImportVgm()
{
	vgKernel::StringVector strExts;
	strExts.push_back("vgm");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec );

}

void CvgFrameWorkView::OnVgiImportVgi()
{

	vgKernel::StringVector strExts;
	strExts.push_back("vgi");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec );

}

void CvgFrameWorkView::OnVgmSaveVgm()
{
	//vgGlobal::GlobalFacade::getSingleton().saveModelFileOnly();
	vgGlobal::MeshUtility::saveModelFileOnly();
}

void CvgFrameWorkView::OnVgmiSaveVgmVgi()
{
	//vgGlobal::GlobalFacade::getSingleton().saveModelAndImage();
	vgGlobal::MeshUtility::saveModelAndImage();
}


// 鼠标事件响应
void CvgFrameWorkView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonDblClk(nFlags, point, this);
	vgGlobal::GlobalUtility::responseLButtonDblClk( nFlags, point, this );

	CView::OnLButtonDblClk(nFlags, point);
}

void CvgFrameWorkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonDown(nFlags, point);
	vgGlobal::GlobalUtility::responseLButtonDown( nFlags, point );

	CView::OnLButtonDown(nFlags, point);
}

void CvgFrameWorkView::OnMove(int x, int y)
{
	CView::OnMove(x, y);
}

void CvgFrameWorkView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//vgGlobal::SystemFacade::responseLButtonUp(nFlags, point);
	vgGlobal::GlobalUtility::responseLButtonUp( nFlags, point );

	CView::OnLButtonUp(nFlags, point);
}

void CvgFrameWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
	vgKernel::InputSystem::getSingleton().OnMouseMove(nFlags, point);

	CView::OnMouseMove(nFlags, point);

	static bool m_bIsShow = true;		//@FengYK 2009/11/13
	int y = point.y;					//全屏浮动菜单
	CMainFrame *m_pFrame =(CMainFrame *)(this->GetParentFrame());
	BOOL m_bFullScreen = m_pFrame->IsFullScreen();
	if ( m_bFullScreen)
	{
		if (y<5)
		{
			if ( m_bIsShow)
			{
				m_pFrame->EnableFullScreenMainMenu(TRUE);
				m_pFrame->setMainMenuShowOnFullScreen();
				m_bIsShow = false;
			}
		}
		else
		{
			if (!m_bIsShow)
			{
				m_pFrame->EnableFullScreenMainMenu(FALSE);
				m_pFrame->setMainMenuShowOnFullScreen();
				m_bIsShow = true;
			}
		}
	}
}

 BOOL CvgFrameWorkView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
 {
 	vgKernel::InputSystem::getSingleton().OnMouseWheel(nFlags, zDelta, pt);
 	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
 }

 void CvgFrameWorkView::OnRButtonUp(UINT nFlags, CPoint point)
 {
	vgKernel::InputSystem::getSingleton().OnRButtonUp(nFlags, point);
	 
	CView::OnRButtonUp(nFlags, point);
 }

 void CvgFrameWorkView::OnRButtonDown(UINT nFlags, CPoint point)
 {
	 vgKernel::InputSystem::getSingleton().OnRButtonDown(nFlags, point);
	
	 CView::OnRButtonDown(nFlags, point);
 }


// vgtr
void CvgFrameWorkView::OnVgterrainWireframe()
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void CvgFrameWorkView::OnVgterrainNowireframe()
{
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void CvgFrameWorkView::OnVgterrainTurnon()
{
 
}

void CvgFrameWorkView::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	CView::OnActivateApp(bActive, dwThreadID);
	
	if (bActive)
	{
		VGK_TRACE("View 获得焦点");
	}
	else
	{
		VGK_TRACE("View 失去焦点");
	}
}




void CvgFrameWorkView::OnVgterrainConvertDemToVgtr()
{
	//vgTerrain::TerrainManager::getSingleton().selectDemsToVgtr();
}

void CvgFrameWorkView::OnVgterrainConvertVgtrHeightmap()
{
	//vgTerrain::TerrainManager::getSingleton().convertVgtrToHeightImage();
}



// vg
void CvgFrameWorkView::OnFileImportMod()
{	
	vgGlobal::ModUtility::importModFile();
}

void CvgFrameWorkView::OnFileImportKfm()
{
	vgGlobal::ModUtility::importModFile();
}
void CvgFrameWorkView::OnFileImportMs3d()
{
	vgKernel::StringVector strExts;
	strExts.push_back("ms3d");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec );
}




#if 0
void CvgFrameWorkView::OnCameraCapture()
{
	//vgCam::CamManager::getSingleton().captureToFile();

	CString DefExt;

	DefExt.Format("%s","*.bmp|*.bmp|*.tga|*.tga|*.jpg|*.jpg|");

	CFileDialog dialog( false ,"*",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

	dialog.m_ofn.lpstrTitle = "保存截屏文件";

	if( dialog.DoModal() != IDOK )
	{
		return;
	}

	String FilePathName = dialog.GetPathName();

	//------------------------------------------
	// 从视口创建
	//------------------------------------------
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);

	int width = viewport[2];
	int height = viewport[3];

	char *imageData = new char[width*height*4];		// allocate memory for the imageData

	memset(imageData, 0, width*height*4);	// clear imageData memory contents

	// read the image data from the window
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	for (int i =0 ; i < width * height; i++)
	{
		char data = imageData[i*4];
		imageData[i*4] = imageData[i*4 + 2];
		imageData[i * 4 + 2] = data;
		imageData[i * 4 + 3] = 1;//不透明
	}


	//------------------------------------------
	// 创建image
	//------------------------------------------
	vgImage::CximageWrapperPtr pimg( new vgImage::CximageWrapper() );

	bool create_result = 
		pimg->createFromArray( (unsigned char*)imageData , width , height ,
		32 , false );

	assert( create_result == true );

	//------------------------------------------
	// 保存文件
	//------------------------------------------
	bool save_ret = pimg->saveToFile( FilePathName );
	assert( save_ret == true );

	//-----------------------------------------
	// 清理
	//------------------------------------------
	delete imageData;

}
#endif


// 相机&相机动画
void CvgFrameWorkView::OnCreatcam()
{
	vgGlobal::CamUtility::createViewCam();
}

void CvgFrameWorkView::OnAddanimation()
{
	vgGlobal::CamUtility::importVcrFile();
}

void CvgFrameWorkView::OnAniStart()
{
	vgGlobal::CamUtility::beginRecordVcr();
}

void CvgFrameWorkView::OnAniEnd()
{
	vgGlobal::CamUtility::endRecordVcr();
}

void CvgFrameWorkView::OnAniPlay()
{
	vgGlobal::CamUtility::runVcr();
}

void CvgFrameWorkView::OnAniResume()
{
	vgGlobal::CamUtility::continueRunVcr();
}

void CvgFrameWorkView::OnAniStop()
{
	vgGlobal::CamUtility::stopRunVcr();
}




void CvgFrameWorkView::OnSwitchcam()
{
	vgGlobal::CamUtility::switchViewCam();
}

void CvgFrameWorkView::OnPositiontoobj()
{
	vgGlobal::CamUtility::positionViewCamToRenderer();
}


void CvgFrameWorkView::OnExpAvi()
{
	vgGlobal::CamUtility::exportAvi();
}

void CvgFrameWorkView::OnExpBmp()
{
	VGMSGBOX2(vgGlobal::CamUtility::exportBmp());
}

void CvgFrameWorkView::OnCamReheight()
{

	vgCam::CameraRecord *pCurrentVCR = vgCam::CamManager::getSingleton().getCurrentCameraRecord();

	if (pCurrentVCR == NULL)
	{
		AfxMessageBox("请选择一个相机.");
		return ;
	}

	vgVcrHeightDlg dlg;

	this->SetTimer(1, 150, NULL);

	if (dlg.DoModal() != IDOK)
	{
		this->SetTimer(1, 15, NULL);
		return ;
	}
	this->SetTimer(1, 15, NULL);

	float y = dlg.getTransHeight();

	Vec3 transVec = pCurrentVCR->getOffset();//offset_vcr;
	pCurrentVCR->translate(transVec.x, transVec.y+y, transVec.z);

}

void CvgFrameWorkView::OnVcrAcce()
{
	vgGlobal::CamUtility::accelerateVcrSpeed();
}

void CvgFrameWorkView::OnVcrDeacce()
{
	vgGlobal::CamUtility::decelerateVcrSpeed();
}

// 特效
void CvgFrameWorkView::OnSeFountain()
{
	vgGlobal::EffectUtility::addFountain();
}

void CvgFrameWorkView::OnFireAdd()
{
	vgGlobal::EffectUtility::addFire();
}

void CvgFrameWorkView::OnSeSmoke()
{
	vgGlobal::EffectUtility::addSmoke();
}

void CvgFrameWorkView::OnAddflag()
{
	vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_FLAG );
}

void CvgFrameWorkView::OnWaterConvert()
{
	VGMSGBOX2( vgGlobal::ModUtility::convertToWater() );
}

void CvgFrameWorkView::OnGlassConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToGlass();
	)
}

void CvgFrameWorkView::OnAviNodeConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToAviTex();
	)
}

void CvgFrameWorkView::OnSkyboxConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToSkybox();
	)
}
void CvgFrameWorkView::OnMirrorConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToMirror();
	)
}

void CvgFrameWorkView::OnMetalConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToMetal();
	)
}

void CvgFrameWorkView::OnConvertBrigthfloor()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToBrightFloor();
	)
}

void CvgFrameWorkView::OnDyntextureConvert()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToDynTex();
	)
}



void CvgFrameWorkView::OnRain() 
{
	vgGlobal::EffectUtility::beginRain();
}

void CvgFrameWorkView::OnSnow() 
{	
	vgGlobal::EffectUtility::beginSnow();
}
void CvgFrameWorkView::OnRainDel() 
{	
	vgGlobal::EffectUtility::endRain();
}

void CvgFrameWorkView::OnSnowDel() 
{	
	vgGlobal::EffectUtility::endSnow();
}

void CvgFrameWorkView::OnSeFog()
{
	vgCore::MovingManager::getSingleton().getClimate()->fogoff();
}
void CvgFrameWorkView::OnFogDel() 
{
	vgCore::MovingManager::getSingleton().getClimate()->fogoff();
}


void CvgFrameWorkView::OnConfigdynbillboard()
{
	// TODO: 在此添加命令处理程序代码
	VGMSGBOX2( vgGlobal::EffectUtility::configDynbillboard() );
}

void CvgFrameWorkView::OnDynamicbillboard()
{
	vgGlobal::EffectUtility::generateDynbillboard();
}


// 音效
void CvgFrameWorkView::On3dsoundAdd()
{
	vgGlobal::SoundUtility::addStereo();
}

void CvgFrameWorkView::OnBacksoundSet()
{
	vgGlobal::SoundUtility::addBackgroundSound();
}

// billboard tree
void CvgFrameWorkView::OnSettree()
{
	VGMSGBOX2( vgGlobal::EffectUtility::configPlanting() );
}

#if 0
void CvgFrameWorkView::OnBeginplant()
{ 
	vgGlobal::EffectUtility::beginPlanting();
}
void CvgFrameWorkView::OnSelect()
{
	vgMod::ModMisc::getSingleton().setStatus( -1 );
}

void CvgFrameWorkView::OnPlantinline()
{
	vgGlobal::EffectUtility::plantInLine();
}

#endif
// AutoBuild
void CvgFrameWorkView::OnAutobuildClone()
{
	vgGlobal::ModUtility::cloneAutoBuildObj();
}

void CvgFrameWorkView::OnAutobuild()
{
	VGMSGBOX2(
		vgGlobal::ModUtility::convertToAutoBuild();
	)
} 

//触发器
void CvgFrameWorkView::OnTriggerSetAs()
{
	vgGlobal::EffectUtility::setAsTrigger();
}

void CvgFrameWorkView::OnTriggerConfig()
{
	VGMSGBOX2( vgGlobal::EffectUtility::configTrigger() );
}

// terrain
void CvgFrameWorkView::OnVgterrainNewVtr()
{

	vgKernel::StringVector strExts;
	strExts.push_back("vtr");

	vgKernel::StringVector filePaths = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	if(filePaths.empty())
	{
		return;
	}

	vgGlobal::SceneFileUtility::importGivenFile( filePaths[0] );

}

// GIS
void CvgFrameWorkView::OnZuobiao() 
{
	vgGlobal::GisUtility::measureGisPoint();
}

void CvgFrameWorkView::OnJuli() 
{
	vgGlobal::GisUtility::measureGisLength();
}

void CvgFrameWorkView::OnMianji() 
{
	vgGlobal::GisUtility::measureGisArea();
}

void CvgFrameWorkView::OnTiji() 
{
	vgGlobal::GisUtility::measureGisVolume();
}


void CvgFrameWorkView::OnUpdateZuobiao(CCmdUI *pCmdUI)
{
	bool bCheck = vgGlobal::GisUtility::updateStateGisPoint();
	pCmdUI->SetCheck(bCheck);
}

void CvgFrameWorkView::OnUpdateJuli(CCmdUI *pCmdUI)
{
	bool bCheck = vgGlobal::GisUtility::updateStateGisLength();
	pCmdUI->SetCheck(bCheck);

}

void CvgFrameWorkView::OnUpdateMianji(CCmdUI *pCmdUI)
{
	bool bCheck = vgGlobal::GisUtility::updateStateGisArea();
	pCmdUI->SetCheck(bCheck);
}


void CvgFrameWorkView::OnGismatch()
{
	vgMod::GisRoadMatch *_gismatch = new vgMod::GisRoadMatch();

	vgDlgGismatch _Dlgmatch( _gismatch, this );

	int status;

	VGMSGBOX2( status = _Dlgmatch.DoModal())

		if ( status == IDCANCEL )
		{
			return;
		}

		vgCore::MovingManager::getSingleton().addGisMatchNode( _gismatch );

}



// Tools
void CvgFrameWorkView::OnToolMakerVgm()
{
	return;

	String	binPath = vgKernel::SystemUtility::getCurrentProcessPath();
	
	binPath += "vgModelGenerator_Release.exe";

	VGMSGBOX2(
		ShellExecute(NULL, "open", CString(binPath.c_str()), NULL, NULL, SW_SHOWNORMAL)	
		)
	
}

void CvgFrameWorkView::OnToolMakerVgi()
{
	return;

	String	binPath = vgKernel::SystemUtility::getCurrentProcessPath();
	
	binPath += "vgImagePacker_Release.exe";

	VGMSGBOX2(
		ShellExecute(NULL, "open", CString(binPath.c_str()), NULL, NULL, SW_SHOWNORMAL)	
		)
}
void CvgFrameWorkView::OnToolMakerDds()
{
	return;

	String	binPath = vgKernel::SystemUtility::getCurrentProcessPath();

	binPath += "vgImageConverter_Release.exe";

	VGMSGBOX2(
		ShellExecute(NULL, "open", CString(binPath.c_str()), NULL, NULL, SW_SHOWNORMAL)	
		)
}


// Edit
void CvgFrameWorkView::OnEditSelect()
{
	// TODO: 在此添加命令处理程序代码
	vgMod::ModMisc::getSingleton().setStatus( ID_EDIT_SELECT );

}

void CvgFrameWorkView::OnEditSelectAll()
{
	vgGlobal::EditUtility::selectionAll();
}

void CvgFrameWorkView::OnEditSelectClear()
{
	vgGlobal::EditUtility::clearSelection();
}


void CvgFrameWorkView::OnFindObj()
{
	// TODO: 在此添加命令处理程序代码
	VGMSGBOX2( vgGlobal::EditUtility::FindObject() );
}

void CvgFrameWorkView::OnSelectShapeRect()
{
	vgGlobal::EditUtility::selectShapeRect();
}

void CvgFrameWorkView::OnSelectShapePolygon()
{
	vgGlobal::EditUtility::selectShapePolygon();
}

void CvgFrameWorkView::OnSelectRegionNew()
{
	vgGlobal::EditUtility::selectRegionNew();
}

void CvgFrameWorkView::OnSelectRegionAdd()
{
	vgGlobal::EditUtility::selectRegionAdd();
}
void CvgFrameWorkView::OnSelectRegionSubtract()
{
	vgGlobal::EditUtility::selectRegionSubtract();
}

void CvgFrameWorkView::OnSelectRegionIntersect()
{
	vgGlobal::EditUtility::selectRegionIntersect();
}

void CvgFrameWorkView::OnSelectModeInclude()
{
	vgGlobal::EditUtility::selectModeInclude();
}

void CvgFrameWorkView::OnSelectModeIntersect()
{
	vgGlobal::EditUtility::selectModeIntersect();
}

void CvgFrameWorkView::OnEditTranslate()
{
	vgGlobal::EditUtility::translate();
}

void CvgFrameWorkView::OnUpdateEditTranslate( CCmdUI *pCmdUI )
{
	bool bCheck = vgGlobal::EditUtility::updateTranslate();
	pCmdUI->SetCheck( bCheck );
}

void CvgFrameWorkView::OnEditRotate()
{
	vgGlobal::EditUtility::rotate();
}

void CvgFrameWorkView::OnUpdateEditRotate( CCmdUI *pCmdUI )
{
	bool bCheck = vgGlobal::EditUtility::updateRotate();
	pCmdUI->SetCheck( bCheck );
}

void CvgFrameWorkView::OnEditScale()
{
	vgGlobal::EditUtility::scale();
}

void CvgFrameWorkView::OnUpdateEditScale( CCmdUI *pCmdUI )
{
	bool bCheck = vgGlobal::EditUtility::updateScale();
	pCmdUI->SetCheck( bCheck );
}

void CvgFrameWorkView::OnUndo()
{
	vgGlobal::EditUtility::undo();
}

void CvgFrameWorkView::OnRedo()
{
	vgGlobal::EditUtility::redo();
}

void CvgFrameWorkView::OnEditSetTransparent()
{
	vgGlobal::EditUtility::setSelTransparent();
}

void CvgFrameWorkView::OnEditSetUnTransparent()
{
	vgGlobal::EditUtility::setSelUnTransparent();
}

void CvgFrameWorkView::OnUpdateEditSetTransparent(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( vgGlobal::EditUtility::updateSetSelTransprant() );
}

void CvgFrameWorkView::OnUpdateEditSetUntransparent(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( vgGlobal::EditUtility::updateSetSelUnTransprant() );
}

void CvgFrameWorkView::OnEditSingleFaceRenderSel()
{
	vgGlobal::EditUtility::SingleFaceRenderSelected();
}

void CvgFrameWorkView::OnEditSingleFaceRenderAll()
{
	vgGlobal::EditUtility::SingleFaceRenderAll();
}
void CvgFrameWorkView::OnUpdateEditSingleFaceRenderSelect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !vgGlobal::EditUtility::updateSingleFaceRenderAll() );
	pCmdUI->SetCheck( vgGlobal::EditUtility::updateSingleFaceRenderSelect() );
	
}
void CvgFrameWorkView::OnUpdateEditSingleFaceRenderAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( !vgGlobal::EditUtility::updateSingleFaceRenderSelect() );
	pCmdUI->SetCheck( vgGlobal::EditUtility::updateSingleFaceRenderAll() );
}
void CvgFrameWorkView::OnMeshOrLine()
{
	vgGlobal::GlobalUtility::renderEntityOrLine();
}

void CvgFrameWorkView::OnUpdateMeshOrLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck( vgGlobal::GlobalUtility::updateRenderEntityOrLine() );
}

void CvgFrameWorkView::OnTanslateSelected()
{
	VGMSGBOX2( vgGlobal::EditUtility::translateSeleted() );
}


void CvgFrameWorkView::OnEditTranall()
{
	VGMSGBOX2( vgGlobal::EditUtility::translateAll() );
}


// Multi Channel多通道
void CvgFrameWorkView::OnChannel1()
{
	// TODO: 在此添加命令处理程序代码
	//vgCam::CamManager::getSingleton().setChannelNum(1);
	vgGlobal::CamUtility::setChannelNum(1);
}

void CvgFrameWorkView::OnChannel0()
{
	// TODO: 在此添加命令处理程序代码
	//vgCam::CamManager::getSingleton().setChannelNum(0);
	vgGlobal::CamUtility::setChannelNum(0);
}

void CvgFrameWorkView::OnChannelm1()
{
	// TODO: 在此添加命令处理程序代码
	//vgCam::CamManager::getSingleton().setChannelNum(-1);
	vgGlobal::CamUtility::setChannelNum(-1);
}


// about
void CvgFrameWorkView::OnAppAbout()
{
	VGMSGBOX2( vgGlobal::GlobalUtility::showAboutDlg() );
}


// File
void CvgFrameWorkView::OnSceneRead()
{
	vgGlobal::SceneFileUtility::openSceneFile();

	loadAddonMod();
}


void CvgFrameWorkView::loadAddonMod()
{
	// 取得场景路径

	string vgScenePath = vgGlobal::SceneFileUtility::getCurrentScenePath();

	// 读取txt
	string addonPath = vgScenePath + "addon.txt";

	FILE *fp = fopen(addonPath.c_str(), "r");

	if (fp == NULL)
	{
		// AfxMessageBox("no addons.");
		return ;
	}

	vgKernel::StringVector mod;

	char buffer[256];

	while (fgets(buffer, 256, fp) != NULL)
	{
		if (buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';

		string modPath = vgScenePath + "mod\\";
		modPath += buffer;

		mod.push_back(modPath);
	}

	fclose(fp);

	for (int i=0; i<mod.size(); i++)
	{
		FILE *fpMod = fopen(mod[i].c_str(), "r");

		if (fpMod == NULL)
		{
			continue ;
		}

		fclose(fp);

		vgGlobal::ModUtility::importModFile(mod[i]);
	}
}

void CvgFrameWorkView::OnSceneSave()
{
	vgGlobal::SceneFileUtility::saveSceneFile();
}

void CvgFrameWorkView::OnPublishCollect()
{
	// Part 1：vg、vgimg
#if 0
	string	strSavePath = 
		vgCore::QuadtreeSceneManager::getSingleton().saveSceneToVG();

	if (strSavePath.empty())
	{
		return;
	}

	// Part 2：vgm、vgi
	vgGlobal::GlobalFacade::getSingleton().collectModelAndImage(strSavePath);

	MessageBox("收集资源操作成功!");
	return;
#endif
}

void CvgFrameWorkView::OnFileImport()
{	
	vgGlobal::SceneFileUtility::importFiles();
}

void CvgFrameWorkView::OnFileExport()
{
	vgGlobal::SceneFileUtility::exportFile();
}


// 优化
void CvgFrameWorkView::OnOccSwitch()
{
	// TODO: 在此添加命令处理程序代码
	if (vgOcclusion::vgOcclusionManager::getSingleton().GetOccState())
	{
		vgOcclusion::vgOcclusionManager::getSingleton().DisableOcc();
	}
	else
		vgOcclusion::vgOcclusionManager::getSingleton().EnableOcc();
}

void CvgFrameWorkView::OnUpdateOccSwitch(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(vgOcclusion::vgOcclusionManager::getSingleton().GetOccState());
}
// vgTerritory
void CvgFrameWorkView::OnVgtAttach()
{
	// TODO: 在此添加命令处理程序代码
	vgGlobal::GlobalUtility::attachRendererToTerrain( 
		&vgKernel::SelectManager::getSingleton().getSelectedItems() , true );
}

void CvgFrameWorkView::OnTerrainCollisionDetect()
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCollisionDetectedFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCollisionDetectedFlag, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	(*pfn2)( !(*pfn1)() );
}

void CvgFrameWorkView::OnUpdateTerrainCollisionDetect(CCmdUI *pCmdUI)//zhu，开启地面碰撞
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCollisionDetectedFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::On32972()
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getRenderFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setRenderFlag, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	(*pfn2)( !(*pfn1)() );
	
	return ;
}

void CvgFrameWorkView::OnUpdate32972(CCmdUI *pCmdUI)//开启地形渲染
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getRenderFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::On32973()
{	
	VGK_DLL_RUN_CLASSFUNC( VGT_DLL_NAME , 
		TerrainManager , dropTerrianData )();
}

void CvgFrameWorkView::OnUpdate32973(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert(  pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
}

void CvgFrameWorkView::On32974()//剖面分析
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceAnalysisFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutSurfaceAnalysisFlag, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	(*pfn2)( !(*pfn1)() );
}

void CvgFrameWorkView::OnUpdate32974(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceAnalysisFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::OnVgtVisibility()//通透分析
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceVisibilityFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutSurfaceVisibilityFlag, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	(*pfn2)( !(*pfn1)() );
}
void CvgFrameWorkView::OnUpdateVgtVisibility(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceVisibilityFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::OnUpdateVgtAttach(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
}

void CvgFrameWorkView::OnVgtCutAnalysis2()//剪切面的剖面分析
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceAnalysisFlag2, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, setCutSurfaceAnalysisFlag2, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	(*pfn2)( !(*pfn1)() );
}

void CvgFrameWorkView::OnUpdateVgtCutAnalysis2(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getCutSurfaceAnalysisFlag2, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::OnVgtTerrainSave()
{
	// 需要重新整理才能使用

	VGK_DLL_RUN_FUNC(
		VGT_DLL_NAME , saveInEditMode )();

}

void CvgFrameWorkView::OnUpdateVgtTerrainSave(CCmdUI *pCmdUI)
{

	pCmdUI->Enable( VGK_DLL_CHECK_LOAD( VGT_DLL_NAME ) );

}
void CvgFrameWorkView::Onterraintesting()//地形还原
{
	// 需要重新整理才能使用
	VGK_DLL_RUN_FUNC(
		VGT_DLL_NAME , restoreInEditMode )();


}
void CvgFrameWorkView::OnUpdate33109(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( VGK_DLL_CHECK_LOAD( VGT_DLL_NAME ) );
}

void CvgFrameWorkView::OnVgtBlend()
{


	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		::MessageBox(NULL , "没载入地形dll!" , "Error" , MB_OK );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager , 
		getBlendFlag, pfn1 );

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager , 
		setBlendFlag, pfn2 );

	if ( pfn1 == NULL || pfn2 == NULL )
	{
		return;
	}

	(*pfn2)( !( *pfn1 )() );

}

void CvgFrameWorkView::OnUpdateVgtBlend(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, getBlendFlag, pfn1 );
	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );

}

void CvgFrameWorkView::OnVgtMappingOrigin()
{
	// 需要重新整理才能使用

	using namespace vgTerritory;
	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_FUNC( plg, getTerrainCoord, pfn );

	assert( pfn != NULL );

	vgKernel::Vec3* coo = (*pfn)();

	if ( coo == NULL )
	{
		return;
	}
	else
	{
		CoordSystem::getSingleton().setProjectionCoord( *coo );
		delete coo;
	}

	//assert(0);
#if 0
	vgTerritory::VtrHeaderPtr header = 
		vgTerritory::ElevationManager::getSingleton().getMainFileHandleVtr()->getHeader();

	if ( header.isNull() == true )
	{
		return;
	}

	vgCore::vgCoordinate::getSingleton().SetSceneCood( 
		vgCore::Vector3( header->originX , header->originY , -header->originZ) );
#endif
}



void CvgFrameWorkView::OnUpdateVgtMappingOrigin(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGT_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, TerrainManager, hasTerrainData, pfn2 );

	assert( pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
}
// vgGIS3D
void CvgFrameWorkView::OnHideVec()
{
	//vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_HIDE_VEC, this);
#if 0
	if(vgGIS3D::GIS3D::getSingleton().getGisState() != vgGIS3D::GisHideVec)
		vgGIS3D::GIS3D::getSingleton().setGisState(vgGIS3D::GisHideVec );
	else
		vgGIS3D::GIS3D::getSingleton().setGisState(vgGIS3D::GisNone);
#endif
}

void CvgFrameWorkView::OnNoselVec()
{
	assert(0);
	// TODO: 在此添加命令处理程序代码
	//vgApp.appProc(VG_COMMAND_GIS, VG_COMMAND_GIS_SELNONE_VEC, this);
	//vgGIS3D::GIS3D::getSingleton().setCurrentVertexStringPtr(NULL);
	//vgGIS3D::GIS3D::getSingleton().setGisState(vgGIS3D::GisNone);
}




void CvgFrameWorkView::OnNdbConnect()
{
	// TODO: 在此添加命令处理程序代码

	assert(0 && "禁用此功能");
	return;

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

	if ( plg == NULL )
	{
		AfxMessageBox("动态库未加载!");
		return;
	}

	DBConnectDlg dialog;

	VGMSGBOX2(dialog.DoModal());
}

void CvgFrameWorkView::OnNdbDisconnect()
{
	// TODO: 在此添加命令处理程序代码

	assert(0 && "禁用此功能");
	return;

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

	if ( plg == NULL )
	{
		AfxMessageBox("动态库未加载!");
		return;
	}

	if (! vgDatabase::DatabaseManager::getSingleton().CloseDatabase())
	{
		AfxMessageBox("数据库未连接或关闭失败.");
	}
	else
	{
		AfxMessageBox("已关闭数据库连接.");
	}
}

void CvgFrameWorkView::OnNdbCondition()
{
	// TODO: 在此添加命令处理程序代码
	assert(0 && "禁用此功能");
	return;

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

	if ( plg == NULL )
	{
		AfxMessageBox("动态库未加载!");
		return;
	}

	if (! DatabaseManager::getSingleton().IsOpen())
	{
		DBConnectDlg dialog;

		VGMSGBOX2(dialog.DoModal());

		if (! DatabaseManager::getSingleton().IsOpen())
		{
			return ;
		}
	}

// 	if (!vgDatabase::ProfileManager::getSingleton().IsProfileLoaded())
// 	{
// 		AfxMessageBox("未加载profile文件，请先打开场景vg文件！");
// 		return;
// 	}

	if(m_dbCondition)
	{
		m_dbCondition->SetForegroundWindow();
	}
	else
	{
		m_dbCondition = new DBCondition(this);
		m_dbCondition->Create(DBCondition::IDD, GetDesktopWindow());
		m_dbCondition->ShowWindow(SW_SHOW);
	}

}

void CvgFrameWorkView::OnShapefileDb()
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

	if ( plg == NULL )
	{
		AfxMessageBox("动态库未加载!");
		return;
	}

	if (!vgDatabase::DatabaseManager::getSingleton().IsOpen())
	{
		AfxMessageBox("请先连接数据库！");
		return;
	}
	//vgDatabase::DatabaseManager::getSingleton().CreateShapeTable();
}

void CvgFrameWorkView::OnCollisionOnoff()
{
	vgGlobal::CamUtility::onOrOffCollicition();
}

void CvgFrameWorkView::OnUpdateCollisionOnoff(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( vgGlobal::CamUtility::updateOnOrOffCollication() );
}




// ShapeFile -----------------------------------------------------------------
void CvgFrameWorkView::OnVectorShpExport2db()
{
#if 0
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGD_DLL_NAME );

	if ( plg == NULL )
	{
		AfxMessageBox("动态库未加载!");
		return;
	}

	if (! DatabaseManager::getSingleton().IsOpen())
	{
		DBConnectDlg dialog;

		VGMSGBOX2(dialog.DoModal());

		if (! DatabaseManager::getSingleton().IsOpen())
		{
			return ;
		}
	}

	VGK_DLL_RES_SWITCH_NAME(VGSH_DLL_NAME);

	CDlgShpToDBEx dialog;

	VGMSGBOX2(dialog.DoModal());
#endif
}

// Renfang Dingzhi add-------------------------------------------------------------
void CvgFrameWorkView::OnVgviBgConfig()
{
	vgVisualEffects::BackgroundManager::getSingleton().configBackground();
}


// 脚本			-------------------------------------------------------------
void CvgFrameWorkView::OnScriptRunfile()
{
	//vgScript::ScriptManager::getSingleton().createMultiSelectDailogAndRunScript();
}

void CvgFrameWorkView::OnScriptTestscript()
{
	//vgCam::CamFacade::gotoCameraByName( "ViewCam0" );
	AfxGetApp()->m_pMainWnd->SetWindowText( "我们的发生发生大幅阿飞" );  
}

void CvgFrameWorkView::OnScriptTestmenu()
{

	//vgScript::ScriptManager::getSingleton().runScriptConsole();

	//return;
	//CWnd *wnd = AfxGetMainWnd();


	//CMainFrame* mainwnd = ( CMainFrame* )wnd;
	//mainwnd->loadScriptMenu( "d:\\TestFile.dat" , "fasdf" , 0 );

	//mainwnd->loadScriptMenu( "d:\\TestFile2.dat" , "哈士大夫df" , 0 );


	//std::wstring wstr = 
	//	vgKernel::StringUtility::convertStringToWString( "哈哈发大水" );
	//VGK_SHOW( 
	//	vgKernel::StringUtility::convertWStringToString( wstr ) );

}

void CvgFrameWorkView::OnScriptConsole()
{
	//vgScript::ScriptManager::getSingleton().runScriptConsole();

	return;

}

// 打包成EXE			-------------------------------------------------------------
void CvgFrameWorkView::OnPublishPackageExe()
{// TODO: 在此添加命令处理程序代码
	
#if 0
	//-----Step 1、获取所打的包的绝对路径 并 使用包的名字新建供打包的临时目录	------------------
	String	strPackageSrcPathTemp, strPackageDestiPath, 
		strPackageName,strPackageFileName;
	
	//获取路径
	CString DefExt;
	DefExt.Format("%s","EXE文件(*.EXE)|*.EXE|");

	CFileDialog dlgmodelFile(false,"EXE",NULL,
	OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON|OFN_OVERWRITEPROMPT,DefExt);

	dlgmodelFile.m_ofn.lpstrTitle="打包成EXE";

	if(dlgmodelFile.DoModal()!=IDOK)
	{
		return;
	}
	
	strPackageDestiPath = dlgmodelFile.GetPathName();
	strPackageName = dlgmodelFile.GetFileTitle();
	strPackageFileName = dlgmodelFile.GetFileName();
	

	//新建目录
	strPackageSrcPathTemp = vgCore::QuadtreeSceneManager::getSingleton().getBinaryPath();
	strPackageSrcPathTemp += "\\" + strPackageName;
	CreateDirectory( strPackageSrcPathTemp.c_str(), 0 );
	
	//-----Step 2、保存	------------------------------------------------------------------------
	String strSrcFilePath = strPackageSrcPathTemp + "\\" + strPackageFileName;
	OnSceneSave(strSrcFilePath);

	//-----Step 3、打包	------------------------------------------------------------------------
	vgGlobal::GlobalFacade::getSingleton().packageToEXE(strPackageSrcPathTemp
		,strPackageDestiPath);
#endif

	return;
}

// 重置场景			-------------------------------------------------------------
void CvgFrameWorkView::OnSceneReset()
{
	// TODO: 在此添加命令处理程序代码
	
	//vgVector::VectorManager::getSingleton().reset();
	
	//vgCore::QuadtreeSceneManager::getSingleton().ResetScene();

	std::ostringstream o;

	o << "是否进行复位操作? 操作将删除所有数据.";

	int ret = VGK_WARN( vgKernel::Warning::WARN_INTERNAL_WARNING , 
		vgKernel::Warning::BUTTON_YES_NO, 
		o.str(),
		"CvgFrameWorkView::OnSceneReset");

	if ( ret == vgKernel::Warning::RETURN_NO )
	{
		return;
	}

	vgGlobal::SceneFileUtility::resetScene();

}

// 卸载矢量模型
void CvgFrameWorkView::OnVectorShpUnload()
{

}



// vgShape
void CvgFrameWorkView::OnVgscUserScriptConfig()
{
	//vgScript::ScriptManager::getSingleton().runUserScriptConfig();
}



void CvgFrameWorkView::OnGisSun()
{
	//zhu 日照分析对话框啊
	//vgDlgSun *dlg=new vgDlgSun;
	//dlg->Create(IDD_DLG_SUN,NULL);			
	//dlg->SetWindowPos(AfxGetMainWnd(),400,300,NULL,NULL,SWP_NOSIZE);
	//dlg->ShowWindow(SW_SHOW);
	////vgCore::MFCApplication::getSingleton().b_DrawShadow=true;//开启阴影
}



void CvgFrameWorkView::OnVectorShpGreenRatio()
{
	// TODO: 在此添加命令处理程序代码
	vgKernel::InputSystem::getSingleton().setCurrentStatus(
		VG_INPUT_VECTOR_ANALYSIS_GREEN);

	assert(0);

	//if( !vgShape::ShapeManager::getSingleton().setQueryRatioFlag(vgShape::GREEN_RATIO) )
	//{
	//	vgKernel::InputSystem::getSingleton().setDefaultStatus();
	//}

}

void CvgFrameWorkView::OnVgshapeReadshpfile()
{
	vgKernel::StringVector strExts;
	strExts.push_back("shp");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec );
}

void CvgFrameWorkView::OnVgshapeSelectshparea()
{
	vgGlobal::ShapeUtility::convertShpToEditState();
}

void CvgFrameWorkView::OnUpdateVgshapeSelectshparea(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( 
		vgGlobal::ShapeUtility::getSelectFlag()
		);
}


void CvgFrameWorkView::OnVgshapeSaveasshape()
{
	assert(0);
#if 0
	vgBaseEntry* entry = 
		vgUI::UIController::getSingleton().GetCurrentSelectedNode();

	if ( entry == NULL )
	{
		MessageBox( "请选中导出shp对象" );
		return;
	}

	ShapeDataSourceEntry* ds = dynamic_cast<ShapeDataSourceEntry*>
		( entry );

	if ( ds == NULL )
	{
		MessageBox( "请选中shp对象" );
		return;
	}

	vgShape::DataSourcePtr psource = 
		ds->getShapeDataSource();
	assert( psource.isNull() == false );

	//------------------------------------------
	// 弹出对话框
	//------------------------------------------
	CString DefExt;

	DefExt.Format("%s","shp文件(*.shp)|*.shp|");

	CFileDialog dlgmodelFile(false,"shp",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

	dlgmodelFile.m_ofn.lpstrTitle="保存shp文件";

	if(dlgmodelFile.DoModal()==IDOK)
	{
		String FilePathName = dlgmodelFile.GetPathName();

		bool saveok = psource->saveToFilePath( FilePathName );

		if ( saveok == false )
		{
			::MessageBox(NULL , "保存失败" , "Error" , MB_OK );
		}
	}

#endif
	return;
}

void CvgFrameWorkView::OnQueryplaninfoQueryplotratio()
{
	assert(0);

	//// TODO: 在此添加命令处理程序代码
	//vgKernel::InputSystem::getSingleton().setCurrentStatus(
	//	VG_INPUT_VECTOR_ANALYSIS_GREEN);

	//if( !vgShape::ShapeManager::getSingleton().setQueryRatioFlag(vgShape::PLOT_RATIO) )
	//{
	//	vgKernel::InputSystem::getSingleton().setDefaultStatus();
	//}
}

void CvgFrameWorkView::OnUpdateQueryplaninfoQueryplotratio(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	//pCmdUI->SetCheck( vgShape::PLOT_RATIO ==
	//	vgShape::ShapeManager::getSingleton().getQueryType());
}

void CvgFrameWorkView::OnVgshapeTranslateall()
{
	// TODO: 在此添加命令处理程序代码
	CDlgTranslateVector dialog;

	VGMSGBOX2(dialog.DoModal());
}


void CvgFrameWorkView::OnVgshapeReadgridshpfile()
{
	vgKernel::StringVector strExts;
	strExts.push_back("shp");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec , true );
}

void CvgFrameWorkView::OnVgshapeImporttext()
{
	vgAutoBuild::AutoBuildManager::getSingleton().importShpInfo();
}


void CvgFrameWorkView::OnVgshapeCaculateposition()
{
	// TODO: 在此添加命令处理程序代码
	int schem, year;
	DlgAutoIn dlg;

	this->SetTimer(1, 150, NULL);

	if (dlg.DoModal() == IDOK)
	{
		schem = dlg.getSchemId();
		year = dlg.getYear();
	}
	vgAutoBuild::AutoBuildManager::getSingleton().generateBuildingAll(schem, year);

	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnVgshapeClearplan()
{
	// TODO: 在此添加命令处理程序代码
	vgAutoBuild::AutoBuildManager::getSingleton().clearPlan();
}

void CvgFrameWorkView::OnVgshapeGenerateselected()
{
	// TODO: 在此添加命令处理程序代码
	int schem, year;
	DlgAutoIn dlg;

	this->SetTimer(1, 150, NULL);

	if (dlg.DoModal() == IDOK)
	{
		schem = dlg.getSchemId();
		year = dlg.getYear();

		vgAutoBuild::AutoBuildManager::getSingleton().generateBuildingSelected(schem, year);
	}

	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnVgshapeImportinfofromtxt()
{
	// TODO: 在此添加命令处理程序代码
	vgAutoBuild::AutoBuildManager::getSingleton().OnReadTxt();
}

void CvgFrameWorkView::OnAutobuildingCloseinfofile()
{
	// TODO: 在此添加命令处理程序代码
	vgAutoBuild::AutoBuildManager::getSingleton().removeAllShpInfo();

}



// vgPlan
void CvgFrameWorkView::OnVgplanAddground()
{
	// TODO: 在此添加命令处理程序代码
// 	vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();
// 
// 	if (pScene != NULL)
// 	{
// 		if ( pScene->addGroundFromSelectedShp() )
// 		{
// 			AfxMessageBox("添加Ground成功.");
// 		}
// 		else
// 		{
// 			AfxMessageBox("未能添加Ground.");
// 		}
// 	}
}

void CvgFrameWorkView::OnVgplanAddsecne()
{
	// TODO: 在此添加命令处理程序代码
	//vgPlan::vgPlanManager::getSingleton().addNewScene();
}




void CvgFrameWorkView::OnVgshadowTurnonshadow()
{

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, getShadowEnabled, enabled_func );
	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, turnOffShadowEffect, turnoff_func );
	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, turnOnShadowEffect, turnon_func );


	if ( enabled_func == NULL || 
		turnon_func == NULL || 
		turnoff_func == NULL )
	{
		return ;
	}


	// TODO: Add your command handler code here
	// 当已经开启的时候，这个时候先卸载。
	if ( (*enabled_func)() )
	{
		(*turnoff_func)();
	}

	vgKernel::RendererQueue* qu = 
		&vgKernel::SelectManager::getSingleton().getSelectedItems();

	//vgKernel::Vec3 dir( -1 , -1 , 2 );
	//dir.normalise();

	(*turnon_func)( qu ,NULL , true );

}

void CvgFrameWorkView::OnVgshadowSelectshadowcastobjects()
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, getShadowCastObjects, getobjs_func );



	if ( getobjs_func == NULL )
	{
		return ;
	}



	vgKernel::ShadowCastObjectVec* vec = 
		(*getobjs_func)();

	if ( vec == NULL )
	{
		MessageBox( "没有投影的物体" );
		return;
	}

	vgKernel::SelectManager::getSingleton().clearSelection();

	vgKernel::ShadowCastObjectVec::iterator iter = vec->begin();
	vgKernel::ShadowCastObjectVec::iterator iter_end = vec->end();

	for( ; iter != iter_end ; ++ iter )
	{
		vgKernel::Renderer* ren = 
			dynamic_cast<vgKernel::Renderer*>( *iter );

		if ( ren != NULL )
		{
			vgKernel::SelectManager::getSingleton().addSelection( ren , false );
		}	
	}

	vgKernel::SelectManager::getSingleton().updateBox();

}

void CvgFrameWorkView::OnVgplanSetparameter()
{
	// TODO: Add your command handler code here
}

void CvgFrameWorkView::OnVgshadowChange()
{

	VGK_DLL_RES_SWITCH_NAME( VGSO_DLL_NAME );


	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_FUNC( plg, doDailogAndChangeSolarLightDirection, change_func );


	if ( change_func == NULL )
	{
		return ;
	}

	this->SetTimer(1, 150, NULL);

	(*change_func)();

	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnVgshadowTurnoffshadow()
{

	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, getShadowEnabled, enabled_func );
	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, turnOffShadowEffect, turnoff_func );
	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, turnOnShadowEffect, turnon_func );


	if ( enabled_func == NULL || 
		turnon_func == NULL || 
		turnoff_func == NULL )
	{
		return ;
	}

	(*turnoff_func)();

}

void CvgFrameWorkView::OnVgshadowSolaranalysis()
{
	VGK_DLL_RES_SWITCH_NAME( VGSO_DLL_NAME );


	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_FUNC( plg, doDailogAndSolarAnalysis, analysis_func );


	if ( analysis_func == NULL )
	{
		return ;
	}

	this->SetTimer(1, 150, NULL);

	(*analysis_func)();

	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnUpdateVgshadowSolaranalysis(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( FALSE );

	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager,getSolarAnalysisEnable, func );

	if ( func == NULL )
	{
		return ;
	}


	pCmdUI->SetCheck( (*func)() );
}

void CvgFrameWorkView::OnUpdateVgshadowTurnonshadow(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( FALSE );

	using namespace vgKernel;

	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGSO_DLL_NAME );

	if ( plg == NULL )
	{
		return ;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, SolarManager, getShadowEnabled, func );

	if ( func == NULL )
	{
		return ;
	}


	pCmdUI->SetCheck( (*func)() );

}


void CvgFrameWorkView::OnTesttestSelectchangecolor()
{
	vgKernel::RendererQueue& selectedBuffer = vgKernel::SelectManager::
		getSingleton().getSelectedItems();
	if (selectedBuffer.empty())
	{
		AfxMessageBox("请选择需要着色的模型！");
		return;
	}

	vgKernel::RendererQueue::iterator iter = selectedBuffer.begin();
	vgKernel::RendererQueue::iterator end = selectedBuffer.end();
	for (; iter != end; iter++)
	{
		vgKernel::ColorableObject* pNode = 
			dynamic_cast<vgKernel::ColorableObject*>(*iter);

		if ( pNode == NULL )
		{
			continue;
		}
		assert( pNode != NULL );

		pNode->setColorableValue( vgKernel::RgbaQuad( 255, 0 , 0 , 128) );
	}
}

// plan
void CvgFrameWorkView::OnVgplanAddstreetline()
{
// 	// TODO: 在此添加命令处理程序代码
// 	vgPlan::vgPlanScene *pScene = vgPlan::vgPlanManager::getSingleton().getActiveScene();
// 	
// 	if (pScene != NULL)
// 	{
// 		if ( pScene->addStreetFromSelectedShp() )
// 		{
// 			AfxMessageBox("添加Street成功.");
// 		}
// 		else
// 		{
// 			AfxMessageBox("未能添加Street.");
// 		}
// 	}
// 	else
// 	{
// 		AfxMessageBox("场景中未添加规划区域.");
//	}
}

void CvgFrameWorkView::OnPlanExportscene()
{
	// TODO: 在此添加命令处理程序代码
	//vgPlan::vgPlanManager::getSingleton().exportAllSceneToShpFile("");
}

void CvgFrameWorkView::OnVgplanGenerateplanmap()
{
	// TODO: 在此添加命令处理程序代码
	//vgPlan::vgPlanManager::getSingleton().generateMap();
}

void CvgFrameWorkView::OnVgplanAddregion()
{
	// TODO: 在此添加命令处理程序代码
	//vgPlan::vgPlanManager::getSingleton().getActiveScene()->addExclusiveAreaFromSelectedShp();
}

void CvgFrameWorkView::OnVgplanAddnew()
{
	// TODO: 在此添加命令处理程序代码
// 	DlgPlanShpIn dlg;
// 
// 	this->SetTimer(1, 150, NULL);
// 
// 	if ( dlg.DoModal() != IDOK )
// 	{
// 		this->SetTimer(1, 15, NULL);
// 
// 		return ;
// 	}
// 	this->SetTimer(1, 15, NULL);
// 
// 	vgPlan::vgPlsanManager::getSingleton().addNewScene(dlg.getPlanName());
// 	
// 	if (dlg.getAreaFilePath().length() > 0)
// 	{
// 		// vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(dlg.getAreaFilePath());
// 
// 		//if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addGroundFromLayer(dlg.getAreaFileName()) )
// 		if (!vgPlan::vgPlanManager::getSingleton().getActiveScene()->addGroundFromLayer(dlg.getAreaShpName()))	
// 		{	
// 			AfxMessageBox("未能创建Ground.");
// 			return ;
// 		}
// 	}
// 
// 	if (dlg.getRoadFilePath().length() > 0)
// 	{
// 		// vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(dlg.getRoadFilePath());
// 	
// 		// if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addStreetFromLayer(dlg.getRoadFileName()) )
// 		if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addStreetFromLayer(dlg.getRoadShpName(), dlg.getRoadWidth()) )
// 		{
// 			stringstream outString;
// 			outString << "未能创建Street - " << dlg.getRoadFileName(); 
// 			AfxMessageBox(outString.str().c_str());
// 			return ;
// 		}
// 	}
// 
// 	if (dlg.getExlcFilePath().length() > 0)
// 	{
// 		// vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(dlg.getExlcFilePath());
// 
// 		//if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addExculsiveAreaFromLayer( dlg.getExlcFileName()) )
// 		if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addExculsiveAreaFromLayer( dlg.getExlcShpName()) )
// 		{
// 			AfxMessageBox("未能创建Exclusive Area.");
// 
// 			return ;
// 		}

// 	} 
// 
// 	if (dlg.getRegionFilePath().length() > 0)
// 	{
// 		// vgShape::ShapeManager::getSingleton().openShapeFileWithUpdateUI(dlg.getRegionFilePath());
// 
// 		//if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addBuildingAreaFromLayer( dlg.getRegionFileName()) )
// 		if ( !vgPlan::vgPlanManager::getSingleton().getActiveScene()->addBuildingAreaFromLayer( dlg.getRegionShpName()) )
// 		{
// 			AfxMessageBox("未能创建Region Area. ");
// 		
// 			return ;
// 		}
// 	}
// 	AfxMessageBox("创建成功.", MB_OK);
// 
// 	vgKernel::RendererManager::getSingleton().invalidate();
}

void CvgFrameWorkView::OnVgplanCgrid()
{
	// TODO: 在此添加命令处理程序代码
// 	DlgPlanParam dlg;
// 
// 	this->SetTimer(1, 150, NULL);
// 	
//  	dlg.DoModal();
// 
// 	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnVgplanCalgrid()
{

// 	vgPlan::vgSunAngle sunangle;
// 	sunangle.SetDate(2009,12,22);
// 	sunangle.SetTime(11,0);
// 	sunangle.SetLat(40);
// 	float aa=sunangle.GetHeightOfSun();
// 
// 	float height = (20-0.9)/tan(aa);
// 	
// 	float angle = aa * 180 / 3.1415692;
// 
// 	stringstream outString;
// 
// 	outString << "太阳高度角" << aa <<  ", " << angle << " 前后间距" << height << "\n";
// 
// 	VGK_SHOW(outString.str());
}

void CvgFrameWorkView::OnVgplanGenplan()
{
	// TODO: 在此添加命令处理程序代码
// 	DlgPlanBlock dlg;
// 
// 	vgPlan::vgSunAngle sunangle;
// 
// 	this->SetTimer(1, 150, NULL);
// 
// 	if (dlg.DoModal() == IDOK)
// 	{
// 		vgPlan::BlockParam blockParam = dlg.getBlockParam();
// 		vgPlan::SunlightParam sunlightParam = dlg.getSunlightParam();
// 	
// 		vgPlan::vgPlanManager::getSingleton().getActiveScene()->generatePlan(blockParam, sunlightParam);
// 	}
// 
// 	this->SetTimer(1, 15, NULL);
}

void CvgFrameWorkView::OnVgplanOutput()
{
// 	DlgPlanOutput dlg;
// 
// 	this->SetTimer(1, 150, NULL);
// 	
// 	dlg.DoModal();
// 	
// 	this->SetTimer(1, 15, NULL);
}



void CvgFrameWorkView::OnVmdImport()
{
	vgKernel::StringVector strExts;
	strExts.push_back("vmd");
	vgKernel::StringVector strVec = vgKernel::SystemUtility::getFilesOpenByDialog(strExts);

	vgGlobal::SceneFileUtility::importFiles( strVec );
}

LONG CvgFrameWorkView::OnDelDlgMsg(WPARAM wP,LPARAM lP)
{
	assert(0 && "禁用此功能");

	delete m_dbCondition;
	m_dbCondition = NULL;
	return 0;
}


void CvgFrameWorkView::OnUpdateVgterrainNewVtr(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here

/*	TRACE ("%d \n", pCmdUI->m_nID);*/
	pCmdUI->Enable( VGK_DLL_CHECK_LOAD(VGT_DLL_NAME ) );
}

void CvgFrameWorkView::OnScenePublish()
{
	// TODO: 在此添加命令处理程序代码

	VGMSGBOX2( 
		vgGlobal::SceneFileUtility::publishScene(); 
	);

	return;

}



void CvgFrameWorkView::OnVgsoLoadDll()
{

	VGK_DLL_LOAD( VGSO_DLL_NAME );
}

void CvgFrameWorkView::OnVgsoUnloadDll()
{

	VGK_DLL_UNLOAD( VGSO_DLL_NAME );
}

void CvgFrameWorkView::OnUpdateScenePublish(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ((CvgFrameWorkApp*)AfxGetApp())->_enablePackage );
}


// 场景切块保存，包括mod,vgm,vtr
void CvgFrameWorkView::OnSaveCutBlock()
{
	// TODO: Add your command handler code here
	vgGlobal::SceneFileUtility::saveCutSceneFile();
}

void CvgFrameWorkView::OnSwitchToTopView()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToTopView();
}

void CvgFrameWorkView::OnSwitchToPerspectView()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToPerspectiveView();
}

void CvgFrameWorkView::OnAxonoViewNorthWest()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToAxonoViewNorthWest();
}

void CvgFrameWorkView::OnAxonoViewSouthWest()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToAxonoViewSouthWest();
}

void CvgFrameWorkView::OnAxonoViewNorthEast()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToAxonoViewNorthEast();
}

void CvgFrameWorkView::OnAxonoViewSouthEast()
{
	// TODO: Add your command handler code here
	vgGlobal::CamUtility::switchToAxonoViewSouthEast();
}

void CvgFrameWorkView::OnBeginCutBlock()
{
	// TODO: Add your command handler code here
	vgGlobal::SceneFileUtility::setCutSceneBeginState();
}


void CvgFrameWorkView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	vgCam::CamManager::getSingleton().setMovingEnable( false );
}

void CvgFrameWorkView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	vgCam::CamManager::getSingleton().setMovingEnable( true );
}

void CvgFrameWorkView::OnWaterDirection()
{
	// TODO: 在此添加命令处理程序代码
	VGMSGBOX2( vgGlobal::ModUtility::changeWaterDirection() );
}


void CvgFrameWorkView::OnSolidBuild()
{
	// TODO: 在此添加命令处理程序代码
	vgGlobal::ModUtility::generateSolidBuild();
}

void CvgFrameWorkView::OnUpdateSolidBuild(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码、

	bool _bState = vgGlobal::ModUtility::getGenerateBuildFlag();
	pCmdUI->SetCheck(_bState);

}

void CvgFrameWorkView::OnLandMarkBuild()
{
	vgGlobal::ModUtility::generateMarkBuild();
}

void CvgFrameWorkView::OnUpdateLandMark(CCmdUI *pCmdUI)
{
	bool _bState = vgGlobal::ModUtility::getAllLandMarkFlag();
	pCmdUI->Enable(_bState);
}

void CvgFrameWorkView::OnEnableAllMark()
{
	// TODO: 在此添加命令处理程序代码
	bool _bState = vgGlobal::ModUtility::getAllLandMarkFlag();
	vgGlobal::ModUtility::enableAllLandMark(!_bState);
}

void CvgFrameWorkView::OnUpdateAllMark(CCmdUI *pCmdUI)
{
	bool _bState = vgGlobal::ModUtility::getAllLandMarkFlag();
	pCmdUI->SetCheck(_bState);
}

void CvgFrameWorkView::OnTestAddupdate()
{
	// TODO: 在此添加命令处理程序代码
	m_oldVgPath = vgGlobal::SceneFileUtility::getCurrentSceneVgPath();
	m_oldVgimgPath = vgGlobal::SceneFileUtility::getCurrentSceneVgimgPath();
	string oldScenePath = vgGlobal::SceneFileUtility::getCurrentScenePath();

	if (m_oldVgPath.length() == 0)
	{
		return ;
	}

	m_updateVgimgPath = oldScenePath + "tmp.vgimg";
	// m_updataVgPath = oldScenePath + "tmp.vg";

	vgGlobal::ModUtility::exportVgFileDirectly(m_oldVgPath);
	vgGlobal::ModUtility::exportVgImgFile( m_updateVgimgPath );
	
	// ArchiveManager::getSingleton().clear();


// 	string copy = "copy " + newImg + " " + oldImgPath;
// 	string del = "del " + newImg;
// 
//  	system(copy.c_str());
//  	system(del.c_str());
	// string cmd = "copy " + tmpPath
}

void CvgFrameWorkView::OnTestV()
{
	// TODO: 在此添加命令处理程序代码
	static bool visiable = false;

	vgKernel::RendererManager::getSingleton().setAllRenderersVisiable(visiable);

	visiable = !visiable;
}

bool CvgFrameWorkView::initializeSock()
{
	WSADATA wsd;

	int ret = WSAStartup(0x0202,&wsd);

	if( ret != 0 )
	{
		AfxMessageBox("Init sock error.");
		WSACleanup();

		return false;
	}

	return true;
}

bool CvgFrameWorkView::finalizeSock()
{
	WSACleanup();

	return true;
}

bool CvgFrameWorkView::createClientRecvSocket()
{

	// 创建Client接收Socket
	m_clientRecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP); 

	if(m_clientRecvSocket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	// 绑定本机所有IP地址
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(m_clientRecvPort);
	// 绑定Server发送使用的端口和地址
	bool ret = bind(m_clientRecvSocket, (struct sockaddr *)&addr, sizeof(addr));

	if(ret != 0)
	{
		return false;
	}

	HANDLE handle = CreateThread(NULL, 0, ClientRecvDeamon, this, 0, NULL);

	SetThreadPriority( handle, THREAD_PRIORITY_IDLE);
}

SOCKET CvgFrameWorkView::m_clientRecvSocket;
bool CvgFrameWorkView::m_needUpdate;
string CvgFrameWorkView::m_newModPath;

DWORD WINAPI CvgFrameWorkView::ClientRecvDeamon(LPVOID lpParameter)
{
	int ret;
	unsigned long lLength;

	while( true )
	{
		ret = ioctlsocket(m_clientRecvSocket, FIONREAD, &lLength);
		if(ret != 0)
		{
			break;
		}
		else
		{
			if(lLength>0)
			{
				char *pbuf;
				int addr_len, iRecLen;;
				struct sockaddr_in addr;

				pbuf = new char[lLength + 1];
				memset(pbuf, 0, lLength + 1);

				addr_len = sizeof(addr);

				iRecLen = recvfrom(m_clientRecvSocket, pbuf, lLength, 0,(struct sockaddr *)&addr, &addr_len);

				if( iRecLen<=0 )
				{
					AfxMessageBox("Client Receive error.");
				}
				else
				{
					// AfxMessageBox(pbuf);
					m_newModPath = pbuf;
					m_needUpdate = true;
				}
			}
		}

		Sleep(10);
	}

	return 0;
}
void CvgFrameWorkView::OnConnet()
{
	// TODO: 在此添加命令处理程序代码
	vgLogonDialog dialog;

	if (dialog.DoModal() == IDOK)
	{
		loadAddonMod();
	}
}

void CvgFrameWorkView::OnDustsunIni()
{
	// TODO: 在此添加命令处理程序代码
// 	String exepath = vgKernel::SystemUtility::getCurrentProcessPath();
// 
// 	String texturePath =  VG_EXECONF_GET_STRING( 
// 		"DataPathConfig",  
// 		"TexturePath");

	string skypath =  "sky.MOD";

	string originpath = "negx.jpg";

	string dustpath =  "negx2.jpg";

	string lastsunpath =  "negx3.jpg";

	vgCore::MovingManager::getSingleton().Initdustsun(skypath,  originpath, dustpath, lastsunpath );
}

void CvgFrameWorkView::OnDustsunSet()
{
	VGMSGBOX2(vgCore::MovingManager::getSingleton().Dustsuneffect());
	// TODO: 在此添加命令处理程序代码
}

void CvgFrameWorkView::OnCompass()
{
	using namespace vgLogo;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGL_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		getcompassrendersign, pfn1 );

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		setcompassrendersign, pfn2 );

	if ( pfn1 == NULL || pfn2 == NULL )
	{
		return;
	}

	(*pfn2)( !( *pfn1 )() );
}

void CvgFrameWorkView::OnUpdateCompass(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGL_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager, 
		getcompassrendersign, pfn1 );

	assert( pfn1 != NULL );

	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::OnHawkeye()
{
	using namespace vgLogo;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGL_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		getsmallmaprendersign, pfn1 );

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		setsmallmaprendersign, pfn2 );

	if ( pfn1 == NULL || pfn2 == NULL )
	{
		return;
	}

	(*pfn2)( !( *pfn1 )() );

}

void CvgFrameWorkView::OnUpdateHawkeye(CCmdUI *pCmdUI)
{
	using namespace vgKernel;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGL_DLL_NAME );

	if ( plg == NULL )
	{
		pCmdUI->Enable( FALSE );
		return;
	}

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager, 
		getsmallmaprendersign, pfn1 );

	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		getsmallmapdatasign, pfn2 );

	assert( pfn1 != NULL && pfn2 != NULL );

	pCmdUI->Enable( ( *pfn2 )() );
	pCmdUI->SetCheck( ( *pfn1 )() );
}

void CvgFrameWorkView::OnOutputiamge()
{
	using namespace vgLogo;
	Plugin* plg = PluginManager::getSingleton().getPluginRef( VGL_DLL_NAME );

	if ( plg == NULL )
	{
		return;
	}
		
	vgKernel::StringVector strExts;

	strExts.push_back("tga");
	
	string filename = vgKernel::SystemUtility::getFileSaveByDialog(strExts);


	VGK_DLL_DECLARE_CLASSFUNC( plg, LogoManager , 
		OutPutHawkeyeMapInSky, pfn1 );

	if ( pfn1 == NULL  )
	{
		return;
	}

	(*pfn1)(filename );
}

void CvgFrameWorkView::OnEditSelectReverse2()
{
	vgGlobal::EditUtility::selectionReverse();
}
