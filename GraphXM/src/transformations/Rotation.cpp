#include "Rotation.h"
#include "Translation.h"

#include "../vectors/Vector2.h"
#include "../vectors/Vector3.h"

#include "../matrices/Matrix4.h"

#include "../MathUtil.h"

namespace gm
{
	Rotation::Rotation(float Value)
		:Matrix4(),
		m_Angles(Vector3(Value))
	{
		M[0][0] =  (float)MathUtil::Cos(Value);
		M[0][1] = -(float)MathUtil::Sin(Value);
		M[1][0] =  (float)MathUtil::Sin(Value);
		M[1][1] =  (float)MathUtil::Cos(Value);
	}

	Rotation::Rotation(const Vector3& Angles)
		: Matrix4(),
		m_Angles(Angles)
	{
		Matrix4 resultX;
		Matrix4 resultY;
		Matrix4 resultZ;

		// Rotating about x - axis
		resultX[1][1] =  (float)MathUtil::Cos(Angles.x);
		resultX[2][2] =  (float)MathUtil::Cos(Angles.x);
		resultX[1][2] = -(float)MathUtil::Sin(Angles.x);
		resultX[2][1] =  (float)MathUtil::Sin(Angles.x);

		// Rotating about y - axis
		resultY[0][0] =  (float)MathUtil::Cos(Angles.y);
		resultY[0][2] =  (float)MathUtil::Sin(Angles.y);
		resultY[2][2] =  (float)MathUtil::Cos(Angles.y);
		resultY[2][0] = -(float)MathUtil::Sin(Angles.y);

		// Rotating about z - axis
		resultZ[0][0] =  (float)MathUtil::Cos(Angles.z);
		resultZ[0][1] = -(float)MathUtil::Sin(Angles.z);
		resultZ[1][0] =  (float)MathUtil::Sin(Angles.z);
		resultZ[1][1] =  (float)MathUtil::Cos(Angles.z);

		*this = resultZ * resultY * resultX;
	}

	Rotation::Rotation(float Angle, const Vector3& Axis)
	{
		// Get the normalized Axis
		Vector3 l_Axis = Axis.Normal();

		// Get the projection of Axis on the XZ - plane and the YZ - plane
		Vector3 ProjXY = l_Axis * Vector3(1, 1, 0);
		Vector3 ProjXZ = l_Axis * Vector3(1, 0, 1);

		float MagXY = ProjXY.Magnitude();
		float MagXZ = ProjXZ.Magnitude();

		// Calculate the Roll (Rotation about z-axis) and the Yaw (Rotation about y-axis) for the axis
		float Roll = MagXY == 0 ? 0.0f : (float)MathUtil::CosInverse(Vector3::DotProduct(ProjXY, Vector3::XAxis) / MagXY);
		float Yaw  = MagXZ == 0 ? 0.0f : (float)MathUtil::CosInverse(Vector3::DotProduct(ProjXZ, Vector3::XAxis) / MagXZ);

		// Rotate the axes to make the given axis as the new X - axis
		Rotation rotate(Vector3(0, Yaw, Roll));

		// Rotate the matrix about this new X - Axis;
		M[1][1] =  (float)MathUtil::Cos(Angle);
		M[2][2] =  (float)MathUtil::Cos(Angle);
		M[1][2] = -(float)MathUtil::Sin(Angle);
		M[2][1] =  (float)MathUtil::Sin(Angle);

		// Rotate the axes back to the original orientation
		*this = rotate.Inverse() * (*this) * rotate;
	}

	const Rotation& Rotation::operator=(const Matrix4& OtherMat)
	{
		Matrix4::operator=(OtherMat);
		return *this;
	}

	Matrix4 Rotation::Inverse() const
	{
		// For rotation the inverse is the transpose of the matrix
		return Transpose();
	}

	/* Static Members */
	Matrix4 Rotation::Rotate(const Matrix4& Mat, const Vector3& Angles)
	{
		Rotation result(Angles);

		return Mat * result;
	}

	Matrix4 Rotation::Rotate(const Matrix4& Mat, float Angle, const Vector3& Axis)
	{
		return Mat * Rotation(Angle, Axis);
	}

	Matrix4 Rotation::Rotate(const Matrix4& Mat, float Value)
	{
		Rotation result(Value);

		return Mat * result;
	}
}