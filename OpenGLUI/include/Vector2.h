#pragma once
namespace glui
{
	template <typename T>
	class Vector2
	{
	public:
		T X;
		T Y;

		Vector2<T> operator+(const Vector2<T>& a)
		{
			return Vector2<T>(X+a.X, Y+a.Y);
		}
		Vector2<T> operator-(const Vector2<T>& a)
		{
			return Vector2<T>(X-a.X, Y-a.Y);
		}
		void operator+=(const Vector2<T>& a)
		{
			X += a.X;
			Y += a.Y;
		}
		void operator-=(const Vector2<T>& a)
		{
			X -= a.X;
			Y -= a.Y;
		}
		void operator*(const T a);
		void operator/(const T a);

		bool operator<=(const Vector2<T>& a) { return (X <= a.X && Y <= a.Y); };
		bool operator>=(const Vector2<T>& a) { return (X >= a.X && Y >= a.Y); };

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