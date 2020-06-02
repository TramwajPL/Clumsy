
#include "../pch.h"

#include "AudioMaster.h"

namespace Clumsy
{
    AudioMaster* AudioMaster::GetInstance()
    {
        if (!m_Instance)
            m_Instance = new AudioMaster;
        return m_Instance;
    }

    void AudioMaster::PlayAmbientMusic()
    {
        m_SoundEngine->play2D("../Clumsy/src/Audio/ophelia.mp3", true);
    }

    void AudioMaster::PlayBell()
    {
        m_SoundEngine->play2D("../Clumsy/src/Audio/bell.wav", false);
    }

    void AudioMaster::Drop()
    {
        m_SoundEngine->drop();
    }

    AudioMaster::AudioMaster()
    {
        m_SoundEngine = irrklang::createIrrKlangDevice();
    }

	void AudioMaster::HandleEvent(Event* event)
	{
		if (event->GetEventId() == "scroll")
		{
			PlayBell();
		}
		
	}
}
