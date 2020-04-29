#pragma once
#include "../Core/Transform.h" // to jest tak na razie tylko (bo potem on dodaje tutaj klas� CameraComponent, 
								//kt�ra sie przyda ale potrzeba do tego klasy EntityComponent i tam bd zainkludowany Transform
								// Kamera potem b�dzie u�ywana ( z forward declaration) w Entity ( a entity w game)

namespace Clumsy {

	//Kamera reprezentuje lokalizacj�, orientacj� i projekcj� na jakich scena mo�e by� wyrenderowana,
	class Camera
	{
	public:

		//jak tutaj transformacja jest przekazywana to kamera nie musi by� pod�aczona pod obiekt gry, to dzia�a troche jak Transform w unity no nie
		//  tylko �e on kamer� takto uzywa dopiero w Entity przekazuje j� jako arg do renderowania i tam robi tez ten input, kt�ry wgl torche 
		//nie wiem jak on go wgl u�ywa 
		Camera(const glm::mat4 projection, Transform* transform) : 
			m_Projection(projection), 
			m_Transform(transform) {}

		Transform* GetTransform() { return m_Transform; }
		inline const Transform& GetTransform() const { return *m_Transform; }

		glm::mat4 GetViewProjection() const;

		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }
		inline void SetTransform(Transform* transform) { m_Transform = transform; }

	private:
		glm::mat4 m_Projection;
		Transform* m_Transform;
	};
}

// tu bd ta 2 klasa CameraComponent