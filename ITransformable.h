#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			ref class Vector3D;

			public interface class ITransformable
			{
			public:
				void move(double x, double y, double z);
				void scale(double a, double b, double c);
				void rotate(double alphaDeg, double betaDeg, double gammaDeg);
				/*void move(double x, double y, double z);
				void move(Vector3D ^ offset) : move(offset->x, offset->y, offset->z);
				void scale(double a, double b, double c);
				void scale(Vector3D ^ koefs);
				void rotate(double alpha, double beta, double gamma);*/
			};
		}
	}
}
