#pragma once

#include "Facet.h"
#include "IUpdatable.h"
#include "IDrawable.h"

namespace Geometry
{
	public ref class Cylinder : public ITransformable, public IUpdatable, public IDrawable
	{
	internal:
		Point ^ bottomCenter;
		Point ^ topCenter;
		double exRadius;
		double height;
		array<Point^> ^ exBottomPoints;		//36 точек нижней окружности
		array<Point^> ^ exTopPoints;		//36 точек верхней окружности
		array<Facet^> ^ exFacets;			//72 внешние боковые грани
		array<Facet^> ^ topCircleFacets;	//36(72?) грани оснований
		array<Facet^> ^ bottomCircleFacets;	//36(72?) грани оснований

	public:
		static const int N_CIRCLE_POINTS = 36;
		static const int N_CIRCLE_FACETS = 36;
		static const int N_SIZE_FACETS = 72;

		Cylinder(Point ^ bottomCenter, double exRadius, double height);
		virtual void update() override;
		virtual void updatePoints();
		virtual void updateFacets();
		Point ^ getBottomCenter();
		void setBottomCenter(Point ^ bottomCenter);
		Point ^ getTopCenter();
		void setTopCenter(Point ^ topCenter);
		double getExRadius();
		void setExRadius(double exRadius);
		double getHeight();
		void setHeight(double height);
		array<Point^> ^ getExBottomPoints();
		array<Point^> ^ getExTopPoints();
		array<Facet^> ^ getExFacets();
		array<Facet^> ^ getTopCircleFacets();
		array<Facet^> ^ getBottomCircleFacets();
	};
}
