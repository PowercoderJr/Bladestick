#pragma once

#include "Cylinder.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public ref class HollowCylinder : Cylinder
			{
			internal:
				double inRadius;
				array<Vector3D^> ^ inBottomPoints;	//36 ����� ������ ����������
				array<Vector3D^> ^ inTopPoints;	//36 ����� ������� ����������
				array<Facet^> ^ inFacets;		//72 ���������� ������� �����

			public:
				static const int N_CIRCLE_FACETS = 72;

				HollowCylinder(Vector3D ^ bottomCenter, double exRadius, double inRadius, double height);
				virtual void update() override;
				virtual void updatePoints() override;
				virtual void updateFacets() override;
				double getInRadius();
				void setInRadius(double inRadius);
				array<Vector3D^> ^ getInBottomPoints();
				array<Vector3D^> ^ getInTopPoints();
				array<Facet^> ^ getInFacets();
			};
		}
	}
}
