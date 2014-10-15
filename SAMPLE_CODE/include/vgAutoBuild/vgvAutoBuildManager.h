#ifndef _VGVAUTOBUILDMANAGER_H_
#define _VGVAUTOBUILDMANAGER_H_

#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkRendererHolder.h>
#include <vgAutoBuild/vgAutoBuildNode.h>
#include <vector>

#include "gdal/ogrsf_frmts.h"
#include "gdal/ogr_api.h"

#include <vgShape/vgshLayer.h>

#include <vgAutoBuild/vgSolidBuildNode.h>
#include <vgAutoBuild/vgSolidBuildHandle.h>

#include <vgAutoBuild/vgMarkBuildNode.h>
#include <vgAutoBuild/vgMarkBuildHandle.h>

#include <vgKernel/vgkInputSystem.h>

#include <vgKernel/vgkRenderCommandManager.h>
/********************************************************************
	@date:		2009/03/03
	@created:	3:3:2009   16:00

	@author:	zsc
	
	@brief 	
	@see  
*********************************************************************/

using std::vector;

namespace vgAutoBuild
{
	typedef vector<AutoBuildNode*>		AutobuildNodeVec;
	typedef vector<AutoBuildNode*>		*AutobuildNodeVecPtr;
	typedef map<string, int*>			YearsParmMap;


	class  VGDEP_EXPORT AutoBuildManager : public vgKernel::Singleton<AutoBuildManager>, 
		public vgKernel::RendererHolder,
		public vgKernel::InputHandler

	{
		friend class vgKernel::Singleton<AutoBuildManager>;
		static const unsigned int VG_FILE_ID_AUTOBUILDMANAGER_END = 4999;
		static const unsigned int VG_FILE_ID_AUTOBUILDMANAGER	  =	5000;
		static const unsigned int VG_FILE_ID_AUTOBUILDMANAGER_V2  = 5001;

	public:	static string scheStr[4];
	public: static const int	  ShpGridNum = 144;

	public:

		virtual void reset(){};

		bool addAutoBuildNode(AutoBuildNode* pNode);

		virtual bool onDeleteRenderer( vgKernel::Renderer *render);
	
		void writeAutoBuildToFile(CFile* pCfile , String savePath);
		bool readAutoBuildFromFile(CFile* pCfile  , String readPath);

		void writeSolidBuildToFile(CFile* pCfile , String savePath);
		bool readSolidBuildFromFile(CFile* pCfile  , String readPath);

		void writeMarkBuildToFile(CFile* pCfile , String savePath);
		bool readMarkBuildFromFile(CFile* pCfile  , String readPath);

		bool writeToVGFile( CFile* pCfile , String savePath);	

		bool readFromVGFile( CFile* pCfile  , String readPath);
		
		bool importShpInfo();

		bool importSpecialShpInfo( const String &filename );
		bool saveInfoToShpFile();
		
		bool addAutoShpInfo(int sid, OGRFeature* pInfoFeature, OGRGeometry *pGemo);

		bool removeAllShpInfo();

		bool generateBuildingSelected(int schem, int years);

		bool generateBuildingAll(int schem, int years);
		
		bool addPlanNode(AutoBuildNode* pNode);

		bool clearPlan(); 

		bool clearPlan(int gridID);

		void OnReadTxt();

		void readTxtFile(String shpfilepath, String txtfilepath, YearsParmMap& infoMap);

		// int getRPS(string id, int schem, int year);

	private:
		AutoBuildManager()
			: Singleton<AutoBuildManager>( VGK_SINGLETON_LEFE_AUTOBUILDMANAGER ) 
		{

			for (int i=0; i<4; i++)
			{
				m_yearsParam[i].clear();
			}
			m_autoBuildNodeList.clear();
			m_autoBuildNodeRenderList.clear();

			m_shpInfoIsOpen = false;
			m_pDS = NULL;

			m_solidBuildHandler = NULL;
			m_markBuildHandler = NULL;

			statusFlag = VG_INPUTMODE_SELECT;
			vgKernel::InputSystem::getSingleton().registerHandle(this);

			setAllMarkEnable(true);

			m_markEnable = true;
		}

		~AutoBuildManager()
		{
			for (int i=0; i<4; i++)
			{
				map<string, int*>::iterator iter	 = m_yearsParam[i].begin();
				map<string, int*>::iterator iter_end = m_yearsParam[i].end();

				while (iter != iter_end)
				{
					delete (*iter).second;
					iter ++;
				}
			}

			if (m_solidBuildHandler != NULL)
			{
				delete m_solidBuildHandler;
			}

			if (m_markBuildHandler != NULL)
			{
				delete m_markBuildHandler;
			}
		}
		
	protected:

		virtual bool initialise();

		virtual bool shutdown();

		
	
	protected:

		// leven add
		vgShape::GeometryPointerVec* getSpecialPolygons();
		
		vgShape::GeometryPointerVec* getSelectedSpecialPolygons();

	public:

		bool addSolidBuildNode(SolidBuildNode* pNode);

		void generateSolidBuild();

		bool getGenerateBuildFlag();

		void renderElements();

		bool addMarkBuildNode(MarkBuildNode* pNode);

		void generateMarkBuild();

		void setAllMarkEnable(bool enable); 

		bool getAllMarkEnable() { return m_markEnable; }

	public:
		//继承自InputHandler的接口
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);

	private:
		MarkBuildNode* testClick(CPoint position);

	private:

		bool m_shpInfoIsOpen;
		OGRDataSource *m_pDS;

		vector<AutoBuildNode*> m_autoBuildNodeList;
		vector<AutoBuildNode*> m_autoBuildNodeRenderList;

		// 0.gs, 1.ls, 2.ne 3.wm
		map<string, int*> m_yearsParam[4];

	private:
		SolidBuildHandler*      m_solidBuildHandler;
		vector<SolidBuildNode*> m_solidBuildNodeList;

		MarkBuildHandler*       m_markBuildHandler;
		vector<MarkBuildNode*>  m_markBuildNodeList;

		vgKernel::RenderCommand *m_pAutoBuildRenderCommand;

		bool m_markEnable;
	};


	class AutoBuildRenderCommand : public vgKernel::RenderCommand
	{
	public:
		AutoBuildRenderCommand() : vgKernel::RenderCommand(VG_RP_AUTOBUILD_RENDER) {}

		inline virtual bool render()
		{
			vgAutoBuild::AutoBuildManager::getSingleton().renderElements();
			return true;
		}
	};

}

#endif