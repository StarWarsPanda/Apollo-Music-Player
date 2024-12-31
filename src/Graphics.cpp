#include "Graphics.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

const Apollo::Graphics::Color Apollo::Graphics::Color::Black = Color(0, 0, 0);
const Apollo::Graphics::Color Apollo::Graphics::Color::Red = Color(255, 0, 0);
const Apollo::Graphics::Color Apollo::Graphics::Color::Blue = Color(0, 0, 255);
const Apollo::Graphics::Color Apollo::Graphics::Color::Green = Color(0, 255, 0);
const Apollo::Graphics::Color Apollo::Graphics::Color::Yellow = Color(255, 255, 0);
const Apollo::Graphics::Color Apollo::Graphics::Color::White = Color(255, 255, 255);

Apollo::Graphics::Graphics(Application& app)
	:m_app(app)
{
	#ifdef WINDOWS
	m_hdc = GetDC(m_app.m_window);

	/* For double buffering */
	m_hdcMem = CreateCompatibleDC(m_hdc);

	RECT clientRect;
	GetClientRect(m_app.m_window, &clientRect);
	m_width = clientRect.right - clientRect.left;
	m_height = clientRect.bottom - clientRect.top;

	m_hbmMem = CreateCompatibleBitmap(m_hdc, m_width, m_height);
	m_hbmOld = (HBITMAP)SelectObject(m_hdcMem, m_hbmMem);
	#endif
}

Apollo::Graphics::~Graphics()
{
	#ifdef WINDOWS
	SelectObject(m_hdcMem, m_hbmOld);
	DeleteObject(m_hbmMem);
	DeleteDC(m_hdcMem);
	ReleaseDC(m_app.m_window, m_hdc);
	#endif

}

void Apollo::Graphics::Clear(Color color)
{
	#ifdef WINDOWS
	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	RECT rect = { 0, 0, m_width, m_height };
	FillRect(m_hdcMem, &rect, brush);
	
	DeleteObject(brush);
	#endif
}

void Apollo::Graphics::DrawPixel(int x, int y, Color color)
{
	#ifdef WINDOWS
	SetPixel(m_hdcMem, x, y, RGB(color.r, color.g, color.b));
	#endif
}

void Apollo::Graphics::DrawLine(int startX, int startY, int endX, int endY, Color color)
{
	DrawLine(startX, startY, endX, endY, 1, color);
}

void Apollo::Graphics::DrawLine(int startX, int startY, int endX, int endY, double thickness, Color color)
{
	#ifdef WINDOWS
	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);

	MoveToEx(m_hdcMem, startX, startY, nullptr);
	LineTo(m_hdcMem, endX, endY);

	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawCircle(int x, int y, double radius, Color color)
{
	DrawCircle(x, y, radius, 1, color);
}

void Apollo::Graphics::DrawCircle(int x, int y, double radius, double thickness, Color color)
{
	#ifdef WINDOWS
	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Ellipse(m_hdcMem, x - radius, y - radius, x + radius, y + radius);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawFillCircle(int x, int y, double radius, Color color)
{
	#ifdef WINDOWS
	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, GetStockObject(NULL_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, brush);

	Ellipse(m_hdcMem, x - radius, y - radius, x + radius, y + radius);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(brush);
	#endif
}

void Apollo::Graphics::DrawRectangle(int x, int y, int width, int height, Color color)
{
	DrawRectangle(x, y, width, height, 1, color);
}

void Apollo::Graphics::DrawRectangle(int x, int y, int width, int height, double thickness, Color color)
{
	#ifdef WINDOWS
	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b)); 
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Rectangle(m_hdcMem, x, y, x + width, y + height);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawFillRectangle(int x, int y, int width, int height, Color color)
{
	#ifdef WINDOWS
	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, GetStockObject(NULL_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, brush);

	Rectangle(m_hdcMem, x, y, x + width, y + height);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(brush);
	#endif
}

void Apollo::Graphics::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color)
{
	DrawTriangle(x1, y1, x2, y2, x3, y3, 1, color);
}

void Apollo::Graphics::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, double thickness, Color color)
{
	#ifdef WINDOWS
	POINT vertices[3] = { {x1,y1},{x2,y2},{x3,y3} };

	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Polygon(m_hdcMem, vertices, 3);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color)
{
	#ifdef WINDOWS
	POINT vertices[3] = { {x1,y1},{x2,y2},{x3,y3} };

	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, GetStockObject(NULL_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, brush);

	Polygon(m_hdcMem, vertices, 3);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(brush);
	#endif
}

