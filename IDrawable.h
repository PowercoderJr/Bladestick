#pragma once

namespace Bladestick
{
	namespace Drawing
	{
		ref class ZBuffer;

		public interface class IDrawable
		{
		public:
			void draw(ZBuffer ^ buffer);
		};
	}
}
