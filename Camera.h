#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;
		public ref class Camera
		{
		internal:
			Vector3D ^ position;
			Vector3D ^ target;
			Vector3D ^ backDir;
			Vector3D ^ rightDir;
			Vector3D ^ upDir;
			double near;
			double far;
			double fov;
			bool perspective;

		public:
			Camera(Vector3D ^ position, Vector3D ^ target, double near, double far, double fov, bool perspective);
			void setPosition(double x, double y, double z);
			void setPosition(Vector3D ^ position);
			void setTarget(double x, double y, double z);
			void setTarget(Vector3D ^ target);
			void updateDirs();
		};
	}
}
