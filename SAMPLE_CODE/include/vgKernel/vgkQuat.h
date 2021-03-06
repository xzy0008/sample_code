


#ifndef __VGKQUAT_H__
#define __VGKQUAT_H__

#include <vgKernel/vgkForward.h>

#undef PI

#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkVec3.h>

#undef PI

#define SQU(x) (x * x)
//#define PI 3.1415926535f
	
namespace vgKernel {

	/**
		@date 	2008/07/14  8:40	
		@author  xy
	
		@brief 	
	
		@see    
	*/
	class  VGK_EXPORT Quat  
	{
	public:

		inline Quat(float fX, float fY, float fZ, float fW)
		{
			m_x= fX;
			m_y = fY;
			m_z = fZ;
			m_w = fW;
		}

		inline Quat()
		{
			m_x = m_y = m_z = 0.0f;
			m_w = 1.0f;
		}
		inline Quat(Vec3 axis,float radian)
		{
			m_x = axis.x ;
			m_y = axis.y ;
			m_z = axis.z ;
			m_w = radian;
		}

		~Quat()
		{

		}

		/**
			通过欧拉角来创建quat.
			注意,参数是degree, 角度.
		*/
		void fromEulerAnglesDegree( const float& pitch , const float& head , const float& roll );

		inline const Quat operator *(const float fScalar) const
		{
			return Quat(m_fQuat[0] * fScalar, m_fQuat[1] * fScalar, 
				m_fQuat[2] * fScalar, m_fQuat[3] * fScalar);  
		}	

		inline Quat operator *(Quat q);

		/**
			这里载入的是opengl列主序
		*/
		inline void createMatrix(float *pMatrix);

		inline void createFromAxisAngle(float x, float y, float z, float degrees);
		inline void createFromAxisRadian(float x, float y, float z, float radians);


		inline void toRadianAxis (float & rfRadian, Vec3& rkAxis) const;

		inline void normalize();

		static Quat slerp ( float fT, const Quat& rkP, const Quat& rkQ);

		inline const Quat operator +(const Quat& rQuat) const
		{
			return Quat(m_fQuat[0] + rQuat.m_fQuat[0], m_fQuat[1] + rQuat.m_fQuat[1],
				m_fQuat[2] + rQuat.m_fQuat[2], m_fQuat[3] + rQuat.m_fQuat[3]);
		}
		inline float magnitude() const;


		float getPitchDegrees( const bool& reprojectAxis = true ) const;
		float getHeadDegrees(void) const;

		inline const Quat operator-(void) const;

		inline const Quat operator -(const Quat& rQuat) const
		{
			return Quat(m_fQuat[0] - rQuat.m_fQuat[0], m_fQuat[1] - rQuat.m_fQuat[1],
				m_fQuat[2] - rQuat.m_fQuat[2], m_fQuat[3] - rQuat.m_fQuat[3]);

		}
		inline const Quat operator /(const float fScalar) const
		{
			float fInvScl = 1/fScalar;
			return Quat(m_fQuat[0] * fInvScl, m_fQuat[1] * fInvScl, 
				m_fQuat[2] * fInvScl, m_fQuat[3] * fInvScl);  
		}

		friend Quat operator* (float fScalar, const Quat& rkQ);

		String getDetails()
		{
			std::ostringstream o;
			o << "Quat: ( x: " << m_x 
				<< ", y: " << m_y 
				<< ", z: " << m_z
				<< ", w: " << m_w << " )";

			return o.str();
		}

		float dot (const Quat& rkQ) const
		{
			float fDot = 0.0f;
			for (int i = 0; i < 4; i++)
			{
				fDot += m_fQuat[i]*rkQ.m_fQuat[i];
			}
			return fDot;
		}

	private:

		inline Quat LERP(Quat& rQuat0, Quat& rQuat1, float fInterp);

	public:

		union
		{
			struct
			{  		
				float m_x;
				float m_y;	
				float m_z;		
				float m_w;  
			};

			struct
			{  		
				float x;
				float y;	
				float z;		
				float w;  
			};

			float m_fQuat[4];
		};
	};

	
	#include "vgkQuat.inl"

	
}// end of namespace vgKernel
	


#endif // end of __VGKQUAT_H__