#ifndef __VGKMATH_H__
#define __VGKMATH_H__

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkSegment3.h>
#include <vgKernel/vgkBox.h>

namespace vgKernel {


	class  VGK_EXPORT Math 
	{
	public:

		Math(){}
		~Math(){}

		static bool floatEqual( const float& a, const float& b, const float& tolerance )
		{
			if (fabs(b-a) <= tolerance)
				return true;
			else
				return false;
		}

		static inline float Sqrt (float fValue) { return sqrt(fValue); }

		static float Abs (float fValue) { return float(fabs(fValue)); }


		static bool intersects( const Segment3& segment, const Box& box );

		static std::pair<bool, float> intersects(const Ray& ray, const Box& box);
		
		static std::pair<bool, float> intersects(const Ray& ray, Vec3& v0, Vec3& v1, Vec3& v2);
		
		static std::pair<bool, float> intersects(const Ray& ray, const Vec3& a,
			const Vec3& b, const Vec3& c, const Vec3& normal,
			bool positiveSide, bool negativeSide);

		
		
		static Vec3 trans2DPointTo3DVec( const int& x , const int& y );

		static void loadIdentityMatrix(Mat4& matrix);
	
		static void createTranslationMatrix(float x, float y, float z, Mat4& mTranslate);
	
		static void createScaleMatrix(float x, float y, float z, Mat4& mScale);
		
		static void createRotationMatrix(float angle, float x, float y, float z, Mat4& mMatrix);
	
		static void multiplyMatrix(const Mat4& m1, const Mat4& m2, Mat4 &mProduct );
	
		static void invertMatrix(const Mat4& mat, Mat4& mInverse);

		static Vec3 translateVec3(const Mat4& mat, const Vec3& v1);
	
		static bool checkPointInTriangle(const vgKernel::Vec3& point,
			const vgKernel::Vec3& pa,const vgKernel::Vec3& pb, const vgKernel::Vec3& pc);

		static bool getLowestRoot(float a, float b, float c, float maxR,
			float* root);

	private:
		static float DetIJ(const Mat4& mx, int i, int j);

	public:

		static const float ZERO_TOLERANCE;

		static const float POS_INFINITY;
		static const float NEG_INFINITY;

#undef PI
		static const float PI;
		static const float TWO_PI;
		static const float HALF_PI;
		static const float fDeg2Rad;
		static const float fRad2Deg;
		static const float MAX_REAL;
	};
}

#endif


