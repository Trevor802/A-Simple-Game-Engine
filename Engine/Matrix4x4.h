#pragma once
#include <iostream>
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.hpp"
namespace Engine {
	namespace Matrix {
		static union M4
		{
			float m[4][4];
			float _m[16];
		};
		static union M3
		{
			float m[3][3];
			float _m[9];
		};
		static union M2
		{
			float m[2][2];
			float _m[4];
		};
		static float GetDet2x2(const M2& m) {
			return m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
		}
		static M2 ConvertTo2x2(const M3& i_m, int row, int col) {
			M2 m;
			int rowShift = 0;
			for (int i = 0; i < 3; i++) {
				if (i == row) {
					rowShift = 1;
					continue;
				};
				int colShift = 0;
				for (int j = 0; j < 3; j++) {
					if (j == col) {
						colShift = 1;
						continue;
					}
					m.m[i-rowShift][j-colShift] = i_m.m[i][j];
				}
			}
			return m;
		}
		static float GetDet3x3(const M3& i_m) {
			M2 m00 = ConvertTo2x2(i_m, 0, 0);
			M2 m01 = ConvertTo2x2(i_m, 0, 1);
			M2 m02 = ConvertTo2x2(i_m, 0, 2);
			return
				i_m.m[0][0] * GetDet2x2(m00) -
				i_m.m[0][1] * GetDet2x2(m01) +
				i_m.m[0][2] * GetDet2x2(m02);
		}
		static M3 ConvertTo3x3(const M4& i_m, int row, int col) {
			M3 m;
			int rowShift = 0;
			for (int i = 0; i < 4; i++) {
				if (i == row) {
					rowShift = 1;
					continue;
				};
				int colShift = 0;
				for (int j = 0; j < 4; j++) {
					if (j == col) {
						colShift = 1;
						continue;
					}
					m.m[i - rowShift][j - colShift] = i_m.m[i][j];
				}
			}
			return m;
		}
		static float GetDet4x4(const M4& i_m) {
			M3 m00 = ConvertTo3x3(i_m, 0, 0);
			M3 m01 = ConvertTo3x3(i_m, 0, 1);
			M3 m02 = ConvertTo3x3(i_m, 0, 2);
			M3 m03 = ConvertTo3x3(i_m, 0, 3);
			return
				i_m.m[0][0] * GetDet3x3(m00) -
				i_m.m[0][1] * GetDet3x3(m01) +
				i_m.m[0][2] * GetDet3x3(m02) -
				i_m.m[0][3] * GetDet3x3(m03);
		}
	}
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
		inline Matrix4x4 operator*(const Matrix4x4& m2) const {
			Matrix4x4 r;
			r.m.m[0][0] = m.m[0][0] * m2.m.m[0][0] + m.m[0][1] * m2.m.m[1][0] + m.m[0][2] * m2.m.m[2][0] + m.m[0][3] * m2.m.m[3][0];
			r.m.m[0][1] = m.m[0][0] * m2.m.m[0][1] + m.m[0][1] * m2.m.m[1][1] + m.m[0][2] * m2.m.m[2][1] + m.m[0][3] * m2.m.m[3][1];
			r.m.m[0][2] = m.m[0][0] * m2.m.m[0][2] + m.m[0][1] * m2.m.m[1][2] + m.m[0][2] * m2.m.m[2][2] + m.m[0][3] * m2.m.m[3][2];
			r.m.m[0][3] = m.m[0][0] * m2.m.m[0][3] + m.m[0][1] * m2.m.m[1][3] + m.m[0][2] * m2.m.m[2][3] + m.m[0][3] * m2.m.m[3][3];

			r.m.m[1][0] = m.m[1][0] * m2.m.m[0][0] + m.m[1][1] * m2.m.m[1][0] + m.m[1][2] * m2.m.m[2][0] + m.m[1][3] * m2.m.m[3][0];
			r.m.m[1][1] = m.m[1][0] * m2.m.m[0][1] + m.m[1][1] * m2.m.m[1][1] + m.m[1][2] * m2.m.m[2][1] + m.m[1][3] * m2.m.m[3][1];
			r.m.m[1][2] = m.m[1][0] * m2.m.m[0][2] + m.m[1][1] * m2.m.m[1][2] + m.m[1][2] * m2.m.m[2][2] + m.m[1][3] * m2.m.m[3][2];
			r.m.m[1][3] = m.m[1][0] * m2.m.m[0][3] + m.m[1][1] * m2.m.m[1][3] + m.m[1][2] * m2.m.m[2][3] + m.m[1][3] * m2.m.m[3][3];

			r.m.m[2][0] = m.m[2][0] * m2.m.m[0][0] + m.m[2][1] * m2.m.m[1][0] + m.m[2][2] * m2.m.m[2][0] + m.m[2][3] * m2.m.m[3][0];
			r.m.m[2][1] = m.m[2][0] * m2.m.m[0][1] + m.m[2][1] * m2.m.m[1][1] + m.m[2][2] * m2.m.m[2][1] + m.m[2][3] * m2.m.m[3][1];
			r.m.m[2][2] = m.m[2][0] * m2.m.m[0][2] + m.m[2][1] * m2.m.m[1][2] + m.m[2][2] * m2.m.m[2][2] + m.m[2][3] * m2.m.m[3][2];
			r.m.m[2][3] = m.m[2][0] * m2.m.m[0][3] + m.m[2][1] * m2.m.m[1][3] + m.m[2][2] * m2.m.m[2][3] + m.m[2][3] * m2.m.m[3][3];

			r.m.m[3][0] = m.m[3][0] * m2.m.m[0][0] + m.m[3][1] * m2.m.m[1][0] + m.m[3][2] * m2.m.m[2][0] + m.m[3][3] * m2.m.m[3][0];
			r.m.m[3][1] = m.m[3][0] * m2.m.m[0][1] + m.m[3][1] * m2.m.m[1][1] + m.m[3][2] * m2.m.m[2][1] + m.m[3][3] * m2.m.m[3][1];
			r.m.m[3][2] = m.m[3][0] * m2.m.m[0][2] + m.m[3][1] * m2.m.m[1][2] + m.m[3][2] * m2.m.m[2][2] + m.m[3][3] * m2.m.m[3][2];
			r.m.m[3][3] = m.m[3][0] * m2.m.m[0][3] + m.m[3][1] * m2.m.m[1][3] + m.m[3][2] * m2.m.m[2][3] + m.m[3][3] * m2.m.m[3][3];

			return r;
		}
		~Matrix4x4() {}
		const bool operator==(const Matrix4x4& i_rhs) const;
		const bool operator!=(const Matrix4x4& i_rhs) const;
		Vector4 operator*(const Vector4& i_rhs) const;

