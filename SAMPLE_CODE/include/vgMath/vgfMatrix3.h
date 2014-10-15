/*
-----------------------------------------------------------------------------
  VRES(Virtual Reality GIS Engine System)    
  -------------------------------------------------------------
  License details ... waiting to add...
  -------------------------------------------------------------
  Copyright  (C) 2007 , leven - All Rights Reserved
-----------------------------------------------------------------------------
*/

#ifndef __VGFMATRIX3_H__
#define __VGFMATRIX3_H__

#include <vgMath/vgfPrerequisites.h>
#include <vgMath/vgfVector3.h>


namespace vgMath {


	/**
	@date 	2007/02/20  17:43	
	@author  leven

	@brief 	3*3矩阵类。右手坐标系

	术语:
		Column	 列
		Row		 行
		Diagonal  对角线
		determinant   行列式的值
		decomposition 分解
		orthonormal	 标准正交
		orthogonal		正交

	@see    
	*/
	// NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
	// Coordinate axis rotation matrices are of the form
	//   RX =    1       0       0
	//           0     cos(t) -sin(t)
	//           0     sin(t)  cos(t)
	// where t > 0 indicates a counterclockwise rotation in the yz-plane
	//   RY =  cos(t)    0     sin(t)
	//           0       1       0
	//        -sin(t)    0     cos(t)
	// where t > 0 indicates a counterclockwise rotation in the zx-plane
	//   RZ =  cos(t) -sin(t)    0
	//         sin(t)  cos(t)    0
	//           0       0       1
	// where t > 0 indicates a counterclockwise rotation in the xy-plane.
	
	class VgfExport Matrix3
	{

	public:
		union
		{
			struct
			{  Real m[3][3];  };
			Real v[9];
		};

		// for faster access
		friend class Matrix4;

	public:

		/** Default constructor.
		@note
		It does <b>NOT</b> initialize the matrix for efficiency.
		*/
		inline Matrix3 () { makeZero(); };
		inline explicit Matrix3 (const Real arr[3][3]);
		inline Matrix3 (const Matrix3& rkMatrix);

		Matrix3 (Real fEntry00, Real fEntry01, Real fEntry02,
			Real fEntry10, Real fEntry11, Real fEntry12,
			Real fEntry20, Real fEntry21, Real fEntry22);

		// member access, allows use of construct mat[r][c]
		inline Real* operator[] (size_t iRow) const;

		//inline operator Real* ()
		//{
		//	return (Real*)m[0];
		//}

		///注意size_t是以0开头.
		Vector3 getColumn (size_t iCol) const;
		Vector3 getRow (size_t iCol) const;
		void setColumn(size_t iCol, const Vector3& vec);
		void setRow(size_t iCol, const Vector3& vec);

		///指定三个轴向量，构成一个Matrix3,注意：每个轴在Matrix3表现为一列。
		void fromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);



		// assignment and comparison
		inline Matrix3& operator= (const Matrix3& rkMatrix);

		///比较函数.从第一个数开始,直到遇到一个不相等的返回.
		// comparison
		inline bool operator == (const Matrix3& rkMatrix) const;
		inline bool operator != (const Matrix3& rkMatrix) const;
		inline bool operator<  (const Matrix3& rkM) const;
		inline bool operator<= (const Matrix3& rkM) const;
		inline bool operator>  (const Matrix3& rkM) const;
		inline bool operator>= (const Matrix3& rkM) const;


		// arithmetic operations
		Matrix3 operator+ (const Matrix3& rkMatrix) const;
		Matrix3 operator- (const Matrix3& rkMatrix) const;
		///矩阵相乘,注意为叉乘.
		Matrix3 operator* (const Matrix3& rkM) const;
		Matrix3 operator- () const;

		// arithmetic updates
		Matrix3& operator+= (const Matrix3& rkM);
		Matrix3& operator-= (const Matrix3& rkM);
		Matrix3& operator*= (Real fScalar);
		Matrix3& operator/= (Real fScalar);

		///右乘向量
		// matrix * vector [3x3 * 3x1 = 3x1]
		Vector3 operator* (const Vector3& rkVector) const;

		// vector * matrix [1x3 * 3x3 = 1x3]
		VgfExport friend Vector3 operator* (const Vector3& rkVector,
			const Matrix3& rkMatrix);

		// matrix * scalar
		Matrix3 operator* (Real fScalar) const;
		Matrix3 operator/ (Real fScalar) const;

		// scalar * matrix
		VgfExport friend Matrix3 operator* (Real fScalar, const Matrix3& rkMatrix);

		// utilities
		///矩阵沿对角线翻转.
		Matrix3 transpose () const;				// M^T

