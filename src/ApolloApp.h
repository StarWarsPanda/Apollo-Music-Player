#pragma once

#include <functional>

#include "Application.h"
#include "Graphics.h"
#include "Music.h"
#include "FileSelector.h"

class Button
{
    public:
        Button(int x, int y, int width, int height, Apollo::Keycodes shortcut = Apollo::Keycodes::Unknown) : m_bounds(Apollo::Graphics::Rectangle(x,y,width,height)), m_shortcutKey(shortcut) {}
        Button(Apollo::Graphics::Rectangle bounds,  Apollo::Keycodes shortcut = Apollo::Keycodes::Unknown) : m_bounds(bounds), m_shortcutKey(shortcut) {}
        ~Button() {}

        void Update();
        void Draw(Apollo::Graphics& graphics);

    protected:
        Apollo::Graphics::Rectangle m_bounds;
        Apollo::Keycodes m_shortcutKey;
        std::function<void()> m_trigger;
};

class ApolloApp : public Apollo::Application
{
    public:
        ApolloApp(const std::string& name, int width, int height) : Apollo::Application(name, width, height), hasSucceeded(false), volume(1.0) {}

        ~ApolloApp() { Application::~Application(); }

        void Update() override;
        void Draw() override;

    private:
        Apollo::Music m_music;
        double volume;
        bool hasSucceeded;
};