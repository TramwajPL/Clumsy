#include "GameObject.h"

namespace Clumsy {

	Clumsy::GameObject::GameObject(Transform transform) 
		: m_Transform(transform)
	{

	}

	Transform Clumsy::GameObject::GetTransform() {
		return m_Transform;
	}


}