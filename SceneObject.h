#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;

		public ref class SceneObject
		{
		internal:
			//Vector3D ^ origin; //Центральная точка
			Vector3D ^ offset; //Смещение в МСК
			Vector3D ^ scaling; //Коэффициенты масштабирования
			Vector3D ^ rotation; //Углы поворотов в градусах
			array<Vector3D ^> ^ vertices; //Вершины
			array<int> ^ indices; //Индексы вершин, образующие треугольники
			array<System::Drawing::Color ^> ^ colors; //Цвета треугольников

		public:
			SceneObject();
			//void transform();
			void setOffset(double x, double y, double z);
			void setOffset(Vector3D ^ offset);
			void setScaling(double a, double b, double c);
			void setScaling(Vector3D ^ factors);
			void setRotation(double alphaDeg, double betaDeg, double gammaDeg);
			void setRotation(Vector3D ^ angles);

			void loadFromStream(System::IO::Stream ^ stream);
		};
	}
}
