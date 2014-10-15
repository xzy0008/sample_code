/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFQUATERNION_H__
#define __VGFQUATERNION_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfMath.h>

namespace vgMath {

	/**
		@date 	2007/02/22  17:19	
		@author  leven
	
		@brief 	四元数类,特别地,用于物体旋转和动画插值.
		详见:3D游戏编程大师技巧,其中有详细的解释.

		Implementation of a Quaternion, i.e. a rotation around an axis.
	
		@see    
	*/
    class VgfExport Quaternion
    {

	public:

		union
		{
			struct
			{  Real w, x, y, z;  };
			Real v[4];
		};

    public:
        inline Quaternion (
            Real fW = 1.0,
            Real fX = 0.0, Real fY = 0.0, Real fZ = 0.0)
			: w ( fW ) ,x ( fX ) , y ( fY ) , z( fZ )
		{
		}

        inline Quaternion (const Quaternion& rkQ)
		{
			w = rkQ.w;
			x = rkQ.x;
			y = rkQ.y;
			z = rkQ.z;
		}
        /// Construct a quaternion from a rotation matrix
        inline Quaternion(const Matrix3& rot)
        {
            this->FromRotationMatrix(rot);
        }
        /// Construct a quaternion from an angle/axis
        inline Quaternion(const Radian& rfAngle, const Vector3& rkAxis)
        {
            this->FromAngleAxis(rfAngle, rkAxis);
        }

        inline Quaternion(const Real& rfAngle, const Vector3& rkAxis)
		{
			this->FromAngleAxis(rfAngle, rkAxis);
		}

        /// Construct a quaternion from 3 orthonormal local axes
        inline Quaternion(const Vector3& xaxis, const Vector3& yaxis, const Vector3& zaxis)
        {
            this->FromAxes(xaxis, yaxis, zaxis);
        }
        /// Construct a quaternion from 3 orthonormal local axes
        inline Quaternion(const Vector3* akAxis)
        {
            this->FromAxes(akAxis);
        }
		/// Construct a quaternion from 4 manual w/x/y/z values
		inline Quaternion(Real* valptr)
		{
			memcpy(&w, valptr, sizeof(Real)*4);
		}

		/// Array accessor operator
		inline Real operator [] ( const size_t i ) const;

		/// Array accessor operator
		inline Real& operator [] ( const size_t i );

		// assignment
		inline Quaternion& operator= (const Quaternion& rkQ);

		// comparison
		inline bool operator== (const Quaternion& rkQ) const;
		inline bool operator!= (const Quaternion& rkQ) const;
		inline bool operator<  (const Quaternion& rkQ) const;
		inline bool operator<= (const Quaternion& rkQ) const;
		inline bool operator>  (const Quaternion& rkQ) const;
		inline bool operator>= (const Quaternion& rkQ) const;

		// arithmetic operations
		inline Quaternion operator+ (const Quaternion& rkQ) const;
		inline Quaternion operator- (const Quaternion& rkQ) const;
		inline Quaternion operator/ (Real fScalar) const;
		inline Quaternion operator* (const Quaternion& rkQ) const;
		inline Quaternion operator* (Real fScalar) const;
		inline Quaternion operator- () const;

		// arithmetic updates
		inline Quaternion& operator+= (const Quaternion& rkQ);
		inline Quaternion& operator-= (const Quaternion& rkQ);
		inline Quaternion& operator*= (Real fScalar);
		inline Quaternion& operator/= (Real fScalar);

		// rotation of a vector by a quaternion
		inline Vector3 operator* (const Vector3& rkVector) const;

		/// Pointer accessor for direct copying
		inline Real* ptr();

		/// Pointer accessor for direct copying
		inline const Real* ptr() const;

		void FromRotationMatrix (const Matrix3& kRot);

		///创建旋转矩阵.注意:此旋转矩阵左乘才可以得到正确的结果.
		///将四元数转换为旋转矩阵，参数是回传参数，接收得到的旋转矩阵。
        void ToRotationMatrix (Matrix3& kRot) const;

		///注意!rkAxis要满足单位长度!
		inline Quaternion& FromAngleAxis (const Radian& rfAngle, const Vector3& rkAxis);
		inline Quaternion& FromAngleAxis (const Real& rfAngle, const Vector3& rkAxis);
		inline Quaternion& FromAngleAxis (const Degree& rfAngle, const Vector3& rkAxis);

        void ToAngleAxis (Radian& rfAngle, Vector3& rkAxis) const;
        inline void ToAngleAxis (Degree& dAngle, Vector3& rkAxis) const;
        inline void ToAngleAxis (Real& rfAngle, Vector3& rkAxis) const; 

