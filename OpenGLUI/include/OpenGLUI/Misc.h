// misc.h
#pragma once
#include "Typedefs.h"

namespace glgui {

#ifndef M_PI
#define M_PI					= 3.14159265358979323846264338327;
#endif
const float DESIRED_DELTA		= 0.0166667f;
const long double DEGREE_TO_RAD	= 0.01745329251994329576923690;//768489
const long double RAD_TO_DEGREE	= 57.295779513082320876798154;//814105

//---------------------------------------------------------------------
inline int Rnd (float f);
inline float DotPart (float f);
inline float Average (float a, float b);
int Random (int range_min, int range_max);

template<class T>
inline T Sqre(const T A)
{
	return A*A;
}

template<typename T>
inline bool IsPointInRec (const CVector2<T>& point, const CVector2<T>& recStart, const CVector2<T>& recSize)
{
	if (point.X >= recStart.X && point.X <= recStart.X+recSize.X 
		&& point.Y >= recStart.Y && point.Y <= recStart.Y+recSize.Y)
	{
		return true;
	}
	return false;
}

/// Clampuje value do zakresu <a, b>
template<typename T>
inline T Range(T value, T a, T b)
{
	if (value<a)
		value=a;
	if (value>b)
		value=b;
	return value;
}

// From wiki: fast inverse sqrt
inline float InvSqrt(const float Number)
{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;
 
		x2 = Number * 0.5F;
		y  = Number;
		i  = * ( long * ) &y;                       // evil floating point bit level hacking [sic]
		i  = 0x5f3759df - ( i >> 1 );               // what the fuck? [sic]
		y  = * ( float * ) &i;
		y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//    y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
 
		return y;
}

float odl_od1_do2 (float X1, float Y1, float X2, float Y2);
float kat_od1_do2 (float X1, float Y1, float X2, float Y2);

std::string ToLower (const std::string& in);

}
