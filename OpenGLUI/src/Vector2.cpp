#include "Vector2.h"

namespace glui
{

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& a)
{
	return Vector2<T>(X+a.X, Y+a.Y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& a)
{
	return Vector2<T>(X-a.X, Y-a.Y);
}

template <typename T>
void Vector2<T>::operator+=(const Vector2<T>& a)
{
	X += a.X;
	Y += a.Y;
}

template <typename T>
void Vector2<T>::operator-=(const Vector2<T>& a)
{
	X -= a.X;
	Y -= a.Y;
}

template <typename T>
void Vector2<T>::operator*(const T a)
{
	X *= a;
	Y *= a;
}

template <typename T>
void Vector2<T>::operator/(const T a)
{
	X /= a;
	Y /= a;
}

template <typename T>
bool Vector2<T>::operator<=(const Vector2<T>& a)
{
	return (X <= a.X && Y <= a.Y);
}

template <typename T>
bool Vector2<T>::operator>=(const Vector2<T>& a)
{
	return (X >= a.X && Y >= a.Y);
}

}