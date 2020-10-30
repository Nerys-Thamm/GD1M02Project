#include "CSlerpCalc.h"

//Class for SLERP calculations


//Nerys
void CSlerpCalc::Slerp(CQuaternionCalc::Quaternion a, CQuaternionCalc::Quaternion b, double t, CQuaternionCalc::Quaternion& res) 
{


    a.Normalise(); //Normalise both quaternions
    b.Normalise();


    double dotproduct = ((a.i * b.i) + (a.j * b.j) + (a.k * b.k) + (a.w * b.w)); //Get the dot product
    
    double angle = cos(dotproduct); //Find the angle between them

    angle = (angle < 0 ? -angle : angle); //Invert the angle if its negative

    double sine = sin(angle); //Find the sine of the angle

    

    double Wa, Wb;

    Wa = sin((1 - t) * angle) / sine; //find the angle between quaternion a and t
    Wb = sin(t * angle) / sine; //find the angle between quaternion b and t

    res = a * Wa + b * Wb; //Generate the result

    res.Normalise(); //Normalise the result
    

}


//Dunstan
void CSlerpCalc::ToMatrix(CQuaternionCalc::Quaternion quaternion, float(&ResultMatrix)[4][4]) //Generate a rotation matrix from the quaternion
{
    ResultMatrix[0][0] = 1 - 2 * (quaternion.j * quaternion.j + quaternion.k * quaternion.k);
    ResultMatrix[1][0] = 2 * (quaternion.i * quaternion.j - quaternion.w * quaternion.k);
    ResultMatrix[2][0] = 2 * (quaternion.i * quaternion.k + quaternion.w * quaternion.j);
    ResultMatrix[3][0] = 0;


    ResultMatrix[0][1] = 2 * (quaternion.i * quaternion.j + quaternion.w * quaternion.k);
    ResultMatrix[1][1] = 1 - 2 * (quaternion.i * quaternion.i + quaternion.k * quaternion.k);
    ResultMatrix[2][1] = 2 * (quaternion.j * quaternion.k - quaternion.w * quaternion.i);
    ResultMatrix[3][1] = 0;

    ResultMatrix[0][2] = 2 * (quaternion.i * quaternion.k - quaternion.w * quaternion.j);
    ResultMatrix[1][2] = 2 * (quaternion.j * quaternion.k + quaternion.w * quaternion.i);
    ResultMatrix[2][2] = 1 - 2 * (quaternion.i * quaternion.i + quaternion.j * quaternion.j);
    ResultMatrix[3][2] = 0;

    ResultMatrix[0][3] = 0;
    ResultMatrix[1][3] = 0;
    ResultMatrix[2][3] = 0;
    ResultMatrix[3][3] = 1;
} 


