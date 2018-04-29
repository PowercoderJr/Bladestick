#pragma once

#include "ITransformable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Point : public ITransformable
			{
			internal:
				double x;
				double y;
				double z;
				double w;
				double sx;
				double sy;
				double sz;
				double sw;

			public:
				Point(double x, double y, double z, double w, double sx, double sy, double sz, double sw);
				Point(double x, double y, double z, double w);
				Point(double x, double y, double z);
				Point(const Point %point);
				Point();
				double getX();
				void setX(double x);
				double getY();
				void setY(double y);
				double getZ();
				void setZ(double z);
				double getW();
				void setW(double w);
				double getSx();
				double getSy();
				double getSz();
				double getSw();
				Point operator= (Point point);
				Point ^ operator= (Point ^ point);
				Point ^ add(double x, double y, double z);
				Point ^ add(double x);
				Point ^ add(Point ^ point);
				Point ^ operator+ (double x);
				Point ^ operator+ (Point ^ point);
				Point ^ subtract(double x, double y, double z);
				Point ^ subtract(double x);
				Point ^ subtract(Point ^ point);
				Point ^ operator- (double x);
				Point ^ operator- (Point ^ point);
				Point ^ operator- ();
				Point ^ multiply(double x, double y, double z);
				Point ^ multiply(double x);
				Point ^ multiply(Point ^ point);
				Point ^ operator* (double x);
				Point ^ operator* (Point ^ point);
				Point ^ divide(double x, double y, double z);
				Point ^ divide(double x);
				Point ^ divide(Point ^ point);
				Point ^ operator/ (double x);
				Point ^ operator/ (Point ^ point);
			};
		}
	}
}
