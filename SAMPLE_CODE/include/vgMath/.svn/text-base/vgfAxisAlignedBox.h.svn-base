/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFAXISALIGNEDBOX_H__
#define __VGFAXISALIGNEDBOX_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfVector4.h>
#include <vgMath/vgfMatrix4.h>
#include <vgMath/vgfVector3.h>

namespace vgMath {

	/**
		@date 	2007/02/21  10:46	
		@author  leven
	
		@brief 	AABB包围盒类,通过2个点定义空间中的盒子.

		A 3D box aligned with the x/y/z axes.

		This class represents a simple box which is aligned with the
		axes. Internally it only stores 2 points as the extremeties of
		the box, one which is the minima of all 3 axes, and the other
		which is the maxima of all 3 axes. This class is typically used
		for an axis-aligned bounding box (AABB) for collision and
		visibility determination.

		@see    
	*/
	class VgfExport AxisAlignedBox
	{
	protected:
		///用于设定box的类型:空类型,边界无限大型,边界确定型.
		///注意,还有一种情况:部分有限型(EXTENT_PARTLY_FINITE)
		///若需要完备的考虑此情况,则要考虑加入,参见isSafe()
		enum Extent
		{
			EXTENT_NULL,
			EXTENT_FINITE,
			EXTENT_INFINITE
		};

		Vector3 mMinimum;
		Vector3 mMaximum;
		Extent mExtent;

		///用于存储八个顶点的数组指针.构造函数时并不创建八个顶点,只有需要的时候
		///创建,详见getAllCorners()
		mutable Vector3* mpCorners;			

	public:

		/*
		   1-----2
		  /|    /|
		 / |   / |
		5-----4  |
		|  0--|--3
		| /   | /
		|/    |/
		6-----7
		*/
		///设定取得哪个Corner点,设定方式如图.具体参见getCorner(...)
		enum CornerEnum {
			FAR_LEFT_BOTTOM = 0,
			FAR_LEFT_TOP = 1,
			FAR_RIGHT_TOP = 2,
			FAR_RIGHT_BOTTOM = 3,
			NEAR_RIGHT_BOTTOM = 7,
			NEAR_LEFT_BOTTOM = 6,
			NEAR_LEFT_TOP = 5,
			NEAR_RIGHT_TOP = 4
		};

		inline AxisAlignedBox() : mpCorners(0)
		{
			// Default to a null box 
			setMinimum( -0.5, -0.5, -0.5 );
			setMaximum( 0.5, 0.5, 0.5 );
			mExtent = EXTENT_NULL;
		}

		inline AxisAlignedBox(const AxisAlignedBox & rkBox) : mpCorners(0)
		{
			if (rkBox.isNull())
				setNull();
			else if (rkBox.isInfinite())
				setInfinite();
			else
				setExtents( rkBox.mMinimum, rkBox.mMaximum );
		}

		///构造函数,通过2个点创建AAB.注意,此处可被更改为安全方式
		inline AxisAlignedBox( const Vector3& min, const Vector3& max ) : mpCorners(0)
		{
			//assert( (min.x <= max.x) && 
			//	(min.x <= max.x) && 
			//	(min.x <= max.x) && 
			//	" vector min并不小于vector max " );

			//setSafeExtents( min , max );
			setExtents( min, max );
		}

		inline AxisAlignedBox(
			Real mx, Real my, Real mz,
			Real Mx, Real My, Real Mz ) : mpCorners(0)
		{
			setExtents( mx, my, mz, Mx, My, Mz );
		}

		AxisAlignedBox& operator=(const AxisAlignedBox& rhs)
		{
			// Specifically override to avoid copying mpCorners
			if (rhs.isNull())
				setNull();
			else if (rhs.isInfinite())
				setInfinite();
			else
				setExtents(rhs.mMinimum, rhs.mMaximum);

			return *this;
		}

		~AxisAlignedBox()
		{
			if (mpCorners)
				delete [] mpCorners;
		}


		/** Gets the minimum corner of the box.
		*/
		inline const Vector3& getMinimum(void) const
		{ 
			return mMinimum; 
		}

		/** Gets a modifiable version of the minimum
		corner of the box.
		*/
		inline Vector3& getMinimum(void)
		{ 
			return mMinimum; 
		}

		/** Gets the maximum corner of the box.
		*/
		inline const Vector3& getMaximum(void) const
		{ 
			return mMaximum;
		}

