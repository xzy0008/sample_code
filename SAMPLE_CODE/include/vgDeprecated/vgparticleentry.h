

#pragma once

#include <vgEntry/vgBaseEntry.h>
#include <vgUIController/vgPropertyPage.h>

#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkRendererObserver.h>

#include <vgEffect/vgParticle.h>

#include <vgCoordinate.h>


namespace vgMod{



	class  VGDEP_EXPORT vgParticleEntry :	public vgBaseEntry
	{
	public:
		const static int s_NumOfParam = 9;
		static PropertiesParam s_ParamArray[s_NumOfParam];

	public:
		vgParticleEntry(  vgParticle* pParticle = NULL)
			: vgBaseEntry( pParticle )
		{
			assert( pParticle != NULL );
			Vector3 vec = pParticle->GetPosition();

			m_Positionx = vec.x + vgCore::vgCoordinate::getSingleton().GetSceneCood().x;
			m_Positiony = vec.y + vgCore::vgCoordinate::getSingleton().GetSceneCood().y;
			m_Positionz = vec.z + vgCore::vgCoordinate::getSingleton().GetSceneCood().z;
			m_PositionzMinus = - m_Positionz;

			m_height	= pParticle->m_height;
			m_width		= pParticle->m_width;
			m_speed		= pParticle->m_speed;

			vgCore::vgCoordinate::getSingleton().registerObserver(this);

		}

		virtual ~vgParticleEntry(void)
		{
			((vgParticle*)m_Renderer)->unregisterObserver( this );
		}

		void AddNodeTabs();

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }

		// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
		void OnPropertyChanged(string paramName);// { TRACE("Camera Property Changed \n");}

		// 继承自Changed，用于Object修改后更新Node
		void onChanged(int eventId, void *param);

		void UpDataProp() {}

		CMenu* GetContextMenu();

	private:
		//vgMod::ObjectNode* m_pObject;

		// 被修改数据的副本
		float m_Positionx;
		float m_Positiony;
		float m_Positionz, m_PositionzMinus;


		float	m_height;
		float	m_width;
		float	m_speed;
		//int m_nParticleCount;
		//bool m_bStopSE;


		string m_sCaption;
	};


}//namespace vgCore
