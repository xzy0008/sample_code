


#ifndef __VGWATERNODE_H__
#define __VGWATERNODE_H__

#include <vgCore/vgPrerequisites.h>
#include <vgMod/vgObjFrameNode.h>
//#include "vgBasedNode.h"//chunyongma
#include <vgCam/vgcaCamManager.h>

namespace vgMod {

	using namespace vgCore;
	/**
		@date 	2008/02/27  16:46	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/

	class WaterNode : public ObjFrameNode
	{

	public:
		WaterNode(int nVersionMod = VERSION_1);
		~WaterNode();
	
	
	public:

		void setDefault();
		//------------------------------------------
		// 模型数据没有删除.只是删除cg等信息
		//------------------------------------------
		void destroy();

		virtual void Render();

		virtual	unsigned long PositDataToNode(char *data );
	
		virtual void WriteNodeToVG(CFile &fp);

//////////////////////////////////////////////////////////////////////////chunyongma
		bool recreate(vgCam::CamManager *camera , const vgCore::StringVector& strvec , const String& bumpmap , 
			const String& decalmap , const float& bumpscale);

		virtual vgKernel::StringVector getTexNameVec();

	public:

		bool initWaterImpl();
//chunyongma
		void setCamera( vgCam::CamManager* camera )
		{
			this->mpEyeCamera = camera;
		}

		vgCam::CamManager *mpEyeCamera;

		WaterGpuProgram *mpWaterProgram;

		std::string  m_StrEnvMap[6];
		std::string m_StrBumpMap;
		std::string m_StrDecalMap;
		float m_fBumpScale;

		// 是否初始化了
		bool mIsInited;

		// Add By FengYK @2010-03-23 
		float _utimeline;
		float _vtimeline;

	public:
		void setColorParameter(float red, float green, float blue, float alpha)
		{
			m_redValue = red;
			m_greenValue = green;
			m_blueValue = blue;
			m_alphaVaule = alpha;

		}

	private :
		float m_redValue;
		float m_blueValue;
		float m_greenValue;
		float m_alphaVaule;
	};

	//////////////////////////////////////////////////////////////////////////chunyongma
#if 0
	template< class T >
	class GpuseAdapter : public vgBasedNode, public ChangedObserver
	{
	public:
		const static int s_NumOfParam = 5 ;
		static PropertiesParam s_ParamArray[s_NumOfParam];

	public:
		GpuseAdapter(string particalName = "GPUSE",  T* pObject = NULL);

		virtual ~GpuseAdapter<T>(void)	{	}

		void AddNodeTabs();

		int GetSelectedImage() { return 1; }

		int GetUnSelectedImage() { return 2; }


		// 继承自vgBasedNode修改Node后重新设置Object 和TreeItem
		void OnPropertyChanged();// { TRACE("Camera Property Changed \n");}

		// 继承自Changed，用于Object修改后更新Node
		void OnChanged();

		void UpDataProp() {}
	private:
		T* m_pObject;

		// 被修改数据的副本
		float m_Positionx;
		float m_Positiony;
		float m_Positionz;


		string m_sCaption;
	};
	//////////////////////////////////////////////////////////////////////////chunyongma
//--------------------------------------------------------------------------------------
	

	template< class T>
	PropertiesParam GpuseAdapter<T>::s_ParamArray[s_NumOfParam];

	template< class T >
	GpuseAdapter< T >::GpuseAdapter(string particalName, T* pObject)
		:vgBasedNode(particalName),m_sCaption(particalName)
	{
		assert( pObject != NULL );

		m_Positionx = pObject->m_Position.x;
		m_Positiony = pObject->m_Position.y;
		m_Positionz = pObject->m_Position.z;

		m_pObject = pObject;

		//dynamic_cast<ObserverHandler*>
		m_pObject->registerObserver( this );
	}


	template< class T >
	void GpuseAdapter< T >::OnPropertyChanged()
	{
		m_pObject->SetPosition( Vector3(m_Positionx, m_Positiony, m_Positionz) );

	}
	template< class T >
	void GpuseAdapter< T >::OnChanged()
	{
		Vector3 pos = m_pObject->GetPosition();


		m_Positionx = pos.x;
		m_Positiony = pos.y;
		m_Positionz = pos.z;

		//TRACE("New Camera Position %.2f %.2f %.2f \n", posPtr->x, posPtr->y, posPtr->z);
		if (this == vgUI::UIController::getSingleton().GetCurrentSelectedNode())
		{
			s_ParamArray[1].pProp->SetValue(m_Positionx);
			s_ParamArray[2].pProp->SetValue(m_Positiony);
			s_ParamArray[3].pProp->SetValue(m_Positionz);
		}
	}
	template< class T >
	void GpuseAdapter< T >::AddNodeTabs()
	{
		vgUI::UIController::getSingleton().RemoveAllPages();

		vgPropertiesViewBar* pageViewBar = vgUI::UIController::getSingleton().GetPropertiesViewBar();

		s_ParamArray[0].label = "坐标值设置";
		s_ParamArray[0].typeId = PROP_ITEM_GROUP;
		s_ParamArray[0].dataType = PROP_DATA_NONE;
		s_ParamArray[0].connectedPtr = NULL;
		s_ParamArray[0].comment = "设置粒子坐标";

		s_ParamArray[1].label = "X 坐标";
		s_ParamArray[1].typeId = PROP_ITEM_DATA;
		s_ParamArray[1].dataType = PROP_DATA_FLOAT;
		s_ParamArray[1].connectedPtr = &m_Positionx;
		s_ParamArray[1].comment = "设置X坐标";


		s_ParamArray[2].label = "Y 坐标";
		s_ParamArray[2].typeId = PROP_ITEM_DATA;
		s_ParamArray[2].dataType = PROP_DATA_FLOAT;
		s_ParamArray[2].connectedPtr = &m_Positiony;
		s_ParamArray[2].comment = "设置Y坐标";

		s_ParamArray[3].label = "Z 坐标";
		s_ParamArray[3].typeId = PROP_ITEM_DATA;
		s_ParamArray[3].dataType = PROP_DATA_FLOAT;
		s_ParamArray[3].connectedPtr = &m_Positionz;
		s_ParamArray[3].comment = "设置Z坐标";

		s_ParamArray[4].label = "其他设置";
		s_ParamArray[4].typeId = PROP_ITEM_GROUP;
		s_ParamArray[4].dataType = PROP_DATA_NONE;
		s_ParamArray[4].connectedPtr = NULL;
		s_ParamArray[4].comment = string();

		vgPropertyPage* propPage = vgUI::UIController::getSingleton().GetPropPage();
		propPage->Create(NIDD_PROPERTY, pageViewBar->GetTabControl());

		propPage->ConnectNode(this, s_ParamArray, s_NumOfParam);

		pageViewBar->AddTab("自动属性", propPage);
	}
	
#endif
	
}// end of namespace vgCore

#endif // end of __VGWATERNODE_H__