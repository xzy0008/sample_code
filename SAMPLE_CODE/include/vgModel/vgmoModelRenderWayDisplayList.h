


#ifndef __VGMO_MESHRENDERWAYDISPLAYLIST_H__
#define __VGMO_MESHRENDERWAYDISPLAYLIST_H__


#if 0

#include <vgKernel/vgkForward.h>
#include <vgModel/vgmoModelRenderWayVertexArray.h>

	
namespace vgModel {


	#define  VG_NULL_VBO_ID	-1



	class ModelRenderWayVertexArray;

	/**
		@date 	2008/07/17  15:23	
		@author  leven
	
		@brief 	注意,只能在主线程中创建,因为构造函数中含有创建
		vbo的命令
	
		@see    
	*/

	class ModelRenderWayDisplayList : public ModelRenderWay
	{
	public:
		friend class ModelRenderWayVertexArray;

		ModelRenderWayDisplayList( ModelRenderWayVertexArray* vertexarray);
		virtual ~ModelRenderWayDisplayList();

		virtual void render(const int& lod);

		bool testIntersection(const vgKernel::Ray* ray);

		virtual bool testIntersection(const vgKernel::Segment3* segment);

		virtual bool initialiseInMainThread();
	
	private:

		void renderInOneLayer();
		void renderInTwoLayer();

		void requireTexObserverByLod( const int& lod );

		bool generateDisplaylist( ModelRenderWayVertexArray* vertexarray  );

	private:

		//////////////////////////////////////////////////////////////////////////

		ModelRenderWayVertexArray* _vertexarray;

		GLint *_lists;
		//////////////////////////////////////////////////////////////////////////

	};
	
	
}// end of namespace vgModel
	

#endif


#endif // end of __VGMO_MESHRENDERWAYVBO_H__