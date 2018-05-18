#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;
		value class Camera;

		public ref class SceneObject
		{
		private:
			static Drawing::SceneObject ^ buildHandle(double radius, double height, int nEdges);
			static Drawing::SceneObject ^ buildBladeRing(double inRadius, double bevelRadius,
				double exRadius, double thickness, int nEdges);
			static Drawing::SceneObject ^ buildCross(double pLength, double pWidth, double pThickness);
			static Drawing::SceneObject ^ buildSpike(double inDistance, double exDistance, double alphaDeg,
				double betaDeg, double thickness, double inLength, double bevelStartPoint, double exLength);
		internal:
			Vector3D ^ offset; //Смещение в МСК
			Vector3D ^ scaling; //Коэффициенты масштабирования
			Vector3D ^ rotation; //Углы поворотов в градусах
			array<Vector3D ^> ^ vertices; //Вершины
			array<int> ^ indices; //Индексы вершин, образующие треугольники
			array<System::Drawing::Color> ^ colors; //Цвета треугольников

		public:
			static Drawing::SceneObject ^ buildBladestick(double handleLength, int handleRingsCount,
				double handleEdgesCount, double inBladeRadius, double exBladeRadius,
				double bladeEdgesCount, double bladeThickness,
				double primarySpikeLength, double secondarySpikeLength,
				double primarySpikeAngle, double secondarySpikeAngle, int secondarySpikesCount);
			static Drawing::SceneObject ^ unite(array<Drawing::SceneObject ^> ^ components);

			SceneObject();
			SceneObject(array<Vector3D ^> ^ vertices, array<int> ^ indices, array<System::Drawing::Color> ^ colors);
			void transform(Camera camera);
			void setOffset(double x, double y, double z);
			void setOffset(Vector3D ^ offset);
			void setScaling(double a, double b, double c);
			void setScaling(Vector3D ^ factors);
			void setRotation(double alphaDeg, double betaDeg, double gammaDeg);
			void setRotation(Vector3D ^ angles);

			void moveOriginal(double x, double y, double z);
			void moveOriginal(Vector3D ^ offset);

			void loadFromStream(System::IO::Stream ^ stream);
		};
	}
}
