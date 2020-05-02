#pragma once
#include "../Core/EntityComponent.h"
#include "../RenderEngine/Model.h"

namespace Clumsy {
	class RenderModelComponent : public EntityComponent {
	public:
		virtual void Render() {
			//TODO: renderowanie modelu
		}
	private:
		Model* model;

	};
}