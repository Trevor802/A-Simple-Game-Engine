#pragma once
#include <iostream>
#include "Matrix.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.hpp"
namespace Engine {
	using namespace Matrix;
	class Matrix4x4
	{
	protected:
		M4 m;
	public:
		Matrix4x4() {}
		inline Matrix4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) {
			m.m[0][0] = m00; m.m[0][1] = m01; m.m[0][2] = m02; m.m[0][3] = m03;
			m.m[1][0] = m10; m.m[1][1] = m11; m.m[1][2] = m12; m.m[1][3] = m13;
			m.m[2][0] = m20; m.m[2][1] = m21; m.m[2][2] = m22; m.m[2][3] = m23;
			m.m[3][0] = m30; m.m[3][1] = m31; m.m[3][2] = m32; m.m[3][3] = m33;
		}
		inline Matrix4x4(
			const Vector4& i_col0,
			const Vector4& i_col1,
			const Vector4& i_col2,
			const Vector4& i_col3
		) {
			m.m[0][0] = i_col0.GetX(); m.m[0][1] = i_col1.GetX(); m.m[0][2] = i_col2.GetX(); m.m[0][3] = i_col3.GetX();
			m.m[1][0] = i_col0.GetY(); m.m[1][1] = i_col1.GetY(); m.m[1][2] = i_col2.GetY(); m.m[1][3] = i_col3.GetY();
			m.m[2][0] = i_col0.GetZ(); m.m[2][1] = i_col1.GetZ(); m.m[2][2] = i_col2.GetZ(); m.m[2][3] = i_col3.GetZ();
			m.m[3][0] = i_col0.GetW(); m.m[3][1] = i_col1.GetW(); m.m[3][2] = i_col2.GetW(); m.m[3][3] = i_col3.GetW();
		}
		Matrix4x4 operator*(const Matrix4x4& m2) const;
		inline Matrix4x4(const M4& i_m) : m(i_m) {}
		~Matrix4x4() {}
		const bool operator==(const Matrix4x4& i_rhs) const;
		const bool operator!=(const Matrix4x4& i_rhs) const;
		Vector4 operator*(const Vector4& i_rhs) const;
		friend Matrix4x4 operator*(const Matrix4x4& i_matrix, const float i_scalar);
		friend Matrix4x4 operator*(const float i_scalar, const Matrix4x4& i_matrix);

		static Matrix4x4 CreateScale(float i_x, float i_y, float i_z, float i_w = 1.0f);
		static Matrix4x4 CreateXRotation(float i_theta);
		static Matrix4x4 CreateYRotation(float i_theta);
		static Matrix4x4 CreateZRotation(float i_theta);
		static Matrix4x4 CreateRotation(const Vector4& i_axis, float i_theta);
		static Matrix4x4 CreateTranslation(float i_x, float i_y, float i_z);
		static Matrix4x4 CreateTranslation(Vector3 i_v);
		static Matrix4x4 CreateTranslation(Vector2 i_v);
		static M4 CreateTransformMatrix(const M3& i_m);
		static bool IsValid(const M4& i_m);

		Matrix4x4 getInverse() const;

		inline const Vector4 GetRow(int i_row) const {
			return Vector4(m.m[i_row][0], m.m[i_row][1], m.m[i_row][2], m.m[i_row][3]);
		}

		inline const Vector4 GetCol(int i_col) const {
			return Vector4(m.m[0][i_col], m.m[1][i_col], m.m[2][i_col], m.m[3][i_col]);
		}

		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& i_other);

	};

	inline Matrix4x4 operator*(const Matrix4x4& i_matrix, const float i_scalar){
		return Matrix4x4(i_matrix.m * i_scalar);
	}
	inline Matrix4x4 operator*(const float i_scalar, const Matrix4x4& i_matrix){
		return operator*(i_matrix, i_scalar);
	}
	/*
	inline Vector4 operator*(const Matrix4x4& m, const Vector4& v) {
		return Vector4(
			m.m[0][0] * v.GetX() + m.m[0][1] * v.GetY() + m.m[0][2] * v.GetZ() + m.m[0][3] * v.GetW(),
			m.m[1][0] * v.GetX() + m.m[1][1] * v.GetY() + m.m[1][2] * v.GetZ() + m.m[1][3] * v.GetW(),
			m.m[2][0] * v.GetX() + m.m[2][1] * v.GetY() + m.m[2][2] * v.GetZ() + m.m[2][3] * v.GetW(),
			m.m[3][0] * v.GetX() + m.m[3][1] * v.GetY() + m.m[3][2] * v.GetZ() + m.m[3][3] * v.GetW()
		);
	}
	*/

	inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& i_other) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				os << i_other.m.m[i][j] << "\t";
			}
			os << std::endl;
		}
		return os;
	}

}


