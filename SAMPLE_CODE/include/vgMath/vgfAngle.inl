
/** Wrapper class which identifies a value as the currently default angle 
type, as defined by Math::setAngleUnit.
@remarks
Angle values will be automatically converted between radians and degrees,
as appropriate.
*/
class Angle
{
	Real mAngle;
public:
	explicit Angle ( Real angle ) : mAngle(angle) {}
	operator Radian() const;
	operator Degree() const;

	///Êä³öº¯Êý,·½±ã²âÊÔ
	inline /*VgfExport*/ friend StdOStream& operator <<
		( StdOStream& o, const Angle& v )
	{
		//std::cout.setf(std::ios::fixed);
		o << _T("Angle( ") <<  v.mAngle << _T(" )");
		return o;
	}
	inline String getDetails() const
	{
		StdOStringStream o;
		o << _T("Angle( ") <<  mAngle << _T(" )");
		return o.str();
	}
};

