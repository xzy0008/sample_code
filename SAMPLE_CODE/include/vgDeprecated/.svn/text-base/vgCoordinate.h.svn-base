


#ifndef __VGCOORDINATE222_H__
#define __VGCOORDINATE222_H__
#if 0

#include <vgCore/vgPrerequisites.h>
#include <vgCore/vgSingleton.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkCoordSystem.h>
#include <vgMath/vgfVector3.h>


namespace vgCore{

	class  VGDEP_EXPORT vgCoordinate  : public ::Singleton<vgCoordinate>
		,public vgKernel::ObserverContainer//chunyongma2008.9.8
	{
	public:
		vgCoordinate();
		~vgCoordinate();

		static vgCoordinate* getSingletonPtr(void)
		{
			return ms_pSingleton;
		}
		static vgCoordinate& getSingleton(void)
		{  
			assert( ms_pSingleton );  return ( *ms_pSingleton );  
		}

		bool initialise()
		{
			return true;
		}
	private:

		//Vector3 m_SceneCood;

	public:

		Vector3 GetSceneCood()
		{ 
			Vector3 ret;
			vgKernel::Vec3* ref = 
				vgKernel::CoordSystem::getSingleton().getProjectionCoordRef();

			ret.x = ref->x;
			ret.y  =ref->y;
			ret.z = ref->z;

			return ret;
			//return m_SceneCood; 
		}

		void SetSceneCood( Vector3 &vec)
		{
			vgKernel::CoordSystem::getSingleton().setProjectionCoord( 
				vgKernel::Vec3( vec.x , vec.y, 
				vec.z ) );
		}

		// 读写文件vg
		void writeToFile( CFile* pCfile )
		{
			vgKernel::Vec3 coor=
				vgKernel::CoordSystem::getSingleton().getProjectionCoord();

			Vector3 m_SceneCood;
			m_SceneCood.x = coor.x;
			m_SceneCood.y = coor.y;
			m_SceneCood.z = coor.z;
			pCfile->Write(&m_SceneCood, sizeof(Vector3) );
		}
		bool readFromFile( CFile* pCfile  )
		{
			Vector3 m_SceneCood;
			pCfile->Read(&m_SceneCood, sizeof(Vector3) );
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
			return true;
		}


		//------------------------------------------
		// leven add 
		//------------------------------------------
		vgKernel::Vec3 transOpenGLCoordToGisCoord( const vgKernel::Vec3& opengl_coord )
		{
			return vgKernel::CoordSystem::getSingleton().transCoordOpenGLToProj( opengl_coord );

			//vgKernel::Vec3 ret;
			//ret.x = opengl_coord.x + m_SceneCood.x;
			//ret.y = opengl_coord.y + m_SceneCood.y;
			//ret.z = opengl_coord.z + m_SceneCood.z;
			//ret.z = -ret.z; // 取反

			//return ret;
		}
		vgKernel::Vec3 transGisCoordToOpenGLCoord( const vgKernel::Vec3& gis_coord )
		{
			return vgKernel::CoordSystem::getSingleton().transCoordProjToOpenGL( gis_coord );

			//vgKernel::Vec3 ret;
			//ret.x = gis_coord.x - m_SceneCood.x;
			//ret.y = gis_coord.y - m_SceneCood.y;
			//ret.z = -gis_coord.z; // 取反
			//ret.z = ret.z - m_SceneCood.z;
		
			//return ret;
		}


	};//class vgCoordinate

}//namespace vgCore

#endif // end of __VGOBJNODE_H__
#endif