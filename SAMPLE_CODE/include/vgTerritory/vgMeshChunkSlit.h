


#ifndef __VGTERRITORY_MESHCHUNKSLIT_H__
#define __VGTERRITORY_MESHCHUNKSLIT_H__


#include <vgTerritory/vgtDefinition.h>

#include <vgTerritory/vgMeshVertex.h>
#include <vgTerritory/vgtTerrainCenter.h>
#include <vgTerritory/vgMeshDrawingData.h>
#include <vgKernel/vgkSharePtr.h>


namespace vgTerritory {



	/**
	@date 	2008/04/24  15:18	
	@author  leven

	@brief 	

	@see    
	*/
	class MeshChunkSlitData
	{
	public:
		MeshChunkSlitData( const int& n , const float& cellsize );

		void setDefault();

		~MeshChunkSlitData();

	public:

		void render( const bool& render_up , 
			const bool& render_left,
			const int& texcenterx , 
			const int& texcenterz , 
			ElevationItem* leftup , 
			ElevationItem* leftdown ,
			ElevationItem* rightup ,
			ElevationItem* rightdown );



	private:

		void createMeshImpl();

		void createUpMeshImpl( const int face1x1num, 
			const float beginx, const float beginy, const float beginz );

		void createLeftMeshImpl( const int face1x1num, 
			const float beginx, const float beginy, const float beginz );


		void renderUp();
		void renderLeft();
		void renderLeftUp();


		void destroyVboData();

		int _N;
		float _cellSize;
		int _face1x1num;
		int _face2x2num;

		// 分开渲染的间隔
		int _upSeparated;
		// 纹理上下隔开的标志.
		// true --> leftUp和rightUp的纹理
		// false --> leftDown和rightDown的纹理
		bool _upSeparatedTexFlag;
		int _leftSeparated;
		// 纹理左右隔开的标志.
		// true --> leftUp和leftDown的纹理
		// false --> rightUp和rightDown的纹理
		bool _leftSeparatedTexFlag;


		int _centerX;
		int _centerZ;


		GLuint _upVertexBufID;
		GLuint _upIndexBufID;
		int _upIndexStride;
		int _upIndexStrideUnit;


		GLuint _leftVertexBufID;
		GLuint _leftIndexBufID;
		int _leftIndexStride;
		int _leftIndexStrideUnit;


		ElevationItem* _pTexBlockLeftUp;
		ElevationItem* _pTexBlockLeftDown;
		ElevationItem* _pTexBlockRightUp;
		ElevationItem* _pTexBlockRightDown;


	};

	typedef vgKernel::SharePtr<MeshChunkSlitData> MeshChunkSlitDataPtr;


	class MeshChunkSlit
	{
	public:
		MeshChunkSlit( MeshChunkSlitDataPtr data, 
			TerrainCenter* center ,
			float stepsize, 
			float scale , 
			float* curposx , float* curposy ,
			float* curposz);

		~MeshChunkSlit()
		{

		}


		void render( const int& transXint , const int& transZint );

		void update(const int& transXint , const int& transZint );

		inline void setRenderUpFlag( const bool& if_render )
		{
			this->_renderUp = if_render;
		}
		inline void setRenderLeftFlag( const bool& if_render )
		{
			this->_renderLeft = if_render;
		}


	private:

		float _stepSize;

		bool _renderUp;
		bool _renderLeft;

		int _centerX;
		int _centerZ;

		float _scale;

		float* _pCurrentPosX;
		float* _pCurrentPosY;
		float* _pCurrentPosZ;


		MeshChunkSlitDataPtr _data;


		TerrainCenter* _terrainCenter;



		ElevationItem** _ppTexBlockLeftUp;
		ElevationItem** _ppTexBlockLeftDown;
		ElevationItem** _ppTexBlockRightUp;
		ElevationItem** _ppTexBlockRightDown;


	};


}// end of namespace vgTerritory

#endif // end of __VGTERRITORY_MESHCHUNKSLIT_H__