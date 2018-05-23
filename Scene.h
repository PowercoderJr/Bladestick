#pragma once

#include "Vector3D.h"
#include "SceneObject.h"
#include "Camera.h"

namespace Bladestick
{
	namespace Drawing
	{
		public enum DrawFlags
		{
			DRAW_EDGES = 1,
			DRAW_FILL = 1 << 1
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
			Camera ^ camera;

			void setPixel(int x, int y, double z, System::Drawing::Color color);
			void drawLine(double x0, double y0, double z0, double x1, double y1, double z1, System::Drawing::Color color);
			void drawLine(Vector3D ^ p1, Vector3D ^ p2, System::Drawing::Color color);
			void drawTriangle(Vector3D ^ p1, Vector3D ^ p2, Vector3D ^ p3, System::Drawing::Color color, char drawFlags);

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
			void drawToBuffer(SceneObject ^ obj, char drawFlags, bool useRandomPalette);
			void drawToBuffer(SceneObject ^ obj, char drawFlags);
			void render(System::Drawing::Graphics ^ g);
			System::Drawing::Color getBgColor();
			void setBgColor(System::Drawing::Color color);
		};

	}
}