void Apollo::Graphics::DrawPolygon(int* points, int pointsLength, int posX, int posY, Color color)
{
	if (pointsLength < 3 || points == nullptr) return;

	#ifdef WINDOWS
	std::vector<POINT> vertices(pointsLength);

	for (size_t i = 0; i < pointsLength; i++)
	{
		vertices[i] = { points[i * 2] + posX, points[i * 2 + 1] + posY };
	}

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Polygon(m_hdcMem, vertices.data(), pointsLength);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawPolygon(int* points, int pointsLength, int posX, int posY, double thickness, Color color)
{
	if (pointsLength < 3 || points == nullptr) return;

	#ifdef WINDOWS
	std::vector<POINT> vertices(pointsLength);

	for (size_t i = 0; i < pointsLength; i++)
	{
		vertices[i] = { points[i * 2] + posX, points[i * 2 + 1] + posY };
	}

	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Polygon(m_hdcMem, vertices.data(), pointsLength);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, Color color)
{
	DrawPolygon(points, posX, posY, 1, color);
}

void Apollo::Graphics::DrawPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, double thickness, Color color)
{
	if (points.size() < 3 || points.data() == nullptr) return;

	#ifdef WINDOWS
	std::vector<POINT> vertices(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		vertices[i] = { points[i].first + posX, points[i].second + posY };
	}

	HPEN pen = CreatePen(PS_SOLID, thickness, RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, GetStockObject(NULL_BRUSH));

	Polygon(m_hdcMem, vertices.data(), points.size());

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(pen);
	#endif
}

void Apollo::Graphics::DrawFillPolygon(int* points, int pointsLength, int posX, int posY, Color color)
{
	if (pointsLength < 3 || points == nullptr) return;

	#ifdef WINDOWS
	std::vector<POINT> vertices(pointsLength);

	for (size_t i = 0; i < pointsLength; i++)
	{
		vertices[i] = { points[i * 2] + posX, points[i * 2 + 1] + posY };
	}

	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, GetStockObject(NULL_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, brush);

	Polygon(m_hdcMem, vertices.data(), pointsLength);

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(brush);
	#endif
}

void Apollo::Graphics::DrawFillPolygon(std::vector<std::pair<int, int>> points, int posX, int posY, Color color)
{
	if (points.size() < 3 || points.data() == nullptr) return;

	#ifdef WINDOWS
	std::vector<POINT> vertices(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		vertices[i] = { points[i].first + posX, points[i].second + posY };
	}

	HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
	HPEN oldPen = (HPEN)SelectObject(m_hdcMem, GetStockObject(NULL_PEN));
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_hdcMem, brush);

	Polygon(m_hdcMem, vertices.data(), points.size());

	SelectObject(m_hdcMem, oldBrush);
	SelectObject(m_hdcMem, oldPen);
	DeleteObject(brush);
	#endif
}

bool Apollo::Graphics::RectanglePointCollision(int rectX, int rectY, int rectWidth, int rectHeight, int x, int y)
{
	double invW = 2.0 / rectWidth;
	double invH = 2.0 / rectHeight;
	double wP = invW * (x - rectX);
	double hP = invH * (y - rectY);

	return std::abs(wP + hP - 2.0) + std::abs(hP - wP) <= 2.0;
}

double Apollo::Graphics::DrawSlider(double& value, double valMin, double valMax, int x, int y, int width, int height, Color foreColor, Color backColor)
{
	Vector2D<int> mousePos = m_app.GetMousePosition();
	
	if (m_app.IsMouseButtonDown(MouseButton::LeftButton) && RectanglePointCollision(x, y, width, height, mousePos.x, mousePos.y))
	{
		value = maprange(mousePos.y, y, y + height, valMin, valMax);
	}

	DrawFillRectangle(x, y, width, height, backColor);
	DrawFillRectangle(x, maprange(value, valMin, valMax, y, y + height - 3), width, 3, foreColor);

	return 0.0;
}

void Apollo::Graphics::DrawImage(Image& image, int x, int y, int width, int height)
{
	#ifdef WINDOWS
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = image.width();
	bmi.bmiHeader.biHeight = -static_cast<LONG>(image.height()); // Top-down DIB
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* pBits;
	HBITMAP hBitmap = CreateDIBSection(m_hdcMem, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);
	if (!hBitmap) return;

	/* ARGB --> BGRA */
	for (int i = 0; i < image.width() * image.height(); ++i)
	{
		((uint32_t*)pBits)[i] = ((image.data()[i] & 0x000000ff) << 16) | // b
								((image.data()[i] & 0x0000ff00) <<  0) | // g
								((image.data()[i] & 0x00ff0000) >> 16) | // r
								((image.data()[i] & 0xff000000) >>  0);  // a
	}

	HDC hdcMem = CreateCompatibleDC(m_hdcMem);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

	StretchBlt(m_hdcMem, x, y, width, height, hdcMem, 0, 0, image.width(), image.height(), SRCCOPY);

	SelectObject(hdcMem, hOldBitmap);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	#endif
}

