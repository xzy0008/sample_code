

#ifndef __VGEFFECT_DUSTSUN_H__
#define __VGEFFECT_DUSTSUN_H__

#include <vgKernel/vgkForward.h>
#include <vgCore/vgPrerequisites.h>
#include <vgKernel/vgkRgbaQuad.h>
#include <vgKernel/vgkVec2.h>
#include <vgKernel/vgkVec3.h>
#include <vgMod/vgNode.h>
#include <vgMod/vgObjNode.h>
#include <vgTex/tvgDustsunGpuProgram.h>

#include <vgTex/tvgDustsunGpuProgram.h>
#include <vgMod/vgobjframenode.h>
#include <vgDeprecated/DlgDustsun.h>
namespace vgMod {

	class  VGDEP_EXPORT Dustsun
	{
	public:
	
		Dustsun();

		~Dustsun();

	public:

		void Initdata( string modfile = "", string lastsuntex = "", string  dusttex= "", string origtex =  "" );

		void dustsuneffect();

		void render();		

	private:

		void updatedustsun();

	private:

		float m_ratio;

		vgCore::DustsunGpuProgram *dustsungpuprog;
	
		ObjFrameNode *sky;

		DlgDustsun _dustdlg;

		int dusttimepos;
	};
	
	
	
}// end of namespace vgModel

#endif // end of __VGMO_MESHDATA_H__