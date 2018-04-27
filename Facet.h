#pragma once

#include "Point.h"
#include "IDrawable.h"

namespace Geometry
{
	public ref class Facet : public ITransformable, public IDrawable
	{
	internal:
		array<Point^> ^ vertices;  //3 вершины
		System::Drawing::Color color;

	public:
		static const int N_VERTICES = 3;
		Facet(array<Point^> ^ vertices, System::Drawing::Color color);
		Facet(array<Point^> ^ vertices);
		Facet(Point ^ p1, Point ^ p2, Point ^ p3);
		Facet();
		virtual void draw(Bladestick::ZBuffer ^ buffer);
		array<Point^> ^ getVertices();
		void setVertices(array<Point^> ^ vertices);
		System::Drawing::Color getColor();
		void setColor(System::Drawing::Color color);
	};
}
