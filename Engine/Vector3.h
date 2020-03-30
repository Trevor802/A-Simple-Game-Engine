#pragma once
#include <iostream>
#include "Vector2.hpp"
namespace Engine {
	class Vector3
	{
	public:
		Vector3(void);
		Vector3(float i_x, float i_y, float i_z);
		Vector3(const Vector2& i_v, float z = 0.0f);
		Vector3(const Vector3& i_other);
		Vector3& operator=(const Vector3& i_other);
		Vector3(Vector3&& i_other) noexcept;
		Vector3& operator=(Vector3&& i_other);

		~Vector3() {};
		const bool operator==(const Vector3& i_rhs) const;
		const bool operator!=(const Vector3& i_rhs) const;

		Vector3& operator+=(const Vector3& i_rhs);
		const Vector3 operator+(const Vector3& i_rhs) const;
		Vector3& operator-=(const Vector3& i_rhs);
		const Vector3 operator-(const Vector3& i_rhs) const;
		Vector3& operator*=(const float i_scalar);

		friend Vector3 operator*(const Vector3& i_vec, const float i_scalar);
		friend Vector3 operator*(const float i_scalar, const Vector3& i_vec);
		friend Vector3 operator-(const Vector3& i_vec);

		static const Vector3 ZERO_VECTOR;
		static const float AngleBetween(const Vector3& i_lhs, const Vector3& i_rhs);
		
		const float DotProduct(const Vector3& i_rhs) const;
		const Vector3 CrossProduct(const Vector3& i_rhs) const;
		const Vector3 Normalized() const;
		const float Magnitude() const;

		inline const float GetX(void) const { return m_x; }
		inline const float GetY(void) const { return m_y; }
		inline const float GetZ(void) const { return m_z; }

		inline void SetX(float i_x) { m_x = i_x; }
		inline void SetY(float i_y) { m_y = i_y; }
		inline void SetZ(float i_z) { m_z = i_z; }

		inline friend std::ostream& operator<<(std::ostream& os, const Vector3& i_vec) {
			os << "(" << i_vec.m_x << "," << i_vec.m_y << "," << i_vec.m_z << ")";
			return os;
		}


	private:
		float m_x;
		float m_y;
		float m_z;
	};

	inline Vector3 operator*(const Vector3& i_vec, const float i_scalar) {
		return Vector3(i_vec.m_x * i_scalar, i_vec.m_y * i_scalar, i_vec.m_z * i_scalar);
	}

	inline Vector3 operator*(const float i_scalar, const Vector3& i_vec) {
		return Vector3(i_vec.m_x * i_scalar, i_vec.m_y * i_scalar, i_vec.m_z * i_scalar);
	}

	inline Vector3 operator-(const Vector3& i_vec) {
		return Vector3(-i_vec.m_x, -i_vec.m_y, -i_vec.m_z);
	}
}