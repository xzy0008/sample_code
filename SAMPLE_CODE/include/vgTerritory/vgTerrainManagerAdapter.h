
#ifndef __VGTERRAINMANAGERADAPTER_H__
#define  __VGTERRAINMANAGERADAPTER_H__


#include <vgPlugin/vgplCoreTerrainManager.h>
#include <vgTerritory/vgtTerrainManager.h>

namespace vgTerritory
{
	class VGT_EXPORT vgTerrainManagerAdapter : public vgPlugin::CoreTerrainManager
	{
	public:
		vgTerrainManagerAdapter()
		{
			vgTerritory::TerrainManager::getSingleton();
			m_pTM = vgTerritory::TerrainManager::getSingletonPtr() ;
		}
		~vgTerrainManagerAdapter(){}

	public:

		void render()
		{
			m_pTM->render();
		}

		bool openVtrFile( std::string &filename )
		{
			return m_pTM->openVtrFile( filename );
		}

		bool initAfterOpenGLSetup()
		{
			return m_pTM->initAfterOpenGLSetup();
		}

		bool hasTerrainData()
		{
			return m_pTM->hasTerrainData();
		}

		void setCollisionDetectedFlag( const bool& enable )
		{
			m_pTM->setCollisionDetectedFlag(enable);
		}

		bool getCollisionDetectedFlag()
		{
			return m_pTM->getCollisionDetectedFlag();
		}

		void setRenderFlag( const bool& enable )
		{
			m_pTM->setRenderFlag(enable);
		}

		bool getRenderFlag()
		{
			return m_pTM->getRenderFlag();
		}

		void dropTerrianData()
		{
			m_pTM->dropTerrianData();
		}

		float* getUserClipPlaneParam()
		{
			return m_pTM->getUserClipPlaneParam();
		}
		
		bool	getElevationByPosition( const vgKernel::Vec3& pos ,float& out_elevation , 
			const bool& use_accurate )
		{
			return m_pTM->getElevationByPosition(pos, out_elevation, use_accurate);
		}


		void setCutSurfaceAnalysisFlag( const bool& enable )
		{
			m_pTM->setCutSurfaceAnalysisFlag(enable);
		}

		bool getCutSurfaceAnalysisFlag()
		{
			return m_pTM->getCutSurfaceAnalysisFlag();
		}

		void setCutSurfaceAnalysisFlag2( const bool& enable )
		{
			m_pTM->setCutSurfaceAnalysisFlag2(enable);
		}

		bool getCutSurfaceAnalysisFlag2()
		{
			return m_pTM->getCutSurfaceAnalysisFlag2();
		}

		void setCutSurfaceVisibilityFlag( const bool& enable )
		{
			m_pTM->setCutSurfaceVisibilityFlag(enable);
		}

		bool getCutSurfaceVisibilityFlag()
		{
			return m_pTM->getCutSurfaceVisibilityFlag();
		}	

		void setCutSurfaceVisibilityFlag2( const bool& enable )
		{
			m_pTM->setCutSurfaceVisibilityFlag2(enable);
		}

		bool getCutSurfaceVisibilityFlag2()
		{
			return m_pTM->getCutSurfaceVisibilityFlag2();
		}

		void setCutSurfaceLevellingFlag( const bool& enable )
		{
			m_pTM->setCutSurfaceLevellingFlag(enable);
		}

		bool getCutSurfaceLevellingFlag()
		{
			return m_pTM->getCutSurfaceLevellingFlag();
		}	
		
		void setCutAreaFlag( const bool& enable )
		{
			m_pTM->setCutAreaFlag(enable);
		}

		bool getCutAreaFlag()
		{
			return m_pTM->getCutAreaFlag();
		}

		void setBlendFlag( const bool& enable )
		{
			m_pTM->setBlendFlag(enable);
		}

		bool getBlendFlag()
		{
			return m_pTM->getBlendFlag();
		}

	private:
		vgTerritory::TerrainManager* m_pTM;
	};




}


#endif