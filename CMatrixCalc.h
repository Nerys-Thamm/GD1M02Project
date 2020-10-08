#pragma once
class CMatrixCalc
{
public:
	static void SetIdentity(float(&Matrix)[4][4]);
	static float GetDeterminant(const float(&Matrix)[4][4]);
	static float GetDeterminant3X(float _mat[3][3]);
	static void Transpose(float(&Matrix)[4][4]);
	static void Inverse(float(&Matrix)[4][4]);
	static void Multiply(float(&Matrix)[4][4], float scalar);
	static void Multiply(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4]);
	static void Add(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4]);
	static void Subtract(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4]);

};
