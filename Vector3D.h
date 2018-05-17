#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		public ref class Vector3D
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
			Vector3D operator= (Vector3D vector);
			Vector3D ^ operator= (Vector3D ^ vector);
			Vector3D ^ add(double x, double y, double z);
			Vector3D ^ operator+ (double x);
			Vector3D ^ operator+ (Vector3D ^ vector);
			Vector3D ^ subtract(double x, double y, double z);
			Vector3D ^ operator- (double x);
			Vector3D ^ operator- (Vector3D ^ vector);
			Vector3D ^ operator- ();
			Vector3D ^ scale(double x, double y, double z);
			Vector3D ^ scale(double x);
			double getMagnitude();
			Vector3D ^ normalized();
		};
	}
}
