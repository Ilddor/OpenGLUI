#include "Vector2.h"

namespace glui
{

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

}