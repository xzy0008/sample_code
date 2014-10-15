

#ifndef __VGCACAMERARECORDFRAME_H__
#define __VGCACAMERARECORDFRAME_H__


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkQuat.h>


namespace vgCam {

	/**
	@date 	2009/02/09  15:49	
	@author  leven

	@brief 	

	@see    
	*/
	class VCRFrame 
	{
	public:
		VCRFrame()
		{
			index  = 0;
			//fov = 0;

			_head = 0.0f;
		}
		~VCRFrame()
		{

		}

		VCRFrame& operator = ( const VCRFrame& rkVector )
		{
			index = rkVector.index;
			//fov= rkVector.fov;

			_head = rkVector._head;

			pos= rkVector.pos;
			qt= rkVector.qt;

			return *this;
		}

		vgKernel::Quat getQuat()
		{
			vgKernel::Quat ret;
			ret.createFromAxisRadian( qt.m_x, qt.m_y, qt.m_z, qt.m_w);
			ret.normalize();
			return ret;
		}

		vgKernel::Vec3 getPosition() 
		{
			return pos;
		}

		void setQuat( const vgKernel::Quat& quat )
		{
			float radian = 0.0f;
			vgKernel::Vec3 axis;
			quat.toRadianAxis ( radian , axis );

			qt.m_x = axis.x ;
			qt.m_y = axis.y ;
			qt.m_z = axis.z ;
			qt.m_w = radian;
		}

		long index;


		//long fov;

		float _head;


		vgKernel::Vec3 pos;

		// 注意,这里不是四元数的值!要用Quat, 使用getQuat()
		vgKernel::Quat qt;

	};


	typedef std::vector<VCRFrame> VCRFrameList;


}// end of namespace vgCam



#endif // end of __VGCACAMERARECORDFRAME_H__