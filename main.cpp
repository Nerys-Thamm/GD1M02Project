//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2020 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//


#define WIN32_LEAN_AND_MEAN

#include <windows.h>   // Include all the windows headers.
#include <windowsx.h>  // Include useful macros.
#include <cmath> // include cmath for sqrt

#include "utils.h"
#include "resource.h"
#include "CMatrixCalc.h"
#include "CQuaternionCalc.h"
#include "CSlerpCalc.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

//matrix calculator
float matrixA[4][4], matrixB[4][4], resultantMat[4][4], TempMatrix[4][4];
float AScale, BScale;
float tempValue;

void DisplayMatrixA(HWND _hwnd)
{
	//row 1
	WriteToEditBox(_hwnd, IDC_EDIT_A11, matrixA[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_A12, matrixA[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_A13, matrixA[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_A14, matrixA[0][3]);
	//row 2
	WriteToEditBox(_hwnd, IDC_EDIT_A21, matrixA[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_A22, matrixA[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_A23, matrixA[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_A24, matrixA[1][3]);
	//row 3
	WriteToEditBox(_hwnd, IDC_EDIT_A31, matrixA[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_A32, matrixA[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_A33, matrixA[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_A34, matrixA[2][3]);
	//row 4
	WriteToEditBox(_hwnd, IDC_EDIT_A41, matrixA[3][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_A42, matrixA[3][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_A43, matrixA[3][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_A44, matrixA[3][3]);
}

void DisplayMatrixB(HWND _hwnd)
{
	//row 1
	WriteToEditBox(_hwnd, IDC_EDIT_B11, matrixB[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_B12, matrixB[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_B13, matrixB[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_B14, matrixB[0][3]);
	//row 2
	WriteToEditBox(_hwnd, IDC_EDIT_B21, matrixB[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_B22, matrixB[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_B23, matrixB[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_B24, matrixB[1][3]);
	//row 3
	WriteToEditBox(_hwnd, IDC_EDIT_B31, matrixB[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_B32, matrixB[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_B33, matrixB[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_B34, matrixB[2][3]);
	//row 4
	WriteToEditBox(_hwnd, IDC_EDIT_B41, matrixB[3][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_B42, matrixB[3][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_B43, matrixB[3][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_B44, matrixB[3][3]);
}

void DisplayMatrixR(HWND _hwnd)
{
	//row 1
	WriteToEditBox(_hwnd, IDC_EDIT_R11, resultantMat[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_R12, resultantMat[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_R13, resultantMat[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_R14, resultantMat[0][3]);
	//row 2
	WriteToEditBox(_hwnd, IDC_EDIT_R21, resultantMat[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_R22, resultantMat[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_R23, resultantMat[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_R24, resultantMat[1][3]);
	//row 3
	WriteToEditBox(_hwnd, IDC_EDIT_R31, resultantMat[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_R32, resultantMat[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_R33, resultantMat[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_R34, resultantMat[2][3]);
	//row 4
	WriteToEditBox(_hwnd, IDC_EDIT_R41, resultantMat[3][0]);
	WriteToEditBox(_hwnd, IDC_EDIT_R42, resultantMat[3][1]);
	WriteToEditBox(_hwnd, IDC_EDIT_R43, resultantMat[3][2]);
	WriteToEditBox(_hwnd, IDC_EDIT_R44, resultantMat[3][3]);
}

//quarternion calculator
CQuaternionCalc::Quaternion QuarternionA(0, 0, 0, 0);
CQuaternionCalc::Quaternion QuarternionB(0, 0, 0, 0);
CQuaternionCalc::Quaternion QuarternionR(0, 0, 0, 0);
CQuaternionCalc::Quaternion QuarternionTemp(0, 0, 0, 0);

double MagResult;

double DotProductResult = 0;

double ConstantT = 0;

void DisplayQauternionR(HWND _hwnd)
{
	//display answer
	WriteToEditBox(_hwnd, IDC_EDIT10, QuarternionR.i);
	WriteToEditBox(_hwnd, IDC_EDIT11, QuarternionR.j);
	WriteToEditBox(_hwnd, IDC_EDIT12, QuarternionR.k);
	WriteToEditBox(_hwnd, IDC_EDIT13, QuarternionR.w);
}

void DisplayDotProduct(HWND _hwnd)
{
	//display answer
	WriteToEditBox(_hwnd, IDC_EDIT10, 0);
	WriteToEditBox(_hwnd, IDC_EDIT11, 0);
	WriteToEditBox(_hwnd, IDC_EDIT12, 0);
	WriteToEditBox(_hwnd, IDC_EDIT13, DotProductResult);
}

void DisplayMagnitude(HWND _hwnd)
{
	//display answer
	WriteToEditBox(_hwnd, IDC_EDIT10, 0);
	WriteToEditBox(_hwnd, IDC_EDIT11, 0);
	WriteToEditBox(_hwnd, IDC_EDIT12, 0);
	WriteToEditBox(_hwnd, IDC_EDIT13, MagResult);
}

//Gaussian Eliminator
float GaussianMatrix[3][4];

//multiply function
float MultiplyRowConstant;
int MultiplyRow;

//swap function
int SwapRowA;
int SwapRowB;
float tempGaussianMatrix[4];

//add function
float AddRowConstant;
int AddRowA;
int AddRowB;

void DisplayGaussianMatrix(HWND _hwnd)
{// displays full matrix
	WriteToEditBox(_hwnd, IDC_EDIT1, GaussianMatrix[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT4, GaussianMatrix[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT2, GaussianMatrix[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT3, GaussianMatrix[0][3]);

	WriteToEditBox(_hwnd, IDC_EDIT5, GaussianMatrix[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT8, GaussianMatrix[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT6, GaussianMatrix[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT7, GaussianMatrix[1][3]);

	WriteToEditBox(_hwnd, IDC_EDIT9, GaussianMatrix[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT12, GaussianMatrix[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT10, GaussianMatrix[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT11, GaussianMatrix[2][3]);
	}


//SLERP calculator
CQuaternionCalc::Quaternion a(0,0,0,0);
CQuaternionCalc::Quaternion b(0,0,0,0);
CQuaternionCalc::Quaternion res(0,0,0,0);
float InducedMatrix[4][4];

//Transformation matrix
float ResMatRow[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

float xScale = 0;
float yScale = 0;
float zScale = 0;

float xTrans = 0;
float yTrans = 0;
float zTrans = 0;

float OperationM[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
float TempMat[4][4];

float RotAngle = 0;
float Distance = 0;

int RotXYZ;
int ProXYZ;

//display functions
void DisplayBothMatrix(HWND _hwnd)
{
	//row major
	//row 1
	WriteToEditBox(_hwnd, IDC_EDIT47, ResMatRow[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT48, ResMatRow[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT49, ResMatRow[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT50, ResMatRow[0][3]);
	//row 2
	WriteToEditBox(_hwnd, IDC_EDIT51, ResMatRow[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT52, ResMatRow[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT53, ResMatRow[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT54, ResMatRow[1][3]);
	//row 3
	WriteToEditBox(_hwnd, IDC_EDIT55, ResMatRow[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT56, ResMatRow[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT57, ResMatRow[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT58, ResMatRow[2][3]);
	//row 4
	WriteToEditBox(_hwnd, IDC_EDIT59, ResMatRow[3][0]);
	WriteToEditBox(_hwnd, IDC_EDIT60, ResMatRow[3][1]);
	WriteToEditBox(_hwnd, IDC_EDIT61, ResMatRow[3][2]);
	WriteToEditBox(_hwnd, IDC_EDIT62, ResMatRow[3][3]);

	//collum major
	//row 1
	WriteToEditBox(_hwnd, IDC_EDIT16, ResMatRow[0][0]);
	WriteToEditBox(_hwnd, IDC_EDIT18, ResMatRow[1][0]);
	WriteToEditBox(_hwnd, IDC_EDIT19, ResMatRow[2][0]);
	WriteToEditBox(_hwnd, IDC_EDIT20, ResMatRow[3][0]);
	//row 2
	WriteToEditBox(_hwnd, IDC_EDIT21, ResMatRow[0][1]);
	WriteToEditBox(_hwnd, IDC_EDIT22, ResMatRow[1][1]);
	WriteToEditBox(_hwnd, IDC_EDIT23, ResMatRow[2][1]);
	WriteToEditBox(_hwnd, IDC_EDIT8, ResMatRow[3][1]);
	//row 3
	WriteToEditBox(_hwnd, IDC_EDIT9, ResMatRow[0][2]);
	WriteToEditBox(_hwnd, IDC_EDIT10, ResMatRow[1][2]);
	WriteToEditBox(_hwnd, IDC_EDIT11, ResMatRow[2][2]);
	WriteToEditBox(_hwnd, IDC_EDIT12, ResMatRow[3][2]);
	//row 4
	WriteToEditBox(_hwnd, IDC_EDIT24, ResMatRow[0][3]);
	WriteToEditBox(_hwnd, IDC_EDIT25, ResMatRow[1][3]);
	WriteToEditBox(_hwnd, IDC_EDIT26, ResMatRow[2][3]);
	WriteToEditBox(_hwnd, IDC_EDIT27, ResMatRow[3][3]);
}



void GameLoop()
{
	//One frame of game logic occurs here...
}

LRESULT CALLBACK WindowProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc;        // Handle to a device context.

					// What is the message?
	switch (_msg)
	{
	case WM_CREATE:
	{
		// Do initialization stuff here.

		// Return Success.
		return (0);
	}
	break;

	case WM_PAINT:
	{
		// Simply validate the window.
		hdc = BeginPaint(_hwnd, &ps);

		// You would do all your painting here...

		EndPaint(_hwnd, &ps);

		// Return Success.
		return (0);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case ID_EXIT:
		{
			PostQuitMessage(0);
			break;
		}
		case ID_CALCULATOR_MATRIX:
		{
			ShowWindow(g_hDlgMatrix, SW_SHOWNORMAL);
			break;
		}
		case ID_CALCULATOR_TRANSFORMATION:
		{
			ShowWindow(g_hDlgTransformation, SW_SHOWNORMAL);
			break;

		}
		//open the matrix dialog
		case ID_CALCULATOR_GAUSSIAN:
		{
			ShowWindow(g_hDlgGaussian, SW_SHOWNORMAL);
			break;
		}
		//open the gaussian dialog
		case ID_CALCULATOR_QUATERNION:
		{
			ShowWindow(g_hDlgQuaternion, SW_SHOWNORMAL);
			break;
		}
		//open the quaternion dialog
		case ID_CALCULATOR_SLERP:
		{
			ShowWindow(g_hDlgSLERP, SW_SHOWNORMAL);
			break;
		}
		default:
			break;
		}
		return(0);
	}
	break;

	case WM_DESTROY:
	{
		// Kill the application, this sends a WM_QUIT message.
		PostQuitMessage(0);

		// Return success.
		return (0);
	}
	break;

	default:break;
	} // End switch.

	  // Process any messages that we did not take care of...

	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}

BOOL CALLBACK MatrixDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	static float _value;
	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
			//Matrix A
			//row 1
		case IDC_EDIT_A11:
		{ 
			matrixA[0][0] = ReadFromEditBox(_hwnd, IDC_EDIT_A11);
			break;
		}
		case IDC_EDIT_A12:
		{
			matrixA[0][1] = ReadFromEditBox(_hwnd, IDC_EDIT_A12);
			break;
		}
		case IDC_EDIT_A13:
		{
			matrixA[0][2] = ReadFromEditBox(_hwnd, IDC_EDIT_A13);
			break;
		}
		case IDC_EDIT_A14:
		{
			matrixA[0][3] = ReadFromEditBox(_hwnd, IDC_EDIT_A14);
			break;
		}
			//row 2
		case IDC_EDIT_A21:
		{
			matrixA[1][0] = ReadFromEditBox(_hwnd, IDC_EDIT_A21);
			break;
		}
		case IDC_EDIT_A22:
		{
			matrixA[1][1] = ReadFromEditBox(_hwnd, IDC_EDIT_A22);
			break;
		}
		case IDC_EDIT_A23:
		{
			matrixA[1][2] = ReadFromEditBox(_hwnd, IDC_EDIT_A23);
			break;
		}
		case IDC_EDIT_A24:
		{
			matrixA[1][3] = ReadFromEditBox(_hwnd, IDC_EDIT_A24);
			break;
		}
		//row 3
		case IDC_EDIT_A31:
		{
			matrixA[2][0] = ReadFromEditBox(_hwnd, IDC_EDIT_A31);
			break;
		}
		case IDC_EDIT_A32:
		{
			matrixA[2][1] = ReadFromEditBox(_hwnd, IDC_EDIT_A32);
			break;
		}
		case IDC_EDIT_A33:
		{
			matrixA[2][2] = ReadFromEditBox(_hwnd, IDC_EDIT_A33);
			break;
		}
		case IDC_EDIT_A34:
		{
			matrixA[2][3] = ReadFromEditBox(_hwnd, IDC_EDIT_A34);
			break;
		}
		//row 4
		case IDC_EDIT_A41:
		{
			matrixA[3][0] = ReadFromEditBox(_hwnd, IDC_EDIT_A41);
			break;
		}
		case IDC_EDIT_A42:
		{
			matrixA[3][1] = ReadFromEditBox(_hwnd, IDC_EDIT_A42);
			break;
		}
		case IDC_EDIT_A43:
		{
			matrixA[3][2] = ReadFromEditBox(_hwnd, IDC_EDIT_A43);
			break;
		}
		case IDC_EDIT_A44:
		{
			matrixA[3][3] = ReadFromEditBox(_hwnd, IDC_EDIT_A44);
			break;
		}
		//Matrix b
		//row 1
		case IDC_EDIT_B11:
		{
			matrixB[0][0] = ReadFromEditBox(_hwnd, IDC_EDIT_B11);
			break;
		}
		case IDC_EDIT_B12:
		{
			matrixB[0][1] = ReadFromEditBox(_hwnd, IDC_EDIT_B12);
			break;
		}
		case IDC_EDIT_B13:
		{
			matrixB[0][2] = ReadFromEditBox(_hwnd, IDC_EDIT_B13);
			break;
		}
		case IDC_EDIT_B14:
		{
			matrixB[0][3] = ReadFromEditBox(_hwnd, IDC_EDIT_B14);
			break;
		}
		//row 2
		case IDC_EDIT_B21:
		{
			matrixB[1][0] = ReadFromEditBox(_hwnd, IDC_EDIT_B21);
			break;
		}
		case IDC_EDIT_B22:
		{
			matrixB[1][1] = ReadFromEditBox(_hwnd, IDC_EDIT_B22);
			break;
		}
		case IDC_EDIT_B23:
		{
			matrixB[1][2] = ReadFromEditBox(_hwnd, IDC_EDIT_B23);
			break;
		}
		case IDC_EDIT_B24:
		{
			matrixB[1][3] = ReadFromEditBox(_hwnd, IDC_EDIT_B24);
			break;
		}
		//row 3
		case IDC_EDIT_B31:
		{
			matrixB[2][0] = ReadFromEditBox(_hwnd, IDC_EDIT_B31);
			break;
		}
		case IDC_EDIT_B32:
		{
			matrixB[2][1] = ReadFromEditBox(_hwnd, IDC_EDIT_B32);
			break;
		}
		case IDC_EDIT_B33:
		{
			matrixB[2][2] = ReadFromEditBox(_hwnd, IDC_EDIT_B33);
			break;
		}
		case IDC_EDIT_B34:
		{
			matrixB[2][3] = ReadFromEditBox(_hwnd, IDC_EDIT_B34);
			break;
		}
		//row 4
		case IDC_EDIT_B41:
		{
			matrixB[3][0] = ReadFromEditBox(_hwnd, IDC_EDIT_B41);
			break;
		}
		case IDC_EDIT_B42:
		{
			matrixB[3][1] = ReadFromEditBox(_hwnd, IDC_EDIT_B42);
			break;
		}
		case IDC_EDIT_B43:
		{
			matrixB[3][2] = ReadFromEditBox(_hwnd, IDC_EDIT_B43);
			break;
		}
		case IDC_EDIT_B44:
		{
			matrixB[3][3] = ReadFromEditBox(_hwnd, IDC_EDIT_B44);
			break;
		}

		case IDC_EDIT_AScaled:
		{
			AScale = ReadFromEditBox(_hwnd, IDC_EDIT_AScaled);
			break;
		}

		case IDC_EDIT_BScaled:
		{
			BScale = ReadFromEditBox(_hwnd, IDC_EDIT_BScaled);
			break;
		}

		case IDOK3: // Det A
		{
			tempValue = CMatrixCalc::GetDeterminant(matrixA);
			WriteToEditBox(_hwnd, IDC_EDIT_DetA, tempValue);
			break;
		}
		case IDOK7: // Det B
		{
			tempValue = CMatrixCalc::GetDeterminant(matrixB);
			WriteToEditBox(_hwnd, IDC_EDIT_DetB, tempValue);
			break;
		}
		case IDCANCEL2: //Inverse A
		{
			CMatrixCalc::Inverse(matrixA);
			//Display matrix
			DisplayMatrixA(_hwnd);
			break;
		}
		case IDCANCEL3: //Inverse B
		{
			CMatrixCalc::Inverse(matrixB);
			//display matrix
			DisplayMatrixB(_hwnd);
			break;
		}
		case IDOK6: // A * scalar
		{
			CMatrixCalc::Multiply(matrixA, AScale);
			//Display matrix
			DisplayMatrixA(_hwnd);
			break;
		}
		case IDOK10: // B * scalar
		{
			
			CMatrixCalc::Multiply(matrixB, BScale);
			//display matrix
			DisplayMatrixB(_hwnd);
			break;
		}

		case IDOK9: // A Transpose
		{
			CMatrixCalc::Transpose(matrixA);
			
			//Display matrix
			DisplayMatrixA(_hwnd);
			break;
		}
		case IDOK11: // b Transpose
		{
			CMatrixCalc::Transpose(matrixB);
			//display matrix
			DisplayMatrixB(_hwnd);
			break;
		}
		case IDOK4: // A = I
		{
			CMatrixCalc::SetIdentity(matrixA);

			//Display matrix
			DisplayMatrixA(_hwnd);
			break;
		}
		case IDOK8: // B = I
		{
			CMatrixCalc::SetIdentity(matrixB);
			//display matrix
			DisplayMatrixB(_hwnd);
			break;
		}
		case IDOK: // A + B
		{ 
			
			CMatrixCalc::Add(matrixA, matrixB, resultantMat);
			//Display matrix
			DisplayMatrixR(_hwnd);
			break;
		}
		case IDCANCEL: // A - B
		{
			CMatrixCalc::Subtract(matrixA, matrixB, resultantMat);
			//Display matrix
			DisplayMatrixR(_hwnd);
			break;
		}
		case IDOK2: // A * B
		{
			CMatrixCalc::Multiply(matrixA, matrixB, resultantMat);
			//Display matrix
			DisplayMatrixR(_hwnd);
			break;
		}
		case IDOK5: // B * A
		{
			CMatrixCalc::Multiply(matrixB, matrixA, resultantMat);
			//Display matrix
			DisplayMatrixR(_hwnd);
			break;
		}
		default:
			break;
		}
		return TRUE;
		break;
	}
	case WM_CLOSE:
	{
		MessageBox(_hwnd, ToWideString(_value).c_str(), L"Default Value", MB_OK);
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK TransformationDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{//Nerys did this
			//setting XYZ scale 
		case IDC_EDIT1:
			xScale = ReadFromEditBox(_hwnd, IDC_EDIT1);
			DisplayBothMatrix(_hwnd);
			break;
		case IDC_EDIT2:
			yScale = ReadFromEditBox(_hwnd, IDC_EDIT2);
			break;
		case IDC_EDIT3:
			zScale = ReadFromEditBox(_hwnd, IDC_EDIT3);
			break;

			//setting scale of matrix
		case IDC_BUTTON4:
			CMatrixCalc::SetIdentity(OperationM);

			OperationM[0][0] = xScale;
			OperationM[1][1] = yScale;
			OperationM[2][2] = zScale;

			CMatrixCalc::Multiply(ResMatRow, OperationM, TempMat);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ResMatRow[i][j] = TempMat[i][j];
				}
			}

			DisplayBothMatrix(_hwnd);
			break;
			//dunstan did this
			//setting XYZ Translation
		case IDC_EDIT4:
			xTrans = ReadFromEditBox(_hwnd, IDC_EDIT4);
			break;
		case IDC_EDIT5:
			yTrans = ReadFromEditBox(_hwnd, IDC_EDIT5);
			break;
		case IDC_EDIT6:
			zTrans = ReadFromEditBox(_hwnd, IDC_EDIT6);
			break;

			//setting Translation of matrix
		case IDC_BUTTON15:
			CMatrixCalc::SetIdentity(OperationM);

			OperationM[0][3] = xTrans;
			OperationM[1][3] = yTrans;
			OperationM[2][3] = zTrans;

			CMatrixCalc::Multiply(ResMatRow, OperationM, TempMat);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ResMatRow[i][j] = TempMat[i][j];
				}
			}

			DisplayBothMatrix(_hwnd);
			break;
			//nerys did this
			//Rotation Matrix
		case IDC_EDIT13:
			RotAngle = ReadFromEditBox(_hwnd, IDC_EDIT13);
			break;

		case IDC_RADIO1:
			RotXYZ = 1;
			break;

		case IDC_RADIO2:
			RotXYZ = 2;
			break;

		case IDC_RADIO3:
			RotXYZ = 3;
			break;

		case IDC_BUTTON16:
			CMatrixCalc::SetIdentity(OperationM);
			switch (RotXYZ)
			{
			case 1:
				OperationM[1][1] = cos(RotAngle);
				OperationM[1][2] = sin(RotAngle);
				OperationM[2][1] = -sin(RotAngle);
				OperationM[2][2] = cos(RotAngle);
				break;
			case 2:
				OperationM[0][0] = cos(RotAngle);
				OperationM[0][2] = -sin(RotAngle);
				OperationM[2][0] = sin(RotAngle);
				OperationM[2][2] = cos(RotAngle);
				break;
			case 3:
				OperationM[0][0] = cos(RotAngle);
				OperationM[0][1] = -sin(RotAngle);
				OperationM[1][0] = sin(RotAngle);
				OperationM[1][1] = cos(RotAngle);
				break;
			default:
				break;
			}

			CMatrixCalc::Multiply(ResMatRow, OperationM, TempMat);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ResMatRow[i][j] = TempMat[i][j];
				}
			}

			DisplayBothMatrix(_hwnd);
			break;
			//dunstan did this
			//Projection Matrix
		case IDC_EDIT15:
			Distance = ReadFromEditBox(_hwnd, IDC_EDIT15);
			break;

		case IDC_RADIO4:
			ProXYZ = 1;
			break;

		case IDC_RADIO5:
			ProXYZ = 2;
			break;

		case IDC_RADIO6:
			ProXYZ = 3;
			break;

		case IDC_BUTTON17:
			CMatrixCalc::SetIdentity(OperationM);
			switch (ProXYZ)
			{
			case 1:
				OperationM[3][0] = (1/Distance);
				break;
			case 2:
				OperationM[3][1] = (1 / Distance);
				break;
			case 3:
				OperationM[3][2] = (1 / Distance);
				break;
			default:
				break;
			}

			CMatrixCalc::Multiply(ResMatRow, OperationM, TempMat);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ResMatRow[i][j] = TempMat[i][j];
				}
			}

			DisplayBothMatrix(_hwnd);
			break;


		default:
			break;
		}

	return TRUE;
	break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


BOOL CALLBACK GaussianDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		int currentnonzeroindex = -1;
		bool validRowEchelon = true;
		bool validReducedRowEchelon = true;
		switch (LOWORD(_wparam))
		{
			//Gaussian Array input
			//row 1
		case IDC_EDIT1:
			GaussianMatrix[0][0] = ReadFromEditBox(_hwnd, IDC_EDIT1);
			break;

		case IDC_EDIT4:
			GaussianMatrix[0][1] = ReadFromEditBox(_hwnd, IDC_EDIT4);
			break;

		case IDC_EDIT2:
			GaussianMatrix[0][2] = ReadFromEditBox(_hwnd, IDC_EDIT2);
			break;

		case IDC_EDIT3:
			GaussianMatrix[0][3] = ReadFromEditBox(_hwnd, IDC_EDIT3);
			break;
			//row 2
		case IDC_EDIT5:
			GaussianMatrix[1][0] = ReadFromEditBox(_hwnd, IDC_EDIT5);
			break;

		case IDC_EDIT8:
			GaussianMatrix[1][1] = ReadFromEditBox(_hwnd, IDC_EDIT8);
			break;

		case IDC_EDIT6:
			GaussianMatrix[1][2] = ReadFromEditBox(_hwnd, IDC_EDIT6);
			break;

		case IDC_EDIT7:
			GaussianMatrix[1][3] = ReadFromEditBox(_hwnd, IDC_EDIT7);
			break;
			//row 3
		case IDC_EDIT9:
			GaussianMatrix[2][0] = ReadFromEditBox(_hwnd, IDC_EDIT9);
			break;

		case IDC_EDIT12:
			GaussianMatrix[2][1] = ReadFromEditBox(_hwnd, IDC_EDIT12);
			break;

		case IDC_EDIT10:
			GaussianMatrix[2][2] = ReadFromEditBox(_hwnd, IDC_EDIT10);
			break;

		case IDC_EDIT11:
			GaussianMatrix[2][3] = ReadFromEditBox(_hwnd, IDC_EDIT11);
			break;

			//Multiply Row
		case IDC_EDIT13:
			MultiplyRow = ReadFromEditBox(_hwnd, IDC_EDIT13);
			break;

		case IDC_EDIT14:
			MultiplyRowConstant = ReadFromEditBox(_hwnd, IDC_EDIT14);
			break;

		case IDC_BUTTON1: 
			for (int i = 0; i < 4; i++)
			{
				GaussianMatrix[MultiplyRow - 1][i] *= MultiplyRowConstant;
			}
			DisplayGaussianMatrix(_hwnd);
			
			for (int i = 0; i < 3; i++) //for each row
			{
				for (int j = 0; j < 4; j++) //for each number in that row
				{
					if (GaussianMatrix[i][j] != 0) //is it nonzero?
					{
						if (j <= currentnonzeroindex) //Is its index smaller than or equal to the current highest index?
						{
							validRowEchelon = false; //if so then it doesnt fufill the criteria for Row Echelon
						}
						if (GaussianMatrix[i][j] != 1) //Is the nonzero number not 1?
						{
							validReducedRowEchelon = false; //If so it doesnt fit the criteria for reduced row echelon
						}
						currentnonzeroindex = j; //Set the current highest nonzero index to be this index
						break; //skip to the next row
					}
				}
			}
			if (validReducedRowEchelon && validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Reduced Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else if (validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else
			{
				MessageBox(_hwnd, ToWideString("No").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			break;

			//Swap function
		case IDC_EDIT16:
			SwapRowA = ReadFromEditBox(_hwnd, IDC_EDIT16);
			break;

		case IDC_EDIT17:
			SwapRowB = ReadFromEditBox(_hwnd, IDC_EDIT17);
			break;

		case IDC_BUTTON2:
			for (int i = 0; i < 4; i++)
			{
				tempGaussianMatrix[i] = GaussianMatrix[SwapRowA-1][i];
				GaussianMatrix[SwapRowA - 1][i] = GaussianMatrix[SwapRowB - 1][i];
				GaussianMatrix[SwapRowB - 1][i] = tempGaussianMatrix[i];
			}
			DisplayGaussianMatrix(_hwnd);
			
			for (int i = 0; i < 3; i++) //for each row
			{
				for (int j = 0; j < 4; j++) //for each number in that row
				{
					if (GaussianMatrix[i][j] != 0) //is it nonzero?
					{
						if (j <= currentnonzeroindex) //Is its index smaller than or equal to the current highest index?
						{
							validRowEchelon = false; //if so then it doesnt fufill the criteria for Row Echelon
						}
						if (GaussianMatrix[i][j] != 1) //Is the nonzero number not 1?
						{
							validReducedRowEchelon = false; //If so it doesnt fit the criteria for reduced row echelon
						}
						currentnonzeroindex = j; //Set the current highest nonzero index to be this index
						break; //skip to the next row
					}
				}
			}
			if (validReducedRowEchelon && validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Reduced Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else if (validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else
			{
				MessageBox(_hwnd, ToWideString("No").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			break;

			//add function
		case IDC_EDIT19:
			AddRowConstant = ReadFromEditBox(_hwnd, IDC_EDIT19);
			break;

		case IDC_EDIT20:
			AddRowA = ReadFromEditBox(_hwnd, IDC_EDIT20);
			break;

		case IDC_EDIT22:
			AddRowB = ReadFromEditBox(_hwnd, IDC_EDIT22);
			break;

		case IDC_BUTTON3:
			for (int i = 0; i < 4; i++)
			{
				GaussianMatrix[AddRowA - 1][i] *= AddRowConstant;
				GaussianMatrix[AddRowA - 1][i] += GaussianMatrix[AddRowB - 1][i];
			}
			DisplayGaussianMatrix(_hwnd);
			
			for (int i = 0; i < 3; i++) //for each row
			{
				for (int j = 0; j < 4; j++) //for each number in that row
				{
					if (GaussianMatrix[i][j] != 0) //is it nonzero?
					{
						if (j <= currentnonzeroindex) //Is its index smaller than or equal to the current highest index?
						{
							validRowEchelon = false; //if so then it doesnt fufill the criteria for Row Echelon
						}
						if (GaussianMatrix[i][j] != 1) //Is the nonzero number not 1?
						{
							validReducedRowEchelon = false; //If so it doesnt fit the criteria for reduced row echelon
						}
						currentnonzeroindex = j; //Set the current highest nonzero index to be this index
						break; //skip to the next row
					}
				}
			}
			if (validReducedRowEchelon && validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Reduced Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else if (validRowEchelon)
			{
				MessageBox(_hwnd, ToWideString("This is Row Echelon").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			else
			{
				MessageBox(_hwnd, ToWideString("No").c_str(), L"Is it Row Echelon?", MB_OK);
			}
			break;

		default:
			break;
		}

		return TRUE;
		break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}


BOOL CALLBACK QuaternionDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
			//Quaternion A
		case IDC_EDIT1: // edit A i component
			QuarternionA.i = ReadFromEditBox(_hwnd, IDC_EDIT1);
			break;

		case IDC_EDIT2: // edit A j component
			QuarternionA.j = ReadFromEditBox(_hwnd, IDC_EDIT2);
			break;

		case IDC_EDIT3: // edit A k component
			QuarternionA.k = ReadFromEditBox(_hwnd, IDC_EDIT3);
			break;

		case IDC_EDIT4: // edit A w component
			QuarternionA.w = ReadFromEditBox(_hwnd, IDC_EDIT4);
			break;

			//QuaternionB= B
		case IDC_EDIT5: // edit B i component
			QuarternionB.i = ReadFromEditBox(_hwnd, IDC_EDIT5);
			break;

		case IDC_EDIT6: // edit B j component
			QuarternionB.j = ReadFromEditBox(_hwnd, IDC_EDIT6);
			break;

		case IDC_EDIT7: // edit B k component
			QuarternionB.k = ReadFromEditBox(_hwnd, IDC_EDIT7);
			break;

		case IDC_EDIT8: // edit B w component
			QuarternionB.w = ReadFromEditBox(_hwnd, IDC_EDIT8);
			break;

			//Constant T
		case IDC_EDIT9: // edit B w component
			ConstantT = ReadFromEditBox(_hwnd, IDC_EDIT9);
			break;
		
			//Calculation inputs.
		case IDC_BUTTON1: // A+B
			QuarternionR = QuarternionA + QuarternionB;

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON5: // A-B
			QuarternionR = QuarternionA - QuarternionB;
			//display QuaternionR
			DisplayQauternionR(_hwnd);

			break;

		case IDC_BUTTON6: // B-A
			QuarternionR = QuarternionB - QuarternionA;
			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON2: // AB 
			// Multiply :)
			QuarternionR = QuarternionA * QuarternionB;

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON7: // BA
			
			QuarternionR = QuarternionB * QuarternionA;

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON8: // A dot B
			DotProductResult = ((QuarternionA.i * QuarternionB.i) + (QuarternionA.j * QuarternionB.j) + (QuarternionA.k * QuarternionB.k) + (QuarternionA.w * QuarternionB.w));

			//display DotProduct
			DisplayDotProduct(_hwnd);
			break;

		case IDC_BUTTON3: // A*
			QuarternionR = QuarternionA.Conjugate();

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON9: // B*
			QuarternionR = QuarternionB.Conjugate();

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON10: // |A|
			// setting a temporary quaternion to hold each term of quaternion a^2
			QuarternionR.i = (QuarternionA.i * QuarternionA.i);
			QuarternionR.j = (QuarternionA.j * QuarternionA.j);
			QuarternionR.k = (QuarternionA.k * QuarternionA.k);
			QuarternionR.w = (QuarternionA.w * QuarternionA.w);

			//setting MagResult to the square root of the sum of each term^2 in the quaternion
			MagResult = sqrt(QuarternionR.i + QuarternionR.j + QuarternionR.k + QuarternionR.w);

			//display Magnitude
			DisplayMagnitude(_hwnd);
			break;

		case IDC_BUTTON11: // |B|
			// setting a temporary quaternion to hold each term of quaternion b^2
			QuarternionR.i = (QuarternionB.i * QuarternionB.i);
			QuarternionR.j = (QuarternionB.j * QuarternionB.j);
			QuarternionR.k = (QuarternionB.k * QuarternionB.k);
			QuarternionR.w = (QuarternionB.w * QuarternionB.w);

			//setting MagResult to the square root of the sum of each term^2 in the quaternion
			MagResult = sqrt(QuarternionR.i + QuarternionR.j + QuarternionR.k + QuarternionR.w);

			//display Magnitude
			DisplayMagnitude(_hwnd);
			break;

		case IDC_BUTTON12: // A inv 
			//inverse = (q*) / (|q|^2)
			//finding the magnitude of quaternion a (same process as |a|)
			QuarternionR.i = (QuarternionA.i * QuarternionA.i);
			QuarternionR.j = (QuarternionA.j * QuarternionA.j);
			QuarternionR.k = (QuarternionA.k * QuarternionA.k);
			QuarternionR.w = (QuarternionA.w * QuarternionA.w);

			MagResult = sqrt(QuarternionR.i + QuarternionR.j + QuarternionR.k + QuarternionR.w);

			//MagResult^2
			MagResult = pow(MagResult, 2);

			//get the conjugate of quaternion A
			QuarternionTemp = QuarternionA.Conjugate();
			
			//divide each component of conjugate A by magresult (mag result has already been squared)
			QuarternionR.i = (QuarternionTemp.i / MagResult);
			QuarternionR.j = (QuarternionTemp.j / MagResult);
			QuarternionR.k = (QuarternionTemp.k / MagResult);
			QuarternionR.w = (QuarternionTemp.w / MagResult);

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON13: // B inv
			//getting magnitude of B
			QuarternionR.i = (QuarternionB.i * QuarternionB.i);
			QuarternionR.j = (QuarternionB.j * QuarternionB.j);
			QuarternionR.k = (QuarternionB.k * QuarternionB.k);
			QuarternionR.w = (QuarternionB.w * QuarternionB.w);

			MagResult = sqrt(QuarternionR.i + QuarternionR.j + QuarternionR.k + QuarternionR.w);

			//MagResult^2
			MagResult = pow(MagResult, 2);

			//get the conjugate of quaternion B
			QuarternionTemp = QuarternionB.Conjugate();

			//divide each component of conjugate B by magresult (mag result has already been squared)
			QuarternionR.i = (QuarternionTemp.i / MagResult);
			QuarternionR.j = (QuarternionTemp.j / MagResult);
			QuarternionR.k = (QuarternionTemp.k / MagResult);
			QuarternionR.w = (QuarternionTemp.w / MagResult);

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON14: // TA
			QuarternionR = QuarternionA * ConstantT;

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		case IDC_BUTTON15: // TB
			QuarternionR = QuarternionB * ConstantT;

			//display QuaternionR
			DisplayQauternionR(_hwnd);
			break;

		default:
			break;
		}

		return TRUE;
		break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK SLERPDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDC_BUTTON1:
			a = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT4), ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT2), ReadFromEditBox(_hwnd, IDC_EDIT3));
			b = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT8), ReadFromEditBox(_hwnd, IDC_EDIT5), ReadFromEditBox(_hwnd, IDC_EDIT6), ReadFromEditBox(_hwnd, IDC_EDIT7));
			CSlerpCalc::Slerp(a,b, ReadFromEditBox(_hwnd, IDC_EDIT9), res);
			WriteToEditBox(_hwnd, IDC_EDIT10, res.i);
			WriteToEditBox(_hwnd, IDC_EDIT11, res.j);
			WriteToEditBox(_hwnd, IDC_EDIT12, res.k);
			WriteToEditBox(_hwnd, IDC_EDIT13, res.w);
			break;
		case IDC_BUTTON2:
			a = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT4), ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT2), ReadFromEditBox(_hwnd, IDC_EDIT3));
			CSlerpCalc::ToMatrix(a, InducedMatrix);

			WriteToEditBox(_hwnd, IDC_EDIT34, InducedMatrix[0][0]);
			WriteToEditBox(_hwnd, IDC_EDIT35, InducedMatrix[0][1]);
			WriteToEditBox(_hwnd, IDC_EDIT36, InducedMatrix[0][2]);
			WriteToEditBox(_hwnd, IDC_EDIT37, InducedMatrix[0][3]);

			WriteToEditBox(_hwnd, IDC_EDIT38, InducedMatrix[1][0]);
			WriteToEditBox(_hwnd, IDC_EDIT39, InducedMatrix[1][1]);
			WriteToEditBox(_hwnd, IDC_EDIT40, InducedMatrix[1][2]);
			WriteToEditBox(_hwnd, IDC_EDIT41, InducedMatrix[1][3]);

			WriteToEditBox(_hwnd, IDC_EDIT42, InducedMatrix[2][0]);
			WriteToEditBox(_hwnd, IDC_EDIT43, InducedMatrix[2][1]);
			WriteToEditBox(_hwnd, IDC_EDIT44, InducedMatrix[2][2]);
			WriteToEditBox(_hwnd, IDC_EDIT45, InducedMatrix[2][3]);

			WriteToEditBox(_hwnd, IDC_EDIT46, InducedMatrix[3][0]);
			WriteToEditBox(_hwnd, IDC_EDIT47, InducedMatrix[3][1]);
			WriteToEditBox(_hwnd, IDC_EDIT48, InducedMatrix[3][2]);
			WriteToEditBox(_hwnd, IDC_EDIT49, InducedMatrix[3][3]);
			break;
		case IDC_BUTTON3:
			b = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT8), ReadFromEditBox(_hwnd, IDC_EDIT5), ReadFromEditBox(_hwnd, IDC_EDIT6), ReadFromEditBox(_hwnd, IDC_EDIT7));
			CSlerpCalc::ToMatrix(b, InducedMatrix);
			WriteToEditBox(_hwnd, IDC_EDIT34, InducedMatrix[0][0]);
			WriteToEditBox(_hwnd, IDC_EDIT35, InducedMatrix[0][1]);
			WriteToEditBox(_hwnd, IDC_EDIT36, InducedMatrix[0][2]);
			WriteToEditBox(_hwnd, IDC_EDIT37, InducedMatrix[0][3]);

			WriteToEditBox(_hwnd, IDC_EDIT38, InducedMatrix[1][0]);
			WriteToEditBox(_hwnd, IDC_EDIT39, InducedMatrix[1][1]);
			WriteToEditBox(_hwnd, IDC_EDIT40, InducedMatrix[1][2]);
			WriteToEditBox(_hwnd, IDC_EDIT41, InducedMatrix[1][3]);

			WriteToEditBox(_hwnd, IDC_EDIT42, InducedMatrix[2][0]);
			WriteToEditBox(_hwnd, IDC_EDIT43, InducedMatrix[2][1]);
			WriteToEditBox(_hwnd, IDC_EDIT44, InducedMatrix[2][2]);
			WriteToEditBox(_hwnd, IDC_EDIT45, InducedMatrix[2][3]);

			WriteToEditBox(_hwnd, IDC_EDIT46, InducedMatrix[3][0]);
			WriteToEditBox(_hwnd, IDC_EDIT47, InducedMatrix[3][1]);
			WriteToEditBox(_hwnd, IDC_EDIT48, InducedMatrix[3][2]);
			WriteToEditBox(_hwnd, IDC_EDIT49, InducedMatrix[3][3]);
			break;
		case IDC_BUTTON4:
			a = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT4), ReadFromEditBox(_hwnd, IDC_EDIT1), ReadFromEditBox(_hwnd, IDC_EDIT2), ReadFromEditBox(_hwnd, IDC_EDIT3));
			b = CQuaternionCalc::Quaternion(ReadFromEditBox(_hwnd, IDC_EDIT8), ReadFromEditBox(_hwnd, IDC_EDIT5), ReadFromEditBox(_hwnd, IDC_EDIT6), ReadFromEditBox(_hwnd, IDC_EDIT7));
			CSlerpCalc::Slerp(a, b, ReadFromEditBox(_hwnd, IDC_EDIT9), res);
			CSlerpCalc::ToMatrix(res, InducedMatrix);
			WriteToEditBox(_hwnd, IDC_EDIT34, InducedMatrix[0][0]);
			WriteToEditBox(_hwnd, IDC_EDIT35, InducedMatrix[0][1]);
			WriteToEditBox(_hwnd, IDC_EDIT36, InducedMatrix[0][2]);
			WriteToEditBox(_hwnd, IDC_EDIT37, InducedMatrix[0][3]);

			WriteToEditBox(_hwnd, IDC_EDIT38, InducedMatrix[1][0]);
			WriteToEditBox(_hwnd, IDC_EDIT39, InducedMatrix[1][1]);
			WriteToEditBox(_hwnd, IDC_EDIT40, InducedMatrix[1][2]);
			WriteToEditBox(_hwnd, IDC_EDIT41, InducedMatrix[1][3]);

			WriteToEditBox(_hwnd, IDC_EDIT42, InducedMatrix[2][0]);
			WriteToEditBox(_hwnd, IDC_EDIT43, InducedMatrix[2][1]);
			WriteToEditBox(_hwnd, IDC_EDIT44, InducedMatrix[2][2]);
			WriteToEditBox(_hwnd, IDC_EDIT45, InducedMatrix[2][3]);

			WriteToEditBox(_hwnd, IDC_EDIT46, InducedMatrix[3][0]);
			WriteToEditBox(_hwnd, IDC_EDIT47, InducedMatrix[3][1]);
			WriteToEditBox(_hwnd, IDC_EDIT48, InducedMatrix[3][2]);
			WriteToEditBox(_hwnd, IDC_EDIT49, InducedMatrix[3][3]);
			break;
		default:
			break;
		}

		return TRUE;
		break;

	}
	case WM_CLOSE:
	{
		ShowWindow(_hwnd, SW_HIDE);
		return TRUE;
		break;
	}
	default:
		break;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPSTR _lpCmdLine,
	int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd;           // Generic window handle.
	MSG msg;             // Generic message.

						 // First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground =
		static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	//Laod the Menu
	g_hMenu = LoadMenu(_hInstance, MAKEINTRESOURCE(IDR_MENU1));

	// create the window
	hwnd = CreateWindowEx(NULL, // Extended style.
		WINDOW_CLASS_NAME,      // Class.
		L"Your Basic Window",   // Title.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,                    // Initial x,y.
		400, 100,                // Initial width, height.
		NULL,                   // Handle to parent.
		g_hMenu,                   // Handle to menu.
		_hInstance,             // Instance of this application.
		NULL);                  // Extra creation parameters.

	if (!(hwnd))
	{
		return (0);
	}

	//Create the modeless dialog boxes for the calculators
	//Matrix Calculator
	g_hDlgMatrix = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogMatrix), hwnd, (DLGPROC)MatrixDlgProc);
	g_hDlgTransformation = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogTransformations), hwnd, (DLGPROC)TransformationDlgProc);
	g_hDlgGaussian = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogGaussian), hwnd, (DLGPROC)GaussianDlgProc);
	g_hDlgQuaternion = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogQuaternion), hwnd, (DLGPROC)QuaternionDlgProc);
	g_hDlgSLERP = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DialogSLERP), hwnd, (DLGPROC)SLERPDlgProc);

	// Enter main event loop
	while (true)
	{
		// Test if there is a message in queue, if so get it.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Test if this is a quit.
			if (msg.message == WM_QUIT)
			{
				break;
			}

			if ((g_hDlgMatrix == 0 && g_hDlgTransformation == 0 && g_hDlgGaussian == 0 && g_hDlgQuaternion == 0 && g_hDlgSLERP == 0) ||
				(!IsDialogMessage(g_hDlgMatrix, &msg) && !IsDialogMessage(g_hDlgTransformation, &msg) && !IsDialogMessage(g_hDlgGaussian, &msg) && !IsDialogMessage(g_hDlgQuaternion, &msg) && !IsDialogMessage(g_hDlgSLERP, &msg)))
			{
				// Translate any accelerator keys.
				TranslateMessage(&msg);
				// Send the message to the window proc.
				DispatchMessage(&msg);
			}
		}

		// Main game processing goes here.
		GameLoop(); //One frame of game logic occurs here...
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}


