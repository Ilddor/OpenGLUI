#pragma once
#include <istream>
#include <ostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327
#endif

namespace glgui {

/*! \class CVector2
* \brief Vector class
*
*	Class used to store the point coordinates
*/
template<typename T>
class CVector2
{
public:
	T X;		//!< \public X coordinate of the vector
	T Y;		//!< \public Y coordinate of the vector

	void operator() (T x, T y)				{ X = x; Y = y; }		//!< \public Overloaded operator
	void operator+= (const CVector2<T>& a)	{ X+=a.X; Y+=a.Y; }		//!< \public Overloaded operator
	void operator-= (const CVector2<T>& a)	{ X-=a.X; Y-=a.Y; }		//!< \public Overloaded operator
	void operator*= (const CVector2<T>& a)	{ X*=a.X; Y*=a.Y; }		//!< \public Overloaded operator
	void operator*= (const T a)				{ X*=a; Y*=a; }			//!< \public Overloaded operator
	void operator/= (const CVector2<T>& a)	{ X/=a.X; Y/=a.Y; }		//!< \public Overloaded operator
	void operator/= (const T a)				{ X/=a; Y/=a; }			//!< \public Overloaded operator
	void operator= (const CVector2<T>& a)	{ X = a.X; Y = a.Y; }	//!< \public Overloaded operator

	void Normalize ()
	{
		if (X == 0 && Y == 0)
			return;
		//T Length= std::sqrt(X*X+Y*Y);
		T InvLength=InvSqrt((X*X)+(Y*Y));
		X *= InvLength;
		Y *= InvLength;
	}	//!< \public Function used to normalize vector

	/*! \fn T DistanceTo(const CVector2<T>& a)
	*	\brief Calculate the distance to other vector
	*	\param a Const reference of other vector
	*	\return T Distance between vectors
	*/
	template<typename T>
	T DistanceTo (const CVector2<T>& a) const
	{
		T TempX = abs(X - a.X);
		T TempY = abs(Y - a.Y);

		return sqrtf((TempX * TempX) + (TempY * TempY));
	}

	/*! \fn float HeadingTo(const CVector2<T>& a)
	*	\brief Calculate the angle of vector between two points relative to the coordinate system
	*	\param a Const reference of other vector
	*	\return float Angle
	*/
	template<typename T>
	float HeadingTo (const CVector2<T>& a) const
	{
		float l;

		if (X == a.X)
		{
		 if (a.Y < Y)
			 return 0.0f;     
		 else
			 return 180.0f;
		}

		if (Y == a.Y)
		{
		 if (a.X < X)
			 return 270.0f;     
		 else
			 return 90.0f;
		}

		l = atan2f ( (a.Y-Y), (a.X-X) );
		l *= (180.0f/M_PI);
		l += 90.0f;
		if (l<0) l += 360.0f;
		   
		return l;
	}

	/*! \fn CVector2<T> GetZero()
	*	\brief Function to get zero vector
	*	\return CVector2<T> Zero Vector
	*/
	static CVector2<T> GetZero() { return CVector2<T>(0, 0); }

	CVector2() : X(0), Y(0) { }				//!< \public Default constructor
	CVector2(T x, T y) : X(x), Y(y) { }		//!< \public Costructor with initial values
};
//-----------------------------------------------------------------------------
template<typename T>
CVector2<T> operator+ (const CVector2<T>& a, const CVector2<T>& b)
{
	return CVector2<T> (a.X+b.X, a.Y+b.Y);
}
template<typename T>
CVector2<T> operator- (const CVector2<T>& a, const CVector2<T>& b)
{
	return CVector2<T> (a.X-b.X, a.Y-b.Y);
}

template<typename T>
CVector2<T> operator- (const CVector2<T>& a, const CVector2<T>& b);
template<typename T>
CVector2<T> operator* (const CVector2<T>& a, const T b);
template<typename T>
CVector2<T> operator/ (const CVector2<T>& a, const T b);

template<typename T>
bool operator!= (const CVector2<T>& a, const CVector2<T>& b)
{
	if ((a.X != b.X) || (a.Y != b.Y))
		return true;
	return false;
}
template<typename T>
bool operator== (const CVector2<T>& a, const CVector2<T>& b)
{
	if ((a.X != b.X) || (a.Y != b.Y))
		return false;
	return true;
}


template<typename T>
std::istream& operator>> (std::istream& str, CVector2<T>& a) { str >> a.X >> a.Y; return str; }
template<typename T>
std::ostream& operator<< (std::ostream& str, const CVector2<T>& a) { str << a.X << a.Y; return str; }

}
