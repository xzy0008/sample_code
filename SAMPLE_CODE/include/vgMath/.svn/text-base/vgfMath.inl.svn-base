/**
	@date 	2007/02/19  23:13	
	@author  leven

	@brief 	数学库.可以参照boost::random添加相应的高级随机函数.
		1.添加了数学单位库,包括Radian(弧度),Degree(角度数),Angle(Math类中用到)
		由于含有大量inline函数,故需要放在一个头文件中,不然编译器不通过会报错.
		2.Math类如果要使用Tables,全局范围内要先创建一个实例,tables的初始化操作在
		构造函数里面.
		3.Math中的Angle默认方式是AU_DEGREE,即角度的形式,若要换成弧度,使用setAngleUnit(...);

		术语:
		Sign		实数为正时返回1,为负时返回-1.
		Tangent		正切
	@see    
*/

/** Class to provide access to common mathematical unctions.
@remarks
Most of the maths functions are aliased versions of the C runtime
library functions. They are aliased here to provide future
optimisation opportunities, either from faster RTLs or custom
math approximations.
@note
<br>This is based on MgcMath.h from
<a href="http://www.geometrictools.com/">Wild Magic</a>.
*/
class VgfExport Math 
{
public:
	/** The angular units used by the API. This functionality is now deprecated in favor
	of discreet angular unit types ( see Degree and Radian above ). The only place
	this functionality is actually still used is when parsing files. Search for
	usage of the Angle class for those instances
	*/
	enum AngleUnit
	{
		AU_DEGREE,
		AU_RADIAN
	};

public:
	/** Default constructor.
	@param
	trigTableSize Optional parameter to set the size of the
	tables used to implement Sin, Cos, Tan
	*/
	Math(unsigned int trigTableSize = 4096);

	/** Default destructor.
	*/
	~Math();

	///返回int的标准数学函数
	static inline int IAbs (int iValue) { return ( iValue >= 0 ? iValue : -iValue ); }
	static inline int ICeil (float fValue) { return int(ceil(fValue)); }
	static inline int IFloor (float fValue) { return int(floor(fValue)); }
	static int ISign (int iValue);

	static inline Real Abs (Real fValue) { return Real(fabs(fValue)); }
	static inline Degree Abs (const Degree& dValue) { return Degree(fabs(dValue.valueDegrees())); }
	static inline Radian Abs (const Radian& rValue) { return Radian(fabs(rValue.valueRadians())); }
	static Radian ACos (Real fValue);
	static Radian ASin (Real fValue);
	static inline Radian ATan (Real fValue) { return Radian(atan(fValue)); }
	static inline Radian ATan2 (Real fY, Real fX) { return Radian(atan2(fY,fX)); }
	static inline Real Ceil (Real fValue) { return Real(ceil(fValue)); }


	/**
	///快速估计函数,最新的geometrictools添加.还未做测试.留给以后用.
	///实现在cpp文件里.可以考虑声明为inline.

	// Fast evaluation of trigonometric and inverse trigonometric functions
	// using polynomial approximations.  The speed ups were measured on an
	// AMD 2800 (2.08 GHz) processor using Visual Studion .NET 2003 with a
	// release build.

	// The input must be in [0,pi/2].
	// max error sin0 = 1.7e-04, speed up = 4.0
	// max error sin1 = 1.9e-08, speed up = 2.8
	static Real FastSin0 (Real fAngle);
	static Real FastSin1 (Real fAngle);

	// The input must be in [0,pi/2]
	// max error cos0 = 1.2e-03, speed up = 4.5
	// max error cos1 = 6.5e-09, speed up = 2.8
	static Real FastCos0 (Real fAngle);
	static Real FastCos1 (Real fAngle);

	// The input must be in [0,pi/4].
	// max error tan0 = 8.1e-04, speed up = 5.6
	// max error tan1 = 1.9e-08, speed up = 3.4
	static Real FastTan0 (Real fAngle);
	static Real FastTan1 (Real fAngle);

	// The input must be in [0,1].
	// max error invsin0 = 6.8e-05, speed up = 7.5
	// max error invsin1 = 1.4e-07, speed up = 5.5
	static Real FastInvSin0 (Real fValue);
	static Real FastInvSin1 (Real fValue);

	// The input must be in [0,1].
	// max error invcos0 = 6.8e-05, speed up = 7.5
	// max error invcos1 = 1.4e-07, speed up = 5.7
	static Real FastInvCos0 (Real fValue);
	static Real FastInvCos1 (Real fValue);

	// The input must be in [-1,1]. 
	// max error invtan0 = 1.2e-05, speed up = 2.8
	// max error invtan1 = 2.3e-08, speed up = 1.8
	static Real FastInvTan0 (Real fValue);
	static Real FastInvTan1 (Real fValue);

	// A fast approximation to 1/sqrt.
	static Real FastInvSqrt (Real fValue);

	// Fast approximations to exp(-x).  The input x must be in [0,infinity).
	// max error negexp0 = 0.00024, speed up = 25.4
	// max error negexp1 = 0.000024, speed up = 25.4
	// max error negexp2 = 0.0000024, speed up = 20.5
	// max error negexp3 = 0.00000025, speed up = 17.3
	static Real FastNegExp0 (Real fValue);
	static Real FastNegExp1 (Real fValue);
	static Real FastNegExp2 (Real fValue);
	static Real FastNegExp3 (Real fValue);
	*/

