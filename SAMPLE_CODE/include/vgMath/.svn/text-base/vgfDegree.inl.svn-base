/** Wrapper class which indicates a given angle value is in Degrees.
@remarks
Degree values are interchangeable with Radian values, and conversions
will be done automatically between them.
*/
class Degree
{
	Real mDeg; // if you get an error here - make sure to define/typedef 'Real' first

public:
	explicit Degree ( Real d=0 ) : mDeg(d) {}
	Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
	Degree& operator = ( const Real& f ) { mDeg = f; return *this; }
	Degree& operator = ( const Degree& d ) { mDeg = d.mDeg; return *this; }
	//Degree& operator = ( const Radian& r ) { mDeg = r.valueDegrees(); return *this; }

	Real valueDegrees() const { return mDeg; }
	Real valueRadians() const; // see bottom of this file
	Real valueAngleUnits() const;

	const Degree& operator + () const { return *this; }
	Degree operator + ( const Degree& d ) const { return Degree ( mDeg + d.mDeg ); }
	Degree operator + ( const Radian& r ) const { return Degree ( mDeg + r.valueDegrees() ); }
	Degree& operator += ( const Degree& d ) { mDeg += d.mDeg; return *this; }
	Degree& operator += ( const Radian& r ) { mDeg += r.valueDegrees(); return *this; }
	Degree operator - () const { return Degree(-mDeg); }
	Degree operator - ( const Degree& d ) const { return Degree ( mDeg - d.mDeg ); }
	Degree operator - ( const Radian& r ) const { return Degree ( mDeg - r.valueDegrees() ); }
	Degree& operator -= ( const Degree& d ) { mDeg -= d.mDeg; return *this; }
	Degree& operator -= ( const Radian& r ) { mDeg -= r.valueDegrees(); return *this; }
	Degree operator * ( Real f ) const { return Degree ( mDeg * f ); }
	Degree operator * ( const Degree& f ) const { return Degree ( mDeg * f.mDeg ); }
	Degree& operator *= ( Real f ) { mDeg *= f; return *this; }
	Degree operator / ( Real f ) const { return Degree ( mDeg / f ); }
	Degree& operator /= ( Real f ) { mDeg /= f; return *this; }

	bool operator <  ( const Degree& d ) const { return mDeg <  d.mDeg; }
	bool operator <= ( const Degree& d ) const { return mDeg <= d.mDeg; }
	bool operator == ( const Degree& d ) const { return mDeg == d.mDeg; }
	bool operator != ( const Degree& d ) const { return mDeg != d.mDeg; }
	bool operator >= ( const Degree& d ) const { return mDeg >= d.mDeg; }
	bool operator >  ( const Degree& d ) const { return mDeg >  d.mDeg; }


	///Êä³öº¯Êý,·½±ã²âÊÔ
	inline /*VgfExport*/ friend StdOStream& operator <<
		( StdOStream& o, const Degree& v )
	{
		//std::cout.setf(std::ios::fixed);
		o << _T("Degree( ") <<  v.mDeg << _T(" )");
		return o;
	}
	inline String getDetails() const
	{
		StdOStringStream o;
		o << _T("Degree( ") <<  mDeg << _T(" )");
		return o.str();
	}


};

