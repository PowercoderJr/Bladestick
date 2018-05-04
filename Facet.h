#pragma once

#include "Vector3D.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Facet : public AbstractTransformable, public IDrawable
			{
			internal:
				array<Vector3D^> ^ vertices;  //3 �������
				System::Drawing::Color ^ color;

			public:
				static const int N_VERTICES = 3;
				Facet(array<Vector3D^> ^ vertices, System::Drawing::Color ^ color);
				Facet(array<Vector3D^> ^ vertices);
				Facet(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, System::Drawing::Color ^ color);
				Facet(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3);
				Facet();
				virtual void draw(ZBuffer ^ buffer);
				virtual void setPosition(double x, double y, double z) override;
				virtual void setOrigin(double x, double y, double z) override;
				virtual void setScalingFactors(double a, double b, double c) override;
				virtual void setRotationAngles(double alphaDeg, double betaDeg, double gammaDeg) override;
				virtual void transform() override;
				/*virtual void scale(double a, double b, double c) override;
				virtual void rotate(double alphaDeg, double betaDeg, double gammaDeg) override;*/
				array<Vector3D^> ^ getVertices();
				void setVertices(array<Vector3D^> ^ vertices);
				System::Drawing::Color ^ getColor();
				void setColor(System::Drawing::Color ^ color);
			};
		}
	}
}
