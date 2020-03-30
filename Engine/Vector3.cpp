#include "Vector3.h"
#include "Numeric.h"
#include <assert.h>
#include <algorithm>

namespace Engine {
	Vector3::Vector3(void) : m_x(0), m_y(0), m_z(0) {}

	Vector3::Vector3(float i_x, float i_y, float i_z) : m_x(i_x), m_y(i_y), m_z(i_z) {}

	Vector3::Vector3(const Vector2& i_v, float z) : m_x(i_v.x), m_y(i_v.y), m_z(z) {}

	Vector3::Vector3(const Vector3& i_other) : m_x(i_other.m_x), m_y(i_other.m_y), m_z(i_other.m_z) {}

	Vector3& Vector3::operator=(const Vector3& i_other)
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;
		m_z = i_other.m_z;
		return *this;
	}

	Vector3::Vector3(Vector3&& i_other) noexcept
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;
		m_z = i_other.m_z;
		i_other.m_x = 0;
		i_other.m_y = 0;
		i_other.m_z = 0;
	}

	Vector3& Vector3::operator=(Vector3&& i_other)
	{
		if (this != &i_other) {
			m_x = i_other.m_x;
			m_y = i_other.m_y;
			m_z = i_other.m_z;
			i_other.m_x = 0;
			i_other.m_y = 0;
			i_other.m_z = 0;
		}
		return *this;
	}

	const bool Vector3::operator==(const Vector3& i_rhs) const
	{
		return	Numeric::AreEqual(m_x, i_rhs.m_x) &&
				Numeric::AreEqual(m_y, i_rhs.m_y) &&
				Numeric::AreEqual(m_z, i_rhs.m_z);
	}

	const bool Vector3::operator!=(const Vector3& i_rhs) const
	{
		return !operator==(i_rhs);
	}

	Vector3& Vector3::operator+=(const Vector3& i_rhs)
	{
		m_x += i_rhs.m_x;
		m_y += i_rhs.m_y;
		m_z += i_rhs.m_z;
		return *this;
	}

	const Vector3 Vector3::operator+(const Vector3& i_rhs) const
	{
		Vector3 result = *this;
		result += i_rhs;
		return result;
	}

	Vector3& Vector3::operator-=(const Vector3& i_rhs)
	{
		m_x -= i_rhs.m_x;
		m_y -= i_rhs.m_y;
		m_z -= i_rhs.m_z;
		return *this;
	}

	const Vector3 Vector3::operator-(const Vector3& i_rhs) const
	{
		Vector3 result = *this;
		result -= i_rhs;
		return result;
	}

	Vector3& Vector3::operator*=(const float i_scalar)
	{
		m_x *= i_scalar;
		m_y *= i_scalar;
		m_z *= i_scalar;
		return *this;
	}

	const float Vector3::AngleBetween(const Vector3& i_lhs, const Vector3& i_rhs)
	{
		float dotResult = i_lhs.DotProduct(i_rhs);
		float lengthLHS = i_lhs.Magnitude();
		float lengthRHS = i_rhs.Magnitude();
		if (Numeric::AreEqual(lengthLHS, 0.0f) || Numeric::AreEqual(lengthRHS, 0.0f))
			return 0.0f;
		float quotient = Numeric::clamp(dotResult / (lengthLHS * lengthRHS), -1.0f, 1.0f);
		return acos(quotient);;
	}

	const float Vector3::DotProduct(const Vector3& i_rhs) const
	{
		return m_x * i_rhs.m_x + m_y * i_rhs.m_y + m_z * i_rhs.m_z;
	}

	const Vector3 Vector3::CrossProduct(const Vector3& i_rhs) const
	{
		return Vector3(	(m_y * i_rhs.m_z - m_z * i_rhs.m_y),
						(m_z * i_rhs.m_x - m_x * i_rhs.m_z),
						(m_x * i_rhs.m_y - m_y * i_rhs.m_x));
	}

	const Vector3 Vector3::Normalized() const
	{
		float magnitude = Magnitude();
		assert(!Numeric::AreEqual(magnitude, 0.0f));
		return Vector3(	m_x / magnitude,
						m_y / magnitude,
						m_z / magnitude);
	}

	const float Vector3::Magnitude() const
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	const Vector3 Vector3::ZERO_VECTOR(0, 0, 0);

}