/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFFRUSTUM_H__
#define __VGFFRUSTUM_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfMatrix4.h>

namespace vgMath {



	/// 定义投影方式.
	enum ProjectionType
	{
		PT_ORTHOGRAPHIC,
		PT_PERSPECTIVE
	};

	/// 世界坐标下plane的位置.
	enum FrustumPlane
	{
		FRUSTUM_PLANE_NEAR   = 0,
		FRUSTUM_PLANE_FAR    = 1,
		FRUSTUM_PLANE_LEFT   = 2,
		FRUSTUM_PLANE_RIGHT  = 3,
		FRUSTUM_PLANE_TOP    = 4,
		FRUSTUM_PLANE_BOTTOM = 5
	};
	
	/**
	@date 	2007/03/30  10:33	
	@author  Leven

	@brief 	视锥类,6面体,注意实现还不充分,比如,Othro方式还没有实现.

	@see    
	*/

	class VgfExport Frustum
	{

	public:
		Frustum()
		{
			this->setDefaultParmeters();
		}
		virtual ~Frustum()
		{

		}


	protected:

	public:

		/// 投影方式.
		ProjectionType mProjType;

		/// 视角(视场)度数,默认45度.y轴方向(向里看)
		Radian mFOVy;

		/// 距离最远处plane的距离.
		Real mFarDist;

		/// 距离最近处plane的距离.
		Real mNearDist;

		/// 即视口的长宽比例,例如:800/600 = 1.3333333
		/// x/y viewport ratio - default 1.3333
		Real mAspect;

		/// 为0,Opengl中都为1个单位的盒子.
		Real mFocalLength;

		/// 6个面.
		/// The 6 main clipping planes
		mutable Plane mFrustumPlanes[6];

		mutable Plane mExtendPlanes[2];

		/// 8个顶点.
		mutable Vector3 mWorldSpaceCorners[8];

		mutable Vector3 mWorldSpaceCorners2[12];

		/// 投影矩阵
		/// Pre-calced standard projection matrix
		mutable Matrix4 mProjectMatrix;

		/// 模型视口矩阵 - ModelViewMatrix.
		mutable Matrix4 mModelViewMatrix;


		/// 是否使用自定义模型矩阵.
		bool mUseCustomMatrix;

		/// 自定义模型矩阵的存储.
		mutable Matrix4 mCustomModelMatrix;

		/// 是否需要重新计算planes
		mutable bool mRecalcFrustumPlanes;

		/// 是否需要重新计算8个定点.
		mutable bool mRecalcWorldSpaceCorners;

		/// Signal to update frustum information.
		void invalidateFrustum(void) const
		{
			//mRecalcFrustum = true;
			this->invalidateFrustumCorners();
			this->invalidateFrustumPlanes();
		}
		
		/// 激活更新planes
		inline void invalidateFrustumPlanes(void) const
		{
			this->mRecalcFrustumPlanes = true;
		}

		/// 激活更新8个定点.
		inline void invalidateFrustumCorners(void) const
		{
			this->mRecalcWorldSpaceCorners = true;
		}

		/// 查看8个定点是否过期,然后更新.
		inline bool isCornersOutOfDate(void) const
		{
			return mRecalcWorldSpaceCorners;
		}

		/// 查看平面是否过期,然后更新.
		inline bool isPlanesOutOfDate(void) const
		{
			return mRecalcFrustumPlanes;
		}

		/// 通过得到的ProjecMatrix和ModelViewMatrix更新矩阵.
		inline void updateFrustumPlanes()
		{
			if ( isPlanesOutOfDate() )
			{
				this->updateFrustumPlanesImpl();
			}
		}

		/// 实现planes的更新函数
		inline void updateFrustumPlanesImpl();

		/// 更新定点.
		inline void updateWorldSpaceCorners()
		{
			if ( isCornersOutOfDate() )
			{
				this->updateWorldSpaceCornersImpl();
			}
		}

		/// 实现更新8个定点的函数.
		inline void updateWorldSpaceCornersImpl();

		AxisAlignedBox getBoundingBox(void) const
		{
			AxisAlignedBox ret;
			ret.setSafeExtents( mWorldSpaceCorners[0] , mWorldSpaceCorners[1] );
			for ( int i = 2 ; i < 8 ; ++i )
			{
				ret.merge( mWorldSpaceCorners[i] );
			}
			return ret;
		}