	/** Cosine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Cos (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? Real(cos(fValue.valueRadians())) : SinTable(fValue.valueRadians() + HALF_PI);
	}
	/** Cosine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Cos (Real fValue, bool useTables = false) {
		return (!useTables) ? Real(cos(fValue)) : SinTable(fValue + HALF_PI);
	}

	static inline Real Exp (Real fValue) { return Real(exp(fValue)); }

	///取最小值,如The floor of 2.8 is 2.000000
	static inline Real Floor (Real fValue) { return Real(floor(fValue)); }

	static inline Real Log (Real fValue) { return Real(log(fValue)); }

	static inline Real Pow (Real fBase, Real fExponent) { return Real(pow(fBase,fExponent)); }

	static Real Sign (Real fValue);
	static inline Radian Sign ( const Radian& rValue )
	{
		return Radian(Sign(rValue.valueRadians()));
	}
	static inline Degree Sign ( const Degree& dValue )
	{
		return Degree(Sign(dValue.valueDegrees()));
	}

	static inline Real Max ( const Real& v1, const Real& v2 )
	{
		return ( v1 > v2 ? v1 : v2 );
	}
	static inline Real Min ( const Real& v1, const Real& v2 )
	{
		return ( v1 > v2 ? v2 : v1 );
	}

	/** Sine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Sin (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? Real(sin(fValue.valueRadians())) : SinTable(fValue.valueRadians());
	}
	/** Sine function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Sin (Real fValue, bool useTables = false) {
		return (!useTables) ? Real(sin(fValue)) : SinTable(fValue);
	}

	///即为squaredSqrt(),sqrt的平方.
	static inline Real Sqr (Real fValue) { return fValue*fValue; }

	static inline Real Sqrt (Real fValue) { return Real(sqrt(fValue)); }

	static inline Radian Sqrt (const Radian& fValue) { return Radian(sqrt(fValue.valueRadians())); }

	static inline Degree Sqrt (const Degree& fValue) { return Degree(sqrt(fValue.valueDegrees())); }

	/** Inverse square root i.e. 1 / Sqrt(x), good for vector
	normalisation.
	*/
	inline static Real InvSqrt(Real fValue)
	{
		return Real(asm_rsq(fValue));
	}

	///注意,前提是已经分配了随机数
	static Real UnitRandom ();  // in [0,1]

	static Real RangeRandom (Real fLow, Real fHigh);  // in [fLow,fHigh]

	///返回[-1,1]内的随机数
	static Real SymmetricRandom ();  // in [-1,1]

	/** Tangent function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Tan (const Radian& fValue, bool useTables = false) {
		return (!useTables) ? Real(tan(fValue.valueRadians())) : TanTable(fValue.valueRadians());
	}
	/** Tangent function.
	@param
	fValue Angle in radians
	@param
	useTables If true, uses lookup tables rather than
	calculation - faster but less accurate.
	*/
	static inline Real Tan (Real fValue, bool useTables = false) {
		return (!useTables) ? Real(tan(fValue)) : TanTable(fValue);
	}

	static inline Real DegreesToRadians(Real degrees) { return degrees * fDeg2Rad; }
	static inline Real RadiansToDegrees(Real radians) { return radians * fRad2Deg; }

	/** These functions used to set the assumed angle units (radians or degrees) 
	expected when using the Angle type.
	@par
	You can set this directly after creating a new Root, and also before/after resource creation,
	depending on whether you want the change to affect resource files.
	*/
	static void setAngleUnit(AngleUnit unit);
	/** Get the unit being used for angles. */
	static AngleUnit getAngleUnit(void);

