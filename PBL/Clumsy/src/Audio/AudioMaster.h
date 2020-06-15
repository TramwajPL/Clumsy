#pragma once

#include <irrKlang.h>
#include "../EventSystem/Listener.h"

namespace Clumsy
{
	class AudioMaster : public Listener
	{
	public:
		static AudioMaster* GetInstance();
		void PlayAmbientMusic();
		void PlayBell();
		void PlayWalk();
		void Drop();
		void HandleEvent(Event* event);

	private:
		AudioMaster();
		static AudioMaster* m_Instance;
		irrklang::ISoundEngine* m_SoundEngine;
	};

}