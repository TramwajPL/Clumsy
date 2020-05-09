#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#define NUM_BUFFERS 3

namespace Clumsy
{
	class AudioMaster
	{
	public:
		AudioMaster();
		static void Init();
		static int LoadSound(std::string file);
		static void SetListenerData();
		static void CleanUp();

	private:
		static ALCdevice* m_Device;
		static ALCcontext* m_Context;
		static ALuint m_Buffers[NUM_BUFFERS];
		static ALuint m_Source;
	};
}