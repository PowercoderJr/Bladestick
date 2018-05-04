#pragma once

#include "AbstractTransformable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Vector3D : public AbstractTransformable
			{
			internal:
				double x;
				double y;
				double z;
				double w;
				double mx;
				double my;
				double mz;
				double mw;

			public:
				Vector3D(double x, double y, double z, double w, double sx, double sy, double sz, double sw);
				Vector3D(double x, double y, double z, double w);
				Vector3D(double x, double y, double z);
				Vector3D(const Vector3D %vector);
				Vector3D();
				virtual void setPosition(double x, double y, double z) override;
				virtual void transform() override;
				/*virtual void scale(double a, double b, double c) override;
				virtual void rotate(double alphaDeg, double betaDeg, double gammaDeg) override;*/
				/*double getX();
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
				double getSw();*/
				Vector3D operator= (Vector3D vector);
				Vector3D ^ operator= (Vector3D ^ vector);
				Vector3D ^ add(double x, double y, double z);
				Vector3D ^ operator+ (double x);
				Vector3D ^ operator+ (Vector3D ^ vector);
				Vector3D ^ subtract(double x, double y, double z);
				Vector3D ^ operator- (double x);
				Vector3D ^ operator- (Vector3D ^ vector);
				Vector3D ^ operator- ();
				Vector3D ^ multiply(double x, double y, double z);
				Vector3D ^ operator* (double x);
				Vector3D ^ operator* (Vector3D ^ vector);
				Vector3D ^ divide(double x, double y, double z);
				Vector3D ^ operator/ (double x);
				Vector3D ^ operator/ (Vector3D ^ vector);
			};
		}
	}
}
