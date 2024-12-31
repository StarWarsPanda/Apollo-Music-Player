#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "external/miniaudio.h"

#include "Graphics.h"

namespace Apollo
{
    class Music 
    {
        public:
            Music();
            ~Music();

            bool Load(const std::string& filename);
            bool Load(const std::wstring& filename);

            void Play();
            void Stop();
            bool IsPlaying();

            void SetVolume(float volume);
            float GetVolume();

            double GetLength() const;
            void SetCurrentPlaying(double seconds);
            double GetCurrentPlaying();
            std::string GetLengthTime() const;
            std::string GetCurrentPlayingTime();
        private:
            void initID3V2();

        private:
            ma_engine m_engine;
            ma_sound m_sound;
            bool m_isLoaded;
            bool m_isPlaying;
            double m_length;

            Apollo::Graphics::Image m_albumCover;
            std::string m_artist;
            std::string m_album;
            std::string m_song;
            uint16_t m_year;
    };
}