



#ifndef __VGSHRAYLINE3D_H__
#define __VGSHRAYLINE3D_H__



#include <vgShape/vgshDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgShape {

	/**
		@date 	2009/02/20  20:50	
		@author  leven
	
		@brief 	定义2个点的line, 用于选取操作.
	
		@see    
	*/
	class RayLine3d
	{
	public:
		RayLine3d()
		{
		}
		RayLine3d( const Vec3d& p1 ,const Vec3d& p2 )
		{
			_pointStart = p1;
			_pointEnd = p2;
		}
		~RayLine3d()
		{
			
		}

		Ray3d getRay3d() const 
		{
			Vec3d dir( _pointEnd - _pointStart );
			dir.normalise();
			return Ray3d( _pointStart , dir );
		}

	public:

		Vec3d _pointStart;
		Vec3d _pointEnd;
	
	
	};
	
	
}// end of namespace vgShape
	


#endif // end of __VGSHRAYLINE3D_H__