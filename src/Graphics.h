#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

#include "Application.h"

#undef max
#undef min

#ifdef WINDOWS

//windows painting function macro
#undef DrawText

#endif

namespace Apollo
{
    class Color 
    {
        public:
            union 
            {
                struct 
                {
                    uint8_t r;
                    uint8_t g;
                    uint8_t b;
                    uint8_t a;
                };
                uint32_t m_value;
            };
        public:
            Color();
            Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
            explicit Color(uint32_t val);

            double hue() const;
            double saturation() const;
            double value() const;
            double luminance() const;

            static const Color Black;
            static const Color Red;
            static const Color Blue;
            static const Color Green;
            static const Color Yellow;
            static const Color White;
    };

	class Graphics
	{
        public:
            int m_width;
            int m_height;
		public:
			Graphics(Application& app);

			~Graphics();

            void Clear(Color color);

            void DrawPixel(int x, int y, Color color);

            void DrawLine(int startX, int startY, int endX, int endY, Color color);
            void DrawLine(int startX, int startY, int endX, int endY, double thickness, Color color);

            void DrawCircle(int x, int y, double radius, Color color);
            void DrawCircle(int x, int y, double radius, double thickness, Color color);
            void DrawFillCircle(int x, int y, double radius, Color color);

            void DrawRectangle(int x, int y, int width, int height, Color color);
            void DrawRectangle(int x, int y, int width, int height, double thickness, Color color);
            void DrawFillRectangle(int x, int y, int width, int height, Color color);

            void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color);
            void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, double thickness, Color color);
            void DrawFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color);

            /* Looking for points to be like this: [x,y,x,y...] where the size should be even and pointsLength should be the */
            /* the amount of points, NOT the size of the array. posX and posY are the centered position of where to draw the */
            /* polygon. */
            void DrawPolygon(int* points, int pointsLength, int posX, int posY, Color color);
            void DrawPolygon(int* points, int pointsLength, int posX, int posY, double thickness, Color color);

            void DrawPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, Color color);
            void DrawPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, double thickness, Color color);
            
            void DrawFillPolygon(int* points, int pointsLength, int posX, int posY, Color color);
            void DrawFillPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, Color color);

			void DrawText(const char* string, int x, int y, int width, int height, Color color);

            /* Show the buffered drawing to the screen to avoid FLICKER! */
            void Present();

		private:
			Application& m_app;
			#ifdef WINDOWS
			HDC m_hdc;

            /* For double buffering */
            HDC m_hdcMem;
            HBITMAP m_hbmMem;
            HBITMAP m_hbmOld;
			#endif

	};
}

