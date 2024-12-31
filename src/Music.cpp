#include "Music.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

namespace Apollo
{
    Music::Music()
        :m_isLoaded(false), m_isPlaying(false), m_length(0.0),m_albumCover(Apollo::Graphics::Image()),m_artist("None"),m_album("None"),m_song("None"),m_year(2024)
    {
        ma_result result = ma_engine_init(NULL, &m_engine);
        m_sound = ma_sound();
    }

    Music::~Music()
    {
        if (m_isLoaded) 
        {
            ma_sound_uninit(&m_sound);
        }

        ma_engine_uninit(&m_engine);
    }

    bool Music::Load(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if (file.good())
        {
            if (m_isLoaded)
            {
                ma_sound_uninit(&m_sound);
                m_albumCover.~Image();
            }
        
            ma_result result = ma_sound_init_from_file(&m_engine, filename.c_str(), 0, NULL, NULL, &m_sound);
            if (result != MA_SUCCESS)
            {
                m_isLoaded = false;
                return false;
            }
        
            m_isLoaded = true;
        
            float length;
            if (ma_sound_get_length_in_seconds(&m_sound, &length) == MA_SUCCESS)
            {
                m_length = length;
            }
            else
            {
                m_length = -1.0;
            }

            


            return true;
        }
        
        return false;
    }

    bool Music::Load(const std::wstring& filename)
    {
        if (std::ifstream(filename).good())
        {
            if (m_isLoaded)
            {
                ma_sound_uninit(&m_sound);
                m_albumCover.~Image();
            }
        
            ma_result result = ma_sound_init_from_file_w(&m_engine, filename.c_str(), 0, NULL, NULL, &m_sound);
            if (result != MA_SUCCESS)
            {
                m_isLoaded = false;
                return false;
            }
        
            m_isLoaded = true;
        
            float length;
            if (ma_sound_get_length_in_seconds(&m_sound, &length) == MA_SUCCESS)
            {
                m_length = length;
            }
            else
            {
                m_length = -1.0;
            }
            return true;
        }

        return false;
    }

    void Music::Play()
    {
        if (!m_isLoaded) return;

        ma_sound_start(&m_sound);
        m_isPlaying = true;
    }

    void Music::Stop()
    {
        if (!m_isLoaded) return;

        ma_sound_stop(&m_sound);
        m_isPlaying = false;
    }

    void Music::SetVolume(float volume)
    {
        if (!m_isLoaded) return;

        ma_engine_set_volume(&m_engine, volume);
    }

    float Music::GetVolume()
    {
        return ma_engine_get_volume(&m_engine);
    }

    double Music::GetLength() const
    {
        return m_length;
    }

    void Music::SetCurrentPlaying(double seconds)
    {
        ma_sound_seek_to_pcm_frame(&m_sound, seconds * static_cast<double>(ma_engine_get_sample_rate(&m_engine)));
    }

    double Music::GetCurrentPlaying()
    {
        if (!m_isLoaded) return -1.0;

        float position = 0.0;
        ma_sound_get_cursor_in_seconds(&m_sound, &position);

        return position;
    }

    std::string Music::GetLengthTime() const
    {
        std::string lengthStr;



        return lengthStr;
    }

    std::string Music::GetCurrentPlayingTime()
    {
        return std::string();
    }

    void Music::initID3V2()
    {

    }

    bool Music::IsPlaying()
    {
        m_isPlaying = (bool)ma_sound_is_playing(&m_sound);

        return m_isPlaying;
    }
}