		///从三个本地坐标轴(本地基坐标,一般满足正交)创建矩阵.
		///由3个向量表达的旋转矩阵生成四元数，参数是指针指向的多个向量表达的旋转矩阵（一般为3个）
        void FromAxes (const Vector3* akAxis);
        void FromAxes (const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);
		
		///创建本地的三个坐标轴向量.
        void ToAxes (Vector3* akAxis) const;
        void ToAxes (Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) const;


		///得到本地的各个坐标轴.
        /// Get the local x-axis
        Vector3 xAxis(void) const;
        /// Get the local y-axis
        Vector3 yAxis(void) const;
        /// Get the local z-axis
        Vector3 zAxis(void) const;


		///对向量执行旋转操作,注意为右乘.
        inline VgfExport friend Quaternion operator* (Real fScalar,
            const Quaternion& rkQ);

        // functions of a quaternion
		inline Real Length () const;  // length of 4-tuple
		inline Real SquaredLength () const;  // squared length of 4-tuple
        Real dotProduct (const Quaternion& rkQ) const;  // dot product
        /// Normalises this quaternion, and returns the previous length
        Real normalise(void); 
        Quaternion Inverse () const;  // apply to non-zero quaternion
		
		///单位翻转,前提是已知本4-tuple为单位长度.
        Quaternion UnitInverse () const;  // apply to unit-length quaternion


   		/// Calculate the local roll element of this quaternion
		inline Radian getRoll(void) const;
   		/// Calculate the local pitch element of this quaternion
		inline Radian getPitch(void) const;
   		/// Calculate the local yaw element of this quaternion
		inline Radian getYaw(void) const;		

		///在一定容差范围内判断2个Quaternion是否相等.
		/// Equality with tolerance (tolerance is max angle difference)
		bool equals(const Quaternion& rhs, const Radian& tolerance) const;
		
		// 未知用途.
		//// spherical linear interpolation
		//static Quaternion Slerp (Real fT, const Quaternion& rkP,
		//	const Quaternion& rkQ, bool shortestPath = false);

		//static Quaternion SlerpExtraSpins (Real fT,
		//	const Quaternion& rkP, const Quaternion& rkQ,
		//	int iExtraSpins);

		///球面线性插值.详见Quaternions.pdf
		// spherical linear interpolation
		Quaternion& Slerp (Real fT, const Quaternion& rkP, const Quaternion& rkQ);

		///带干扰因子的球面线性插值。参数fT为0-1的时间因子。
		///据我所知,干扰因子的作用是使得产生的向量反转,即再转180度.具体情况还未知.
		Quaternion& SlerpExtraSpins (Real fT, const Quaternion& rkP,
			const Quaternion& rkQ, int iExtraSpins);


		///样条插值（二次插值）。目的是在已知样条形状的情况下，通过插值得到平滑的目的线条。
		///fT为0-1的时间因子。rkP和rkQ为样条的起点和终点，而rkA和为rkB插值过程中的某一线段的
		///起点和终点（控制点连线）。详见details.doc
		// spherical quadratic interpolation
		Quaternion& Squad (Real fT, const Quaternion& rkQ0,
			const Quaternion& rkA0, const Quaternion& rkA1,
			const Quaternion& rkQ1);





		///求四元数的指数，即e的四元数次方,未知用途.
		Quaternion Exp () const;  // apply to quaternion with w = 0
		///以e为底求四元数的对数,未知用途.
		Quaternion Log () const;  // apply to unit-length quaternion
		///用于线性插值,未知用途.
		// setup for spherical quadratic interpolation
		static void Intermediate (const Quaternion& rkQ0,
			const Quaternion& rkQ1, const Quaternion& rkQ2,
			Quaternion& rka, Quaternion& rkB);
		///未知的静态插值函数.
        // normalised linear interpolation - faster but less accurate (non-constant rotation velocity)
        static Quaternion nlerp(Real fT, const Quaternion& rkP, 
            const Quaternion& rkQ, bool shortestPath = false);

        // cutoff for sine near zero
        //static const Real ms_fEpsilon;

		/** Function for writing to a stream. Outputs "Quaternion(w, x, y, z)" with w,x,y,z
		being the member values of the quaternion.
		*/
		inline VgfExport friend StdOStream& operator <<
			( StdOStream& o, const Quaternion& q );

		String getDetails() const
		{
			StdOStringStream o;
			o << (*this);
			//o << "Quaternion(" << w << ", " << x << ", " << y << ", " << z << ")";
			return o.str();
		}


	public:

        // special values
        static const Quaternion ZERO;
        static const Quaternion IDENTITY;

	protected:
		// support for comparisons
		inline int compareArrays (const Quaternion& rkQ) const;

    };

	#include <vgMath/vgfQuaternionImpl.inl>
	
}

#endif // end of __VGFQUATERNION_H__