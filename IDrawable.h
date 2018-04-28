#pragma once

#include "ZBuffer.h"

namespace Bladestick
{
	namespace Drawing
	{
		namespace Geometry
		{
			public interface class IDrawable
			{
			public:
				void draw(Bladestick::Drawing::ZBuffer ^ buffer);
			};
		}
	}
}
