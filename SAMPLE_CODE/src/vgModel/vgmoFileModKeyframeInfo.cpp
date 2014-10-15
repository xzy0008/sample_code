


#include <vgStableHeaders.h>
#include <vgKernel/vgkMath.h>

#include <vgModel/vgmoFileModKeyframeInfo.h>


namespace vgModel {
	

	// 使用弧度
	void mycreateRotationMatrix(float angle, float x, float y, float z, Mat4& mMatrix)
	{




		//_math_matrix_rotate( ctx->CurrentStack->Top, angle, x, y, z);


		//using namespace vgKernel;

		//Quat qCur;

		//qCur.createFromAxisRadian( x, y ,z , angle );

		//qCur.createMatrix( mMatrix._m );


		//return;

#if 0


		vgKernel::Vec3 aa( x , y , z );
		aa.normalise();
		x = aa.x;
		y  =aa.y;
		z=aa.z;

		/**
		( xx(1-c)+c	xy(1-c)-zs  xz(1-c)+ys	 0  )
		|					    |
		| yx(1-c)+zs	yy(1-c)+c   yz(1-c)-xs	 0  |
		| xz(1-c)-ys	yz(1-c)+xs  zz(1-c)+c	 0  |
		|					    |
		(	 0	     0		 0	 1  )
		*/

		float c = cos( angle );
		float s = sin(angle);

		mMatrix._m[0] = x * x * ( 1.0f - c ) + c;
		mMatrix._m[1] = y * x * (1.0f-c)+z * s ;
		mMatrix._m[2] =  x * z * (1.0f-c)-y * s;
		mMatrix._m[3] = 0.0f ;

		mMatrix._m[4] =  x * y * (1.0f-c)-z * s;
		mMatrix._m[5] =  y * y * (1.0f-c)+c;
		mMatrix._m[6] =  y * z * (1.0f-c)+x * s;
		mMatrix._m[7] =  0.0f;

		mMatrix._m[8] =  x * z * (1.0f-c)+y * s;
		mMatrix._m[9] =  y * z * (1.0f-c)-x * s;
		mMatrix._m[10] = z * z * (1.0f-c)+c ;
		mMatrix._m[11] = 0.0f ;

		mMatrix._m[12] = 0.0f ;
		mMatrix._m[13] =  0.0f;
		mMatrix._m[14] =  0.0f;
		mMatrix._m[15] =  1.0f;
#endif



		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c, s, c;

		float *m = mMatrix._m;

		vgKernel::Math::loadIdentityMatrix( mMatrix );


		unsigned char optimized;

		s = (float) sin( angle  );
		c = (float) cos( angle  );

		optimized = 0;

#define M(row,col)  m[col*4+row]

		if (x == 0.0F) {
			if (y == 0.0F) {
				if (z != 0.0F) {
					optimized = 1;
					/* rotate only around z-axis */
					M(0,0) = c;
					M(1,1) = c;
					if (z < 0.0F) {
						M(0,1) = s;
						M(1,0) = -s;
					}
					else {
						M(0,1) = -s;
						M(1,0) = s;
					}
				}
			}
			else if (z == 0.0F) {
				optimized = 1;
				/* rotate only around y-axis */
				M(0,0) = c;
				M(2,2) = c;
				if (y < 0.0F) {
					M(0,2) = -s;
					M(2,0) = s;
				}
				else {
					M(0,2) = s;
					M(2,0) = -s;
				}
			}
		}
		else if (y == 0.0F) {
			if (z == 0.0F) {
				optimized = 1;
				/* rotate only around x-axis */
				M(1,1) = c;
				M(2,2) = c;
				if (x < 0.0F) {
					M(1,2) = s;
					M(2,1) = -s;
				}
				else {
					M(1,2) = -s;
					M(2,1) = s;
				}
			}
		}

		if (!optimized) {
			const float mag = (float) sqrt(x * x + y * y + z * z);

			if (mag <= 1.0e-4) {
				/* no rotation, leave mat as-is */
				return;
			}

			x /= mag;
			y /= mag;
			z /= mag;


			/*
			*     Arbitrary axis rotation matrix.
			*
			*  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
			*  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
			*  (which is about the X-axis), and the two composite transforms
			*  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
			*  from the arbitrary axis to the X-axis then back.  They are
			*  all elementary rotations.
			*
			*  Rz' is a rotation about the Z-axis, to bring the axis vector
			*  into the x-z plane.  Then Ry' is applied, rotating about the
			*  Y-axis to bring the axis vector parallel with the X-axis.  The
			*  rotation about the X-axis is then performed.  Ry and Rz are
			*  simply the respective inverse transforms to bring the arbitrary
			*  axis back to it's original orientation.  The first transforms
			*  Rz' and Ry' are considered inverses, since the data from the
			*  arbitrary axis gives you info on how to get to it, not how
			*  to get away from it, and an inverse must be applied.
			*
			*  The basic calculation used is to recognize that the arbitrary
			*  axis vector (x, y, z), since it is of unit length, actually
			*  represents the sines and cosines of the angles to rotate the
			*  X-axis to the same orientation, with theta being the angle about
			*  Z and phi the angle about Y (in the order described above)
			*  as follows:
			*
			*  cos ( theta ) = x / sqrt ( 1 - z^2 )
			*  sin ( theta ) = y / sqrt ( 1 - z^2 )
			*
			*  cos ( phi ) = sqrt ( 1 - z^2 )
			*  sin ( phi ) = z
			*
			*  Note that cos ( phi ) can further be inserted to the above
			*  formulas:
			*
			*  cos ( theta ) = x / cos ( phi )
			*  sin ( theta ) = y / sin ( phi )
			*
			*  ...etc.  Because of those relations and the standard trigonometric
			*  relations, it is pssible to reduce the transforms down to what
			*  is used below.  It may be that any primary axis chosen will give the
			*  same results (modulo a sign convention) using thie method.
			*
			*  Particularly nice is to notice that all divisions that might
			*  have caused trouble when parallel to certain planes or
			*  axis go away with care paid to reducing the expressions.
			*  After checking, it does perform correctly under all cases, since
			*  in all the cases of division where the denominator would have
			*  been zero, the numerator would have been zero as well, giving
			*  the expected result.
			*/

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * s;
			ys = y * s;
			zs = z * s;
			one_c = 1.0F - c;

			/* We already hold the identity-matrix so we can skip some statements */
			M(0,0) = (one_c * xx) + c;
			M(0,1) = (one_c * xy) - zs;
			M(0,2) = (one_c * zx) + ys;
			/*    M(0,3) = 0.0F; */

			M(1,0) = (one_c * xy) + zs;
			M(1,1) = (one_c * yy) + c;
			M(1,2) = (one_c * yz) - xs;
			/*    M(1,3) = 0.0F; */

			M(2,0) = (one_c * zx) - ys;
			M(2,1) = (one_c * yz) + xs;
			M(2,2) = (one_c * zz) + c;
			/*    M(2,3) = 0.0F; */

			/*
			M(3,0) = 0.0F;
			M(3,1) = 0.0F;
			M(3,2) = 0.0F;
			M(3,3) = 1.0F;
			*/
		}
#undef M


		//matrix_multf( mat, m, MAT_FLAG_ROTATION );



		return;
	}
	
	