		/** Gets a modifiable version of the maximum
		corner of the box.
		*/
		inline Vector3& getMaximum(void)
		{ 
			return mMaximum;
		}


		/** Sets the minimum corner of the box.
		*/
		inline void setMinimum( const Vector3& vec )
		{
			mExtent = EXTENT_FINITE;
			mMinimum = vec;
		}

		inline void setMinimum( Real x, Real y, Real z )
		{
			mExtent = EXTENT_FINITE;
			mMinimum.x = x;
			mMinimum.y = y;
			mMinimum.z = z;
		}

		/** Changes one of the components of the minimum corner of the box
		used to resize only one dimension of the box
		*/
		inline void setMinimumX(Real x)
		{
			mMinimum.x = x;
		}

		inline void setMinimumY(Real y)
		{
			mMinimum.y = y;
		}

		inline void setMinimumZ(Real z)
		{
			mMinimum.z = z;
		}

		///为防止创建不规则的box,下面方法可用merge代替.
		/** Sets the maximum corner of the box.
		*/
		inline void setMaximum( const Vector3& vec )
		{
			mExtent = EXTENT_FINITE;
			mMaximum = vec;
		}

		inline void setMaximum( Real x, Real y, Real z )
		{
			mExtent = EXTENT_FINITE;
			mMaximum.x = x;
			mMaximum.y = y;
			mMaximum.z = z;
		}

		/** Changes one of the components of the maximum corner of the box
		used to resize only one dimension of the box
		*/
		inline void setMaximumX( Real x )
		{
			mMaximum.x = x;
		}

		inline void setMaximumY( Real y )
		{
			mMaximum.y = y;
		}

		inline void setMaximumZ( Real z )
		{
			mMaximum.z = z;
		}

		///设定2个点,注意此处并不对2个点进行安全检查
		/** Sets both minimum and maximum extents at once.
		*/
		inline void setExtents( const Vector3& min, const Vector3& max )
		{
			mExtent = EXTENT_FINITE;
			mMinimum = min;
			mMaximum = max;
		}

		inline void setExtents(
			Real mx, Real my, Real mz,
			Real Mx, Real My, Real Mz )
		{
			mExtent = EXTENT_FINITE;

			mMinimum.x = mx;
			mMinimum.y = my;
			mMinimum.z = mz;

			mMaximum.x = Mx;
			mMaximum.y = My;
			mMaximum.z = Mz;

		}

		/// 得到8个顶点的信息.返回为指针.定点顺序如下图所示
		/** Returns a pointer to an array of 8 corner points, useful for
		collision vs. non-aligned objects.
		@remarks
		If the order of these corners is important, they are as
		follows: The 4 points of the minimum Z face (note that
		because Ogre uses right-handed coordinates, the minimum Z is
		at the 'back' of the box) starting with the minimum point of
		all, then anticlockwise around this face (if you are looking
		onto the face from outside the box). Then the 4 points of the
		maximum Z face, starting with maximum point of all, then
		anticlockwise around this face (looking onto the face from
		outside the box). Like this:
		<pre>
		   1-----2
		  /|    /|
		 / |   / |
		5-----4  |
		|  0--|--3
		| /   | /
		|/    |/
		6-----7
		</pre>
		@remarks as this implementation uses a static member, make sure to use your own copy !
		*/
		inline const Vector3* getAllCorners(void) const
		{
			assert( (mExtent == EXTENT_FINITE) && "Can't get corners of a null or infinite AAB" );

			// The order of these items is, using right-handed co-ordinates:
			// Minimum Z face, starting with Min(all), then anticlockwise
			//   around face (looking onto the face)
			// Maximum Z face, starting with Max(all), then anticlockwise
			//   around face (looking onto the face)
			// Only for optimization/compatibility.
			if (!mpCorners)
				mpCorners = new Vector3[8];

			mpCorners[0] = mMinimum;
			mpCorners[1].x = mMinimum.x; mpCorners[1].y = mMaximum.y; mpCorners[1].z = mMinimum.z;
			mpCorners[2].x = mMaximum.x; mpCorners[2].y = mMaximum.y; mpCorners[2].z = mMinimum.z;
			mpCorners[3].x = mMaximum.x; mpCorners[3].y = mMinimum.y; mpCorners[3].z = mMinimum.z;            

			mpCorners[4] = mMaximum;
			mpCorners[5].x = mMinimum.x; mpCorners[5].y = mMaximum.y; mpCorners[5].z = mMaximum.z;
			mpCorners[6].x = mMinimum.x; mpCorners[6].y = mMinimum.y; mpCorners[6].z = mMaximum.z;
			mpCorners[7].x = mMaximum.x; mpCorners[7].y = mMinimum.y; mpCorners[7].z = mMaximum.z;

			return mpCorners;
		}

