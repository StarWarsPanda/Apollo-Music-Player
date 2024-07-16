#pragma once
#include "Application.h"

#ifdef WINDOWS

//windows painting function macro
#undef DrawText

#endif


namespace Apollo
{
	class Graphics
	{
		public:
			Graphics(Application& app);

			~Graphics();

			void DrawText(const char* string, int x, int y, int width, int height);
		private:
			Application& m_app;
			#ifdef WINDOWS
			HDC m_hdc;
			#endif

	};
}

