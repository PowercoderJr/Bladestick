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
			/// ������ ��������� ������ ������� � ������ �������� ����������
			/// </summary>
			/// <param name="radius">������</param>
			/// <param name="height">������</param>
			/// <param name="nEdges">���������� ���� ��� ���������� ��������</param>
			/// <param name="palette">������� (1 ����: ���� �������)</param>
			static Drawing::SceneObject ^ buildHandle(double radius, double height, int nEdges,
				array<System::Drawing::Color> ^ palette);

			/// <summary>
			/// ������ ��������� ������ ���������� ������ � ������ �������� ����������
			/// </summary>
			/// <param name="inRadius">���������� ������</param>
			/// <param name="bevelRadius">������ ������ �����</param>
			/// <param name="exRadius">������� ������</param>
			/// <param name="thickness">�������</param>
			/// <param name="nEdges">���������� ���� ��� ���������� �����������</param>
			/// <param name="palette">������� (2 �����: 1 - ���� ������� �����, 2 - ���� ����������� �������)</param>
			static Drawing::SceneObject ^ buildBladeRing(double inRadius, double bevelRadius,
				double exRadius, double thickness, int nEdges, array<System::Drawing::Color> ^ palette);

			/// <summary>
			/// ������ ��������� ������ ������ � ������ �������� ����������
			/// </summary>
			/// <param name="pLength">����� ����� �������</param>
			/// <param name="pWidth">������ ����� �������</param>
			/// <param name="pThickness">�������</param>
			/// <param name="palette">������� (1 ����: ���� ������)</param>
			static Drawing::SceneObject ^ buildCross(double pLength, double pWidth, double pThickness,
				array<System::Drawing::Color> ^ palette);
			
			/// <summary>
			/// ������ ��������� ������ ���� � ������ �������� ����������
			/// </summary>
			/// <param name="inDistance">���������� �� �.�. �� ������ ��������� ����������� ����</param>
			/// <param name="exDistance">���������� �� �.�. �� ������ ��������� �������� ����</param>
			/// <param name="alphaDeg">�������� ����</param>
			/// <param name="betaDeg">���� ����� ������ ����</param>
			/// <param name="thickness">�������</param>
			/// <param name="inLength">����� ����������� ����</param>
			/// <param name="bevelStartPoint">2D-���������� �� ��������� �������� ���� �� ������ �����</param>
			/// <param name="exLength">����� �������� ����</param>
			/// <param name="palette">������� (2 ����: 1 - ���� ������� �����, 2 - ���� ����������� �������)</param>
			static Drawing::SceneObject ^ buildSpike(double inDistance, double exDistance, double alphaDeg,
				double betaDeg, double thickness, double inLength, double bevelStartPoint, double exLength,
				array<System::Drawing::Color> ^ palette);
		internal:
			Vector3D ^ offset; //�������� � ���
			Vector3D ^ scaling; //������������ ���������������
			Vector3D ^ rotation; //���� ��������� � ��������
			array<Vector3D ^> ^ vertices; //�������
			array<int> ^ indices; //������� ������, ���������� ������������
			array<System::Drawing::Color> ^ colors; //����� �������������

		public:
			/// <summary>
			/// ������ ��������� ������ Bladestick � ������ �������� ����������
			/// </summary>
			/// <param name="handleLength">����� �������</param>
			/// <param name="handleRingsCount">���������� ����� �� ����� �������</param>
			/// <param name="handleEdgesCount">���������� ���� ��� ���������� �������� �������</param>
			/// <param name="inBladeRadius">���������� ������ ������</param>
			/// <param name="exBladeRadius">������� ������ ������</param>
			/// <param name="bladeEdgesCount">���������� ���� ��� ���������� ����������� ������</param>
			/// <param name="bladeThickness">������� ������</param>
			/// <param name="primarySpikeLength">����� ��������� �����</param>
			/// <param name="secondarySpikeLength">����� ��������� �����</param>
			/// <param name="primarySpikeAngle">���� ��������� �����</param>
			/// <param name="secondarySpikeAngle">���� ��������� �����</param>
			/// <param name="secondarySpikesCount">���������� ��������� �����</param>
			/// <param name="palette">������� (3 �����: 1 - ���� �������, 2 - ���� ������� �����, 3 - ���� ����������� �������)</param>
			static Drawing::SceneObject ^ buildBladestick(double handleLength, int handleRingsCount,
				double handleEdgesCount, double inBladeRadius, double exBladeRadius,
				double bladeEdgesCount, double bladeThickness,
				double primarySpikeLength, double secondarySpikeLength,
				double primarySpikeAngle, double secondarySpikeAngle,
				int secondarySpikesCount, array<System::Drawing::Color> ^ palette);
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
