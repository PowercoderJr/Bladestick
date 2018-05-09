#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;

		public ref class SceneObject
		{
		private:
			static void generateHandle(Drawing::Vector3D ^ bottomCenter, double radius,
				double height, int nEdges, array<Drawing::Vector3D ^> ^* vertices, array<int> ^* indices);
			static void generateBladeRing(Drawing::Vector3D ^ nearCenter,
				double inRadius, double exRadius, double height, int nEdges,
				array<Drawing::Vector3D ^> ^* vertices, array<int> ^* indices);
		internal:
			//Vector3D ^ origin; //����������� �����
			Vector3D ^ offset; //�������� � ���
			Vector3D ^ scaling; //������������ ���������������
			Vector3D ^ rotation; //���� ��������� � ��������
			array<Vector3D ^> ^ vertices; //�������
			array<int> ^ indices; //������� ������, ���������� ������������
			array<System::Drawing::Color> ^ colors; //����� �������������

		public:
			static Drawing::SceneObject ^ buildBladestick(double handleLength, double inBladeRadius,
					double exBladeRadius, double bladeThickness, double primarySpikeLength,
					double secondarySpikeLength, double primarySpikeAngle, double secondarySpikeAngle,
					int secondarySpikesCount, int ringsCount);

			SceneObject();
			SceneObject(array<Vector3D ^> ^ vertices, array<int> ^ indices, array<System::Drawing::Color> ^ colors);
			void transform();
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
