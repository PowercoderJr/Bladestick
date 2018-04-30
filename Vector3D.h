#pragma once

#include "ITransformable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Vector3D : public ITransformable
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
				Vector3D(double x, double y, double z, double w, double sx, double sy, double sz, double sw);
				Vector3D(double x, double y, double z, double w);
				Vector3D(double x, double y, double z);
				Vector3D(const Vector3D %vector);
				Vector3D();
				virtual void move(double x, double y, double z);
				virtual void scale(double a, double b, double c);
				virtual void rotate(double alphaDeg, double betaDeg, double gammaDeg);
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
				Vector3D operator= (Vector3D vector);
				Vector3D ^ operator= (Vector3D ^ vector);
				Vector3D ^ add(double x, double y, double z);
				/*Vector3D ^ add(double x);
				Vector3D ^ add(Vector3D ^ vector);*/
				Vector3D ^ operator+ (double x);
				Vector3D ^ operator+ (Vector3D ^ vector);
				Vector3D ^ subtract(double x, double y, double z);
				/*Vector3D ^ subtract(double x);
				Vector3D ^ subtract(Vector3D ^ vector);*/
				Vector3D ^ operator- (double x);
				Vector3D ^ operator- (Vector3D ^ vector);
				Vector3D ^ operator- ();
				Vector3D ^ multiply(double x, double y, double z);
				/*Vector3D ^ multiply(double x);
				Vector3D ^ multiply(Vector3D ^ vector);*/
				Vector3D ^ operator* (double x);
				Vector3D ^ operator* (Vector3D ^ vector);
				Vector3D ^ divide(double x, double y, double z);
				/*Vector3D ^ divide(double x);
				Vector3D ^ divide(Vector3D ^ vector);*/
				Vector3D ^ operator/ (double x);
				Vector3D ^ operator/ (Vector3D ^ vector);
			};
		}
	}
}
