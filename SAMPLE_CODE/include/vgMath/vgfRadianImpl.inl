// these functions could not be defined within the class definition of class
// Radian because they required class Degree to be defined
inline Radian::Radian ( const Degree& d ) : mRad(d.valueRadians()) {
}
inline Radian& Radian::operator = ( const Degree& d ) {
	mRad = d.valueRadians(); return *this;
}
inline Radian Radian::operator + ( const Degree& d ) const {
	return Radian ( mRad + d.valueRadians() );
}
inline Radian& Radian::operator += ( const Degree& d ) {
	mRad += d.valueRadians();
	return *this;
}
inline Radian Radian::operator - ( const Degree& d ) const {
	return Radian ( mRad - d.valueRadians() );
}
inline Radian& Radian::operator -= ( const Degree& d ) {
	mRad -= d.valueRadians();
	return *this;
}

inline Real Radian::valueDegrees() const
{
	return Math::RadiansToDegrees ( mRad );
}

inline Real Radian::valueAngleUnits() const
{
	return Math::RadiansToAngleUnits ( mRad );
}
