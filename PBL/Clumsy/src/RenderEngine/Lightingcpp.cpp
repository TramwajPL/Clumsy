#include "Lighting.h"
#include "../Core/CoreEngine.h"

namespace Clumsy {

	void BaseLight::AddToEngine(CoreEngine* engine) const
	{
		engine->GetRenderEngine()->AddLights(*this);
	}
}