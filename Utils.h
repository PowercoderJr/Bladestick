#pragma once

namespace Bladestick
{
	static double degToRad(double deg)
	{
		return System::Math::PI / 180 * deg;
	}

	template <typename T> static void swap(T * a, T * b)
	{
		T h = *a;
		*a = *b;
		*b = h;
	}

	/*template <typename T> static void swap(T ^ a, T ^ b)
	{
		T h = *a;
		*a = *b;
		*b = h;
	}*/

	template <typename T> static void swap(array<T> ^ a, int i , int j)
	{
		T h = a[i];
		a[i] = a[j];
		a[j] = h;
	}

	static double cmpDoubles(double a, double b)
	{
		static const double epsilon = 0.00000001;
		return System::Math::Abs(a - b) > epsilon ? a - b : 0;
	}
}