		///翻转后再与参数相乘,提高效率.
		Matrix3 transposeTimes (const Matrix3& rkM) const;  // this^T * M

		///乘以参数的转置.
		Matrix3 timesTranspose (const Matrix3& rkM) const;  // this * M^T

		///矩阵求逆
		Matrix3 inverse () const;

		///行列式的值
		Real determinant () const;

		///由3个矩阵创建,方程式:M = L*S*R.
		///其中L ,R 为正交矩阵,S为对角矩阵.
		// Singular value decomposition, M = L*S*R, where L and R are orthogonal
		// and S is a diagonal matrix whose diagonal entries are nonnegative.
		void singularValueComposition (const Matrix3& rkL,
			const Vector3& rkS, const Matrix3& rkR);
		inline void singularValueComposition (const Matrix3& rkL, const Matrix3& rkS,
			const Matrix3& rkR);

		///矩阵分解(奇异分解),方程式:M = L*S*R.
		///其中L ,R 为正交矩阵,S为对角矩阵.
		void singularValueDecomposition (Matrix3& rkL, Vector3& rkS,
			Matrix3& rkR) const;
		void singularValueDecomposition (Matrix3& rkL, Matrix3& rkS,
			Matrix3& rkR) const;


		/**
			格兰姆-施密特正交化法.
			input:
				M = [m0|m1|m2]
			output:
				Q = [q0|q1|q2]
				其中q0,q1,q2为两两正交的单位向量.
		
			 Gram-Schmidt orthonormalization (applied to columns of rotation matrix)
			 Algorithm uses Gram-Schmidt orthogonalization.  If 'this' matrix is
			 M = [m0|m1|m2], then orthonormal output matrix is Q = [q0|q1|q2],
			
			   q0 = m0/|m0|
			   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
			   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
			
			 where |V| indicates length of vector V and A*B indicates dot
			 product of vectors A and B.
		 */
		void orthonormalize ();

		///分解矩阵为正交矩阵Q,对角线矩阵D,和上三角矩阵U
		///满足的关系为:M = Q*D*U.
		///未知用途.
		// factor M = Q*D*U with orthogonal Q, diagonal D, upper triangular U
		void QDUDecomposition (Matrix3& rkQ, Matrix3& rkD,
			Matrix3& rkU) const;
		// orthogonal Q, diagonal D, upper triangular U stored as (u01,u02,u12)
		void QDUDecomposition (Matrix3& rkQ, Vector3& rkD,
			Vector3& rkU) const;


		/**
		 从正交矩阵得到旋转轴和旋转角,注意矩阵必须满足正交.
		 matrix must be orthonormal.

		 Let (x,y,z) be the unit-length axis and let A be an angle of rotation.
		 The rotation matrix is R = I + sin(A)*P + (1-cos(A))*P^2 where
		 I is the identity and
		
		       +-        -+
		   P = |  0 -z +y |
		       | +z  0 -x |
		       | -y +x  0 |
		       +-        -+
		
		 If A > 0, R represents a counterclockwise rotation about the axis in
		 the sense of looking from the tip of the axis vector towards the
		 origin.  Some algebra will show that
		
		   cos(A) = (trace(R)-1)/2  and  R - R^t = 2*sin(A)*P
		
		 In the event that A = pi, R-R^t = 0 which prevents us from extracting
		 the axis through P.  Instead note that R = I+2*P^2 when A = pi, so
		 P^2 = (R-I)/2.  The diagonal entries of P^2 are x^2-1, y^2-1, and
		 z^2-1.  We can solve these for axis (x,y,z).  Because the angle is pi,
		 it does not matter which sign you choose on the square roots.
		*/
		void toAxisAngle (Vector3& rkAxis, Radian& rfAngle) const;
		inline void toAxisAngle (Vector3& rkAxis, Real& rfReal) const;
		inline void toAxisAngle (Vector3& rkAxis, Degree& rfAngle) const;

		/**
			依据旋转向量和旋转的角度建立旋转矩阵.
			例如:
				mat.FromAxisAngle(Vector3(0,1,0) ,Degree(45).valueRadians());
				cout << mat;
				Vector3 v(1,0,0);
				cout << mat * v << endl;
			可以看到v向量被绕着y轴右手顺时针旋转了45度.
			注意rkAxis要normalized.
		*/
		void fromAxisAngle (const Vector3& rkAxis, const Real& fReals);
		void fromAxisAngle (const Vector3& rkAxis, const Radian& fRadians);
		void fromAxisAngle (const Vector3& rkAxis, const Degree& fDegrees);



