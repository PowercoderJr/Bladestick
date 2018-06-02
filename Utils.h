#pragma once

namespace Bladestick
{
	static double degToRad(double deg)
	{
		return System::Math::PI / 180 * deg;
	}

	static double radToDeg(double rad)
	{
		return 180 * rad / System::Math::PI;
	}

	template <typename T> static void swap(T * a, T * b)
	{
		T h = *a;
		*a = *b;
		*b = h;
	}

	static double cmpDoubles(double a, double b)
	{
		static const double epsilon = 0.00001;
		return System::Math::Abs(a - b) > epsilon ? a - b : 0;
	}
}
