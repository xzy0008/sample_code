#include <vgStableHeaders.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkQuat.h>
#include <vgKernel/vgkIntersectSegment3Box3.h>

#define FORCEUINT(a) ((unsigned int &) a)

namespace vgKernel {


#undef PI
	/**
		正向最大值的设定.注意此值打印出来是"1.#INF",标准的float型含有最大值的表示方法.
		注意,并不是所有的数值都有最大值表示,具体方法可如下查看:

		cout << numeric_limits<float>::has_infinity <<endl;			//为1
		cout << numeric_limits<double>::has_infinity<<endl;			//为1
		cout << numeric_limits<long double>::has_infinity <<endl;	//为1
		cout << numeric_limits<int>::has_infinity <<endl;			//为0

	*/
	const float Math::POS_INFINITY = std::numeric_limits<float>::infinity();		
	const float Math::NEG_INFINITY = -std::numeric_limits<float>::infinity();	
	const float Math::PI = float( 4.0 * atan( 1.0 ) /*3.1415926535898f*/);
	const float Math::TWO_PI = float( 2.0 * PI );
	const float Math::HALF_PI = float( 0.5 * PI );
	const float Math::fDeg2Rad = PI / float(180.0);
	const float Math::fRad2Deg = float(180.0) / PI;
	//const float Math::MAX_REAL = DBL_MAX /*1.7976931348623158e+308*/;		
#undef max
	const float Math::MAX_REAL = std::numeric_limits<float>::max();

	const float Math::ZERO_TOLERANCE = 1e-06f;


	void Math::loadIdentityMatrix(Mat4& matrix)
	{
		static Mat4 identity(1.0f, 0.0f, 0.0f, 0.0f,
							 0.0f, 1.0f, 0.0f, 0.0f,
							 0.0f, 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 0.0f, 1.0f);

		memcpy(matrix._m, identity._m, sizeof(matrix._m));
	}

	void Math::createTranslationMatrix(float x, float y, float z, Mat4& mTranslate)
	{
		Math::loadIdentityMatrix(mTranslate);

		mTranslate._m[12] = x;
		mTranslate._m[13] = y;
		mTranslate._m[14] = z;
	}

	void Math::createScaleMatrix(float x, float y, float z, Mat4& mScale)
	{
		Math::loadIdentityMatrix(mScale);

		mScale._m[0] = x;
		mScale._m[5] = y;
		mScale._m[10] = z;
	}

	void Math::createRotationMatrix(float angle, float x, float y, float z, Mat4& mMatrix)
	{
		vgKernel::Quat quat;// (x, y, z, angle);
		quat.createFromAxisAngle(x, y, z, angle);
		
		quat.createMatrix(mMatrix._m);
// 		float vecLength, sinSave, cosSave, oneMinusCos;
// 		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
// 
// 		// If NULL vector passed in, this will blow up...
// 		if(x == 0.0f && y == 0.0f && z == 0.0f)
// 		{
// 			Math::loadIdentityMatrix(mMatrix);
// 			return;
// 		}
// 
// 		// Scale vector
// 		vecLength = (float)sqrt( x*x + y*y + z*z );
// 
// 		// Rotation matrix is normalized
// 		x /= vecLength;
// 		y /= vecLength;
// 		z /= vecLength;
// 
// 		sinSave = (float)sin(angle);
// 		cosSave = (float)cos(angle);
// 		oneMinusCos = 1.0f - cosSave;
// 
// 		xx = x * x;
// 		yy = y * y;
// 		zz = z * z;
// 		xy = x * y;
// 		yz = y * z;
// 		zx = z * x;
// 		xs = x * sinSave;
// 		ys = y * sinSave;
// 		zs = z * sinSave;
// 
// 		mMatrix._m[0] = (oneMinusCos * xx) + cosSave;
// 		mMatrix._m[4] = (oneMinusCos * xy) - zs;
// 		mMatrix._m[8] = (oneMinusCos * zx) + ys;
// 		mMatrix._m[12] = 0.0f;
// 
// 		mMatrix._m[1] = (oneMinusCos * xy) + zs;
// 		mMatrix._m[5] = (oneMinusCos * yy) + cosSave;
// 		mMatrix._m[9] = (oneMinusCos * yz) - xs;
// 		mMatrix._m[13] = 0.0f;
// 
// 		mMatrix._m[2] = (oneMinusCos * zx) - ys;
// 		mMatrix._m[6] = (oneMinusCos * yz) + xs;
// 		mMatrix._m[10] = (oneMinusCos * zz) + cosSave;
// 		mMatrix._m[14] = 0.0f;
// 
// 		mMatrix._m[3] = 0.0f;
// 		mMatrix._m[7] = 0.0f;
// 		mMatrix._m[11] = 0.0f;
// 		mMatrix._m[15] = 1.0f;
	}


