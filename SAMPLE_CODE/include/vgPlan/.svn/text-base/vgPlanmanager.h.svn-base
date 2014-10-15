
#ifndef __VGPLANMANAGER__
#define  __VGPLANMANAGER__


#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkSingleton.h>
#include <vgPlan/vgPlanscene.h>
#include <vgKernel/vgkRenderer.h>
#include <vgPlan/vgAreaSelector.h>

#include <vgPlan/vgpDefinition.h>
// #include <vgPlan/vgPlanstruct.h>
// #include <vgPlan/vgPlanscene.h>
// 
// #include <vgPlan/vgPlanstrategy.h>
// #include <vgPlan/vgPlantemplatestrategy.h>
// #include <vgPlan/vgPlansimplestrategy.h>
// #include <vgPlan/vgPlanbuildFactory.h>

namespace vgPlan{
	vgKernel::Vec3 convertToOpenGLCoordinate(vgKernel::Vec2 point);

	vgKernel::Vec3 convertToCeometryCoordinate25D(vgKernel::Vec3 point);

	vgKernel::Vec2 convertToGeometryCoordinate(vgKernel::Vec3 point);

	/*!
		@date    2009/10/30  10:38
		@author  zzy
		@action  modify
		@brief   本类改为导出类，供菜单DLL调用 
	*/
	class VGP_EXPORT vgPlanManager : public vgKernel::Singleton<vgPlanManager>, vgKernel::RendererHolder
	{
	public:
		friend class vgKernel::Singleton<vgPlanManager>;
	private:
		vgPlanManager() 
			: Singleton<vgPlanManager>( VGK_SIGLETON_LEFE_AUTOPLANMANAGER )
		{
// 			b_rendershadow = false;
// 
// 			_currentstrategy = NULL;

			m_activeSceneName = "noname";

			m_renderShadow = false;

			m_onEditMode = false;

			m_pSelector = NULL;

			m_bHaveGeneratedPlan = false;
		}

		~vgPlanManager();

	public:
		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			return true;
		}

		bool addNewScene(string name = "noname");

		int getNumOfScene();
		
		vgPlanScene* getLastScenePtr();
		
		vgPlanScene* getScenePtrByName(string name);

		void render();
		
		bool generateMap();
		
		void updateShadowData();

		void updateGemoData();
		
		// 导出所有的Scene到shp文件中
		bool exportAllSceneToShpFile(CString filename);

		vgPlanScene* getActiveScene() { return getScenePtrByName(m_activeSceneName); }
		
		vgPlanScene* getSceneById(int index) 
		{ 
			if (index >= 0 && index < m_sceneList.size())
			{
				return m_sceneList.at(index); 
			}

			return NULL;
		}

		int getActiveSceneId()
		{
			for (int i=0 ;i<m_sceneList.size(); i++)
			{
				if (m_sceneList.at(i)->getName() == m_activeSceneName)
				{
					return i;
				}
			}

			return -1;
		}

		void setActiveSceneByName(string name) { m_activeSceneName = name; }
		
		void setActiveSceneById(int index) 
		{
			if (index < m_sceneList.size())
			{
				m_activeSceneName = m_sceneList.at(index)->getName();
			}
		}
		
		string getSceneNameById(int index)
		{
			return m_sceneList.at(index)->getName();
		}

		bool getShadowEnable()
		{
			return m_renderShadow;
		}

		void setShadowEnable(bool enable)
		{
			m_renderShadow = enable;
		}

		bool calculateGridForCurrentScene(int xResolve, int yResovle);

	public:
		// 通知各个Scene删除Render
		virtual bool onDeleteRenderer( vgKernel::Renderer* renderer );
		
		void addRenderer(vgKernel::Renderer *pRenderer);
		
		void setEditMode(bool onEditMode)
		{
			m_onEditMode = onEditMode;

			if (! onEditMode)
			{
				updateShadowData();
				updateGemoData();
			}
		}

		bool getEditMode()
		{
			return m_onEditMode;
		}
		
		void setSelectorFlag(bool enable/*, CWnd* pWnd = NULL*/);

		//add by zzy 2009/10/27  15:36
		bool getHaveGeneratedPlan() { return m_bHaveGeneratedPlan; } 
		void setHaveGeneratedPlan( bool _bHaveGenerated ) { m_bHaveGeneratedPlan = _bHaveGenerated; }


		bool planTimeline();
	private:
		vector<vgPlanScene*> m_sceneList;
		
		string m_activeSceneName;

		bool m_renderShadow;
		
		bool m_onEditMode;

		AreaSelector *m_pSelector;

		/*! 
			add by zzy 2009/10/27  15:36
			用于记录是否已经生成了规划方案
			如果其为 false 则说明没有方案生成，也就无法显示方案
		*/
		bool m_bHaveGeneratedPlan;  



// 		void generateplanstrategy();
// 
// 		vgPlanstrategy *getcurrentplanstrategy(){return _currentstrategy ;}
// 
// 		void setcurrentplanstrategy( vgPlanstrategy *_strategy){ _currentstrategy = _strategy;}
// 
// 	private:
// 		vector<vgPlanscene *> planscenes;
// 
// 		bool b_rendershadow;
// 
// 		vgPlanstrategy *_currentstrategy;
// 
// 	public:
// 
// 		void setrendershadowsign( bool _render){ b_rendershadow = _render;}
// 
// 		bool getrendershadowsing(){ return b_rendershadow ;}
// 
// 		void addplanscene();
// 
// 		vgPlanscene *getcurrentscene();
// 
// 		vgPlanscene *getscene( int num );
// 
// 		void render();
// 
// 		void ShadowRender();
// 
// 	public:
// 		vgPlanbuildFactory &getplanbuildfactory(){ return buildfactory; }
// 	
// 		plansceneparameter &getcurrentsceneparameter();
// 	
// 		planbuildparameter &getbuildparameter( buildingtype _type );
// 	private:
// 
// 		vgPlanbuildFactory buildfactory;
// 
// 	public:
// 
// 			void monihanshu();
	};


}

#endif