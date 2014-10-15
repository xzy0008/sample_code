
inline void Quat::createMatrix( float *pMatrix )
{
	// Make sure the matrix has allocated memory to store the rotation data
	assert( pMatrix != NULL );

	// First row
 	pMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z ); 
 	pMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
 	pMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
 	pMatrix[ 3] = 0.0f;  
 
 	// Second row
 	pMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );  
 	pMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z ); 
 	pMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );  
 	pMatrix[ 7] = 0.0f;  
 
 	// Third row
 	pMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
 	pMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
 	pMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );  
 	pMatrix[11] = 0.0f;  
 
 	// Fourth row
 	pMatrix[12] = 0;  
 	pMatrix[13] = 0;  
 	pMatrix[14] = 0;  
 	pMatrix[15] = 1.0f;

	// Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
}

inline Quat Quat::operator *(Quat q)
{
	Quat r;

	r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
	r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
	r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
	r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;

	return(r);
}
void Quat::toRadianAxis (float & rfRadian, Vec3& rkAxis) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	float fSqrLength = m_x*m_x+m_y*m_y+m_z*m_z;
	if ( fSqrLength > 0.0 )
	{

		rfRadian = 2.0f*acos(m_w);
		float fInvLength =  1.0f / sqrt(fSqrLength);
		rkAxis.x= m_x*fInvLength;
		rkAxis.y = m_y*fInvLength;
		rkAxis.z = m_z*fInvLength;
	}
	else
	{
		// angle is 0 (mod 2*pi), so any axis will do
		rfRadian = 0.0;
		rkAxis.x = 1.0;
		rkAxis.y = 0.0;
		rkAxis.z = 0.0;
	}
}

inline void Quat::createFromAxisAngle(float x, float y, float z, float degrees)
{
	// First we want to convert the degrees to radians 
	// since the angle is assumed to be in radians
	float angle = float(degrees / 180.0f) * Math::PI;

	// Here we calculate the sin( theta / 2) once for optimization
	float result = (float)sin( angle / 2.0f );

	// Calcualte the w value by cos( theta / 2 )
	m_w = (float)cos( angle / 2.0f );

	// Calculate the x, y and z of the quaternion
	m_x = float(x * result);
	m_y = float(y * result);
	m_z = float(z * result);
}

void Quat::normalize()
{
	float fInvMag = 1/magnitude();
	if(fInvMag != 1.0f)
	{
		m_fQuat[0] *= fInvMag;
		m_fQuat[1] *= fInvMag;
		m_fQuat[2] *= fInvMag;
		m_fQuat[3] *= fInvMag;
	}
}




const Quat Quat::operator -(void) const
{
	return Quat(-m_fQuat[0], -m_fQuat[1], -m_fQuat[2], -m_fQuat[3]);
}


void Quat::createFromAxisRadian(float x, float y, float z, float radians)
{
	// First we want to convert the degrees to radians 
	// since the angle is assumed to be in radians
	float angle = radians;

	// Here we calculate the sin( theta / 2) once for optimization
	float result = (float)sin( angle / 2.0f );

	// Calcualte the w value by cos( theta / 2 )
	m_w = (float)cos( angle / 2.0f );

	// Calculate the x, y and z of the quaternion
	m_x = float(x * result);
	m_y = float(y * result);
	m_z = float(z * result);
}




Quat Quat::LERP(Quat& rQuat0, Quat& rQuat1, float fInterp)
{
	Quat ret(((rQuat1 - rQuat0) * fInterp) + rQuat0);
	ret.normalize();
	return ret;
}


float Quat::magnitude() const
{
	return sqrtf(SQU(m_fQuat[0]) + SQU(m_fQuat[1]) + SQU(m_fQuat[2]) + SQU(m_fQuat[3]));
}