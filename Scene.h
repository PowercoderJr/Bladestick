#pragma once

#include "Vector3D.h"
#include "SceneObject.h"

namespace Bladestick
{
	namespace Drawing
	{
		public value class Camera
		{
		internal:
			Vector3D ^ position;
			//Vector3D ^ target;
			Vector3D ^ rotation;
			int near;
			int far;
			bool perspective;
		};

		public ref class Scene
		{
		internal:
			System::Drawing::Bitmap ^ bitmap;
			array<double> ^ zbuffer;
			System::Drawing::Color bgColor;
			System::Drawing::Color edgeColor;
			int width;
			int height;
			Camera camera;
			System::ComponentModel::BindingList<SceneObject ^> ^ objects;
			int objCount;

		public:
			/*static const int MAX_WIDTH = 1920;
			static const int MAX_HEIGHT = 1080;*/

			Scene(int width, int height, System::Drawing::Color bgColor, System::Drawing::Color edgeColor);
			Scene(int width, int height);
			Scene();
			void setSize(int width, int height);
			int getWidth();
			int getHeight();
			void clear();
			void setPixel(int x, int y, double z, System::Drawing::Color color, bool flipVertical);
			void drawLine(double x0, double y0, double z0, double x1, double y1, double z1, System::Drawing::Color color, bool flipVertical);
			void drawLine(Vector3D ^ p1, Vector3D ^ p2, System::Drawing::Color color, bool flipVertical);
			void drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, System::Drawing::Color color, bool flipVertical, bool drawFill, bool drawEdges);
			void drawToBuffer(SceneObject ^ obj, bool flipVertical, bool drawFill, bool drawEdges, bool useRandomPalette);
			void drawToBuffer(SceneObject ^ obj, bool flipVertical, bool drawFill, bool drawEdges);
			void drawToBuffer(SceneObject ^ obj, bool flipVertical);
			void render(System::Drawing::Graphics ^ g);
			void drawObjectsToBuffer();
			System::Drawing::Color getBgColor();
			void setBgColor(System::Drawing::Color color);
		};

	}
}
