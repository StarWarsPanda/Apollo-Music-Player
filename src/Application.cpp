#include "Application.h"

namespace Apollo
{
    Application::Application() : Application("Application", 800, 600, 0) {}
    Application::Application(const char* name, int width, int height) : Application(name, width, height, 0) {}

    Application::Application(const char* name, int width, int height, unsigned int flags)
    {
        #ifdef WINDOWS
        WNDCLASSEX wc = { 0 };

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = Application::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = APP_CLASS;

        RegisterClassEx(&wc);

        DWORD dwStyle = WS_OVERLAPPEDWINDOW;

        RECT rect = { 0, 0, width, height };
        AdjustWindowRect(&rect, dwStyle, FALSE);

        std::string Name = name;

        m_window = CreateWindow(APP_CLASS, std::wstring(Name.begin(), Name.end()).c_str(), dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

        if (m_window)
        {
            ShowWindow(m_window, SW_SHOW);
            UpdateWindow(m_window);

            InvalidateRect(m_window, NULL, false);

            //Import Application to WindowProc
            SetWindowLongPtr(m_window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        }
        #endif
    }

    Application::Application(const wchar_t* name, int width, int height, unsigned int flags)
    {
        #ifdef WINDOWS
        WNDCLASSEX wc = { 0 };

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = Application::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszClassName = APP_CLASS;

        RegisterClassEx(&wc);

        DWORD dwStyle = WS_OVERLAPPEDWINDOW;

        RECT rect = { 0, 0, width, height };
        AdjustWindowRect(&rect, dwStyle, FALSE);

        m_window = CreateWindowW(APP_CLASS, name, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

        if (m_window)
        {
            ShowWindow(m_window, SW_SHOW);
            UpdateWindow(m_window);
        }
        #endif
    }

    Application::~Application()
    {
        #ifdef WINDOWS
        if (m_window)
        {
            DestroyWindow(m_window);
        }

        UnregisterClass(APP_CLASS, GetModuleHandle(NULL));
        #endif
    }

    void Application::Run()
    {
        #ifdef WINDOWS
        MSG msg = { 0 };
        BOOL bRet;

        while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
        {
            if (bRet == -1)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (!IsWindow(m_window))
            {
                break;
            }

            Update();
            InvalidateRect(m_window, NULL, false);
        }
        #endif
    }

    void Application::Update()
    {

    }

    void Application::Draw()
    {

    }

    Vector2D<int> Application::GetMousePosition()
    {
        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(m_window, &mousePos);

        return Vector2D<int>(mousePos.x, mousePos.y);
    }

    #ifdef WINDOWS
    LRESULT CALLBACK Application::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Getting the Application
        Application* app = reinterpret_cast<Application*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        switch (uMsg)
        {
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hwnd, &ps);
                    if (app != nullptr) app->Draw();
                    EndPaint(hwnd, &ps);
                }
                return 0;
            case WM_CLOSE:
                DestroyWindow(hwnd);
                return 0;
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }
    #endif
}