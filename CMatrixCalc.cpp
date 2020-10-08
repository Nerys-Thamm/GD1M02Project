#include "CMatrixCalc.h"

void CMatrixCalc::SetIdentity(float(&Matrix)[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix[i][j] = (i == j ? 1 : 0);
		}
	}
}

float CMatrixCalc::GetDeterminant(const float(&Matrix)[4][4])
{
	float fTempMat[3][3];
	float fDeterminant[4];
	int iIndex = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == i) { continue; }
			else
			{
				for (int k = 0; k < 3; k++)
				{
					fTempMat[iIndex][k] = Matrix[j][k + 1];
				}
				iIndex++;
			}
		}
		fDeterminant[i] = GetDeterminant3X(fTempMat);
	}
	return fDeterminant[0] - fDeterminant[1] + fDeterminant[2] - fDeterminant[3];
}

float CMatrixCalc::GetDeterminant3X(float _mat[3][3])
{
    return ((_mat[1][1] * _mat[2][2]) - (_mat[2][1] * _mat[1][2])) - ((_mat[0][1] * _mat[2][2]) - (_mat[2][1] * _mat[0][2])) + ((_mat[0][1] * _mat[1][2]) - (_mat[1][1] * _mat[0][2]));
}

void CMatrixCalc::Transpose(float(&Matrix)[4][4])
{
	float fTempMatrix[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fTempMatrix[i][j] = Matrix[j][i];
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix[i][j] = fTempMatrix[i][j];
		}
	}
}

void CMatrixCalc::Inverse(float(&Matrix)[4][4])
{
	//row 1
	float adjugate00[3][3];
	float adjugate10[3][3];
	float adjugate20[3][3];
	float adjugate30[3][3];
	//row 2
	float adjugate01[3][3];
	float adjugate11[3][3];
	float adjugate21[3][3];
	float adjugate31[3][3];
	//row 3
	float adjugate02[3][3];
	float adjugate12[3][3];
	float adjugate22[3][3];
	float adjugate32[3][3];
	//row 4
	float adjugate03[3][3];
	float adjugate13[3][3];
	float adjugate23[3][3];
	float adjugate33[3][3];

	//asigining the adjugates
	adjugate00[0][0] = 

	


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			


		}
	}
}

void CMatrixCalc::Multiply(float(&Matrix)[4][4], float scalar)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Matrix[i][j] *= scalar;
		}
	}
}

void CMatrixCalc::Multiply(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4])
{
	float result;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			result = 0;
			for (int i = 0; i < 4; i++)
			{
				result = result + (MatrixA[y][i] * MatrixB[i][x]);
			}
			Result [y] [x] = result;
		}
	}
}

void CMatrixCalc::Add(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result[i][j] = MatrixA[i][j] + MatrixB[i][j];
		}
	}
}

void CMatrixCalc::Subtract(const float(&MatrixA)[4][4], const float(&MatrixB)[4][4], float(&Result)[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Result[i][j] = MatrixA[i][j] - MatrixB[i][j];
		}
	}
}
