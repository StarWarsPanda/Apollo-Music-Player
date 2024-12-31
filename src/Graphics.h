#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "Application.h"
#include "File.h"

#undef max
#undef min

#ifdef WINDOWS

//windows painting function macro
#undef DrawText

#endif

namespace Apollo
{
	class Graphics
	{
        public:
            class Rectangle
            {
                public:
                    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
                    bool Inside(int x, int y);

                public:
                    unsigned int x, y, width, height;
            };
            class Color
            {
                public:
                    union
                    {
                        struct
                        {
                            uint8_t a;
                            uint8_t r;
                            uint8_t g;
                            uint8_t b;
                        };
                        uint32_t m_value;
                    };
                public:
                    Color();
                    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
                    Color(uint32_t val);

                    operator uint32_t() const { return m_value; }

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

            class Image
            {
                public:
                    Image();
                    Image(uint16_t width, uint16_t height);
                    Image(std::string filename);
                    Image(std::wstring filename);
                    ~Image();

                    void initMP3ID3V2(const std::string& filename);

                    Color getPixelColor(int x, int y);
                    Color setPixelColor(int x, int y, Color color); //returns the previous color of the pixel

                    uint16_t width() const { return m_width; }
                    uint16_t height() const { return m_height; }
                    Apollo::Graphics::Color* data() { return m_data.data(); }
                private:
                    uint16_t m_width, m_height;
                    std::vector<Color> m_data;
            };

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

            void DrawImage(Image& image, int x, int y, int width, int height);

            double DrawSlider(double& value, double valMin, double valMax, int x, int y, int width, int height, Color foreColor, Color backColor);

            /* Show the buffered drawing to the screen to avoid FLICKER! */
            void Present();

            static bool RectanglePointCollision(int rectX, int rectY, int rectWidth, int rectHeight, int x, int y);

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

