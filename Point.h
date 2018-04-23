#pragma once

#include "ITransformable.h"

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
		Point ^ add(double x, double y, double z);
		Point ^ add(Point ^ point);
		Point ^ operator+ (Point ^ point);
	};
}
