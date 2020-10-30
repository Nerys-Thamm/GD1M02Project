#include "CMatrixCalc.h"
#include "CQuaternionCalc.h"

#pragma once
class CSlerpCalc
{
public:
	static void Slerp(CQuaternionCalc::Quaternion a, CQuaternionCalc::Quaternion b, double t, CQuaternionCalc::Quaternion& res);

	static void ToMatrix(CQuaternionCalc::Quaternion quaternion, float(&ResultMatrix)[4][4]);

};