	/** Convert from the current AngleUnit to radians. */
	static Real AngleUnitsToRadians(Real units);
	/** Convert from radians to the current AngleUnit . */
	static Real RadiansToAngleUnits(Real radians);
	/** Convert from the current AngleUnit to degrees. */
	static Real AngleUnitsToDegrees(Real units);
	/** Convert from degrees to the current AngleUnit. */
	static Real DegreesToAngleUnits(Real degrees);

	///判断一个点是否在2d的三角面内.
	/** Checks whether a given point is inside a triangle, in a
	2-dimensional (Cartesian) space.
	@remarks
	The vertices of the triangle must be given in either
	trigonometrical (anticlockwise) or inverse trigonometrical
	(clockwise) order.
	@param
	p The point.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@returns
	If the point resides in the triangle, <b>true</b> is
	returned.
	@par
	If the point is outside the triangle, <b>false</b> is
	returned.
	*/
	static bool pointInTri2D(const Vector2& p, const Vector2& a, 
		const Vector2& b, const Vector2& c);

	///判断一点是否在3d的三角面上.要注意,3个顶点要按顺序放入,另外,
	///p点一定要保证在和三角面相同的平面上
	/** Checks whether a given 3D point is inside a triangle.
	@remarks
	The vertices of the triangle must be given in either
	trigonometrical (anticlockwise) or inverse trigonometrical
	(clockwise) order, and the point must be guaranteed to be in the
	same plane as the triangle
	@param
	p The point.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param 
	normal The triangle plane's normal (passed in rather than calculated
	on demand since the callermay already have it)
	@returns
	If the point resides in the triangle, <b>true</b> is
	returned.
	@par
	If the point is outside the triangle, <b>false</b> is
	returned.
	*/
	static bool pointInTri3D(const Vector3& p, const Vector3& a, 
		const Vector3& b, const Vector3& c, const Vector3& normal);
	/** Ray / plane intersection, returns boolean result and distance. */
	static std::pair<bool, Real> intersects(const Ray& ray, const Plane& plane);

	/** Ray / sphere intersection, returns boolean result and distance. */
	static std::pair<bool, Real> intersects(const Ray& ray, const Sphere& sphere, 
		bool discardInside = true);

	/** Ray / box intersection, returns boolean result and distance. */
	static std::pair<bool, Real> intersects(const Ray& ray, const AxisAlignedBox& box);

	/** Ray / box intersection, returns boolean result and two intersection distance.
	@param
	ray The ray.
	@param
	box The box.
	@param
	d1 A real pointer to retrieve the near intersection distance
	from the ray origin, maybe <b>null</b> which means don't care
	about the near intersection distance.
	@param
	d2 A real pointer to retrieve the far intersection distance
	from the ray origin, maybe <b>null</b> which means don't care
	about the far intersection distance.
	@returns
	If the ray is intersects the box, <b>true</b> is returned, and
	the near intersection distance is return by <i>d1</i>, the
	far intersection distance is return by <i>d2</i>. Guarantee
	<b>0</b> <= <i>d1</i> <= <i>d2</i>.
	@par
	If the ray isn't intersects the box, <b>false</b> is returned, and
	<i>d1</i> and <i>d2</i> is unmodified.
	*/
	static bool intersects(const Ray& ray, const AxisAlignedBox& box,
		Real* d1, Real* d2);

	/** Ray / triangle intersection, returns boolean result and distance.
	@param
	ray The ray.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param 
	normal The triangle plane's normal (passed in rather than calculated
	on demand since the callermay already have it), doesn't need
	normalised since we don't care.
	@param
	positiveSide Intersect with "positive side" of the triangle
	@param
	negativeSide Intersect with "negative side" of the triangle
	@returns
	If the ray is intersects the triangle, a pair of <b>true</b> and the
	distance between intersection point and ray origin returned.
	@par
	If the ray isn't intersects the triangle, a pair of <b>false</b> and
	<b>0</b> returned.
	*/
	static std::pair<bool, Real> intersects(const Ray& ray, const Vector3& a,
		const Vector3& b, const Vector3& c, const Vector3& normal,
		bool positiveSide = true, bool negativeSide = true);

	/** Ray / triangle intersection, returns boolean result and distance.
	@param
	ray The ray.
	@param
	a The triangle's first vertex.
	@param
	b The triangle's second vertex.
	@param
	c The triangle's third vertex.
	@param
	positiveSide Intersect with "positive side" of the triangle
	@param
	negativeSide Intersect with "negative side" of the triangle
	@returns
	If the ray is intersects the triangle, a pair of <b>true</b> and the
	distance between intersection point and ray origin returned.
	@par
	If the ray isn't intersects the triangle, a pair of <b>false</b> and
	<b>0</b> returned.
	*/
	static std::pair<bool, Real> intersects(const Ray& ray, const Vector3& a,
		const Vector3& b, const Vector3& c,
		bool positiveSide = true, bool negativeSide = true);

