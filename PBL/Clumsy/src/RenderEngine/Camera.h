#pragma once

#include "../Core/Timestep.h"
#include "../Core/Transform.h" 

namespace Clumsy {

	//Kamera reprezentuje lokalizacjê, orientacjê i projekcjê na jakich scena mo¿e byæ wyrenderowana,
	class Camera
	{
	public:

		Camera(const glm::mat4 projection, Transform* transform) :
			m_Projection(projection),
			m_Transform(transform) {}

		Transform* GetTransform() { return m_Transform; }
		inline const Transform& GetTransform() const { return *m_Transform; }

		glm::mat4 GetViewProjection() const;

		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }
		inline void SetTransform(Transform* transform) { m_Transform = transform; }

		void RecalculateViewMatrix();

	private:
		glm::mat4 m_Projection;
		Transform* m_Transform;
	};


	//CameraComponents are an easy way to use a camera as a component
	//on a game object.
	class CameraComponent //: public EntityComponent
	{
	public:
		//The camera's transform is initialized to 0 (null) because
		//at construction, this isn't attached to a game object,
		//and therefore doesn't have access to a valid transform.
		CameraComponent(const glm::mat4& projection) :
			m_Camera(projection, 0),
			m_AspectRatio(1280.0f / 720.0f) {}

		//virtual void AddToEngine(CoreEngine* engine) const;

		//inline Matrix4f GetViewProjection() const { return m_camera.GetViewProjection(); }

		inline void SetProjection(const glm::mat4& projection) { m_Camera.SetProjection(projection); }
		//virtual void SetParent(Entity* parent);

		////// CONTROLLER

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		Camera& GetCamera() { return m_Camera; }
		const Camera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

	private:
		Camera m_Camera; //The camera that's being used like a component.

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
	};
}