		///通过CornerEnum获得一个点,默认为FAR_LEFT_BOTTOM = 0 ,即最小的点.
		/** gets the position of one of the corners
		*/
		Vector3 getCorner(CornerEnum cornerToGet = FAR_LEFT_BOTTOM )
		{
			switch(cornerToGet)
			{
			case FAR_LEFT_BOTTOM:
				return mMinimum;
			case FAR_LEFT_TOP:
				return Vector3(mMinimum.x, mMaximum.y, mMinimum.z);
			case FAR_RIGHT_TOP:
				return Vector3(mMaximum.x, mMaximum.y, mMinimum.z);
			case FAR_RIGHT_BOTTOM:
				return Vector3(mMaximum.x, mMinimum.y, mMinimum.z);
			case NEAR_RIGHT_BOTTOM:
				return Vector3(mMaximum.x, mMinimum.y, mMaximum.z);
			case NEAR_LEFT_BOTTOM:
				return Vector3(mMinimum.x, mMinimum.y, mMaximum.z);
			case NEAR_LEFT_TOP:
				return Vector3(mMinimum.x, mMaximum.y, mMaximum.z);
			case NEAR_RIGHT_TOP:
				return mMaximum;
			default:
				return Vector3();
			}
		}

		// leven add
		Vector3 getCorner( const int& cornerNum )
		{
			switch(cornerNum)
			{
			case 0:
				return mMinimum;
			case 1:
				return Vector3(mMinimum.x, mMaximum.y, mMinimum.z);
			case 2:
				return Vector3(mMaximum.x, mMaximum.y, mMinimum.z);
			case 3:
				return Vector3(mMaximum.x, mMinimum.y, mMinimum.z);
			case 7:
				return Vector3(mMaximum.x, mMinimum.y, mMaximum.z);
			case 6:
				return Vector3(mMinimum.x, mMinimum.y, mMaximum.z);
			case 5:
				return Vector3(mMinimum.x, mMaximum.y, mMaximum.z);
			case 4:
				return mMaximum;
			default:
				return Vector3();
			}
		}


		///用于合并2个box
		/** Merges the passed in box into the current box. The result is the
		box which encompasses both.
		*/
		void merge( const AxisAlignedBox& rhs )
		{
			// Do nothing if rhs null, or this is infinite
			if ((rhs.mExtent == EXTENT_NULL) || (mExtent == EXTENT_INFINITE))
			{
				return;
			}
			// Otherwise if rhs is infinite, make this infinite, too
			else if (rhs.mExtent == EXTENT_INFINITE)
			{
				mExtent = EXTENT_INFINITE;
			}
			// Otherwise if current null, just take rhs
			else if (mExtent == EXTENT_NULL)
			{
				setExtents(rhs.mMinimum, rhs.mMaximum);
			}
			// Otherwise merge
			else
			{
				Vector3 min = mMinimum;
				Vector3 max = mMaximum;
				max.makeCeil(rhs.mMaximum);
				min.makeFloor(rhs.mMinimum);

				setExtents(min, max);
			}

		}

		///和一个点的合并方式.
		/** Extends the box to encompass the specified point (if needed).
		*/
		inline void merge( const Vector3& point )
		{
			switch (mExtent)
			{
			case EXTENT_NULL: // if null, use this point
				setExtents(point, point);
				return;

			case EXTENT_FINITE:
				mMaximum.makeCeil(point);
				mMinimum.makeFloor(point);
				return;

			case EXTENT_INFINITE: // if infinite, makes no difference
				return;
			}

			assert( false && "Never reached" );
		}