		friend Matrix4x4 operator*(const Matrix4x4& i_matrix, const float i_scalar);
		friend Matrix4x4 operator*(const float i_scalar, const Matrix4x4& i_matrix);
		//friend Vector4 operator* (const Matrix4x4& i_matrix, const Vector4& i_point);

		static const Matrix4x4 Identity;
		static Matrix4x4 CreateScale(float i_x, float i_y, float i_z, float i_w = 1.0f);
		static Matrix4x4 CreateXRotation(float i_theta);
		static Matrix4x4 CreateYRotation(float i_theta);
		static Matrix4x4 CreateZRotation(float i_theta);
		static Matrix4x4 CreateRotation(const Vector4& i_axis, float i_theta);
		static Matrix4x4 CreateTranslation(float i_x, float i_y, float i_z);
		static Matrix4x4 CreateTranslation(Vector3 i_v);
		static Matrix4x4 CreateTranslation(Vector2 i_v);
		inline Matrix4x4 getTranspose() const {
			Matrix4x4 r;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					r.m._m[i * 4 + j] = m._m[j * 4 + i];
				}
			}
			return r;
		}

		Matrix4x4 getInverse() const;

		inline const Vector4 GetRow(int i_row) const {
			return Vector4(m.m[i_row][0], m.m[i_row][1], m.m[i_row][2], m.m[i_row][3]);
		}

		inline const Vector4 GetCol(int i_col) const {
			return Vector4(m.m[0][i_col], m.m[1][i_col], m.m[2][i_col], m.m[3][i_col]);
		}

		friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& i_other);

	};

	inline Matrix4x4 operator*(const Matrix4x4& i_matrix, const float i_scalar)
	{
		Matrix4x4 r;
		for (int i = 0; i < 16; i++) {
			r.m._m[i] = i_matrix.m._m[i] * i_scalar;
		}
		return r;
	}

	inline Matrix4x4 operator*(const float i_scalar, const Matrix4x4& i_matrix)
	{
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


