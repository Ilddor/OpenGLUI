#pragma once
namespace glui
{
	template <typename T>
	class Vector2
	{
	public:
		T X;
		T Y;

		Vector2<T> operator+(Vector2<T>& a);
		Vector2<T> operator-(Vector2<T>& a);
		void operator+=(Vector2<T>& a);
		void operator-=(Vector2<T>& a);
		void operator*(T a);
		void operator/(T a);

		Vector2(T x, T y)
		{
			X = x;
			Y = y;
		}

		Vector2()
		{
			X = 0;
			Y = 0;
		}

		~Vector2()
		{
		}
	};
}