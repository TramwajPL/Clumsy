#pragma once
#include "../Core/Transform.h" // to jest tak na razie tylko (bo potem on dodaje tutaj klasê CameraComponent, 
								//która sie przyda ale potrzeba do tego klasy EntityComponent i tam bd zainkludowany Transform
								// Kamera potem bêdzie u¿ywana ( z forward declaration) w Entity ( a entity w game)

namespace Clumsy {

	//Kamera reprezentuje lokalizacjê, orientacjê i projekcjê na jakich scena mo¿e byæ wyrenderowana,
	class Camera
	{
	public:

		//jak tutaj transformacja jest przekazywana to kamera nie musi byæ pod³aczona pod obiekt gry, to dzia³a troche jak Transform w unity no nie
		//  tylko ¿e on kamerê takto uzywa dopiero w Entity przekazuje j¹ jako arg do renderowania i tam robi tez ten input, który wgl torche 
		//nie wiem jak on go wgl u¿ywa 
		Camera(const glm::mat4 projection, Transform* transform) : m_Projection(projection), m_Transform(transform) {}

		Transform* GetTransform() { return m_Transform; }
		//nwm po co mu ta 2 funkcja w sumie moze to potem wyjdzie to na razie ja komentujê 
		//inline const Transform& GetTransform() const { return *m_Transform; }

		glm::mat4 GetViewProjection() const;

		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }
		inline void SetTransform(Transform* transform) { m_Transform = transform; }

	private:
		glm::mat4 m_Projection;
		Transform* m_Transform;
	};
}

// tu bd ta 2 klasa CameraComponent