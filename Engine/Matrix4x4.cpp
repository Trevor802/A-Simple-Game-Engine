#include "Matrix4x4.h"
#include "Numeric.h"

namespace Engine {
	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& m2) const
	{
		return Matrix4x4(m * m2.m);
	}
	const bool Matrix4x4::operator==(const Matrix4x4& i_rhs) const
	{
		return m == i_rhs.m;
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
	M4 Matrix4x4::CreateTransformMatrix(const M3& m2)
	{
		M4 r;
		r.m[0][0] = m2.m[0][0]; r.m[0][1] = m2.m[0][1]; r.m[0][2] = m2.m[0][2]; r.m[0][3] = 0;
		r.m[1][0] = m2.m[1][0]; r.m[1][1] = m2.m[1][1]; r.m[1][2] = m2.m[1][2]; r.m[1][3] = 0;
		r.m[2][0] = m2.m[2][0]; r.m[2][1] = m2.m[2][1]; r.m[2][2] = m2.m[2][2]; r.m[2][3] = 0;
		r.m[3][0] = 0;			r.m[3][1] = 0;			r.m[3][2] = 0;			r.m[3][3] = 1;
		return r;
	}
	bool Matrix4x4::IsValid(const M4& m)
	{
		return !(
			Numeric::AreEqual(m.m[3][0], 0) && Numeric::AreEqual(m.m[3][1], 0) &&
			Numeric::AreEqual(m.m[3][2], 0) && Numeric::AreEqual(m.m[3][3], 1));
	}
	Matrix4x4 Matrix4x4::getInverse() const
	{
		float det = Matrix::GetDet(m);
		assert(!Numeric::AreEqual(det, 0.0f));
		if (IsValid(m)) {
			M3 t = ConvertToM3(Matrix::GetTranspose(m), 3, 3);
			M4 r = CreateTransformMatrix(t);
			Vector3 trans = Matrix::GetCol(m, 3).ToVector3();
			Vector3 transI = t * trans * -1;
			r.m[0][3] = transI.GetX();
			r.m[1][3] = transI.GetY();
			r.m[2][3] = transI.GetZ();
			return r;
		}

		return Matrix4x4(Matrix::GetInverse(m));
	}
}