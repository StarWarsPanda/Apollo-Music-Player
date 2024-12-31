#include "Application.h"

#ifdef WINDOWS
#include <ShObjIdl.h>
#endif

namespace Apollo
{
    Application::Application() : Application("Application", 800, 600, 0, 320, 240) {}
    Application::Application(const std::string& name, int width, int height) : Application(name, width, height, 0, 320, 240) {}
    Application::Application(const std::string& name, int width, int height, unsigned int flags) :Application(name, width, height, flags, 320, 240) {}
    
    Application::Application(const std::string& name, int width, int height, unsigned int flags, int minWidth, int minHeight)
        :m_minWidth(minWidth), m_minHeight(minHeight), m_keys(), m_previousKeys(), m_mouseButtons(), m_previousMouseButtons()
    {
        #ifdef WINDOWS

        std::string icoPath = "";

        for (const auto& file : std::filesystem::directory_iterator("src/res"))
        {
            if (file.path().extension() == ".ico")
            {
                icoPath = file.path().string();
                break;
            }
        }

        HICON appIcon = static_cast<HICON>(LoadImage(NULL, std::wstring(icoPath.begin(), icoPath.end()).c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE));
        
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = Application::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = APP_CLASS;
        wc.hIcon = appIcon;        
        wc.hIconSm = appIcon;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

        RegisterClassEx(&wc);

        DWORD dwStyle = WS_OVERLAPPEDWINDOW;

        RECT rect = { 0, 0, width, height };
        AdjustWindowRect(&rect, dwStyle, false);

        std::string Name = name;

        m_window = CreateWindow(APP_CLASS, std::wstring(Name.begin(), Name.end()).c_str(), dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

        SendMessage(m_window, WM_SETICON, ICON_SMALL, (LPARAM)appIcon);
        SendMessage(m_window, WM_SETICON, ICON_BIG,   (LPARAM)appIcon);

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

    Application::Application(const std::wstring& name, int width, int height, unsigned int flags)
        :m_minWidth(320),m_minHeight(240), m_keys(), m_previousKeys(), m_mouseButtons(), m_previousMouseButtons()
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
        AdjustWindowRect(&rect, dwStyle, false);

        m_window = CreateWindowW(APP_CLASS, name.c_str(), dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

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

            for (size_t i = 0; i < KeySize; i++)
            {
                m_previousKeys[i] = m_keys[i];
                m_keys[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
            }

            for (size_t i = 0; i < MouseSize; i++)
            {
                m_previousMouseButtons[i] = m_mouseButtons[i];

                int key = 0;
                switch(i)
                {
                    case MouseButton::LeftButton:
                        key = VK_LBUTTON;
                        break;
                    case MouseButton::MiddleButton:
                        key = VK_MBUTTON;
                        break;
                    case MouseButton::RightButton:
                        key = VK_RBUTTON;
                        break;
                    default:
                        key = 0;
                }

                m_mouseButtons[i] = (GetAsyncKeyState(key) & 0x8000) != 0;
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

    bool Application::IsMouseButtonDown(MouseButton button)
    {
        return m_mouseButtons[button];
    }

    bool Application::IsMouseButtonPressed(MouseButton button)
    {
        return m_mouseButtons[button] && !m_previousMouseButtons[button];
    }

    bool Application::IsMouseButtonUp(MouseButton button)
    {
        return !m_mouseButtons[button];
    }

    void Application::SetCursorStyle(MouseStyle style)
    {
        SetCursor(LoadCursor(NULL, (LPCWSTR)style));
    }

    bool Application::IsKeyPressed(Keycodes keycode)
    {
        #ifdef WINDOWS
        return (GetForegroundWindow() == m_window) && m_keys[keycode] && !m_previousKeys[keycode];
        #endif
    }

    bool Application::IsKeyDown(Keycodes keycode)
    {
        return (GetForegroundWindow() == m_window) && m_keys[keycode];
    }

    bool Application::IsKeyUp(Keycodes keycode)
    {
        return (GetForegroundWindow() == m_window) && !m_keys[keycode];
    }

    #ifdef WINDOWS
    LRESULT CALLBACK Application::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        // Getting the Application
        Application* app = reinterpret_cast<Application*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

        switch (uMsg)
        {
            case WM_GETMINMAXINFO:
                {
                    if (app)
                    {
                        MINMAXINFO* mmi = (MINMAXINFO*)lParam;
                        mmi->ptMinTrackSize.x = app->m_minWidth;
                        mmi->ptMinTrackSize.y = app->m_minHeight;
                    }
                }
                return 0;
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