#pragma once

#include "Vector3D.h"
#include "SceneObject.h"
#include "Camera.h"

namespace Bladestick
{
	namespace Drawing
	{
		public ref class SceneMarks
		{
		public:
			static initonly System::String ^ CAMERA_POSITION = "cpos ";
			static initonly System::String ^ CAMERA_TARGET = "ctar ";
			static initonly System::String ^ FUSTRUM = "fstr ";
			static initonly System::String ^ FOV = "fov ";
			static initonly System::String ^ PROJ_TYPE = "cper ";
			static initonly System::String ^ BG_COLOR = "bc ";
			static initonly System::String ^ LINE_COLOR = "lc ";
			static initonly System::String ^ OBJ_COUNT = "obc ";
			static initonly System::String ^ END_OF_OBJECT = "eoo";
		};

		public enum DrawFlags
		{
			DRAW_EDGES = 1,
			DRAW_FILL = 1 << 1,
			USE_RND_COLORS = 1 << 2,
			SIMULATE_LIGHT = 1 << 3
		};

		public ref class Scene
		{
		private:
			bool isPointVisible(Vector3D ^ p);

		internal:
			System::Drawing::Bitmap ^ bitmap;
			array<double> ^ zbuffer;
			System::Drawing::Color bgColor;
			System::Drawing::Color edgeColor;
			int width;
			int height;
			Camera ^ camera;
			int objTotalCount;
			System::ComponentModel::BindingList<SceneObject ^> ^ objects;

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
			void drawToBuffer(SceneObject ^ obj, char drawFlags);
			void drawObjectsToBuffer(char drawFlags);
			void render(System::Drawing::Graphics ^ g);
			System::Drawing::Color getBgColor();
			void setBgColor(System::Drawing::Color color);

			void saveToStream(System::IO::StreamWriter ^ stream);
			void loadFromStream(System::IO::Stream ^ stream);
		};

	}
}
