#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#define NUM_BUFFERS 1

namespace Clumsy
{
	class AudioMaster
	{
	public:
		AudioMaster();
		void Init();
		void PlaySound();
		void LoadSound(std::string file, int index);
		void SetListenerData();
		void CleanUp();

	private:
		//static AudioMaster* m_Instance;
		ALCdevice* m_Device;
		ALCcontext* m_Context;
		ALuint m_Buffers[NUM_BUFFERS];
		ALuint m_Source;
	};
}