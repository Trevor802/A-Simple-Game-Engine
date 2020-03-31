#pragma once
#include <assert.h>
#include "Numeric.h"
#include "Vector2.hpp"
#include "Vector3.h"
#include "Vector4.h"
namespace Engine {
	namespace Matrix {
		union M4
		{
			float m[4][4];
			float _m[16];
		};
		union M3
		{
			float m[3][3];
			float _m[9];
		};
		union M2
		{
			float m[2][2];
			float _m[4];
		};
		static M2 Identity2 = {
			1, 0,
			0, 1
		};
		static M3 Identity3 = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
		static M4 Identity4 = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
		static M2 ConvertToM2(const M3& i_m, int row, int col) {
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
					m.m[i - rowShift][j - colShift] = i_m.m[i][j];
				}
			}
			return m;
		}
		static M3 ConvertToM3(const M4& i_m, int row, int col) {
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
		static float GetDet(const M2& m) {
			return m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
		}
		static float GetDet(const M3& i_m) {
			M2 m00 = ConvertToM2(i_m, 0, 0);
			M2 m01 = ConvertToM2(i_m, 0, 1);
			M2 m02 = ConvertToM2(i_m, 0, 2);
			return
				i_m.m[0][0] * GetDet(m00) -
				i_m.m[0][1] * GetDet(m01) +
				i_m.m[0][2] * GetDet(m02);
		}
		static float GetDet(const M4& i_m) {
			M3 m00 = ConvertToM3(i_m, 0, 0);
			M3 m01 = ConvertToM3(i_m, 0, 1);
			M3 m02 = ConvertToM3(i_m, 0, 2);
			M3 m03 = ConvertToM3(i_m, 0, 3);
			return
				i_m.m[0][0] * GetDet(m00) -
				i_m.m[0][1] * GetDet(m01) +
				i_m.m[0][2] * GetDet(m02) -
				i_m.m[0][3] * GetDet(m03);
		}
		static M2 GetTranspose(const M2& i_m) {
			M2 r;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					r._m[i * 2 + j] = i_m._m[j * 2 + i];
				}
			}
			return r;
		}
		static M3 GetTranspose(const M3& i_m) {
			M3 r;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					r._m[i * 3 + j] = i_m._m[j * 3 + i];
				}
			}
			return r;
		}
		static M4 GetTranspose(const M4& i_m) {
			M4 r;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					r._m[i * 4 + j] = i_m._m[j * 4 + i];
				}
			}
			return r;
		}
		static M2 GetInverse(const M2& m) {
			float det = GetDet(m);
			assert(!Numeric::AreEqual(det, 0.0f));
			M2 r;
			r.m[0][0] = m.m[1][1] / det;
			r.m[1][0] = -m.m[1][0] / det;

			r.m[0][1] = -m.m[0][1] / det;
			r.m[1][1] = m.m[0][0] / det;

			return r;
		}
		static M3 GetInverse(const M3& m) {
			float det = GetDet(m);
			assert(!Numeric::AreEqual(det, 0.0f));
			M3 r;
			r.m[0][0] = GetDet(ConvertToM2(m, 0, 0)) / det;
			r.m[1][0] = -GetDet(ConvertToM2(m, 0, 1)) / det;
			r.m[2][0] = GetDet(ConvertToM2(m, 0, 2)) / det;

			r.m[0][1] = -GetDet(ConvertToM2(m, 1, 0)) / det;
			r.m[1][1] = GetDet(ConvertToM2(m, 1, 1)) / det;
			r.m[2][1] = -GetDet(ConvertToM2(m, 1, 2)) / det;

			r.m[0][2] = GetDet(ConvertToM2(m, 2, 0)) / det;
			r.m[1][2] = -GetDet(ConvertToM2(m, 2, 1)) / det;
			r.m[2][2] = GetDet(ConvertToM2(m, 2, 2)) / det;

			return r;
		}
		static M4 GetInverse(const M4& m) {
			float det = GetDet(m);
			assert(!Numeric::AreEqual(det, 0.0f));
			M4 r;
			r.m[0][0] = GetDet(ConvertToM3(m, 0, 0)) / det;
			r.m[1][0] = -GetDet(ConvertToM3(m, 0, 1)) / det;
			r.m[2][0] = GetDet(ConvertToM3(m, 0, 2)) / det;
			r.m[3][0] = -GetDet(ConvertToM3(m, 0, 3)) / det;

			r.m[0][1] = -GetDet(ConvertToM3(m, 1, 0)) / det;
			r.m[1][1] = GetDet(ConvertToM3(m, 1, 1)) / det;
			r.m[2][1] = -GetDet(ConvertToM3(m, 1, 2)) / det;
			r.m[3][1] = GetDet(ConvertToM3(m, 1, 3)) / det;

			r.m[0][2] = GetDet(ConvertToM3(m, 2, 0)) / det;
			r.m[1][2] = -GetDet(ConvertToM3(m, 2, 1)) / det;
			r.m[2][2] = GetDet(ConvertToM3(m, 2, 2)) / det;
			r.m[3][2] = -GetDet(ConvertToM3(m, 2, 3)) / det;

			r.m[0][3] = -GetDet(ConvertToM3(m, 3, 0)) / det;
			r.m[1][3] = GetDet(ConvertToM3(m, 3, 1)) / det;
			r.m[2][3] = -GetDet(ConvertToM3(m, 3, 2)) / det;
			r.m[3][3] = GetDet(ConvertToM3(m, 3, 3)) / det;

			return r;
		}
		static M2 operator*(const M2& m1, const M2& m2) {
			M2 r;
			r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0];
			r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1];

			r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0];
			r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1];
			return r;
		}
		static M2 operator*(const M2& m, const float s) {
			M2 r;
			for (int i = 0; i < 4; i++) {
				r._m[i] = m._m[i] * s;
			}
			return r;
		}
		static M2 operator*(const float s, const M2& m) {
			return operator*(m, s);
		}
		static M3 operator*(const M3& m1, const M3& m2) {
			M3 r;
			r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0];
			r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1];
			r.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2];

			r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0];
			r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1];
			r.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2];

			r.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0];
			r.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1];
			r.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2];
			return r;
		}
		static M3 operator*(const M3& m, const float s) {
			M3 r;
			for (int i = 0; i < 9; i++) {
				r._m[i] = m._m[i] * s;
			}
			return r;
		}
		static M3 operator*(const float s, const M3& m) {
			return operator*(m, s);
		}
		static M4 operator*(const M4& m1, const M4& m2) {
			M4 r;
			r.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
			r.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
			r.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
			r.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

			r.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
			r.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
			r.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
			r.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

			r.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
			r.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
			r.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
			r.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

			r.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
			r.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
			r.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
			r.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];
			return r;
		}
		static M4 operator*(const M4& m, const float s) {
			M4 r;
			for (int i = 0; i < 16; i++) {
				r._m[i] = m._m[i] * s;
			}
			return r;
		}
		static M4 operator*(const float s, const M4& m) {
			return operator*(m, s);
		}
		static Vector2 GetRow(const M2& m, int row) {
			assert(row >= 0 && row < 2);
			return Vector2(m.m[row][0], m.m[row][1]);
		}
		static Vector2 GetCol(const M2& m, int col) {
			assert(col >= 0 && col < 2);
			return Vector2(m.m[0][col], m.m[1][col]);
		}
		static Vector3 GetRow(const M3& m, int row) {
			assert(row >= 0 && row < 3);
			return Vector3(m.m[row][0], m.m[row][1], m.m[row][2]);
		}
		static Vector3 GetCol(const M3& m, int col) {
			assert(col >= 0 && col < 3);
			return Vector3(m.m[0][col], m.m[1][col], m.m[2][col]);
		}
		static Vector4 GetRow(const M4& m, int row) {
			assert(row >= 0 && row < 4);
			return Vector4(m.m[row][0], m.m[row][1], m.m[row][2], m.m[row][3]);
		}
		static Vector4 GetCol(const M4& m, int col) {
			assert(col >= 0 && col < 4);
			return Vector4(m.m[0][col], m.m[1][col], m.m[2][col], m.m[3][col]);
		}
		static Vector2 operator*(const M2& m, const Vector2& v) {
			return Vector2(
				GetRow(m, 0).DotProduct(v),
				GetRow(m, 1).DotProduct(v)
				);
		}
		static Vector3 operator*(const M3& m, const Vector3& v) {
			return Vector3(
				GetRow(m, 0).DotProduct(v),
				GetRow(m, 1).DotProduct(v),
				GetRow(m, 2).DotProduct(v)
				);
		}
		static Vector4 operator*(const M4& m, const Vector4& v) {
			return Vector4(
				GetRow(m, 0).DotProduct(v),
				GetRow(m, 1).DotProduct(v),
				GetRow(m, 2).DotProduct(v),
				GetRow(m, 3).DotProduct(v)
				);
		}
		static bool operator==(const M2& m1, const M2& m2) {
			for (int i = 0; i < 4; i++) {
				if (!Numeric::AreEqual(m1._m[i], m2._m[i]))
					return false;
			}
			return true;
		}
		static bool operator!=(const M2& m1, const M2& m2){
			return !operator!=(m1, m2);
		}
		static bool operator==(const M3& m1, const M3& m2) {
			for (int i = 0; i < 9; i++) {
				if (!Numeric::AreEqual(m1._m[i], m2._m[i]))
					return false;
			}
			return true;
		}
		static bool operator!=(const M3& m1, const M3& m2) {
			return !operator!=(m1, m2);
		}
		static bool operator==(const M4& m1, const M4& m2) {
			for (int i = 0; i < 16; i++) {
				if (!Numeric::AreEqual(m1._m[i], m2._m[i]))
					return false;
			}
			return true;
		}
		static bool operator!=(const M4& m1, const M4& m2) {
			return !operator!=(m1, m2);
		}
	}
}

