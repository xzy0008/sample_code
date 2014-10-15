


#include <vgStableHeaders.h>
#include <vgKernel/vgkMat4.h>
#include <vgKernel/vgkMath.h>

#undef PI

namespace vgKernel {
	
	
	const Mat4 Mat4::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 );

	const Mat4 Mat4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 );



	Mat4::Mat4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 )
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;
		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;
		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;
		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}
	//----------------------------------------------------------------
	String Mat4::getDetails() const
	{
		std::ostringstream o;

		o << _T( "Mat4(" );
		for (size_t i = 0; i < 4; ++i)
		{
			o << _T(" row") << (unsigned)i << _T("{");
			for(size_t j = 0; j < 4; ++j)
			{
				o << m[i][j] << _T(" ");
			}
			o << _T("}");
		}
		o << _T(")");
		return o.str();
	}
	//----------------------------------------------------------------
	void Mat4::inverse()
	{
		vgKernel::Math::invertMatrix( *this, *this );
	}
	//----------------------------------------------------------------

}// end of namespace vgKernel
