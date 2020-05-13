#pragma once

#include <irrKlang.h>

namespace Clumsy
{
	class AudioMaster
	{
	public:
		static AudioMaster* GetInstance();
		void PlayAmbientMusic();
		void PlayBell();

	private:
		AudioMaster();
		static AudioMaster* m_Instance;
		irrklang::ISoundEngine* m_SoundEngine;
	};

}