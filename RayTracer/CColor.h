// Author : Jean-Rene Bedard (jrbedard@gmail.com)

#pragma once

#include <math.h>

class CColor
{
public:
	float r, g, b;

	inline CColor() { }
	inline CColor(float a)                   { r = a; g = a; b = a; }
	inline CColor(float i,float j,float k)   { r = i; g = j; b = k; }

	// set
	void inline set(float a)                 { r = a; g = a; b = a; }
	void inline set(float i,float j,float k) { r = i; g = j; b = k; }
	void inline set(CColor &a)               { r = a.r; g = a.g; b = a.b; }
	
	// operators overloading
	float inline operator!()                 { return sqrtf(r * r + g * g + b * b); }
	CColor inline operator|(float a)         { return *this * (a / !*this); }
	void inline operator|=(float a)          { *this = *this | a; }
	CColor inline operator=(float a)         { return CColor(a,a,a); }
	CColor inline operator+(float a)         { return CColor(r + a,g + a,b + a); }
	CColor inline operator-(float a)         { return CColor(r - a,g - a,b - a); }
	CColor inline operator*(float a)         { return CColor(r * a,g * a,b * a); }
	CColor inline operator/(float a)         { a = 1.0f / a; return *this * a; }
	CColor inline operator+(CColor &a)       { return CColor(r + a.r,g + a.g,b + a.b); }
	CColor inline operator-(CColor &a)       { return CColor(r - a.r,g - a.g,b - a.b); }
	CColor inline operator*(CColor &a)       { return CColor(r * a.r,g * a.g,b * a.b); }
	CColor inline operator/(CColor &a)       { return CColor(r / a.r,g / a.g,b / a.b); }
	void inline operator=(CColor &a)         { r = a.r; g = a.g; b = a.b; }
	void inline operator+=(float a)          { r += a; g += a; b += a; }
	void inline operator-=(float a)          { r -= a; g -= a; b -= a; }
	void inline operator*=(float a)          { r *= a; g *= a; b *= a; }
	void inline operator/=(float a)          { a = 1.0f / a; r *= a; g *= a; b *= a; }
	void inline operator+=(CColor &a)        { r += a.r; g += a.g; b += a.b; }
	void inline operator-=(CColor &a)        { r -= a.r; g -= a.g; b -=a.b; }
	void inline operator*=(CColor &a)        { r *= a.r; g *= a.g; b *= a.b; }
	void inline operator/=(CColor &a)        { r /= a.r; g /= a.g; b /= a.b; }
};