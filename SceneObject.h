#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;
		value class Camera;

		public ref class SceneObject
		{
		private:/// <summary>
			/// Строит трёхмерную модель рукояти с учётом заданных параметров
			/// </summary>
			/// <param name="radius">Радиус</param>
			/// <param name="height">Высота</param>
			/// <param name="nEdges">Количество рёбер для построения цилиндра</param>
			/// <param name="palette">Палитра (1 цвет: цвет рукояти)</param>
			static Drawing::SceneObject ^ buildHandle(double radius, double height, int nEdges,
				array<System::Drawing::Color> ^ palette);

			/// <summary>
			/// Строит трёхмерную модель кольцевого лезвия с учётом заданных параметров
			/// </summary>
			/// <param name="inRadius">Внутренний радиус</param>
			/// <param name="bevelRadius">Радиус начала скоса</param>
			/// <param name="exRadius">Внешний радиус</param>
			/// <param name="thickness">Толщина</param>
			/// <param name="nEdges">Количество рёбер для построения окружностей</param>
			/// <param name="palette">Палитра (2 цвета: 1 - цвет металла сбоку, 2 - цвет наточенного металла)</param>
			static Drawing::SceneObject ^ buildBladeRing(double inRadius, double bevelRadius,
				double exRadius, double thickness, int nEdges, array<System::Drawing::Color> ^ palette);

			/// <summary>
			/// Строит трёхмерную модель креста с учётом заданных параметров
			/// </summary>
			/// <param name="pLength">Длина одной лопасти</param>
			/// <param name="pWidth">Ширина одной лопасти</param>
			/// <param name="pThickness">Толщина</param>
			/// <param name="palette">Палитра (1 цвет: цвет креста)</param>
			static Drawing::SceneObject ^ buildCross(double pLength, double pWidth, double pThickness,
				array<System::Drawing::Color> ^ palette);
			
			/// <summary>
			/// Строит трёхмерную модель шипа с учётом заданных параметров
			/// </summary>
			/// <param name="inDistance">Расстояние от Н.К. до центра основания внутреннего шипа</param>
			/// <param name="exDistance">Расстояние от Н.К. до центра основания внешнего шира</param>
			/// <param name="alphaDeg">Полярный угол</param>
			/// <param name="betaDeg">Угол между рёбрами шипа</param>
			/// <param name="thickness">Толщина</param>
			/// <param name="inLength">Длина внутреннего шипа</param>
			/// <param name="bevelStartPoint">2D-расстояние от основания внешнего шипа до начала скоса</param>
			/// <param name="exLength">Длина внешнего шипа</param>
			/// <param name="palette">Палитра (2 цвет: 1 - цвет металла сбоку, 2 - цвет наточенного металла)</param>
			static Drawing::SceneObject ^ buildSpike(double inDistance, double exDistance, double alphaDeg,
				double betaDeg, double thickness, double inLength, double bevelStartPoint, double exLength,
				array<System::Drawing::Color> ^ palette);
		internal:
			Vector3D ^ offset; //Смещение в МСК
			Vector3D ^ scaling; //Коэффициенты масштабирования
			Vector3D ^ rotation; //Углы поворотов в градусах
			array<Vector3D ^> ^ vertices; //Вершины
			array<int> ^ indices; //Индексы вершин, образующих треугольники
			array<System::Drawing::Color> ^ colors; //Цвета треугольников
			System::String ^ name;

		public:
			/// <summary>
			/// Строит трёхмерную модель Bladestick с учётом заданных параметров
			/// </summary>
			/// <param name="handleLength">Длина рукояти</param>
			/// <param name="handleRingsCount">Количество колец на конце рукояти</param>
			/// <param name="handleEdgesCount">Количество рёбер для построения цилиндра рукояти</param>
			/// <param name="inBladeRadius">Внутренний радиус лезвия</param>
			/// <param name="exBladeRadius">Внешний радиус лезвия</param>
			/// <param name="bladeEdgesCount">Количество рёбер для построения окружностей лезвия</param>
			/// <param name="bladeThickness">Толщина лезвия</param>
			/// <param name="primarySpikeLength">Длина первичных шипов</param>
			/// <param name="secondarySpikeLength">Длина вторичных шипов</param>
			/// <param name="primarySpikeAngle">Угол первичных шипов</param>
			/// <param name="secondarySpikeAngle">Угол вторичных шипов</param>
			/// <param name="secondarySpikesCount">Количество вторичных шипов</param>
			/// <param name="palette">Палитра (3 цвета: 1 - цвет рукояти, 2 - цвет металла сбоку, 3 - цвет наточенного металла)</param>
			static Drawing::SceneObject ^ buildBladestick(double handleLength, int handleRingsCount,
				double handleEdgesCount, double inBladeRadius, double exBladeRadius,
				double bladeEdgesCount, double bladeThickness,
				double primarySpikeLength, double primarySpikeAngle, 
				double secondarySpikeLength, double secondarySpikeAngle,
				int secondarySpikesCount, array<System::Drawing::Color> ^ palette);
			static Drawing::SceneObject ^ unite(array<Drawing::SceneObject ^> ^ components);

//SceneObject ^ so = SceneObject::buildBladestick(400, 10, 8, 100, 150, /*64*/32, 30, 60, 40, 50, 50, 4, gcnew array<Color>(3) { Color::SaddleBrown, Color::DarkGray, Color::LightGray });
			static double DEFAULT_HANDLE_LENGTH = 400;
			static int DEFAULT_HANDLE_RINGS_COUNT = 4;
			static double DEFAULT_HANDLE_EDGES_COUNT = 8;
			static double DEFAULT_IN_BLADE_RADIUS = 100;
			static double DEFAULT_EX_BLADE_RADIUS = 150;
			static double DEFAULT_BLADE_EDGES_COUNT = 32;
			static double DEFAULT_BLADE_THICKNESS = 30;
			static double DEFAULT_PRIMARY_SPIKE_LENGTH = 60;
			static double DEFAULT_PRIMARY_SPIKE_ANGLE = 50;
			static double DEFAULT_SECONDARY_SPIKE_LENGTH = 40;
			static double DEFAULT_SECONDARY_SPIKE_ANGLE = 50;
			static int DEFAULT_SECONDARY_SPIKES_COUNT = 4;
			static System::Drawing::Color DEFAULT_COLOR_1 = System::Drawing::Color::SaddleBrown;
			static System::Drawing::Color DEFAULT_COLOR_2 = System::Drawing::Color::DarkGray;
			static System::Drawing::Color DEFAULT_COLOR_3 = System::Drawing::Color::LightGray;

			SceneObject();
			SceneObject(array<Vector3D ^> ^ vertices, array<int> ^ indices, array<System::Drawing::Color> ^ colors, System::String ^ name);
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
			System::String ^ ToString() override;
		};
	}
}
