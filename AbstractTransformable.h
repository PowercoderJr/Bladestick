#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			ref class Vector3D;

			public ref class AbstractTransformable abstract
			{
			internal:
				double xOrigin;
				double yOrigin;
				double zOrigin;
				double xOffset;
				double yOffset;
				double zOffset;
				double xScaling;
				double yScaling;
				double zScaling;
				double xRotationDeg;
				double yRotationDeg;
				double zRotationDeg;

			public:
				AbstractTransformable();
				virtual void move(double x, double y, double z) abstract;
				virtual void scale(double a, double b, double c) abstract;
				virtual void rotate(double alphaDeg, double betaDeg, double gammaDeg) abstract;
				/*void move(double x, double y, double z);
				void move(Vector3D ^ offset) : move(offset->x, offset->y, offset->z);
				void scale(double a, double b, double c);
				void scale(Vector3D ^ koefs);
				void rotate(double alpha, double beta, double gamma);*/
				void setOrigin(Vector3D ^ origin);
			};
		}
	}
}
