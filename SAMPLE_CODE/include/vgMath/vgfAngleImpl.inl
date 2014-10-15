
inline Angle::operator Radian() const
{
	return Radian(Math::AngleUnitsToRadians(mAngle));
}

inline Angle::operator Degree() const
{
	return Degree(Math::AngleUnitsToDegrees(mAngle));
}