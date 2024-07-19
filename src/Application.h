#pragma once

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS 1
#include <windows.h>
#elif __APPLE__
#define MACOS 1
// Deal with this later
#include <Cocoa/Cocoa.h>
#elif __linux__
#define LINUX 1
// Deal with this later
#include <X11/Xlib.h>
#endif

#include <string>
#include <Vector2d.h>

#define APP_CLASS L"ApplicationClass"

namespace Apollo
{
    class Graphics;

    class Application
    {
        public:
            Application();
            Application(const char* name, int width, int height);
            Application(const char* name, int width, int height, unsigned int flags);
            Application(const wchar_t* name, int width, int height, unsigned int flags);

            ~Application();

            void Run();

            virtual void Update();
            virtual void Draw();

            Vector2D<int> GetMousePosition();

        protected:
        #ifdef WINDOWS
            HWND m_window;
        #endif
        private:
        #ifdef WINDOWS
            static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        #endif
            friend class Graphics;
    };
}