#pragma once

#include "Facet.h"
#include "IUpdatable.h"
#include "IDrawable.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class Cylinder : public IUpdatable/*, public ITransformable, public IDrawable*/
			{
			internal:
				Vector3D ^ bottomCenter;
				Vector3D ^ topCenter;
				double exRadius;
				double height;
				array<Vector3D^> ^ exBottomPoints;		//36 точек нижней окружности
				array<Vector3D^> ^ exTopPoints;		//36 точек верхней окружности
				array<Facet^> ^ exFacets;			//72 внешние боковые грани
				array<Facet^> ^ topCircleFacets;	//36(72?) грани оснований
				array<Facet^> ^ bottomCircleFacets;	//36(72?) грани оснований

			public:
				static const int N_CIRCLE_POINTS = 36;
				static const int N_CIRCLE_FACETS = 36;
				static const int N_SIZE_FACETS = 72;

				Cylinder(Vector3D ^ bottomCenter, double exRadius, double height);
				virtual void update();
				virtual void updatePoints();
				virtual void updateFacets();
				Vector3D ^ getBottomCenter();
				void setBottomCenter(Vector3D ^ bottomCenter);
				Vector3D ^ getTopCenter();
				void setTopCenter(Vector3D ^ topCenter);
				double getExRadius();
				void setExRadius(double exRadius);
				double getHeight();
				void setHeight(double height);
				array<Vector3D^> ^ getExBottomPoints();
				array<Vector3D^> ^ getExTopPoints();
				array<Facet^> ^ getExFacets();
				array<Facet^> ^ getTopCircleFacets();
				array<Facet^> ^ getBottomCircleFacets();
			};
		}
	}
}
