#include "ApolloApp.h"

void ApolloApp::Update()
{
    Apollo::Graphics graphics(*this);

    if (!hasSucceeded)
    {
        std::wstring filename = Apollo::FileSelector::SelectFile(L"Music(*.mp3)\1*.mp3\1All Files(*.*)\1*.*\1\1", L'\1');

        if (m_music.Load(filename))
        {
            m_music.Play();
            hasSucceeded = true;

            volume = m_music.GetVolume();
        }
    }

    if (IsKeyPressed(Apollo::Keycodes::Space))
    {
        if (m_music.IsPlaying())
        {
            m_music.Stop();
        }
        else
        {
            m_music.Play();
        }
    }

    if (Apollo::Graphics::RectanglePointCollision((graphics.m_width / 2) - 15, graphics.m_height - 60, 30, 40, GetMousePosition().x, GetMousePosition().y) && IsMouseButtonPressed(Apollo::MouseButton::LeftButton))
    {
        if (m_music.IsPlaying())
        {
            m_music.Stop();
        }
        else
        {
            m_music.Play();
        }
    }

    if (IsKeyPressed(Apollo::E))
    {
        m_music.Stop();
        m_music.SetCurrentPlaying(130.0);
        m_music.Play();
    }

    if (IsKeyPressed(Apollo::Left))
    {
        m_music.Stop();
        m_music.SetCurrentPlaying(std::max(m_music.GetCurrentPlaying() - 10.0, 0.0));
    }

    if (IsKeyPressed(Apollo::Right))
    {
        m_music.Stop();
        m_music.SetCurrentPlaying(std::min(m_music.GetCurrentPlaying() + 10.0, m_music.GetLength()));
    }

    if (IsKeyPressed(Apollo::Down))
    {
        m_music.SetVolume(std::max(m_music.GetVolume() - 0.05, 0.0));
    }

    if (IsKeyPressed(Apollo::Up))
    {
        m_music.SetVolume(std::min(m_music.GetVolume() + 0.05, 1.0));
    }

    hasSucceeded = hasSucceeded && (m_music.IsPlaying() || (m_music.GetCurrentPlaying() - m_music.GetLength() < 0.0));
}

void ApolloApp::Draw()
{
    Apollo::Graphics graphics(*this);

    graphics.Clear(Apollo::Graphics::Color(12, 12, 24));

    graphics.DrawFillRectangle(80, graphics.m_height - 100, graphics.m_width - 160, 20, Apollo::Graphics::Color(127, 127, 127));
    graphics.DrawFillRectangle(80, graphics.m_height - 100, maprange(m_music.GetCurrentPlaying() / m_music.GetLength(), 0.0, 1.0, 0.0, graphics.m_width - 160), 20, Apollo::Graphics::Color(224, 127, 0));

    graphics.DrawSlider(volume, 1.0, 0.0, 5, 5, 20, 100, Apollo::Graphics::Color(224, 108, 24), Apollo::Graphics::Color(24, 24, 48));

    int currentSeconds = static_cast<int>(m_music.GetCurrentPlaying());
    int secondsLeft = static_cast<int>(m_music.GetLength()) - currentSeconds;

    graphics.DrawText(std::format("{:02}:{:02}:{:02}", currentSeconds / 3600, (currentSeconds / 60) % 60, currentSeconds % 60).c_str(), 15, graphics.m_height - 99, 200, 100, Apollo::Graphics::Color::White);
    graphics.DrawText(std::format("{:02}:{:02}:{:02}", secondsLeft / 3600, (secondsLeft / 60) % 60, secondsLeft % 60).c_str(), graphics.m_width - 70, graphics.m_height - 99, 200, 100, Apollo::Graphics::Color::White);

    if (m_music.IsPlaying())
    {
        graphics.DrawFillRectangle((graphics.m_width / 2) - 15, graphics.m_height - 60, 10, 40, Apollo::Graphics::Color(191, 191, 191));
        graphics.DrawFillRectangle((graphics.m_width / 2) + 5, graphics.m_height - 60, 10, 40, Apollo::Graphics::Color(191, 191, 191));
    }
    else
    {
        graphics.DrawFillTriangle((graphics.m_width / 2) - 15, graphics.m_height - 60, (graphics.m_width / 2) + 15, graphics.m_height - 40, (graphics.m_width / 2) - 15, graphics.m_height - 20, Apollo::Graphics::Color(191, 191, 191));
    }

    m_music.SetVolume(volume);

    graphics.Present();
}