	void Math::multiplyMatrix(const Mat4& m1, const Mat4& m2, Mat4 &mProduct )
	{
		float res[16];

		res[0]     = m1._m[0] * m2._m[0] + m1._m[4] * m2._m[1] + m1._m[8] * m2._m[2] + m1._m[12] * m2._m[3];
		res[4]     = m1._m[0] * m2._m[4] + m1._m[4] * m2._m[5] + m1._m[8] * m2._m[6] + m1._m[12] * m2._m[7];
		res[8]     = m1._m[0] * m2._m[8] + m1._m[4] * m2._m[9] + m1._m[8] * m2._m[10] + m1._m[12] * m2._m[11];
		res[12]    = m1._m[0] * m2._m[12] + m1._m[4] * m2._m[13] + m1._m[8] * m2._m[14] + m1._m[12] * m2._m[15];

		res[1]     = m1._m[1] * m2._m[0] + m1._m[5] * m2._m[1] + m1._m[9] * m2._m[2] + m1._m[13] * m2._m[3];
		res[5]     = m1._m[1] * m2._m[4] + m1._m[5] * m2._m[5] + m1._m[9] * m2._m[6] + m1._m[13] * m2._m[7];
		res[9]     = m1._m[1] * m2._m[8] + m1._m[5] * m2._m[9] + m1._m[9] * m2._m[10] + m1._m[13] * m2._m[11];
		res[13]    = m1._m[1] * m2._m[12] + m1._m[5] * m2._m[13] + m1._m[9] * m2._m[14] + m1._m[13] * m2._m[15];

		res[2]     = m1._m[2] * m2._m[0] + m1._m[6] * m2._m[1] + m1._m[10] * m2._m[2] + m1._m[14] * m2._m[3];
		res[6]     = m1._m[2] * m2._m[4] + m1._m[6] * m2._m[5] + m1._m[10] * m2._m[6] + m1._m[14] * m2._m[7];
		res[10]    = m1._m[2] * m2._m[8] + m1._m[6] * m2._m[9] + m1._m[10] * m2._m[10] + m1._m[14] * m2._m[11];
		res[14]    = m1._m[2] * m2._m[12] + m1._m[6] * m2._m[13] + m1._m[10] * m2._m[14] + m1._m[14] * m2._m[15];

		res[3]     = m1._m[3] * m2._m[0] + m1._m[7] * m2._m[1] + m1._m[11] * m2._m[2] + m1._m[15] * m2._m[3];
		res[7]     = m1._m[3] * m2._m[4] + m1._m[7] * m2._m[5] + m1._m[11] * m2._m[6] + m1._m[15] * m2._m[7];
		res[11]    = m1._m[3] * m2._m[8] + m1._m[7] * m2._m[9] + m1._m[11] * m2._m[10] + m1._m[15] * m2._m[11];
		res[15]    = m1._m[3] * m2._m[12] + m1._m[7] * m2._m[13] + m1._m[11] * m2._m[14] + m1._m[15] * m2._m[15];     

		memcpy( mProduct._m , res , sizeof( float ) * 16 );
	}

	////////////////////////////////////////////////////////////////////////////
	/// This function is not exported, just for this modules use only
	// 3x3 determinant
	float Math::DetIJ(const Mat4& mx, int i, int j)
	{
		int x, y, ii, jj;
		float ret, mat[3][3];

		x = 0;
		for (ii = 0; ii < 4; ii++)
		{
			if (ii == i) continue;
			y = 0;
			for (jj = 0; jj < 4; jj++)
			{
				if (jj == j) continue;
				mat[x][y] = mx._m[(ii*4)+jj];
				y++;
			}
			x++;
		}

		ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
		ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
		ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);

