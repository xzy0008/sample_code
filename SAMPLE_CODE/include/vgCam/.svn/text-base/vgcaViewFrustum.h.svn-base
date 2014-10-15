


#ifndef __VGCAVIEWFRUSTUM_H__
#define __VGCAVIEWFRUSTUM_H__


#include <vgCam/vgcaDefinition.h>


#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkBox.h>



	
namespace vgCam {

	using namespace vgKernel;

	/**
		@date 	2008/08/30  13:57	
		@author  leven
	
		@brief 	
	
		@see    
	*/
	class  VGCA_EXPORT ViewFrustum
	{
	private:
		enum FrustumSide
		{
			RIGHT	= 0,		// The RIGHT side of the frustum
			LEFT	= 1,		// The LEFT	 side of the frustum
			BOTTOM	= 4,		// The BOTTOM side of the frustum
			TOP		= 5,		// The TOP side of the frustum
			BACK	= 2,		// The BACK	side of the frustum
			FRONT	= 3			// The FRONT side of the frustum
		}; 

		enum PlaneData
		{
			A = 0,				// The X value of the plane's normal
			B = 1,				// The Y value of the plane's normal
			C = 2,				// The Z value of the plane's normal
			D = 3				// The distance the plane is from the origin
		};
	public:
		ViewFrustum()
		{
			_needUpdate = false;
		}
		~ViewFrustum()
		{

		}

		void calculateInEveryFrame();


		inline void validateUpdate()
		{
			_needUpdate = true;
		}

		bool testBoxInFrustum(const Box& box);

		bool testBoxInFrustum( const float& x, const float& y, const float& z, const  float& size);

		//  [9/3/2008 LiuSS]
		//bool testBoxInFrustum( vgMath::BoundingBox& box);
		bool testBoxIncludedInFrustum(const Box& box);

		//bool testBoxIncludedInFrustum( vgMath::BoundingBox& box);

		// Åö×²¼ì²âÏà¹Ø´úÂë
		vgKernel::Box getCameraBox() { return m_collisionBox; }
		void updateCameraBox();


	private:

		void normalizePlane(float frustum[6][4], int side);

	private:

		bool _needUpdate;

		float		m_Frustum[6][4];
		GLfloat		proj[16];			
		GLfloat       modl[16];
		float		clip[16];

		vgKernel::Box m_collisionBox;

		float m_collisionBoxLen;
		float m_collisionBoxWidth;
		float m_collisionBoxHeight;

		vgKernel::Mat4 m_tmpResult;

		vgKernel::Mat4 m_transMat;
		vgKernel::Mat4 m_preModl;
		vgKernel::Mat4 m_modl;
	};
	
	
}// end of namespace vgCam
	


#endif // end of __VGCAVIEWFRUSTUM_H__