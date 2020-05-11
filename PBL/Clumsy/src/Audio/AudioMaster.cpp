
#include "../pch.h"

#include "AudioMaster.h"

namespace Clumsy
{
    static bool IsBigEndian(void)
    {
        int a = 1;
        return !((char*)&a)[0];
    }

    static int ConvertToInt(char* buffer, int len)
    {
        int a = 0;

        if (!IsBigEndian())
        {
            for (int i = 0; i < len; ++i)
            {
                ((char*)&a)[i] = buffer[i];
            }
        }
        else
        {
            for (int i = 0; i < len; ++i)
            {
                ((char*)&a)[3 - i] = buffer[i];
            }
        }

        return a;
    }

    //Location and size of data is found here: http://www.topherlee.com/software/pcm-tut-wavformat.html
    static char* LoadWAV(std::string filename, int& channels, int& sampleRate, int& bps, int& size)
    {
        char buffer[4];

        std::ifstream in(filename.c_str());
        in.read(buffer, 4);

        if (strncmp(buffer, "RIFF", 4) != 0)
        {
            std::cout << "Error here, not a valid WAV file, RIFF not found in header\n This was found instead: "
                << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
        }

        in.read(buffer, 4);//size of file. Not used. Read it to skip over it.  

        in.read(buffer, 4);//Format, should be WAVE

        if (strncmp(buffer, "WAVE", 4) != 0)
        {
            std::cout << "Error here, not a valid WAV file, WAVE not found in header.\n This was found instead: "
                << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
        }

        in.read(buffer, 4);//Format Space Marker. should equal fmt (space)

        if (strncmp(buffer, "fmt ", 4) != 0)
        {
            std::cout << "Error here, not a valid WAV file, Format Marker not found in header.\n This was found instead: "
                << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
        }

        in.read(buffer, 4);//Length of format data. Should be 16 for PCM, meaning uncompressed.

        if (ConvertToInt(buffer, 4) != 16)
        {
            std::cout << "Error here, not a valid WAV file, format length wrong in header.\n This was found instead: "
                << ConvertToInt(buffer, 4) << std::endl;
        }

        in.read(buffer, 2);//Type of format, 1 = PCM

        if (ConvertToInt(buffer, 2) != 1)
        {
            std::cout << "Error here, not a valid WAV file, file not in PCM format.\n This was found instead: "
                << ConvertToInt(buffer, 4) << std::endl;
        }

        in.read(buffer, 2);//Get number of channels. 

        //Assume at this point that we are dealing with a WAV file. This value is needed by OpenAL
        channels = ConvertToInt(buffer, 2);

        in.read(buffer, 4);//Get sampler rate. 

        sampleRate = ConvertToInt(buffer, 4);

        //Skip Byte Rate and Block Align. Maybe use later?
        in.read(buffer, 4);//Block Align
        in.read(buffer, 2);//ByteRate

        in.read(buffer, 2);//Get Bits Per Sample

        bps = ConvertToInt(buffer, 2);

        //Skip character data, which marks the start of the data that we care about. 
        in.read(buffer, 4);//"data" chunk. 

        in.read(buffer, 4); //Get size of the data

        size = ConvertToInt(buffer, 4);

        if (size < 0)
        {
            std::cout << "Error here, not a valid WAV file, size of file reports 0.\n This was found instead: "
                << size << std::endl;
        }

        char* data = new char[size];

        in.read(data, size);//Read audio data into buffer, return.

        in.close();

        return data;
    }

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

        SetListenerData();
        LoadSound("lameshot.wav", 0);
    }

    void AudioMaster::PlaySound()
    {
        alSourcePlay(m_Source);
    }

    void AudioMaster::LoadSound(std::string filename, int index)
    {
        unsigned int format = AL_FORMAT_MONO8;
        int channel, sampleRate, bps, size;
        char* data = LoadWAV(filename, channel, sampleRate, bps, size);
        //ALvoid* data = LoadWAV(filename, int& channels, int& sampleRate, int& bps, int& size;
        //alutLoadWAVFile(file, &format, &data, &size, &freq, &loop);
        alBufferData(m_Buffers[0], format, data, size, sampleRate);
        alSourcei(m_Source, AL_BUFFER, m_Buffers[0]);

        //alutUnloadWAV(format, data, size, freq);
    }    

    void AudioMaster::SetListenerData()
    {
        alListener3f(AL_POSITION, 0, 0, 1.0f);
        alListener3f(AL_VELOCITY, 0, 0, 0);
    }

    void AudioMaster::CleanUp()
    {
        m_Context = alcGetCurrentContext();
        m_Device = alcGetContextsDevice(m_Context);
        alDeleteSources(1, &m_Source);
        alDeleteBuffers(NUM_BUFFERS, m_Buffers);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_Context);
        alcCloseDevice(m_Device);
    }
}