		return ret;
	}

	////////////////////////////////////////////////////////////////////////////
	///
	// Invert matrix
	void Math::invertMatrix(const Mat4& mat, Mat4& mInverse)
	{
		int i, j;
		float det, detij;

		// calculate 4x4 determinant
		det = 0.0f;
		for (i = 0; i < 4; i++)
		{
			det += (i & 0x1) ? (-mat._m[i] * DetIJ(mat, 0, i)) : (mat._m[i] * DetIJ(mat, 0,i));
		}
		det = 1.0f / det;

		// calculate inverse
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				detij = DetIJ(mat, j, i);
				mInverse._m[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det); 
			}
		}
	}

	Vec3 Math::translateVec3(const Mat4& mat, const Vec3& v1)
	{
		Vec3 vec;

		vec.x = mat._m[0] * v1.x + mat._m[4] * v1.y + mat._m[8] * v1.z + mat._m[12];
		vec.y = mat._m[1] * v1.x + mat._m[5] * v1.y + mat._m[9] * v1.z + mat._m[13];
		vec.z = mat._m[2] * v1.x + mat._m[6] * v1.y + mat._m[10] * v1.z + mat._m[14];
		
		return vec;
	}


	std::pair<bool, float> Math::intersects(const vgKernel::Ray& ray, const Box& box)
	{
		//if (box.isNull()) return std::pair<bool, float>(false, 0);
		//if (box.isInfinite()) return std::pair<bool, float>(true, 0);

		float lowt = 0.0f;
		float t;
		bool hit = false;
		Vec3 hitpoint;
		const Vec3& min = box.getMinimum();
		const Vec3& max = box.getMaximum();
		const Vec3& rayorig = ray.getOrigin();
		const Vec3& raydir = ray.getDirection();

		// 射线起点是否在BOX内
		if ( rayorig > min && rayorig < max )
		{
			return std::pair<bool, float>(true, 0);
		}

		// Check each face in turn, only check closest 3
		// Min x
		if (rayorig.x < min.x && raydir.x > 0)
		{
			t = (min.x - rayorig.x) / raydir.x;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				// 求射线与BOX左侧延伸面交点 
				hitpoint = rayorig + raydir * t;
				// 判断是否在BOX左侧面内
				if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max x
		if (rayorig.x > max.x && raydir.x < 0)
		{
			t = (max.x - rayorig.x) / raydir.x;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				// 求射线与BOX右侧延伸面交点
				hitpoint = rayorig + raydir * t;
				// 判断是否在BOX右侧面内
				if (hitpoint.y >= min.y && hitpoint.y <= max.y &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Min y
		if (rayorig.y < min.y && raydir.y > 0)
		{
			t = (min.y - rayorig.y) / raydir.y;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = rayorig + raydir * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max y
		if (rayorig.y > max.y && raydir.y < 0)
		{
			t = (max.y - rayorig.y) / raydir.y;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = rayorig + raydir * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.z >= min.z && hitpoint.z <= max.z &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Min z
		if (rayorig.z < min.z && raydir.z > 0)
		{
			t = (min.z - rayorig.z) / raydir.z;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = rayorig + raydir * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.y >= min.y && hitpoint.y <= max.y &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}
		// Max z
		if (rayorig.z > max.z && raydir.z < 0)
		{
			t = (max.z - rayorig.z) / raydir.z;
			if (t > 0)
			{
				// Substitute t back into ray and check bounds and dist
				hitpoint = rayorig + raydir * t;
				if (hitpoint.x >= min.x && hitpoint.x <= max.x &&
					hitpoint.y >= min.y && hitpoint.y <= max.y &&
					(!hit || t < lowt))
				{
					hit = true;
					lowt = t;
				}
			}
		}

		return std::pair<bool, float>(hit, lowt);

	}

	std::pair<bool, float> Math::intersects(const vgKernel::Ray& ray, Vec3& v0, Vec3& v1, Vec3& v2)
	{
		Vec3 normal = (v1 - v0).crossProduct(v2 - v0);

		return intersects(ray, v0, v1, v2, normal, true, true);
	}

	std::pair<bool, float> Math::intersects(const vgKernel::Ray& ray, const Vec3& a,
		const Vec3& b, const Vec3& c, const Vec3& normal,
		bool positiveSide, bool negativeSide)
	{
		//
		// Calculate intersection with plane.
		//
		float t;
		{
			float denom = normal.dotProduct(ray.getDirection());

			// Check intersect side
			if (denom > + std::numeric_limits<float>::epsilon())
			{
				if (!negativeSide)
					return std::pair<bool, float>(false, 0);
			}
			else if (denom < - std::numeric_limits<float>::epsilon())
			{
				if (!positiveSide)
					return std::pair<bool, float>(false, 0);
			}
			else
			{
				// Parallel or triangle area is close to zero when
				// the plane normal not normalised.
				return std::pair<bool, float>(false, 0);
			}

			t = normal.dotProduct(a - ray.getOrigin()) / denom;

			if (t < 0)
			{
				// Intersection is behind origin
				return std::pair<bool, float>(false, 0);
			}
		}

		//
		// Calculate the largest area projection plane in X, Y or Z.
		//
		size_t i0, i1;
		{
			float n0 = abs(normal[0]);
			float n1 = abs(normal[1]);
			float n2 = abs(normal[2]);

			i0 = 1; i1 = 2;
			if (n1 > n2)
			{
				if (n1 > n0) i0 = 0;
			}
			else
			{
				if (n2 > n0) i1 = 0;
			}
		}

		//
		// Check the intersection point is inside the triangle.
		//
		{
			float u1 = b[i0] - a[i0];
			float v1 = b[i1] - a[i1];
			float u2 = c[i0] - a[i0];
			float v2 = c[i1] - a[i1];
			float u0 = t * ray.getDirection()[i0] + ray.getOrigin()[i0] - a[i0];
			float v0 = t * ray.getDirection()[i1] + ray.getOrigin()[i1] - a[i1];

			float alpha = u0 * v2 - u2 * v0;
			float beta  = u1 * v0 - u0 * v1;
			float area  = u1 * v2 - u2 * v1;

			// epsilon to avoid float precision error
			const float EPSILON = 1e-3f;

			float tolerance = - EPSILON * area;

			if (area > 0)
			{
				if (alpha < tolerance || beta < tolerance || alpha+beta > area-tolerance)
					return std::pair<bool, float>(false, 0);
			}
			else
			{
				if (alpha > tolerance || beta > tolerance || alpha+beta < area-tolerance)
					return std::pair<bool, float>(false, 0);
			}
		}

		return std::pair<bool, float>(true, t);
	}
	//----------------------------------------------------------------
	bool Math::intersects( const Segment3& segment, const Box& box )
	{
		using namespace vgKernel;

		//------------------------------------------
		// 首先将Box转换为Box3
		//------------------------------------------
		Vec3 center = box.getCenter();

		Vec3 half = box.getMaximum() - center;

		Box3 box3( center , Vec3::UNIT_X , 
			Vec3::UNIT_Y , Vec3::UNIT_Z , 
			half.x , half.y , half.z );

		IntrSegment3Box3 intr( segment , box3 );

		return intr.Test();
	}
	//-----------------------------------------------------------------------

	bool Math::checkPointInTriangle(const vgKernel::Vec3& point,
		const vgKernel::Vec3& pa,const vgKernel::Vec3& pb, const vgKernel::Vec3& pc)
	{
		Vec3 e10=pb-pa;
		Vec3 e20=pc-pa;

		float a = e10.dotProduct(e10);
		float b = e10.dotProduct(e20);
		float c = e20.dotProduct(e20);
		float ac_bb=(a*c)-(b*b);

		Vec3 vp(point.x-pa.x, point.y-pa.y, point.z-pa.z);
		float d = vp.dotProduct(e10);
		float e = vp.dotProduct(e20);
		float x = (d*c)-(e*b);
		float y = (e*a)-(d*b);
		float z = x+y-ac_bb;

		unsigned int res = 
			(( FORCEUINT(z)& ~(FORCEUINT(x)|FORCEUINT(y)) ) & 0x80000000);

		return res == 0 ? false : true;
	}

	bool Math::getLowestRoot(float a, float b, float c, float maxR,
		float* root) 
	{
		// Check if a solution exists
		float determinant = b*b - 4.0f*a*c;
		// If determinant is negative it means no solutions.
		if (determinant < 0.0f) return false;
		// calculate the two roots: (if determinant == 0 then
		// x1==x2 but let’s disregard that slight optimization)
		float sqrtD = sqrt(determinant);
		float r1 = (-b - sqrtD) / (2*a);
		float r2 = (-b + sqrtD) / (2*a);
		// Sort so x1 <= x2
		if (r1 > r2) {
			float temp = r2;
			r2 = r1;
			r1 = temp;
		}
		// Get lowest root:
		if (r1 > 0 && r1 < maxR) {
			*root = r1;
			return true;
		}
		// It is possible that we want x2 - this can happen
		// if x1 < 0
		if (r2 > 0 && r2 < maxR) {
			*root = r2;
			return true;
		}
		// No (valid) solutions
		return false;
	}



	vgKernel::Vec3 Math::trans2DPointTo3DVec( const int& x , const int& y )
	{
#ifdef VGK_NO_OPENGL
		assert(0);
		return vgKernel::Vec3();
#else

		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		float winX,winY,winZ;
		GLdouble object_x,object_y,object_z;

		glGetIntegerv(GL_VIEWPORT, viewport);
		winX=(float)x;//OGL中的窗口x坐标
		winY=(float)viewport[3]-(float)y - 1.0f;//OGL中的窗口y坐标


		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);//视图矩阵
		glGetDoublev(GL_PROJECTION_MATRIX, projection);//投影矩阵


		glReadPixels(x,//x坐标
			int(winY),//y坐标
			1,1,//读取一个像素
			GL_DEPTH_COMPONENT,//获得深度信息
			GL_FLOAT,//数据类型为浮点型
			&winZ);//获得的深度值保存在winZ中



		gluUnProject((GLdouble)winX,
			(GLdouble)winY,
			(GLdouble)winZ,
			modelview,
			projection,
			viewport,
			&object_x,
			&object_y,
			&object_z);

		return Vec3(object_x,object_y,object_z);

#endif

	}
}// end of namespace vgKernel
