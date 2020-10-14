#pragma once
class CQuaternionCalc
{
public:
	struct Quaternion
	{
		Quaternion(double w, double i, double j, double k)
			: w(w), i(i), j(j), k(k) {}
		Quaternion(Quaternion& Copy)
			: w(Copy.w), i(Copy.i), j(Copy.j), k(Copy.k) {}
		double w;
		double i;
		double j;
		double k;

		Quaternion operator+(const Quaternion& other)
		{
			Quaternion q(this->w + other.w, this->i + other.i, this->j + other.j, this->k + other.k);
			return q;
		};
		Quaternion operator-(const Quaternion& other)
		{
			Quaternion q(this->w - other.w, this->i - other.i, this->j - other.j, this->k - other.k);
			return q;
		};
		Quaternion operator*(const Quaternion& other)
		{
			Quaternion q(this->w - other.w, this->i - other.i, this->j - other.j, this->k - other.k);
			return q;
		};
		Quaternion operator*(const double& T)
		{
			Quaternion q(this->w *= T, this->i *= T, this->j *= T, this->k *= T);
			return q;
		};
		Quaternion Conjugate()
		{
			Quaternion q(this->w, this->i*-1, this->j*-1, this->k*-1);
			return q;
		};
		
		
	};

	

};
	

