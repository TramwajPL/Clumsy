
#include "../pch.h"

#include "AudioMaster.h"

namespace Clumsy
{
    AudioMaster::AudioMaster()
    {
        Init();
    }

    void AudioMaster::Init()
    {
        m_Device = alcOpenDevice(NULL);
        if (m_Device)
        {
            m_Context = alcCreateContext(m_Device, NULL);
            alcMakeContextCurrent(m_Context);
        }

        alGetError();

        alGenBuffers(NUM_BUFFERS, m_Buffers);
        if (alGetError() != AL_NO_ERROR)
        {
            std::cout << "Error generating buffers" << std::endl;
            return;
        }

        alGenSources(1, &m_Source);
        alSourcef(m_Source, AL_PITCH, 1);
        alSourcef(m_Source, AL_GAIN, 1);
        alSource3f(m_Source, AL_POSITION, 0, 0, 0);
        alSource3f(m_Source, AL_VELOCITY, 0, 0, 0);
        alSourcei(m_Source, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR)
        {
            std::cout << "Error generating source" << std::endl;
            return;
        }
    }

    int AudioMaster::LoadSound(std::string file)
    {
        //alutLoadWAVFile()
    }

    void AudioMaster::SetListenerData()
    {
        alListener3f(AL_POSITION, 0, 0, 1.0f);
        alListener3f(AL_VELOCITY, 0, 0, 0);
    }

    void AudioMaster::CleanUp()
    {
        alDeleteSources(1, &m_Source);
        alDeleteBuffers(NUM_BUFFERS, m_Buffers);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_Context);
        alcCloseDevice(m_Device);
    }
}
