#pragma once
#include <iostream>
#include "Vector3.h"
namespace Engine {
	class Vector4
	{
	public:
		Vector4(void);
		Vector4(float i_x, float i_y, float i_z, float i_w);
		Vector4(const Vector3& i_other);
		Vector4(const Vector4& i_other);
		Vector4& operator=(const Vector4& i_other);
		Vector4(Vector4&& i_other) noexcept;
		Vector4& operator=(Vector4&& i_other);

		~Vector4() {};
		const bool operator==(const Vector4& i_rhs) const;
		const bool operator!=(const Vector4& i_rhs) const;

		Vector4& operator+=(const Vector4& i_rhs);
		const Vector4 operator+(const Vector4& i_rhs) const;
		Vector4& operator-=(const Vector4& i_rhs);
		const Vector4 operator-(const Vector4& i_rhs) const;
		Vector4& operator*=(const float i_scalar);

		friend Vector4 operator*(const Vector4& i_vec, const float i_scalar);
		friend Vector4 operator*(const float i_scalar, const Vector4& i_vec);
		friend Vector4 operator-(const Vector4& i_vec);

		static const Vector4 ZERO_VECTOR;
		static const float AngleBetween(const Vector4& i_lhs, const Vector4& i_rhs);

		const float DotProduct(const Vector4& i_rhs) const;
		const Vector4 Normalized() const;
		const float Magnitude() const;

		inline const float GetX(void) const { return m_x; }
		inline const float GetY(void) const { return m_y; }
		inline const float GetZ(void) const { return m_z; }
		inline const float GetW(void) const { return m_w; }

		inline void SetX(float i_x) { m_x = i_x; }
		inline void SetY(float i_y) { m_y = i_y; }
		inline void SetZ(float i_z) { m_z = i_z; }
		inline void SetW(float i_w) { m_w = i_w; }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector4& i_vec) {
			os << "(" << i_vec.m_x << "," << i_vec.m_y << "," << i_vec.m_z << "," << i_vec.m_w << ")";
			return os;
		}


	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};

	inline Vector4 operator*(const Vector4& i_vec, const float i_scalar) {
		return Vector4(i_vec.m_x * i_scalar, i_vec.m_y * i_scalar, i_vec.m_z * i_scalar, i_vec.m_w * i_scalar);
	}

	inline Vector4 operator*(const float i_scalar, const Vector4& i_vec) {
		return operator*(i_vec, i_scalar);
	}

	inline Vector4 operator-(const Vector4& i_vec) {
		return Vector4(-i_vec.m_x, -i_vec.m_y, -i_vec.m_z, -i_vec.m_w);
	}
}
