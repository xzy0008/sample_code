


#ifndef __VGKSHADOWCASTOBJECT_H__
#define __VGKSHADOWCASTOBJECT_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>

	
namespace vgKernel {

	/**
		@date 	2009/03/30  19:12	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class ShadowCastObject
	{
	public:
		ShadowCastObject()
			: _shadowLightDirection( 0.1f, -0.5f, 0.1f ),
			_enableShadowCast( false )
		{

		}

		virtual ~ShadowCastObject()
		{
			
		}
	
	
	public:


		// 下面的4个方法要继承重写

		// 渲染shadow的caster
		virtual void renderInShadowMode() = 0;

		virtual void turnOffShadowCast()
		{
			// 继承此物体的要在一开始先写上这个方法
			_enableShadowCast = false;
		}

		virtual void turnOnShadowCast( const vgKernel::Vec3& light_dir,
			bool force_to_load )
		{
			_shadowLightDirection = light_dir;
			_enableShadowCast = true;
		}

		// 光影的方向在第一次的时候进行设置
		// 包括光的方向变更的时候，也使用此函数进行通知。
		virtual void onLightDirectionChanged( const vgKernel::Vec3& light_dir )
		{
			// 继承此物体也需要写这一步
			_shadowLightDirection = light_dir;
		}

		// get set 函数

		vgKernel::Vec3 getShadowLightDirection() const
		{
			return _shadowLightDirection;
		}

		bool getShadowCastEnable() const
		{
			return _enableShadowCast;
		}

	private:

		bool _enableShadowCast;
		vgKernel::Vec3 _shadowLightDirection;
	};
	
	
	typedef std::vector<ShadowCastObject*> ShadowCastObjectVec;


}// end of namespace vgKernel
	


#endif // end of __VGKSHADOWCASTOBJECT_H__