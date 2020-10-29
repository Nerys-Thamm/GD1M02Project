#pragma once
#include <math.h>
//Quaternion  calculator class by Nerys :D  && Dunstan :D
//Overloads operators when working with wacky 4D stuff
class CQuaternionCalc
{
public:
	struct Quaternion // [Nerys]
	{
		Quaternion(double w, double i, double j, double k) //Constructor
			: w(w), i(i), j(j), k(k) {}
		Quaternion(Quaternion& Copy) //Copy Constructor
			: w(Copy.w), i(Copy.i), j(Copy.j), k(Copy.k) {} 


		double w; //The real component :)

		double i; //The imaginary component :D
		double j;
		double k;


		//QUATERNION + QUATERNION [Nerys]
		Quaternion operator+(const Quaternion& other) //Overloading addition operator
		{
			Quaternion q(this->w + other.w, this->i + other.i, this->j + other.j, this->k + other.k); //Add all components respectively
			return q;
		};

		//QUATERNION - QUATERNION [Nerys]
		Quaternion operator-(const Quaternion& other) //Overloading subtraction operator
		{
			Quaternion q(this->w - other.w, this->i - other.i, this->j - other.j, this->k - other.k); //Subtract all components respectively
			return q;
		};

		//QUATERNION * QUATERNION [Nerys]
		Quaternion operator*(const Quaternion& other) //Overloading Multiplication operator
		{
			Quaternion q(((-this->i * other.i) - (this->j * other.j) - (this->k * other.k) + (this->w * other.w)),
				          ((this->i * other.w) + (this->j * other.k) - (this->k * other.j) + (this->w * other.i)),
				         ((-this->i * other.k) + (this->j * other.w) + (this->k * other.i) + (this->w * other.j)), 
				          ((this->i * other.j) - (this->j * other.i) + (this->k * other.w) + (this->w * other.k)));
			return q;
		};

		//QUATERNION * DOUBLE [Nerys]
		Quaternion operator*(const double& T) //Overloading Multiplication operator
		{
			Quaternion q(this->w * T, this->i * T, this->j * T, this->k * T); //Multiply everything by a number
			return q;
		};

		//CONJUGATE OF QUATERNION [Nerys]
		Quaternion Conjugate()
		{
			Quaternion q(this->w, this->i*-1, this->j*-1, this->k*-1); //Invert that imaginary component! :D
			return q;
		};
		
		void Normalise()
		{
			double norm = sqrt(w * w + i * i + j * j + k * k);
			i /= norm;
			j /= norm;
			k /= norm;
			w /= norm;
		}
		
	};

	

private:
};
	

