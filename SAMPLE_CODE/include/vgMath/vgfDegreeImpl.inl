
inline Real Degree::valueRadians() const
{
	return Math::DegreesToRadians ( mDeg );
}

inline Real Degree::valueAngleUnits() const
{
	return Math::DegreesToAngleUnits ( mDeg );
}

inline Degree operator * ( Real a, const Degree& b )
{
	return Degree ( a * b.valueDegrees() );
}

inline Degree operator / ( Real a, const Degree& b )
{
	return Degree ( a / b.valueDegrees() );
}