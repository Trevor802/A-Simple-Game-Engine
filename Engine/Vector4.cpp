#include "Vector4.h"
#include "Numeric.h"
#include <assert.h>
#include <algorithm>

namespace Engine {
	Vector4::Vector4(void) : m_x(0), m_y(0), m_z(0) {}

	Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) : m_x(i_x), m_y(i_y), m_z(i_z), m_w(i_w) {}

	Vector4::Vector4(const Vector3& i_other, float i_w) : m_x(i_other.GetX()), m_y(i_other.GetY()), m_z(i_other.GetZ()), m_w(i_w) {}

	Vector4::Vector4(const Vector4& i_other) : m_x(i_other.m_x), m_y(i_other.m_y), m_z(i_other.m_z), m_w(i_other.m_w) {}

	Vector4& Vector4::operator=(const Vector4& i_other)
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;
		m_z = i_other.m_z;
		m_w = i_other.m_w;
		return *this;
	}

	Vector4::Vector4(Vector4&& i_other) noexcept
	{
		m_x = i_other.m_x;
		m_y = i_other.m_y;
		m_z = i_other.m_z;
		m_w = i_other.m_w;
		i_other.m_x = 0;
		i_other.m_y = 0;
		i_other.m_z = 0;
		i_other.m_w = 0;
	}

	Vector4& Vector4::operator=(Vector4&& i_other)
	{
		if (this != &i_other) {
			m_x = i_other.m_x;
			m_y = i_other.m_y;
			m_z = i_other.m_z;
			m_w = i_other.m_w;
			i_other.m_x = 0;
			i_other.m_y = 0;
			i_other.m_z = 0;
			i_other.m_w = 0;
		}
		return *this;
	}

	const bool Vector4::operator==(const Vector4& i_rhs) const
	{
		return	Numeric::AreEqual(m_x, i_rhs.m_x) &&
				Numeric::AreEqual(m_y, i_rhs.m_y) &&
				Numeric::AreEqual(m_z, i_rhs.m_z) &&
				Numeric::AreEqual(m_w, i_rhs.m_w);
	}

	const bool Vector4::operator!=(const Vector4& i_rhs) const
	{
		return !operator==(i_rhs);
	}

	Vector4& Vector4::operator+=(const Vector4& i_rhs)
	{
		m_x += i_rhs.m_x;
		m_y += i_rhs.m_y;
		m_z += i_rhs.m_z;
		m_w += i_rhs.m_w;
		return *this;
	}

	const Vector4 Vector4::operator+(const Vector4& i_rhs) const
	{
		Vector4 result = *this;
		result += i_rhs;
		return result;
	}

	Vector4& Vector4::operator-=(const Vector4& i_rhs)
	{
		m_x -= i_rhs.m_x;
		m_y -= i_rhs.m_y;
		m_z -= i_rhs.m_z;
		m_w -= i_rhs.m_w;
		return *this;
	}

	const Vector4 Vector4::operator-(const Vector4& i_rhs) const
	{
		Vector4 result = *this;
		result -= i_rhs;
		return result;
	}

	Vector4& Vector4::operator*=(const float i_scalar)
	{
		m_x *= i_scalar;
		m_y *= i_scalar;
		m_z *= i_scalar;
		m_w *= i_scalar;
		return *this;
	}

	const float Vector4::AngleBetween(const Vector4& i_lhs, const Vector4& i_rhs)
	{
		float dotResult = i_lhs.DotProduct(i_rhs);
		float lengthLHS = i_lhs.Magnitude();
		float lengthRHS = i_rhs.Magnitude();
		if (Numeric::AreEqual(lengthLHS, 0.0f) || Numeric::AreEqual(lengthRHS, 0.0f))
			return 0.0f;
		float quotient = Numeric::clamp(dotResult / (lengthLHS * lengthRHS), -1.0f, 1.0f);
		return acos(quotient);;
	}

	const float Vector4::DotProduct(const Vector4& i_rhs) const
	{
		return m_x * i_rhs.m_x + m_y * i_rhs.m_y + m_z * i_rhs.m_z + m_w * i_rhs.m_w;
	}

	const Vector4 Vector4::Normalized() const
	{
		float magnitude = Magnitude();
		assert(!Numeric::AreEqual(magnitude, 0.0f));
		return Vector4(	m_x / magnitude,
						m_y / magnitude,
						m_z / magnitude,
						m_w / magnitude);
	}

	const float Vector4::Magnitude() const
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	const Vector4 Vector4::ZERO_VECTOR(0, 0, 0, 0);

}