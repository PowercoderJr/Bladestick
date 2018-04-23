#pragma once

#include "Point.h"

namespace Geometry
{
	public ref class Facet : public ITransformable
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
		array<Point^> ^ getVertices();
		void setVertices(array<Point^> ^ vertices);
		System::Drawing::Color getColor();
		void setColor(System::Drawing::Color color);
	};
}
