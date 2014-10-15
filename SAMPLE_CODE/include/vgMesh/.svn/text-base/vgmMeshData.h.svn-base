

#ifndef __VGMMESHDATA_H__
#define __VGMMESHDATA_H__


#include <vgMesh/vgmDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgMesh/vgmMeshRenderWayVertexArray.h>

namespace vgMesh {

	/**
		@date 	2008/07/01  20:58	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGM_EXPORT MeshData
	{
	public:
		MeshData();

		~MeshData();

	public:

		bool initialise( char* buf , long bufsize );

		bool initInMainThread();

		// lod参数:
		// 为0时,表示最不清晰,也就是最远
		// 为2时,表示最清晰,最近
		// 其他值无效
		// force_render_in_num_layers强制渲染的图层数。0为默认，最大为2
		void render( int lod , int force_render_in_num_layers ,
			bool transparent_mode ,
			RgbaQuad* colorval );


		void convertToVboRenderWay();

		//void convertToDisplayListRenderWay();//chunyongma

		MeshRenderWay* getRenderWay()
		{
			return _renderWay;
		}

	private:

		void destroy();
		void setDefault();

	private:

		MeshRenderWay* _renderWay;

	};
	
	
	
}// end of namespace vgMesh

#endif // end of __VGMMESHDATA_H__