		/// 计算投影值,内部函数.
		inline void calcProjectionParameters(Real& left, Real& right,
			Real& bottom, Real& top) const;
		
	public:

		inline bool isVisible( const Vector3& vec ) 
		{
			updateFrustumPlanes();

			for (int plane = 0; plane < 6; ++plane)
			{
				/// 前提:最远处的平面的d不为0

				/// 若为NEGATIVE_SIDE意味着在外部.
				if (mFrustumPlanes[plane].getSide( vec ) == Plane::NEGATIVE_SIDE)
				{
					return false;
				}
			}
			return true;
		}

		inline void updateFrustum(void) 
		{
			this->updateFrustumPlanes();
			this->updateWorldSpaceCorners();


			//Quaternion  q( 3.1415f/2 ,
			//	mWorldSpaceCorners2[5] - mWorldSpaceCorners2[4] );

			Quaternion  q( Math::PI /2 ,
				Vector3::UNIT_Y );

			const Vector3& n0 = q * mFrustumPlanes[FRUSTUM_PLANE_LEFT].normal ;

			mExtendPlanes[0].redefine( n0 , mWorldSpaceCorners2[0] );

			//mExtendPlanes[0].redefine( mWorldSpaceCorners2[0],
			//	mWorldSpaceCorners2[1] ,
			//	);
			

			q.w = - q.w;

			const Vector3& n1 = q *  mFrustumPlanes[FRUSTUM_PLANE_RIGHT].normal ;

			mExtendPlanes[1].redefine( n1 , mWorldSpaceCorners2[2] );
		}

		virtual void setDefaultParmeters()
		{
			this->mProjType = PT_PERSPECTIVE;
			this->invalidateFrustum();
			this->mFOVy = Radian(Math::PI/4.0);
			this->mFarDist = 10000;
			this->mNearDist = 10;
			this->mAspect = 1.3333;
			this->mFocalLength = 1.0f;
			this->mUseCustomMatrix = false;
		}

		inline const Plane* getFrustumPlanes(void)
		{
			updateFrustumPlanes();

			return mFrustumPlanes;
		}

		inline virtual void setCustomMatrix( const Matrix4& customMatrix )
		{
			this->mCustomModelMatrix = customMatrix;
		}

		inline void turnOnCustomMatrix()
		{
			this->mUseCustomMatrix = true;
		}
		inline void turnOffCustomMatrix()
		{
			this->mUseCustomMatrix = false;
		}

		inline void setMatrix( const Matrix4& proj , const Matrix4& modelview )
		{
			this->mProjectMatrix = proj;
			this->mModelViewMatrix = modelview;

			this->mCustomModelMatrix = Matrix4::IDENTITY;

			this->invalidateFrustum();
			updateFrustum();
		}

		inline void setProjectMatrix( const Matrix4& proj )
		{
			this->mProjectMatrix = proj;
			this->invalidateFrustum();
			updateFrustum();
		}

		inline const Vector3 getWorldCorner( const long& selectCorner ) const
		{
			assert( selectCorner < 8 );
			assert( selectCorner >= 0 );
			return mWorldSpaceCorners[selectCorner];
		}

		inline const Vector3 getWorldCorner2( const long& selectCorner ) const
		{
			assert( selectCorner < 12 );
			assert( selectCorner >= 0 );
			return mWorldSpaceCorners2[selectCorner];
		}

		inline const Real		getFarDist() const 
		{ 
			return this->mFarDist; 
		}

		inline void		setFarDist( const Real& val ) 
		{ 
			this->mFarDist = val;
		}

		virtual const String getDetails() const 
		{
			StdOStringStream o ;
			o << _T("Frustum Details : \n");
			for ( int i = 0 ; i < 6 ; i ++ )
			{	
				o << _T("Planes")  << i <<  _T(" : ") << mFrustumPlanes[i].getDetails() << _T('\n');
			}
			for ( int j = 0 ; j < 8 ; j ++ )
			{
				o << _T("Corner")  << j <<  _T(" : ") << mWorldSpaceCorners[j].getDetails() << _T('\n');
			}

			return o.str();
		}
	
	};

	#include <vgMath/vgfFrustum.inl>
	
}

#endif // end of __VGFFRUSTUM_H__