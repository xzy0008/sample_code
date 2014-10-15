


#ifndef __VGTERRITORY_MESHCHUNKUP_H__
#define __VGTERRITORY_MESHCHUNKUP_H__


#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgTerritory/vgtTerrainCenter.h>
#include <vgTerritory/vgMeshVertex.h>
#include <vgTerritory/vgMeshDrawingData.h>
#include <vgCam/vgcaCamManager.h>
#include <vgTerritory/vgtElevationBound.h>


namespace vgTerritory {

	/**
	@date 	2008/04/17  19:01	
	@author  leven

	@brief 	

	@see    
	*/
	class MeshChunkUp;

	class MeshChunkUpData
	{
		friend class MeshChunkUp;
	public:
		MeshChunkUpData();
		~MeshChunkUpData();



		//------------------------------------------
		// xnum和znum分别为x轴和z轴的数量,注意!为2^n+1
		// xlength和zlength是长度
		// centerx, centery, centerz分别是生成网格中心点
		//------------------------------------------
		bool createFromParameters(
			const int& xnum,
			const int& znum , const float& xlength , const float& zlength,
			const float& centerx,const float& centery , const float& centerz);

		bool renderSmallPieces( const bool& renderinner , const bool& renderouter );


		// rotate_anticlockwise 逆时针旋转
		// 取值: { 0, 90 , 270 , 180 };
		bool renderLargeArea( const int& texcenterx , 
			const int& texcenterz , 
			ElevationItem* leftup , 
			ElevationItem* leftdown ,
			ElevationItem* rightup ,
			ElevationItem* rightdown ,
			const bool& renderGaps);

	private:

		void setDefault();
		void destroy();

		void destroyVboData();
		void destroyMemData();
		void createMeshImpl();

	private:

		bool _initialised;


		int __xnum ;
		int __znum ;
		float __xLength ;
		float __zLength ;
		float __beginx ;
		float __beginy ;
		float __beginz ;

		int __vertCount;
		MeshVertex *__vertices;
		unsigned int __indexsCount ;
		unsigned int __indexsCount2;
		short unsigned int* __indexs;
		short unsigned int* __indexs2;

		GLuint __vertexBufferID;

		// 这个存放满的indexbuffer
		GLuint __indexBufferID;
		// 这个存放有缺口的indexbuffer
		GLuint __indexBufferID2;


		float __nx ;
		float __nz ;


		static int _face2x2num;
		static int _face1x1num;

		static GLvoid*** _indicesTable;
		static GLsizei** _countTable;
		static GLsizei*	_wholeCount;

		MeshDrawingData _drawingData[4];

		//------------------------------------------
		// 索引选项
		//------------------------------------------
		static void buildIndicesTables( const int& face2x2num , 
			GLvoid*** &outIndicesTable , GLsizei** &outCountTable );

		static void getDrawingDataFromTable( const int& in_x , 
			const int& in_y , MeshDrawingData& leftup ,
			MeshDrawingData& rightup , MeshDrawingData& leftdown ,
			MeshDrawingData& rightdown );


	private:


		static void insertFaceindex( int facei2x2 , int facexnum , 
			std::vector<short unsigned int>& outvec , const bool& insertemptyindex,
			const bool& generate_gaps);

		static void insertSingleFace( int i, int facexnum, 
			std::vector<short unsigned int> &outvec ,const bool& generate_gaps);

	};

	typedef vgKernel::SharePtr<MeshChunkUpData> MeshChunkUpDataPtr;


	class MeshChunkUp
	{
	public:
		MeshChunkUp( MeshChunkUpDataPtr data , 
			float stepsize,
			float offsetx , float offsetz , float offset_unit, float scale , int rotate ,
			bool rotatealongZ ,
			TerrainCenter* center , float* curposx , float* curposy ,
			float* curposz );
		~MeshChunkUp();


		void update(const int& transXint , const int& transZint );

		void render( const int& transXint , const int& transZint );

		inline void setRenderGapsFlag( const bool& if_render)
		{
			this->_renderGaps = if_render;
		}

	private:

		ElevationBound _sceneBound;
		ElevationBound _tmpBound;

		float _stepSize;

		bool _renderGaps;

		float* _pCurrentPosX;
		float* _pCurrentPosY;
		float* _pCurrentPosZ;

		ElevationItem** _ppTexBlockLeftUp;
		ElevationItem** _ppTexBlockLeftDown;
		ElevationItem** _ppTexBlockRightUp;
		ElevationItem** _ppTexBlockRightDown;


		vgCam::ViewFrustum* _viewFrustum;


		TerrainCenter* _terrainCenter;


		int _centerX;
		int _centerZ;

		// 最小offset单位
		float _offsetUnit;
		float _scale;

		bool _rotateAlongZ;

		float _offsetX;
		float _offsetZ;


		int _rotate;

		MeshChunkUpDataPtr _data;

	};

	
	
}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHCHUNKUP_H__