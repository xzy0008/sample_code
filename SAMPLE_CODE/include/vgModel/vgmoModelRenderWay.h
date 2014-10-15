


#ifndef __VGMO_MESHRENDERWAY_H__
#define __VGMO_MESHRENDERWAY_H__
#include <vgModel/vgmoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkSegment3.h>
#include <vgKernel/vgkRgbaQuad.h>
	
namespace vgModel {

	class KeyFrameControl;

	/**
		@date 	2008/07/17  15:06	
		@author  leven
	
		@brief 	 实现简单的reference机制，当引用计数为0时，外部负责delete；
		或者，调用自身的doReferenceDelete(),自动执行delete this。
	
		@see    
	*/
	class ModelRenderWay
	{
	public:
		ModelRenderWay()
			: _referenceCount( 0 ),
			_isTransparent( false )
		{
			
		}
		virtual ~ModelRenderWay()
		{
			assert( _referenceCount == 0 );
		}
	
	
		virtual KeyFrameControl* getKeyFrameControlRef() =0;
		// take ownership
		virtual void setKeyFrameControl( KeyFrameControl* newctrl ) = 0;

		virtual void invalidateTextures() = 0;

		// 初始化操作,要保证在render之前执行过一次
		virtual bool initialiseInMainThread() = 0;

		virtual void render( const int& lod , int force_render_in_num_layers,
			RgbaQuad* colorval ) = 0;

		virtual std::pair<bool, float> testIntersection(const vgKernel::Ray* ray) = 0;

		virtual bool testIntersection(const vgKernel::Segment3* segment) = 0;

		// shadow相关
		virtual void turnOnShadowImpl( const vgKernel::Vec3& light_dir ) = 0;
		virtual void turnOffShadowImpl() = 0;
		virtual void changeLightDirectionImpl(  const vgKernel::Vec3& light_dir ) = 0;
		virtual void renderInShadowModeImpl() = 0;


		void setTransparent( bool enable_it )
		{
			_isTransparent = enable_it;
		}

		void addRef()
		{
			++_referenceCount;
		}
		void releaseRef()
		{
			if ( _referenceCount <= 0 )
			{
				assert(0);
			}
			if ( _referenceCount == 0 )
			{
				return;
			}
			--_referenceCount;
		}

		int getRefCount() const
		{
			return _referenceCount;
		}

		// 先releaseRef，然后尝试删除自身
		void doReferenceDelete()
		{
			releaseRef();

			if ( getRefCount() == 0 )
			{
				delete this;
			}
		}

	protected:

		bool _isTransparent;

	private:


		int	 _referenceCount;

	};
	
	
}// end of namespace vgModel
	


#endif // end of __VGMO_MESHRENDERWAY_H__