	VmdKeyFrame* ModKeyFrameInfo::createVmdKeyFrame()
	{
		assert( sizeof( VmdKeyFrame ) == 4*17 );
		VmdKeyFrame* ret = new VmdKeyFrame[_frameCount ];

		for ( int i = 0 ; i < _frameCount ; ++ i )
		{
			ret[i].m_fTime = _frames[i].m_fTime;

			//ret[i].key_translate = _frames[i].key_translate;
			//ret[i].key_scale = _frames[i].key_scale;

			//for ( int j = 0 ; j < 4 ; ++ j )
			//{
			//	memcpy( ret[i].key_rotate, _frames[i].key_rotate, sizeof( float ) * 4 );
			//}


			vgKernel::Mat4 tran;
			vgKernel::Mat4 tmp = vgKernel::Mat4::IDENTITY;

			vgKernel::Vec3 m_pos0 = _frames[0].key_translate;
			vgKernel::Vec3 fScale = _frames[i].key_scale;
			vgKernel::Vec3 fTranslation = _frames[i].key_translate;

			float* pRotate = _frames[i].key_rotate;












			// 平移复位
			vgKernel::Math::createTranslationMatrix(
				-m_pos0.x, -m_pos0.y, -m_pos0.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);



			// 旋转复位
			//vgKernel::Math::createRotationMatrix(
			//	_frames[0].key_rotate[3]/**(180.0/3.1415926)*/,
			//	_frames[0].key_rotate[0],
			//	_frames[0].key_rotate[1],
			//	_frames[0].key_rotate[2], tran);

			mycreateRotationMatrix(
				_frames[0].key_rotate[3]/**(180.0/3.1415926)*/,
				_frames[0].key_rotate[0],
				_frames[0].key_rotate[1],
				_frames[0].key_rotate[2], tran);

			//mycreateRotationMatrix(0, 
			//	0, 1, 0, tran);

			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);



			// 缩放复位
			vgKernel::Math::createScaleMatrix(
				1.0/_frames[0].key_scale.x,
				1.0/_frames[0].key_scale.y,
				1.0/_frames[0].key_scale.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);


			// 缩放
			vgKernel::Math::createScaleMatrix(fScale.x, fScale.y, fScale.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);

			// 旋转
			//vgKernel::Math::createRotationMatrix(-pRotate[3]/*(180.0/3.1415926)*/, 
			//pRotate[0], pRotate[1], pRotate[2], tran);

			mycreateRotationMatrix( -pRotate[3], 
				pRotate[0], pRotate[1], pRotate[2], tran);

			//mycreateRotationMatrix(0, 
			//	0, 1, 0, tran);

			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);



			// 平移
			vgKernel::Math::createTranslationMatrix(fTranslation.x, fTranslation.y, fTranslation.z, tran);
			vgKernel::Math::multiplyMatrix(tran, tmp, tmp);









			ret[i]._matrix = tmp;

		}


		return ret;
	}
}// end of namespace vgModel
