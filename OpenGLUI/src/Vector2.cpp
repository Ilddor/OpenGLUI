#include "stdafx.h"
#include "Vector2.h"
#include <cmath>
#define M_PI 3.14159265358979323846264338327
namespace glgui {

//=============================================================================== GLOBALNE

//-----------------------------------------------------------------------------
template<typename T>
CVector2<T> operator* (const CVector2<T>& a, const T b)
{
	return CVector2<T> (a.X * b, a.Y * b);
}
//-----------------------------------------------------------------------------
template<typename T>
CVector2<T> operator/ (const CVector2<T>& a, const T b)
{
	return CVector2<T> (a.X / b, a.Y / b);
}
//-----------------------------------------------------------------------------

}