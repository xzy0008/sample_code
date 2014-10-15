
#pragma once

#include <vggis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>

	
namespace vgGIS3D {

 
	class  VGG_EXPORT Vec3d
	{
	public:

		union
		{
			struct
			{  double x , y , z;  };
			double v[3];
		};

	public:

		inline Vec3d()
			: x( 0.0 ), y( 0.0 ), z( 0.0 )
		{
		}

		inline Vec3d( vgKernel::Vec3 vec3 )
			: x( vec3.x ), y( vec3.y ), z( vec3.z )
		{
		}


		inline Vec3d( const double fX, const double fY, const double fZ )
			: x( fX ), y( fY ), z( fZ )
		{
		}

		inline explicit Vec3d( const double vec[3] )
			: x( vec[0] ),
			y( vec[1] ),
			z( vec[2] )
		{
		}

		inline explicit Vec3d( const int vec[3] )
		{
			x = (double)vec[0];
			y = (double)vec[1];
			z = (double)vec[2];
		}

		inline explicit Vec3d( double* const r )
			: x( r[0] ), y( r[1] ), z( r[2] )
		{
		}

		inline explicit Vec3d( const double scaler )
			: x( scaler )
			, y( scaler )
			, z( scaler )
		{
		}

		inline Vec3d( const Vec3d& rkVector )
			: x( rkVector.x ), y( rkVector.y ), z( rkVector.z )
		{
		}

		inline double operator [] ( const size_t i ) const;
		inline double& operator [] ( const size_t i );


		///operator操作函数重写
		inline Vec3d& operator = ( const Vec3d& rkVector );
		inline Vec3d& operator = ( const double fScaler );
		inline bool operator == ( const Vec3d& rkVector ) const;
		inline bool operator != ( const Vec3d& rkVector ) const;
		inline Vec3d operator + ( const Vec3d& rkVector ) const;
		inline Vec3d operator - ( const Vec3d& rkVector ) const;
		inline Vec3d operator * ( const double fScalar ) const;
		inline Vec3d operator / ( const double fScalar ) const;
		inline Vec3d operator * ( const Vec3d& rkVector) const;
		inline Vec3d operator / ( const Vec3d& rkVector) const;

		///应当注意的情况:当操作数为空时.
		inline const Vec3d& operator + () const;
		inline Vec3d operator - () const;

		///当操作数为左操作数时,注意为友元函数.
		inline friend Vec3d operator * ( const double fScalar, const Vec3d& rkVector );
		inline friend Vec3d operator / ( const double fScalar, const Vec3d& rkVector );
		inline friend Vec3d operator + (const Vec3d& lhs, const double rhs);
		inline friend Vec3d operator + (const double lhs, const Vec3d& rhs);
		inline friend Vec3d operator - (const Vec3d& lhs, const double rhs);
		inline friend Vec3d operator - (const double lhs, const Vec3d& rhs);

		///另外高级的应用
		// arithmetic updates
		inline Vec3d& operator += ( const Vec3d& rkVector );
		inline Vec3d& operator += ( const double fScalar );
		inline Vec3d& operator -= ( const Vec3d& rkVector );
		inline Vec3d& operator -= ( const double fScalar );
		inline Vec3d& operator *= ( const double fScalar );
		inline Vec3d& operator *= ( const Vec3d& rkVector );
		inline Vec3d& operator /= ( const double fScalar );
		inline Vec3d& operator /= ( const Vec3d& rkVector );

		///长度函数
		inline double length () const;

		///时常用到长度的平方,比如比较的时候
		inline double squaredLength () const;


		///距离函数,计算2个向量间的距离
		inline double distance(const Vec3d& rhs) const;
		inline double squaredDistance(const Vec3d& rhs) const;


		///计算2点间的点乘.
		inline double dotProduct(const Vec3d& vec) const;
		inline double absDotProduct(const Vec3d& vec) const;

		///标准化向量,注意:			
		///1. 此时可以杜绝0向量的情况.
		///2. 含有返回值,返回值为先前向量的长度,注意不是vector3,若要返回vector3 ,请使用normalisedRef().
		inline double normalise();

		///返回经过单位化的向量引用.
		inline Vec3d& normalisedRef();

		///计算叉乘
		inline Vec3d crossProduct( const Vec3d& rkVector ) const;

		///返回相加向量和的一半.
		inline Vec3d midPoint( const Vec3d& vec = ZERO ) const;

		///比较函数
		inline bool operator < ( const Vec3d& rhs ) const;
		inline bool operator > ( const Vec3d& rhs ) const;

		///取与操作数相比较而得到的最小值,并且赋予本身
		inline Vec3d makeFloor( const Vec3d& cmp );

		///取与操作数相比较而得到的最大值,赋予本身,返回自身值.
		inline Vec3d makeCeil( const Vec3d& cmp );
		inline Vec3d ceilProduct( const Vec3d& c ) const;
		inline Vec3d floorProduct( const Vec3d& c ) const;

		///得到一个正交向量.注意,此时的正交向量并不确定,欲得到准确的正交向量,请使用4元数.
		inline Vec3d perpendicular(void) const;


		/** Returns true if this vector is zero length. */
		inline bool isZeroLength(void) const;

		/** As normalise, except that this vector is unaffected and the
		normalised vector is returned as a copy. */
		inline Vec3d normalisedCopy(void) const;

		///计算反射向量
		///注意:
		///1.此时normal要为单位向量
		///2.通常情况下容易和入射向量弄混,请注意各自的方向.
		inline Vec3d reflect(const Vec3d& normal) const;


		inline bool operator <= ( const Vec3d& rhs ) const;
		inline bool operator >= ( const Vec3d& rhs ) const;

		inline  void  reset( const double& X ,
			const double& Y ,const double& Z )
		{
			this->x = X;
			this->y = Y;
			this->z = Z;
		}

		String getDetails() const
		{
			std::ostringstream o;
			o << "Vec3d:(" << x << ", " << y << ", " << z << ")";
			return o.str();
		}

		void setLength(double len)
		{
			double scale = (len / length());

			this->x *= scale;
			this->y *= scale;
			this->z *= scale;

		}

		vgKernel::Vec3 getVec3Float() const
		{
			return vgKernel::Vec3( (float)x ,(float)y ,(float)z );
		}

	public:			

		static const Vec3d ZERO;
		static const Vec3d UNIT_X;
		static const Vec3d UNIT_Y;
		static const Vec3d UNIT_Z;
		static const Vec3d NEGATIVE_UNIT_X;
		static const Vec3d NEGATIVE_UNIT_Y;
		static const Vec3d NEGATIVE_UNIT_Z;
		static const Vec3d UNIT_SCALE;

	};

	//std::ostream& operator<< ( std::ostream& o, Vec3d vec3 )
	//{
	//	o << vec3.getDetails();
	//	return o;
	//}

	///inline 函数实现.
	#include "vggiVec3d.inl"
	
	
}// end of namespace  
	
 