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

#include "utils.h"
#include "resource.h"
#include "CMatrixCalc.h"
#include "CQuaternionCalc.h"

#define WINDOW_CLASS_NAME L"WINCLASS1"

HMENU g_hMenu;
HWND g_hDlgMatrix, g_hDlgTransformation, g_hDlgGaussian, g_hDlgQuaternion, g_hDlgSLERP;

//matrix calculator
float matrixA[4][4], matrixB[4][4], resultantMat[4][4], TempMatrix[4][4];
float AScale, BScale;
float tempValue;

//quarternion calculator


CQuaternionCalc::Quaternion QuarternionA;
CQuaternionCalc::Quaternion QuarternionB;
CQuaternionCalc::Quaternion QuarternionR;

double ConstantT = 0;

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
			break;
		}
		case IDCANCEL3: //Inverse B
		{
			CMatrixCalc::Inverse(matrixB);
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
			break;
		}
		case IDOK6: // A * scalar
		{
			CMatrixCalc::Multiply(matrixA, AScale);
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
			break;
		}
		case IDOK10: // B * scalar
		{
			
			CMatrixCalc::Multiply(matrixB, BScale);
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
			break;
		}

		case IDOK9: // A Transpose
		{
			
			CMatrixCalc::Transpose(matrixA);
			

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
			break;
		}
		case IDOK11: // b Transpose
		{
			CMatrixCalc::Transpose(matrixB);

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
			break;
		}
		case IDOK4: // A = I
		{
			CMatrixCalc::SetIdentity(matrixA);

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
			break;
		}
		case IDOK8: // B = I
		{
			CMatrixCalc::SetIdentity(matrixB);

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
			break;
		}
		case IDOK: // A + B
		{ 
			
			CMatrixCalc::Add(matrixA, matrixB, resultantMat);

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
			break;
		}
		case IDCANCEL: // A - B
		{
			CMatrixCalc::Subtract(matrixA, matrixB, resultantMat);

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
			break;
		}
		case IDOK2: // A * B
		{
			CMatrixCalc::Multiply(matrixA, matrixB, resultantMat);
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
			break;
		}
		case IDOK5: // B * A
		{
			CMatrixCalc::Multiply(matrixB, matrixA, resultantMat);
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
		{

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
		switch (LOWORD(_wparam))
		{

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
			break;

		case IDC_BUTTON5: // A-B
			QuarternionR = QuarternionA - QuarternionB;
			break;

		case IDC_BUTTON6: // B-A
			QuarternionR = QuarternionB - QuarternionA;
			break;

		case IDC_BUTTON2: // AB
			QuarternionR = QuarternionA * QuarternionB;
			break;

		case IDC_BUTTON7: // BA
			QuarternionR = QuarternionB * QuarternionA;
			break;

		case IDC_BUTTON8: // A dot B

			break;

		case IDC_BUTTON3: // A*
			QuarternionR = QuarternionA.Conjugate();
			break;

		case IDC_BUTTON9: // B*
			QuarternionR = QuarternionB.Conjugate();
			break;

		case IDC_BUTTON10: // |A|

			break;

		case IDC_BUTTON11: // |B|

			break;

		case IDC_BUTTON12: // A inv

			break;

		case IDC_BUTTON13: // B inv

			break;

		case IDC_BUTTON14: // TA
			QuarternionR = QuarternionA * ConstantT;
			break;

		case IDC_BUTTON15: // TB
			QuarternionR = QuarternionB * ConstantT;
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