		/** Transforms the box according to the matrix supplied.
		@remarks
		By calling this method you get the axis-aligned box which
		surrounds the transformed version of this box. Therefore each
		corner of the box is transformed by the matrix, then the
		extents are mapped back onto the axes to produce another
		AABB. Useful when you have a local AABB for an object which
		is then transformed.
		*/
		inline void transform( const Matrix4& matrix )
		{
			// Do nothing if current null or infinite
			if( mExtent != EXTENT_FINITE )
				return;

			Vector3 oldMin, oldMax, temp, currentCorner;

			// Getting the old values so that we can use the existing merge method.
			oldMin = mMinimum;
			oldMax = mMaximum;

			// We sequentially compute the corners in the following order :
			// 0, 6, 5, 1, 2, 4 ,7 , 3
			// This sequence allows us to only change one member at a time to get at all corners.

			// For each one, we transform it using the matrix
			// Which gives the resulting point and merge the resulting point.

			// First corner 
			// min min min
			currentCorner = oldMin;
			merge( matrix * currentCorner );

			// min,min,max
			currentCorner.z = oldMax.z;
			merge( matrix * currentCorner );

			// min max max
			currentCorner.y = oldMax.y;
			merge( matrix * currentCorner );

			// min max min
			currentCorner.z = oldMin.z;
			merge( matrix * currentCorner );

			// max max min
			currentCorner.x = oldMax.x;
			merge( matrix * currentCorner );

			// max max max
			currentCorner.z = oldMax.z;
			merge( matrix * currentCorner );

			// max min max
			currentCorner.y = oldMin.y;
			merge( matrix * currentCorner );

			// max min min
			currentCorner.z = oldMin.z;
			merge( matrix * currentCorner ); 
		}

		///通过仿射矩阵变换包围盒.
		/** Transforms the box according to the affine matrix supplied.
		@remarks
		By calling this method you get the axis-aligned box which
		surrounds the transformed version of this box. Therefore each
		corner of the box is transformed by the matrix, then the
		extents are mapped back onto the axes to produce another
		AABB. Useful when you have a local AABB for an object which
		is then transformed.
		@note
		The matrix must be an affine matrix. @see Matrix4::isAffine.
		*/
		void transformAffine(const Matrix4& m)
		{
			assert(m.isAffine());

			// Do nothing if current null or infinite
			if ( mExtent != EXTENT_FINITE )
				return;

			Vector3 centre = getCenter();
			Vector3 halfSize = getHalfSize();

			Vector3 newCentre = m.transformAffine(centre);
			Vector3 newHalfSize(
				Math::Abs(m[0][0]) * halfSize.x + Math::Abs(m[0][1]) * halfSize.y + Math::Abs(m[0][2]) * halfSize.z, 
				Math::Abs(m[1][0]) * halfSize.x + Math::Abs(m[1][1]) * halfSize.y + Math::Abs(m[1][2]) * halfSize.z,
				Math::Abs(m[2][0]) * halfSize.x + Math::Abs(m[2][1]) * halfSize.y + Math::Abs(m[2][2]) * halfSize.z);

			setExtents(newCentre - newHalfSize, newCentre + newHalfSize);
		}

		/** Sets the box to a 'null' value i.e. not a box.
		*/
		inline void setNull()
		{
			mExtent = EXTENT_NULL;
		}

		/** Returns true if the box is null i.e. empty.
		*/
		inline bool isNull(void) const
		{
			return (mExtent == EXTENT_NULL);
		}

		/// 测试一个包围盒是否是无限大
		/** Returns true if the box is finite.
		*/
		bool isFinite(void) const
		{
			return (mExtent == EXTENT_FINITE);
		}

		/** Sets the box to 'infinite'
		*/
		inline void setInfinite()
		{
			mExtent = EXTENT_INFINITE;
		}

		/** Returns true if the box is infinite.
		*/
		bool isInfinite(void) const
		{
			return (mExtent == EXTENT_INFINITE);
		}

		/// 测试2个包围盒的相交性
		/** Returns whether or not this box intersects another. */
		inline bool intersects(const AxisAlignedBox& b2) const
		{
			// Early-fail for nulls
			if (this->isNull() || b2.isNull())
				return false;

			// Early-success for infinites
			if (this->isInfinite() || b2.isInfinite())
				return true;

			// Use up to 6 separating planes
			if (mMaximum.x < b2.mMinimum.x)
				return false;
			if (mMaximum.y < b2.mMinimum.y)
				return false;
			if (mMaximum.z < b2.mMinimum.z)
				return false;

			if (mMinimum.x > b2.mMaximum.x)
				return false;
			if (mMinimum.y > b2.mMaximum.y)
				return false;
			if (mMinimum.z > b2.mMaximum.z)
				return false;

			// otherwise, must be intersecting
			return true;

		}

