#pragma once

#include <math.h>

class Vector {
public:

	// constructors
	Vector();
	Vector(const float &x, const float &y, const float &z = 0.0);

	// accessors
	float GetLength();
	void Normalize();

	// data members
	float x;
	float y;
	float z;

};



class Matrix {
public:

	// constructor
	Matrix();

	union {
		float m[4][4];
		float ml[16];
	};

	void GenerateIdentity();
	Matrix GetInverse();

	Vector operator * (const Vector &v2);
	Matrix operator * (const Matrix &m2);

};

