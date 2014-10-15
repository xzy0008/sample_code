

#ifndef __VGMO_MESHDATA_H__
#define __VGMO_MESHDATA_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgModel/vgmoModelRenderWayVertexArray.h>

namespace vgModel {

	/**
		@date 	2008/07/01  20:58	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGMO_EXPORT ModelData
	{
	public:
		ModelData();

		~ModelData();

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

		ModelRenderWay* getRenderWay()
		{
			return _renderWay;
		}

	private:

		void destroy();
		void setDefault();

	private:

		ModelRenderWay* _renderWay;

	};
	
	
	
}// end of namespace vgModel

#endif // end of __VGMO_MESHDATA_H__