		/// 计算和另一个包围盒相交的部分.
		/// Calculate the area of intersection of this box and another
		inline AxisAlignedBox intersection(const AxisAlignedBox& b2) const
		{
            if (this->isNull() || b2.isNull())
			{
				return AxisAlignedBox();
			}
			else if (this->isInfinite())
			{
				return b2;
			}
			else if (b2.isInfinite())
			{
				return *this;
			}

			Vector3 intMin = mMinimum;
            Vector3 intMax = mMaximum;

            intMin.makeCeil(b2.getMinimum());
            intMax.makeFloor(b2.getMaximum());

            // Check intersection isn't null
            if (intMin.x < intMax.x &&
                intMin.y < intMax.y &&
                intMin.z < intMax.z)
            {
                return AxisAlignedBox(intMin, intMax);
            }

            return AxisAlignedBox();
		}

		/// 计算包围盒的体积
		/// Calculate the volume of this box
		Real volume(void) const
		{
			switch (mExtent)
			{
			case EXTENT_NULL:
				return 0.0f;

			case EXTENT_FINITE:
				{
					Vector3 diff = mMaximum - mMinimum;
					return diff.x * diff.y * diff.z;
				}

			case EXTENT_INFINITE:
				return Math::POS_INFINITY;

			default: // shut up compiler
				assert( false && "Never reached" );
				return 0.0f;
			}
		}

		/// 通过给定的向量对包围盒的2点进行伸缩.
		/** Scales the AABB by the vector given. */
		inline void scale(const Vector3& s)
		{
			// Do nothing if current null or infinite
			if (mExtent != EXTENT_FINITE)
				return;

			// NB assumes centered on origin
			Vector3 min = mMinimum * s;
			Vector3 max = mMaximum * s;
			setExtents(min, max);
		}

		///通过给定的值对包围盒的点进行伸缩.
		inline void scale(const Real& s)
		{
			// Do nothing if current null or infinite
			if (mExtent != EXTENT_FINITE)
				return;

			// NB assumes centered on origin
			Vector3 min = mMinimum * s;
			Vector3 max = mMaximum * s;
			setExtents(min, max);
		}

		/// 与球体的相交测试.
		/** Tests whether this box intersects a sphere. */
		bool intersects(const Sphere& s) const
		{
			return Math::intersects(s, *this); 
		}
		/// 与平面的相交测试
		/** Tests whether this box intersects a plane. */
		bool intersects(const Plane& p) const
		{
			return Math::intersects(p, *this);
		}
		/// 与某一个定点的相交测试.
		/** Tests whether the vector point is within this box. */
		bool intersects(const Vector3& v) const
		{
			switch (mExtent)
			{
			case EXTENT_NULL:
				return false;

			case EXTENT_FINITE:
				return(v.x >= mMinimum.x  &&  v.x <= mMaximum.x  && 
					v.y >= mMinimum.y  &&  v.y <= mMaximum.y  && 
					v.z >= mMinimum.z  &&  v.z <= mMaximum.z);

			case EXTENT_INFINITE:
				return true;

			default: // shut up compiler
				assert( false && "Never reached" );
				return false;
			}
		}

		///得到包围盒的中心点.
		/// Gets the centre of the box
		Vector3 getCenter(void) const
		{
			if ( mExtent == EXTENT_NULL )
			{
				return Vector3::ZERO;
			}

			assert( (mExtent == EXTENT_FINITE) && "Can't get center of a null or infinite AAB" );

			return Vector3(
				(mMaximum.x + mMinimum.x) * 0.5,
				(mMaximum.y + mMinimum.y) * 0.5,
				(mMaximum.z + mMinimum.z) * 0.5);

		}
		///得到box的大小,注意返回为向量.
		/// Gets the size of the box
		Vector3 getSize(void) const
		{
			switch (mExtent)
			{
			case EXTENT_NULL:
				return Vector3::ZERO;

			case EXTENT_FINITE:
				return mMaximum - mMinimum;

			case EXTENT_INFINITE:
				return Vector3(
					Math::POS_INFINITY,
					Math::POS_INFINITY,
					Math::POS_INFINITY);

			default: // shut up compiler
				assert( false && "Never reached" );
				return Vector3::ZERO;
			}
		}
		/// Gets the half-size of the box
		Vector3 getHalfSize(void) const
		{
			switch (mExtent)
			{
			case EXTENT_NULL:
				return Vector3::ZERO;

			case EXTENT_FINITE:
				return (mMaximum - mMinimum) * 0.5;

			case EXTENT_INFINITE:
				return Vector3(
					Math::POS_INFINITY,
					Math::POS_INFINITY,
					Math::POS_INFINITY);

			default: // shut up compiler
				assert( false && "Never reached" );
				return Vector3::ZERO;
			}
		}

