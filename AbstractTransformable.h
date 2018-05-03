#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			ref class Vector3D;

			//TODO: разделить origin на относительный и абсолютный
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
				virtual void transform() abstract;
				/*virtual void setOffsets(double x, double y, double z) abstract;
				void setOffsets(Vector3D ^ offsets);*/
				//virtual void setScalingFactors(double a, double b, double c, double xOrigin, double yOrigin, double zOrigin) abstract;
				virtual void setScalingFactors(double a, double b, double c);
				//void setScalingFactors(Vector3D ^ factors, Vector3D ^ origin);
				void setScalingFactors(Vector3D ^ factors);
				//void setRotationAngles(double alphaDeg, double betaDeg, double gammaDeg, double xOrigin, double yOrigin, double zOrigin);
				virtual void setRotationAngles(double alphaDeg, double betaDeg, double gammaDeg);
				//void setRotationAngles(Vector3D ^ angles, Vector3D ^ origin);
				void setRotationAngles(Vector3D ^ angles);
				virtual void setOrigin(double x, double y, double z);
				void setOrigin(Vector3D ^ origin);
			};
		}
	}
}
