#include "VOdefinition.h"
#pragma once

// 3D vector class
namespace VR_Ocean
{
	class VO_EXPORT  Vector3D
	{
	public:
	   Vector3D(void);
	   Vector3D(const float X, const float Y, const float Z);
	   virtual ~Vector3D(void);

	   void Set(const float X, const float Y, const float Z);
	   void SetX(const float X);
	   void SetY(const float Y);
	   void SetZ(const float Z);

	   const float X(void) const;
	   const float Y(void) const;
	   const float Z(void) const;

	   Vector3D operator-(const Vector3D& otherVector);
	   Vector3D operator+(const Vector3D& otherVector);
	   Vector3D operator+(const float scalar);
	   Vector3D operator*(const Vector3D& otherVector);
	   Vector3D operator*(const float scalar);
	   Vector3D& operator+=(const Vector3D& otherVector);
	   Vector3D Cross(Vector3D otherVector);
	   void Normalise(void);
	private:

	public://livenson change
	   float m_X;
	   float m_Y;
	   float m_Z;
	};
}
