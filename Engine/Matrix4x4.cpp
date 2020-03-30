#include "Matrix4x4.h"
#include "Numeric.h"

namespace Engine {
	const bool Matrix4x4::operator==(const Matrix4x4& i_rhs) const
	{
		for (int i = 0; i < 16; i++) {
			if (!Numeric::AreEqual(m._m[i], i_rhs.m._m[i]))
				return false;
		}
		return true;
	}
	const bool Matrix4x4::operator!=(const Matrix4x4& i_rhs) const
	{
		return !operator==(i_rhs);
	}
	Vector4 Matrix4x4::operator*(const Vector4& i_rhs) const
	{
		return Vector4(
			GetRow(0).DotProduct(i_rhs),
			GetRow(1).DotProduct(i_rhs),
			GetRow(2).DotProduct(i_rhs),
			GetRow(3).DotProduct(i_rhs)
		);
	}
	Matrix4x4 Matrix4x4::CreateScale(float i_x, float i_y, float i_z, float i_w)
	{
		return Matrix4x4(
			i_x, 0, 0, 0,
			0, i_y, 0, 0,
			0, 0, i_z, 0,
			0, 0, 0, i_w
		);
	}
	Matrix4x4 Matrix4x4::CreateXRotation(float i_theta)
	{
		float s = sin(i_theta);
		float c = cos(i_theta);
		return Matrix4x4(
			1,	0,	0,	0,
			0,	c,	-s,	0,
			0,	s,	c,	0,
			0,	0,	0,	1
		);
	}
	Matrix4x4 Matrix4x4::CreateYRotation(float i_theta)
	{
		float s = sin(i_theta);
		float c = cos(i_theta);
		return Matrix4x4(
			c,	0,	s,	0,
			0,	1,	0,	0,
			-s, 0,	c,	0,
			0,	0,	0,	1
		);
	}
	Matrix4x4 Matrix4x4::CreateZRotation(float i_theta)
	{
		float s = sin(i_theta);
		float c = cos(i_theta);
		return Matrix4x4(
			c,	-s,	0,	0,
			s,	c,	0,	0,
			0,	0,	1,	0,
			0,	0,	0,	1
		);
	}
	Matrix4x4 Matrix4x4::CreateRotation(const Vector4& i_axis, float i_theta)
	{
		float ax = i_axis.GetX();
		float ay = i_axis.GetY();
		float az = i_axis.GetZ();

		float ax2 = ax * ax;
		float ay2 = ay * ay;
		float az2 = az * az;

		float c = cos(i_theta);
		float s = sin(i_theta);

		return Matrix4x4(
			c+ax2*(1-c),		ax*ay*(1-c)-az*s,	ax*az*(1-c)+ay*s,	0,
			ay*ax*(1-c)+az*s,	c+ay2*(1-c),		ay*az*(1-c)-ax*s,	0,
			az*ax*(1-c)+ay*s,	az*ay*(1-c)+ax*s,	c+az2*(1-c),		0,
			0,					0,					0,					1
		);
	}
	Matrix4x4 Matrix4x4::CreateTranslation(float i_x, float i_y, float i_z)
	{
		return Matrix4x4(
			1, 0, 0, i_x,
			0, 1, 0, i_y,
			0, 0, 1, i_z,
			0, 0, 0, 1
		);
	}
	Matrix4x4 Matrix4x4::CreateTranslation(Vector3 i_v)
	{
		return Matrix4x4(
			1, 0, 0, i_v.GetX(),
			0, 1, 0, i_v.GetY(),
			0, 0, 1, i_v.GetZ(),
			0, 0, 0, 1
		);
	}
	Matrix4x4 Matrix4x4::CreateTranslation(Vector2 i_v)
	{
		return Matrix4x4(
			1, 0, 0, i_v.x,
			0, 1, 0, i_v.y,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}
	Matrix4x4 Matrix4x4::getInverse() const
	{
		float det = Matrix::GetDet4x4(m);
		assert(!Numeric::AreEqual(det, 0.0f));
		float m00 = GetDet3x3(ConvertTo3x3(m, 0, 0)) / det;
		float m01 = -GetDet3x3(ConvertTo3x3(m, 0, 1)) / det;
		float m02 = GetDet3x3(ConvertTo3x3(m, 0, 2)) / det;
		float m03 = -GetDet3x3(ConvertTo3x3(m, 0, 3)) / det;

		float m10 = -GetDet3x3(ConvertTo3x3(m, 1, 0)) / det;
		float m11 = GetDet3x3(ConvertTo3x3(m, 1, 1)) / det;
		float m12 = -GetDet3x3(ConvertTo3x3(m, 1, 2)) / det;
		float m13 = GetDet3x3(ConvertTo3x3(m, 1, 3)) / det;

		float m20 = GetDet3x3(ConvertTo3x3(m, 2, 0)) / det;
		float m21 = -GetDet3x3(ConvertTo3x3(m, 2, 1)) / det;
		float m22 = GetDet3x3(ConvertTo3x3(m, 2, 2)) / det;
		float m23 = -GetDet3x3(ConvertTo3x3(m, 2, 3)) / det;

		float m30 = -GetDet3x3(ConvertTo3x3(m, 3, 0)) / det;
		float m31 = GetDet3x3(ConvertTo3x3(m, 3, 1)) / det;
		float m32 = -GetDet3x3(ConvertTo3x3(m, 3, 2)) / det;
		float m33 = GetDet3x3(ConvertTo3x3(m, 3, 3)) / det;

		return Matrix4x4(
			m00,	m10,	m20,	m30,
			m01,	m11,	m21,	m31,
			m02,	m12,	m22,	m32,
			m03,	m13,	m23,	m33
		);
	}
	const Matrix4x4 Matrix4x4::Identity(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}