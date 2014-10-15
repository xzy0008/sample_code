#pragma once

/*
@author ZhouSC 
*/

//-------------------原GlobalConsole renderBegin -------------------

#define VG_RP_HIGH								-2000			

#define VG_RP_UPDATEINPUT						-1900				// 捕捉用户输入

#define VG_RP_VISUALEFFECT_BK					-1300				// 背景颜色
#define VG_RP_VISUALEFFECT_FOG					-1290				// 雾特效

#define VG_RP_CHANNEL_RENDER_BEGIN				-1110				// 多通道开始渲染
#define VG_RP_CHANNEL_CLIENT					-1100				// 多通道客户端渲染

#define VG_RP_CAM_AVI_BEGIN						-990				// 相机记录AVI
#define VG_RP_CAM_BEGIN							-960				// 设置相机位置

#define VG_RP_CHANNEL_SERVER					-880				// 多通道服务器端的渲染

#define  VG_RP_TRIGGER                               -840

#define VG_RP_TEX_IODISPATCHER					-800				// vgi纹理请求

#define VG_RP_ASYN_BEGIN						-700				// 异步IO开始

//#define VG_RP_TERRAIN							-650

#define VG_RP_RENDERMNG_BEGIN					-600				// RernderManager render begin

#define VG_RP_CONTOUR_RENDER					-550				// 等值线绘制

//-------------------原GlobalConsole renderPrimitives -------------------
#define VG_RP_MESH_RENDER						-500				// Mesh Render
#define VG_RP_MODEL_RENDER						-400				// VMD Render

#define VG_RP_CLIENT_RENDERMNG_RENDER			0					// 客户端自定义渲染

#define VG_RP_DEFAULT							0					// 默认优先级

#define VG_RP_CONSOLE_RENDER_PRIMITIVES			1

#define	VG_RP_PLUGIN_RENDER						100					// 所有注册插件的渲染

#define VG_RP_GIS_RENDER						20					// GIS模块渲染

#define VG_RP_GIS_CONTOUR						50					// GIS 等值线渲染

#define VG_RP_AUTOBUILD_RENDER					150					//AUTOBUILD 渲染

#define VG_RP_SELECT_RENDER						200					// SelectManager 渲染

#define VG_RP_TRIGGER_RENDER					300					// TriggerManager渲染

//-------------------原GlobalConsole Render End -------------------------
#define VG_RP_RENDERMNG_END						400					// RenderManager RenderEnd

#define VG_RP_CONSOLE_RENDER_END				500					// 原GlobalConsole RenderEnd

#define VG_RP_CHANNEL_RENDER_END				600					// 多通道渲染结束
#define VG_RP_BLEND_ADJUST						610					// 多通道边缘融合和几何校正

#define VG_RP_MISC_RENDER						700					// Mod 特效

// Edit By FengYK @2010-05-11 22:22 为了乐山展示方案,暂时将地形模块的渲染优先级降低
#define VG_RP_TERRAIN							750

#define VG_RP_LOGO_RENDER						900					// logo


#define VG_RP_CAM_AVI_END						800					// 相机导出AVI结束

#define VG_RP_LOW								2000					
