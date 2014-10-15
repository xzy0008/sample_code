

#include "stdafx.h"
#include "vector3d.h"
#include <math.h>

namespace VR_Ocean
{
	Vector3D::Vector3D(void) : m_X(0.0f), m_Y(0.0f), m_Z(0.0f)
	{
	}

	Vector3D::Vector3D(const float X, const float Y, const float Z)
	{
		Set(X, Y, Z);
	}

	Vector3D::~Vector3D(void)
	{
	}

	void Vector3D::Set(const float X, const float Y, const float Z)
	{
		m_X = X;
		m_Y = Y;
		m_Z = Z;
	}

	void Vector3D::SetX(const float X)
	{
		m_X = X;
	}

	void Vector3D::SetY(const float Y)
	{
		m_Y = Y;
	}

	void Vector3D::SetZ(const float Z)
	{
		m_Z = Z;
	}

	const float Vector3D::X(void) const
	{
		return m_X;
	}

	const float Vector3D::Y(void) const
	{
		return m_Y;
	}

	const float Vector3D::Z(void) const
	{
		return m_Z;
	}

	Vector3D Vector3D::operator-(const Vector3D& otherVector)
	{
		Vector3D retVector;
		retVector.Set(this->m_X - otherVector.m_X, this->m_Y - otherVector.m_Y, this->m_Z - otherVector.m_Z);
		return retVector;
	}

	Vector3D Vector3D::operator+(const Vector3D& otherVector)
	{
		Vector3D retVector;
		retVector.Set(this->m_X + otherVector.m_X, this->m_Y + otherVector.m_Y, this->m_Z + otherVector.m_Z);
		return retVector;
	}

	Vector3D Vector3D::operator+(const float scalar)
	{
		Vector3D retVector;
		retVector.Set(this->m_X + scalar, this->m_Y + scalar, this->m_Z + scalar);
		return retVector;
	}

	Vector3D Vector3D::operator*(const Vector3D& otherVector)
	{
		Vector3D retVector;
		retVector.Set(this->m_X * otherVector.m_X, this->m_Y * otherVector.m_Y, this->m_Z * otherVector.m_Z);
		return retVector;
	}

	Vector3D Vector3D::operator*(const float scalar)
	{
		Vector3D retVector;
		retVector.Set(this->m_X * scalar, this->m_Y * scalar, this->m_Z * scalar);
		return retVector;
	}

	Vector3D& Vector3D::operator+=(const Vector3D& otherVector)
	{
		this->m_X += otherVector.m_X;
		this->m_Y += otherVector.m_Y;
		this->m_Z += otherVector.m_Z;

		return *this;
	}

	Vector3D Vector3D::Cross(Vector3D otherVector)
	{
		return Vector3D(this->m_Y*otherVector.Z() - this->m_Z*otherVector.Y(),
			this->m_Z*otherVector.X() - this->m_X*otherVector.Z(),
			this->m_X*otherVector.Y() - this->m_Y*otherVector.X());
	}

	void Vector3D::Normalise(void)
	{
		float vectorLength = (float)sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);

		if (vectorLength == 0)
			vectorLength = 1.0f;

		m_X /= vectorLength;
		m_Y /= vectorLength;
		m_Z /= vectorLength;
	}
}