void Apollo::Graphics::Present()
{
	#ifdef WINDOWS
	BitBlt(m_hdc, 0, 0, m_width, m_height, m_hdcMem, 0, 0, SRCCOPY);
	#endif
}

void Apollo::Graphics::DrawText(const char* string, int x, int y, int width, int height, Color color)
{
	#ifdef WINDOWS
	std::string String = string;
	std::wstring str = std::wstring(String.begin(), String.end());

	COLORREF tempColor = GetTextColor(m_hdcMem);

	SetTextColor(m_hdcMem, RGB(color.r, color.g, color.b));
	SetBkMode(m_hdcMem, TRANSPARENT);

	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;

	DrawTextW(m_hdcMem, str.c_str(), str.length(), &rect, 0);

	SetTextColor(m_hdcMem, tempColor);
	#endif

}

Apollo::Graphics::Color::Color() :r(0), g(0), b(0), a(255) {}
Apollo::Graphics::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :r(red), g(green), b(blue), a(alpha) {}
Apollo::Graphics::Color::Color(uint32_t val) :m_value(val) {}

double Apollo::Graphics::Color::hue() const
{
	double max = std::max({ r,g,b });
	double min = std::max({ r,g,b });

	double diff = 1.0 / (max - min);

	double hue = 0.0;

	if (max == r)
	{
		hue = g - b;
	}
	else if(max == g)
	{
		hue = b - r;
	}
	else if(max == b)
	{
		hue = r - g;
	}

	return std::fmod(60.0 * hue * diff + 240.0, 360.0);
}

double Apollo::Graphics::Color::saturation() const
{
	double max = std::max({ r,g,b });
	double min = std::min({ r,g,b });

	if (max < 0.000000001) return 0.0;

	return 100.0 - ((min / max) * 100.0);
}

double Apollo::Graphics::Color::value() const
{
	/* 0.392156862745 = 100/255 */
	return std::max({ r,g,b }) * 0.392156862745;
}

double Apollo::Graphics::Color::luminance() const
{
	/* Weighted luminance based on perceptual values */
	return 0.1133333333333 * r + 0.226274509804 * g + 0.0525490196078 * b;
}

Apollo::Graphics::Image::Image() :m_width(0), m_height(0) {}

Apollo::Graphics::Image::Image(uint16_t width, uint16_t height)
	:m_width(width), m_height(height)
{
	m_data.resize(m_width * m_height);
}

Apollo::Graphics::Image::Image(std::string filename)
{
	int width, height, channels;
	uint8_t* imageData = stbi_load(filename.c_str(), &width, &height, &channels, 4);

	if (imageData)
	{
		m_width = width;
		m_height = height;

		m_data.resize(m_width * m_height);

		std::memcpy(data(), imageData, m_width * m_height * 4);

		stbi_image_free(imageData);

		return;
	}

	std::string fileExtension = filename.substr(filename.find_last_of(".") + 1, filename.length() - filename.find_last_of(".") - 1);

	if (fileExtension == "mp3")
	{
		initMP3ID3V2(filename);
	}

	m_width = 0;
	m_height = 0;
}

Apollo::Graphics::Image::Image(std::wstring filename)
{
	FILE* file = nullptr;

	#ifdef WINDOWS

	_wfopen_s(&file, filename.c_str(), L"rb");

	#endif


	int channels;
	uint8_t* imageData = stbi_load_from_file(file, (int*)&m_width, (int*)&m_height, &channels, 4);

	if (file) fclose(file);

	if (imageData)
	{
		m_data.resize(m_width * m_height);

		std::memcpy(data(), imageData, m_width * m_height * 4);

		stbi_image_free(imageData);

		return;
	}

	m_width = 0;
	m_height = 0;
}

Apollo::Graphics::Image::~Image(){}

void Apollo::Graphics::Image::initMP3ID3V2(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	std::vector<byte> fileBuffer(std::istreambuf_iterator<char>(file), {});
	file.close();

	std::vector<byte> albumImageStart = { 0x41, 0x50, 0x49, 0x43 }; // APIC

	auto find = std::search(fileBuffer.begin(), fileBuffer.end(), albumImageStart.begin(), albumImageStart.end());

	if (find != fileBuffer.end())
	{
		auto distance = std::distance(fileBuffer.begin(), find);
	}
}

Apollo::Graphics::Color Apollo::Graphics::Image::getPixelColor(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height) 
	{
		return Color();
	}

	return m_data[y * m_width + x];
}

Apollo::Graphics::Color Apollo::Graphics::Image::setPixelColor(int x, int y, Color color)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
	{
		return Color();
	}

	Color previousColor = m_data[y * m_width + x];
	m_data[y * m_width + x] = color;
	return previousColor;
}

bool Apollo::Graphics::Rectangle::Inside(int x, int y)
{
	return Apollo::Graphics::RectanglePointCollision(this->x, this->y, this->width, this->height, x, y);
}
