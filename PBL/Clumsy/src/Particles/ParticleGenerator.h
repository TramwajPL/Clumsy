//#pragma once
//#include "../RenderEngine/Shader.h"
//#include "../RenderEngine/TextureClass.h"
//#include <vector>
//
//namespace Clumsy {
//
//	class Transform;
//
//	struct Particle
//	{
//		glm::vec3 position;
//		glm::vec3 velocity;
//		glm::vec4 color;
//
//		GLfloat life;
//
//		Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
//	};
//
//	class ParticleGenerator
//	{
//	public:
//		ParticleGenerator(Shader* shader, TextureClass texture, GLuint amount, float x, float y, float z);
//		void Update(GLfloat dt, GLuint newParticles, Transform treeTransform, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
//		//na razie do pozycji ?
//		void Draw();
//	private:
//		float m_X, m_Y, m_Z;
//		std::vector<Particle> m_Particles;
//		GLuint m_Amount;
//		Shader* m_Shader;
//		TextureClass m_Texture;
//		GLuint VAO;
//		void init();
//		GLuint firstUnusedParticle();
//		glm::vec3 initialVelocity = glm::vec3(0.0f, 0.0f, 0.3f);
//		void respawnParticle(Particle& particle,Transform treeTransform, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
//	};
//}