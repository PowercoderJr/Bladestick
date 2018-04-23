#pragma once

namespace Geometry
{
	public ref class Point
	{
	private:
		float x;
		float y;
		float z;
		float w;
		float sx;
		float sy;
		float sz;
		float sw;

	public:
		Point(float x, float y, float z, float w, float sx, float sy, float sz, float sw);
		Point(float x, float y, float z, float w);
		Point(float x, float y, float z);
		Point();
		float getX();
		void setX(float x);
		float getY();
		void setY(float y);
		float getZ();
		void setZ(float z);
		float getW();
		void setW(float w);
		float getSx();
		float getSy();
		float getSz();
		float getSw();
		Point^ add(float x, float y, float z);
		Point^ add(Point^ point);
		Point^ operator+ (Point^ point);
	};
}
