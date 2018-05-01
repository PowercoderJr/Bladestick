#pragma once

#include "Facet.h"
#include "IUpdatable.h"
#include "ZBuffer.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Box : public AbstractTransformable, public IUpdatable, public IDrawable
			{
			internal:
				Vector3D ^ corner1;
				Vector3D ^ corner2;
				array<Vector3D^> ^ vertices;  //8 вершин
				array<Facet^> ^ facets;  //12 треугольников
				double width;
				double length;
				double height;
				System::Drawing::Color ^ color;

			public:
				static const int N_VERTICES = 8;
				static const int N_FACETS = 12;

				Box(Vector3D ^ bottomCenter, double width, double length, double height, System::Drawing::Color ^ color);
				Box(Vector3D ^ corner1, Vector3D ^ corner2, System::Drawing::Color ^ color);
				virtual void update();
				virtual void draw(Bladestick::Drawing::ZBuffer ^ buffer);
				virtual void move(double x, double y, double z) override;
				virtual void scale(double a, double b, double c) override;
				virtual void rotate(double alphaDeg, double betaDeg, double gammaDeg) override;
				void updatePoints();
				void updateFacets();
				double getWidth();
				void setWidth(double width);
				double getLength();
				void setLength(double length);
				double getHeight();
				void setHeight(double height);
				array<Vector3D^> ^ getVertices();
				array<Facet^> ^ getFacets();
			};
		}
	}
}