		///检查一个点是否在box内部.
        /** Tests whether the given point contained by this box.
        */
        bool contains(const Vector3& v) const
        {
            if (isNull())
                return false;
            if (isInfinite())
                return true;

            return mMinimum.x <= v.x && v.x <= mMaximum.x &&
                   mMinimum.y <= v.y && v.y <= mMaximum.y &&
                   mMinimum.z <= v.z && v.z <= mMaximum.z;
        }

		/// 检测一个box是否在其内部.
        /** Tests whether another box contained by this box.
        */
        bool contains(const AxisAlignedBox& other) const
        {
            if (other.isNull() || this->isInfinite())
                return true;

            if (this->isNull() || other.isInfinite())
                return false;

            return this->mMinimum.x <= other.mMinimum.x &&
                   this->mMinimum.y <= other.mMinimum.y &&
                   this->mMinimum.z <= other.mMinimum.z &&
                   other.mMaximum.x <= this->mMaximum.x &&
                   other.mMaximum.y <= this->mMaximum.y &&
                   other.mMaximum.z <= this->mMaximum.z;
        }

        /** Tests 2 boxes for equality.
        */
        bool operator== (const AxisAlignedBox& rhs) const
        {
            if (this->mExtent != rhs.mExtent)
                return false;

            if (!this->isFinite())
                return true;

            return this->mMinimum == rhs.mMinimum &&
                   this->mMaximum == rhs.mMaximum;
        }

        /** Tests 2 boxes for inequality.
        */
        bool operator!= (const AxisAlignedBox& rhs) const
        {
            return !(*this == rhs);
        }

		//////////////////////////////////////////////////////////////////////////
		//added by leven

		///输出函数
		friend StdOStream& operator<< ( StdOStream& o, AxisAlignedBox aab )
		{
			switch (aab.mExtent)
			{
			case EXTENT_NULL:
				o << _T("AxisAlignedBox(null)");
				return o;

			case EXTENT_FINITE:
				o << _T("AxisAlignedBox(min=") << aab.mMinimum << _T(", max=") << aab.mMaximum << _T(")");
				return o;

			case EXTENT_INFINITE:
				o << _T("AxisAlignedBox(infinite)");
				return o;

			default: // shut up compiler
				assert( false && "Never reached" );
				return o;
			}
		}


		/** 检测box是否符合安全的条件:
			1.空时.
			2.无限大时.
			3.有限时,最大值点是否小于最小值点.
		
			注意,若之前赋予box的2个参数部分为Math::POS_INFINITY呢?
			如,mMinimum为Vector3(Math::NEG_INFINITY,1,1)
		*/
		bool  isSafe()
		{
			switch( mExtent )
			{
			case EXTENT_NULL:
				return true;
			case EXTENT_INFINITE:
				return true;
			case EXTENT_FINITE:
				if ( mMinimum <= mMaximum )
				{
					return true;
				}
				return false;
			default:
				assert( 0 && "error for checking box safe: 未知的box形式" );
				return false;		///默认返回
			}

		}
		/** 通过2个点设置盒子的边界,设置后的值保证max值大于min值.
		*/
		inline void setSafeExtents( const Vector3& v1, const Vector3& v2 )
		{
			mExtent = EXTENT_FINITE;
			Vector3 min = v1.floorProduct(v2);
			Vector3 max = v1.ceilProduct(v2);
			mMinimum = min;
			mMaximum = max;
		}

		inline void setSafeExtents(
			Real mx, Real my, Real mz,
			Real Mx, Real My, Real Mz )
		{
			Vector3 v1( mx , my , mz );
			Vector3 v2( Mx , My , Mz );
			setSafeExtents( v1 , v2 );
		}

		/** 设置后的值保证max值大于min值.
		*/
		inline void makeSafe()
		{
			switch( mExtent )
			{
			case EXTENT_NULL:
			case EXTENT_INFINITE:
				return ;
			case EXTENT_FINITE:
				{
					Vector3 min = mMinimum.floorProduct(mMaximum);
					Vector3 max = mMinimum.ceilProduct(mMaximum);
					mMinimum = min;
					mMaximum = max;
					return;
				}
			default:
				return;
			}
		}
	};


	
}

#endif // end of __VGFAXISALIGNEDBOX_H__