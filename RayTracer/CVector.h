// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once

#include <math.h>

class CVector
{
public:
	
	union
	{
		float v[3];

		struct
		{
			float x, y, z;
		};
	};

	CVector() { }
	inline CVector(float a)						{ x = a; y = a; z = a; }
	inline CVector(float i,float j,float k)		{ x = i; y = j; z = k; }

	// set
	void inline set(float a)					{ x = a; y = a; z = a; }
	void inline set(float i,float j,float k)	{ x = i; y = j; z = k; }

	// operators overloading
	CVector inline operator-()				{ return CVector(-x,-y,-z); }
	float inline operator!()				{ return sqrtf(x * x + y * y + z * z); }
	CVector inline operator|(float a)		{ return *this * (a / !*this); }
	void inline operator|=(float a)			{ *this = *this | a; }
	float inline operator*(CVector &a)		{ return x * a.x + y * a.y + z * a.z; }
	CVector inline operator=(float a)		{ return CVector(a,a,a); }
	CVector inline operator+(float a)       { return CVector(x + a,y + a,z + a); }
	CVector inline operator-(float a)       { return CVector(x - a,y - a,z - a); }
	CVector inline operator*(float a)		{ return CVector(x * a,y * a,z * a); }
	CVector inline operator^(CVector &a)	{ return CVector(a.y * z - y * a.z,a.z * x - z * a.x,a.x * y - x * a.y); }
	CVector inline operator/(float a)       { a = 1.0f / a; return CVector(x * a,y * a,z * a); }
	CVector inline operator+(CVector &a)    { return CVector(x + a.x,y + a.y,z + a.z); }
	CVector inline operator-(CVector &a)    { return CVector(x - a.x,y - a.y,z - a.z); }
	void inline operator=(CVector &a)       { x = a.x; y = a.y; z = a.z; }
	void inline operator+=(float a)         { x += a; y += a; z += a; }
	void inline operator-=(float a)         { x -= a; y -= a; z -= a; }
	void inline operator*=(float a)         { x *= a; y *= a; z *= a; }
	void inline operator/=(float a)         { a = 1.0f / a; x *= a; y *= a; z *= a; }
	void inline operator+=(CVector &a)      { x += a.x; y += a.y; z += a.z; }
	void inline operator-=(CVector &a)      { x -= a.x; y -= a.y; z -=a.z; }

};
