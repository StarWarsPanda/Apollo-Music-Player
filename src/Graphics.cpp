#include "Graphics.h"

Apollo::Graphics::Graphics(Application& app)
	:m_app(app)
{
	m_hdc = GetDC(m_app.m_window);
}

Apollo::Graphics::~Graphics()
{
	ReleaseDC(m_app.m_window, m_hdc);
}

void Apollo::Graphics::DrawText(const char* string, int x, int y, int width, int height)
{
	std::string String = string;
	std::wstring str = std::wstring(String.begin(), String.end());

	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;

	DrawTextW(m_hdc, str.c_str(), str.length(), &rect, 0);
}
