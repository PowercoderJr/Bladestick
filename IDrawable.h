#pragma once

#include "ZBuffer.h"

namespace Geometry
{
	public interface class IDrawable
	{
	public:
		void draw(Bladestick::ZBuffer ^ buffer);
	};
}