	/** Sphere / box intersection test. */
	static bool intersects(const Sphere& sphere, const AxisAlignedBox& box);

	/** Plane / box intersection test. */
	static bool intersects(const Plane& plane, const AxisAlignedBox& box);

	/** Ray / convex plane list intersection test. 
	@param ray The ray to test with
	@param plaeList List of planes which form a convex volume
	@param normalIsOutside Does the normal point outside the volume
	*/
	static std::pair<bool, Real> intersects(
		const Ray& ray, const std::vector<Plane>& planeList, 
		bool normalIsOutside);
	/** Ray / convex plane list intersection test. 
	@param ray The ray to test with
	@param plaeList List of planes which form a convex volume
	@param normalIsOutside Does the normal point outside the volume
	*/
	static std::pair<bool, Real> intersects(
		const Ray& ray, const std::list<Plane>& planeList, 
		bool normalIsOutside);

	/** Sphere / plane intersection test. 
	@remarks NB just do a plane.getDistance(sphere.getCenter()) for more detail!
	*/
	static bool intersects(const Sphere& sphere, const Plane& plane);

	/** Compare 2 reals, using tolerance for inaccuracies.
	*/
	static bool RealEqual(Real a, Real b,
		Real tolerance = std::numeric_limits<Real>::epsilon());

	///计算三角面上的切线.参数为3个顶点和各点的uv坐标.
	/** Calculates the tangent space vector for a given set of positions / texture coords. */
	static Vector3 calculateTangentSpaceVector(
		const Vector3& position1, const Vector3& position2, const Vector3& position3,
		Real u1, Real v1, Real u2, Real v2, Real u3, Real v3);

	///** Build a reflection matrix for the passed in plane. */
	//static Matrix4 buildReflectionMatrix(const Plane& p);




	///计算Face Normal,注意返回值为Vector4
	/** Calculate a face normal, including the w component which is the offset from the origin. */
	static Vector4 calculateFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	///计算Face Normal基本的函数,返回为Vector3
	/** Calculate a face normal, no w-information. */
	static Vector3 calculateBasicFaceNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	/** Calculate a face normal without normalize, including the w component which is the offset from the origin. */
	static Vector4 calculateFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	/** Calculate a face normal without normalize, no w-information. */
	static Vector3 calculateBasicFaceNormalWithoutNormalize(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	///高斯分布,通过一个偏移,计算值,表达式:
	///Exp( -(x - offset) ^2 / (2 *( scale ^2 ) ) / ( scale * Sqrt(2 * PI) )
	/** Generates a value based on the gaussian (normal) distribution function
	with the given offset and scale parameters.
	*/
	static Real gaussianDistribution(Real x, Real offset = 0.0f, Real scale = 1.0f);


protected:
	// angle units used by the api
	static AngleUnit msAngleUnit;

	/// Size of the trig tables as determined by constructor.
	static int mTrigTableSize;

	/// Radian -> index factor value ( mTrigTableSize / 2 * PI )
	static Real mTrigTableFactor;
	static Real* mSinTable;
	static Real* mTanTable;

	/** Private function to build trig tables.
	*/
	void buildTrigTables();

	static Real SinTable (Real fValue);
	static Real TanTable (Real fValue);

public:
	//////////////////////////////////////////////////////////////////////////
	// leven add
	static Vector3 intersect(const Plane& p1, const Plane& p2, const Plane& p3);


private:

	static inline Real det(Real m11, Real m12, Real m13,
		Real m21, Real m22, Real m23,
		Real m31, Real m32, Real m33	)
	{
		return ((m11)*(m22)*(m33)-(m11)*(m23)*(m32)-(m21)*(m12)*(m33)+
			(m21)*(m13)*(m32)+(m31)*(m12)*(m23)-(m31)*(m13)*(m22));
	}


public:
	static const Real POS_INFINITY;
	static const Real NEG_INFINITY;
#undef PI
	static const Real PI;
	static const Real TWO_PI;
	static const Real HALF_PI;
	static const Real fDeg2Rad;
	static const Real fRad2Deg;
	static const Real MAX_REAL;
	static const Real ZERO_TOLERANCE;

};