		/**
			分解矩阵到欧拉角:yaw*pitch*roll,它们的中文名称分别叫转动角、进动角、章动角.

			注意:
			1.从矩阵分解到欧拉角常常关系到顺序,比如,先绕x轴旋转r1,再绕y轴旋转r2和进行相反的
			顺序生成的矩阵并不一样.也就是关系到顺序的问题.
				下面的一系列函数便利用了这一点:ToEulerAnglesXYZ -指所绕的旋转轴依次为XYZ,其他的
			以此类推.
			2.生成的为限制欧拉角,范围为[-pi,pi],   [-pi/2,pi/2],   [-pi,pi](与参数对应)
			3.返回为false时,wAngle is 0 and vAngle is either pi/2 or
			-pi/2.(详见英文注释)
			
			详见EulerAngles.pdf

				Euler Angle Formulas
				David Eberly
				Geometric Tools, Inc.
				http://www.geometrictools.com
				c
				Copyright 1998-2006. All Rights Reserved.
				Created: December 1, 1999

		 Extract Euler angles from rotation matrices.  The return value is
		 'true' iff the factorization is unique relative to certain angle
		 ranges.  That is, if (U,V,W) is some permutation(置换) of (X,Y,Z), the angle
		 ranges for the outputs from ToEulerAnglesUVW(uAngle,vAngle,wAngle) are
		 uAngle in [-pi,pi], vAngle in [-pi/2,pi/2], and wAngle in [-pi,pi].  If
		 the function returns 'false', wAngle is 0 and vAngle is either pi/2 or
		 -pi/2.

		 A common problem is to factor a rotation matrix as a product of rotations about the coordinate axes. The
		 form of the factorization depends on the needs of the application and what ordering is specified.

		 The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
		 where yaw is rotation about the Up vector, pitch is rotation about the
		 Right axis, and roll is rotation about the Direction axis.

		*/
		bool toEulerAnglesXYZ (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		bool toEulerAnglesXZY (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		bool toEulerAnglesYXZ (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		bool toEulerAnglesYZX (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		bool toEulerAnglesZXY (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		bool toEulerAnglesZYX (Radian& rfYAngle, Radian& rfPAngle,Radian& rfRAngle) const;
		inline bool toEulerAnglesXYZ (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesXZY (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesYXZ (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesYZX (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesZXY (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesZYX (float& rfYAngle, float& rfPAngle,float& rfRAngle) const;
		inline bool toEulerAnglesXYZ (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;
		inline bool toEulerAnglesXZY (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;
		inline bool toEulerAnglesYXZ (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;
		inline bool toEulerAnglesYZX (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;
		inline bool toEulerAnglesZXY (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;
		inline bool toEulerAnglesZYX (Degree& rfYAngle, Degree& rfPAngle,Degree& rfRAngle) const;


		///从欧拉角创建矩阵,注意也是关系到旋转顺序.
		void fromEulerAnglesXYZ (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		void fromEulerAnglesXZY (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		void fromEulerAnglesYXZ (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		void fromEulerAnglesYZX (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		void fromEulerAnglesZXY (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		void fromEulerAnglesZYX (const Radian& fYAngle, const Radian& fPAngle, const Radian& fRAngle);
		inline void fromEulerAnglesXYZ (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesXZY (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesYXZ (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesYZX (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesZXY (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesZYX (const float& fYAngle, const float& fPAngle, const float& fRAngle);
		inline void fromEulerAnglesXYZ (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);
		inline void fromEulerAnglesXZY (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);
		inline void fromEulerAnglesYXZ (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);
		inline void fromEulerAnglesYZX (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);
		inline void fromEulerAnglesZXY (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);
		inline void fromEulerAnglesZYX (const Degree& fYAngle, const Degree& fPAngle, const Degree& fRAngle);


		/**
			求特征值和特征向量,注意矩阵必须满足对称的条件.
			rkRot = [u0|u1|u2] ,其中三个列向量为特征向量.
			rkDiag = diag(d0,d1,d2) ,对角线上的3个值分别为特征值,和rkRot的特征向量对应,
			并且满足大小关系:d0 <= d1 <= d2
		 The matrix must be symmetric.  Factor M = R * D * R^T where
		 R = [u0|u1|u2] is a rotation matrix with columns u0, u1, and u2 and
		 D = diag(d0,d1,d2) is a diagonal matrix whose diagonal entries are d0,
		 d1, and d2.  The eigenvector u[i] corresponds to eigenvector d[i].
		 The eigenvalues are ordered as d0 <= d1 <= d2.
		 */
		void eigenDecomposition (Matrix3& rkRot, Matrix3& rkDiag) const;
		void eigenDecomposition (Real afEigenvalue[3], Vector3 akEigenvector[3]) const;




		///感觉是应用与流体计算方面,还未确定,暂时不用.
		Real SpectralNorm () const;
		///static成员,理应在Math类中创建,可以去掉,以tenorProdect()代替(小写).
		///为了测试的完备性,此处保留.
		static void TensorProduct (const Vector3& rkU, const Vector3& rkV,
			Matrix3& rkProduct);
		///和求特征向量一样的函数,可以去掉.为了测试的完备性,此处保留.
		///注意,这是一个较老的版本,产生的特征向量并不满足大小关系:d0 <= d1 <= d2
		// eigensolver, matrix must be symmetric
		void EigenSolveSymmetric (Real afEigenvalue[3],
			Vector3 akEigenvector[3]) const;


	protected:

		// support for singular value decomposition
		//static const Real ms_fSvdEpsilon;				
		//static const unsigned int ms_iSvdMaxIterations;
		static void Bidiagonalize (Matrix3& kA, Matrix3& kL,
			Matrix3& kR);
		static void GolubKahanStep (Matrix3& kA, Matrix3& kL,
			Matrix3& kR);

		///用于求特征值和特征向量.
		// ------Support for eigendecomposition start--------.  
		// The Tridiagonalize function applies
		// a Householder transformation to the matrix.  If that transformation
		// is the identity (the matrix is already tridiagonal), then the return
		// value is 'false'.  Otherwise, the transformation is a reflection and
		// the return value is 'true'.  The QLAlgorithm returns 'true' iff the
		// QL iteration scheme converged.
		bool tridiagonalize (Real afDiag[3], Real afSubd[2]);
		// This is an implementation of the symmetric QR algorithm from the book
		// "Matrix Computations" by Gene H. Golub and Charles F. Van Loan, second
		// edition.  The algorithm is 8.2.3.  The implementation has a slight
		// variation to actually make it a QL algorithm, and it traps the case
		// when either of the subdiagonal terms s0 or s1 is zero and reduces the
		// 2-by-2 subblock directly.
		bool QLAlgorithm (Real afDiag[3], Real afSubDiag[3]);
		// ------Support for eigendecomposition end--------.  


		// support for spectral norm
		static Real MaxCubicRoot (Real afCoeff[3]);

		///用于比较,例如operator == 中.
		// support for comparisons
		inline int compareArrays (const Matrix3& rkM) const;


	public:


		inline bool  isSymmetric() const ;
		inline Matrix3& makeZero();
		inline Matrix3& makeIdentity();
		inline Matrix3& makeTranspose();
		inline Matrix3& makeInverse();
		inline Matrix3& makeAdjoint();

		///从上三角矩阵创建对称矩阵
		inline Matrix3& makeSymmetricFromUpperTriangularMatrix();

		///从下三角矩阵创建对称矩阵
		inline Matrix3& makeSymmetricFromLowerTriangularMatrix();

		

		///通过行参数和列参数获得矩阵中的某个值.
		///注意row和col可以为0,即0行0列,范围为[0-2]
		inline Real getValueByPosition(const uint& row , const uint& col );
		inline void setValueByPosition(const uint& row , const uint& col , const Real& value);

		///设置对角线上的三个数,其他的为0.
		inline Matrix3& makeDiagonal(Real fM00, Real fM11, Real fM22);

		///矩阵间的叉乘
		Matrix3 crossProduct( const Matrix3& rkm ) const;
		/**
			矩阵每个对应量相乘,如:
				Matrix3 {       1 ,       0 ,       0 ,
								0 ,       1 ,       0 ,
								0 ,       0 ,       1 }

				Matrix3 { 0.365258 , 0.769486 , -0.523906 ,
						0.564374 , -0.630612 , -0.532739 ,
						-0.740316 , -0.101092 , -0.664614 }

				result:
				--------------------------------------
				Matrix3 { 0.365258 ,       0 ,      -0 ,
								0 , -0.630612 ,      -0 ,
								-0 ,      -0 , -0.664614 }

		*/

		Matrix3 tensorProduct(const Matrix3& rkM ) const;

		///求伴随矩阵
		Matrix3 adjoint () const;

		///输出函数,方便测试
		inline friend StdOStream& operator <<
			( StdOStream& o, const Matrix3& v );

		String getDetails() const
		{
			StdStringStream o;
			o << (*this);
			return o.str();
		}

	public:
		static const Real EPSILON;
		static const Matrix3 ZERO;
		static const Matrix3 IDENTITY;
	};

	#include <vgMath/vgfMatrix3Impl.inl>

	
}

#endif // end of __VGFMATRIX3_H__