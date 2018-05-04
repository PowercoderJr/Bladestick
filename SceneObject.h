#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class Vector3D;

		public ref class SceneObject
		{
		internal:
			//Vector3D ^ origin; //����������� �����
			Vector3D ^ offset; //�������� � ���
			Vector3D ^ scaling; //������������ ���������������
			Vector3D ^ rotation; //���� ��������� � ��������
			array<Vector3D ^> ^ vertices; //�������
			array<int> ^ indices; //������� ������, ���������� ������������
			array<System::Drawing::Color ^> ^ colors; //����� �������������

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
