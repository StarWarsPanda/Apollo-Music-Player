#include "Graphics.h"

const Apollo::Color Apollo::Color::Black = Color(0, 0, 0);
const Apollo::Color Apollo::Color::Red = Color(255, 0, 0);
const Apollo::Color Apollo::Color::Blue = Color(0, 0, 255);
const Apollo::Color Apollo::Color::Green = Color(0, 255, 0);
const Apollo::Color Apollo::Color::Yellow = Color(255, 255, 0);
const Apollo::Color Apollo::Color::White = Color(255, 255, 255);

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

Apollo::Color::Color() :r(0), g(0), b(0), a(255) {}
Apollo::Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :r(red), g(green), b(blue), a(alpha) {}
Apollo::Color::Color(uint32_t val) :m_value(val) {}

double Apollo::Color::hue() const
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

double Apollo::Color::saturation() const
{
	double max = std::max({ r,g,b });
	double min = std::min({ r,g,b });

	if (max < 0.000000001) return 0.0;

	return 100.0 - ((min / max) * 100.0);
}

double Apollo::Color::value() const
{
	/* 0.392156862745 = 100/255 */
	return std::max({ r,g,b }) * 0.392156862745;
}

double Apollo::Color::luminance() const
{
	/* Weighted luminance based on perceptual values */
	return 0.1133333333333 * r + 0.226274509804 * g + 0.0525490196078 * b;
}
