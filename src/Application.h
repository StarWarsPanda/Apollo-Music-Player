#pragma once

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS 1
#include <windows.h>
#define APP_CLASS L"ApplicationClass"
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

#define maprange(x, imin, imax, omin, omax) (((x) - (imin)) * ((omax) - (omin)) / ((imax) - (imin)) + (omin))

namespace Apollo
{
    class Graphics;

    enum Keycodes
    {
        Unknown,
        A =
        #ifdef WINDOWS
        'A',
        #endif
        B =
        #ifdef WINDOWS
        'B',
        #endif
        C =
        #ifdef WINDOWS
        'C',
        #endif
        D =
        #ifdef WINDOWS
        'D',
        #endif
        E =
        #ifdef WINDOWS
        'E',
        #endif
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Zero,
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right =
        #ifdef WINDOWS
        VK_RIGHT
        #endif
        ,
        Left =
        #ifdef WINDOWS
        VK_LEFT
        #endif
        ,
        Up =
        #ifdef WINDOWS
        VK_UP
        #endif
        ,
        Down = 
        #ifdef WINDOWS
        VK_DOWN
        #endif
        ,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        KeypadZero,
        KeypadOne,
        KeypadTwo,
        KeypadThree,
        KeypadFour,
        KeypadFive,
        KeypadSix,
        KeypadSeven,
        KeypadEight,
        KeypadNine,
        KeypadDecimal,
        KeypadDivide,
        KeypadMultiply,
        KeypadSubtract,
        KeypadAdd,
        KeypadEnter,
        KeypadEqual,
        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Space =
        #ifdef WINDOWS
        VK_SPACE,
        #endif
        Apostrophe,
        Comma,
        Minus,
        Period,
        Slash,
        Semicolon,
        Equal,
        LeftBracket,
        Backslash,
        RightBracket,
        GraveAccent,
        KeySize = 100
    };

    enum MouseButton
    {
        LeftButton,
        RightButton,
        MiddleButton,
        MouseSize
    };

    enum MouseStyle : intptr_t
    {
        #ifdef WINDOWS
        Default                  = (intptr_t)IDC_ARROW,
        Hand                     = (intptr_t)IDC_HAND,
        IBeam                    = (intptr_t)IDC_IBEAM,
        Busy                     = (intptr_t)IDC_WAIT,
        BusyArrow                = (intptr_t)IDC_APPSTARTING,
        CrossHair                = (intptr_t)IDC_CROSS,
        UpArrow                  = (intptr_t)IDC_UPARROW,
        ResizeNorthwestSoutheast = (intptr_t)IDC_SIZENWSE,
        ResizeNortheastSouthwest = (intptr_t)IDC_SIZENESW,
        ResizeHorizontal         = (intptr_t)IDC_SIZEWE,
        ResizeVertical           = (intptr_t)IDC_SIZENS,
        ResizeAll                = (intptr_t)IDC_SIZEALL,
        Deny                     = (intptr_t)IDC_NO,
        Help                     = (intptr_t)IDC_HELP,
        Location                 = (intptr_t)IDC_PIN,
        Person                   = (intptr_t)IDC_PERSON,
        #endif
        MouseStyleSize = 16
    };

    class Application
    {
        public:
            Application();
            Application(const std::string& name, int width, int height);
            Application(const std::string& name, int width, int height, unsigned int flags);
            Application(const std::string& name, int width, int height, unsigned int flags, int minWidth, int minHeight);
            Application(const std::wstring& name, int width, int height, unsigned int flags);

            ~Application();

            void Run();

            virtual void Update();
            virtual void Draw();

            Vector2D<int> GetMousePosition();
            bool IsMouseButtonDown(MouseButton button);
            bool IsMouseButtonPressed(MouseButton button);
            bool IsMouseButtonUp(MouseButton button);

            void SetCursorStyle(MouseStyle style);
            
            bool IsKeyPressed(Keycodes keycode);
            bool IsKeyDown(Keycodes keycode);
            bool IsKeyUp(Keycodes keycode);

        protected:
            #ifdef WINDOWS
            HWND m_window;
            #endif
            int m_minWidth;
            int m_minHeight;

        private:
            std::array<bool, KeySize> m_keys, m_previousKeys;
            std::array<bool, MouseSize> m_mouseButtons, m_previousMouseButtons;
            #ifdef WINDOWS
            static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
            #endif
            friend class Graphics;
    };
}