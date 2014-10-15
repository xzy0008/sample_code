//** Wrapper class which indicates a given angle value is in Radians.
//@remarks
//Radian values are interchangeable with Degree values, and conversions
//will be done automatically between them.
//*/
class Radian
{
	Real mRad;

public:
	explicit Radian ( Real r=0 ) : mRad(r) {}
	Radian ( const Degree& d );
	inline Radian& operator = ( const Real& f ) { mRad = f; return *this; }
	inline Radian& operator = ( const Radian& r ) { mRad = r.mRad; return *this; }
	inline Radian& operator = ( const Degree& d );

	inline Real valueDegrees() const; // see bottom of this file
	inline Real valueRadians() const { return mRad; }
	inline Real valueAngleUnits() const; 

	const Radian& operator + () const { return *this; }
	Radian operator + ( const Radian& r ) const { return Radian ( mRad + r.mRad ); }
	Radian operator + ( const Degree& d ) const;
	Radian& operator += ( const Radian& r ) { mRad += r.mRad; return *this; }
	Radian& operator += ( const Degree& d );
	Radian operator - () const { return Radian(-mRad); }
	Radian operator - ( const Radian& r ) const { return Radian ( mRad - r.mRad ); }
	Radian operator - ( const Degree& d ) const;
	Radian& operator -= ( const Radian& r ) { mRad -= r.mRad; return *this; }
	Radian& operator -= ( const Degree& d );
	Radian operator * ( Real f ) const { return Radian ( mRad * f ); }
	Radian operator * ( const Radian& f ) const { return Radian ( mRad * f.mRad ); }
	Radian& operator *= ( Real f ) { mRad *= f; return *this; }
	Radian operator / ( Real f ) const { return Radian ( mRad / f ); }
	Radian& operator /= ( Real f ) { mRad /= f; return *this; }

	bool operator <  ( const Radian& r ) const { return mRad <  r.mRad; }
	bool operator <= ( const Radian& r ) const { return mRad <= r.mRad; }
	bool operator == ( const Radian& r ) const { return mRad == r.mRad; }
	bool operator != ( const Radian& r ) const { return mRad != r.mRad; }
	bool operator >= ( const Radian& r ) const { return mRad >= r.mRad; }
	bool operator >  ( const Radian& r ) const { return mRad >  r.mRad; }

	///Êä³öº¯Êý,·½±ã²âÊÔ
	inline /*VgfExport*/ friend StdOStream& operator <<
		( StdOStream& o, const Radian& v )
	{
		//std::cout.setf(std::ios::fixed);
		o << _T("Radian( ") <<  v.mRad << _T(" )");
		return o;
	}

	inline String getDetails() const
	{
		StdOStringStream o;
		o << _T("Radian( ") <<  mRad << _T(" )");
		return o.str();
	}

};

