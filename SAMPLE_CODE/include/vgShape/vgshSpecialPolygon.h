#ifndef __VGSHSPECIALPOLYGON_H__
#define __VGSHSPECIALPOLYGON_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgShape/vgshDefinition.h>
#include <vgShape/vgshPolygon.h>


#include <vgKernel/vgkVec3.h>
	
namespace vgShape {

	
	class Layer;

	class SpecialPolygon : public Polygon
	{
	public:
		SpecialPolygon( OGRFeature* feat , Layer* father )
			: Polygon( feat , father )
		{
			//_nowBuidingNum = 0;
			//m_pResultGemo = NULL;
			//m_pInfoFeature = NULL;

			//m_availPosition.clear();
			//m_gridSizeX = 0.f;
			//m_gridSizeY = 0.f;

		}

		virtual ~SpecialPolygon()
		{
			//if (m_pResultGemo != NULL)
			//{
			//	delete m_pResultGemo;
			//}
		}

#if 0
		OGRGeometry *getGeometry()
		{
			OGRFeature *pFeature = this->getOGRFeature();
			OGRGeometry *pGeometry = pFeature->GetGeometryRef();
			
			delete pFeature;

			return pGeometry;
		}
		
		OGRGeometry *getResultGemo()
		{
			return m_pResultGemo;
		}
		
		void setAutoInfo(OGRFeature *pFeature, OGRGeometry *pGemo);

		void unsetAutoInfo()
		{
			delete m_pResultGemo;
			m_pResultGemo = NULL;

			OGRFeature::DestroyFeature(m_pInfoFeature);
		}

		// 自动生成房屋并摆放
		bool generateAutobuilding(vgVector::AutobuildNodeVec& autoNodeVec, int schem, int years);
		
		vector<Vector2>& getAvailGridVec()
		{
			return m_availPosition;
		}

		float getGridSizeX()
		{
			return m_gridSizeX;
		}

		float getGridSizeY()
		{
			return m_gridSizeY;
		}

		vector<vgVector::AutoBuildNode*>* getAutoBuildNodes()
		{
			return &_autoBuilds;
		}

		void clearAutoBuildNodes()
		{
			_autoBuilds.clear();
		}

		// 得到现在的人口数
		int getNowBuildingNum();

		float getArea();

	public:

		virtual void renderInSelectedMode();


		virtual void outputPointToScreen();

		virtual void renderOnceForDisplayList();
	
		//bool constructInsectVec(vgVector::AutobuildNodeVecPtr pAutoNodeVec);
		bool constructInfoShp();

	private:

		bool calculateBuildingPosition(int buildingCnt, int blockCnt, float& longForScale);

		int generateModelByYears(vgVector::AutobuildNodeVec &autoNodeVec, int schem, int years);
		 
		void makeNewBuilding(vgVector::AutobuildNodeVec &autoBuildVecm, int number, int size);
		
		int getRPs(int schem, int year);

		void calculateGrid(OGRGeometry *pGemo, int gridNum);

		// leven add
		//bool addUIAutoBuildNode( AutoBuildNode* pNode );

	private:


		// leven add
		int _nowBuidingNum;

		OGRGeometry*							m_pResultGemo;
		OGRFeature*								m_pInfoFeature;

		vector<vgVector::AutoBuildNode*>		m_modelList;

		// leven add
		vector<vgVector::AutoBuildNode*>		_autoBuilds;


		vector<vgKernel::Vec3>					m_positionList;

		vector<Vector2>							m_availPosition;
		vector<bool>							m_availFlagList;

		float									m_gridSizeX;
		float									m_gridSizeY;

// 		map<int, int>							m_yearsParam;		
// 
// 		typedef map<int , int>				    YearCntMap;

#endif

	};
	
}// end of namespace vgShape
	


#endif // end of __VGSHSPECIALPOLYGON_H__