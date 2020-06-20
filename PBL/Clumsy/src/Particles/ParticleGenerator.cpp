//#include "ParticleGenerator.h"
//
//
//
//#include "../Core/Transform.h"
//
//namespace Clumsy {
//
//	ParticleGenerator::ParticleGenerator(Shader* shader, TextureClass texture, GLuint amount, float x, float y, float z)
//	: m_Shader(shader), m_Texture(texture), m_Amount(amount), m_X(x), m_Y(y), m_Z(z)
//	{
//		this->init();
//	}
//
//	void ParticleGenerator::Update(GLfloat dt, GLuint newParticles, Transform treeTransform, glm::vec3 offset)
//	{
//		//std::cout << "UPDATE PARTICLE!!!!!!!!!!!" << std::endl;
//		// Add new particles 
//		for (GLuint i = 0; i < newParticles; ++i)
//		{
//			int unusedParticle = this->firstUnusedParticle();
//			this->respawnParticle(this->m_Particles[unusedParticle], treeTransform, offset);
//		}
//		// Update all particles
//		for (GLuint i = 0; i < this->m_Amount; ++i)
//		{
//			Particle& p = this->m_Particles[i];
//			p.life -= dt; // reduce life
//			if (p.life > 0.0f)
//			{	// particle is alive, thus update
//				p.position -= p.velocity * dt; //tu chyba
//				p.color.a -= dt * 2.5;
//			}
//		}
//	}
//
//	// Render all particles
//	void ParticleGenerator::Draw()
//	{
//		//std::cout << "DRAWWWWW PARTICLE!!!!!!!!!!!" << std::endl;
//		//// Use additive blending to give it a 'glow' effect
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//		this->m_Shader->use();
//		for (Particle particle : this->m_Particles)
//		{
//			if (particle.life > 0.0f)
//			{
//				this->m_Shader->setVec3("offset", particle.position);
//				this->m_Shader->setVec4("color", particle.color);
//				this->m_Shader->setFloat("life", particle.life);
//				this->m_Texture.Bind();
//				glBindVertexArray(this->VAO);
//				glDrawArrays(GL_TRIANGLES, 0, 6);
//				glBindVertexArray(0);
//			}
//		}
//		// Don't forget to reset to default blending mode
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	}
//
//	void ParticleGenerator::init()
//	{
//		// Set up mesh and attribute properties
//		GLuint VBO;
//		GLfloat particle_quad[] = {
//			0.0f, 1.0f, 0.0f, 1.0f,
//			1.0f, 0.0f, 1.0f, 0.0f,
//			0.0f, 0.0f, 0.0f, 0.0f,
//
//			0.0f, 1.0f, 0.0f, 1.0f,
//			1.0f, 1.0f, 1.0f, 1.0f,
//			1.0f, 0.0f, 1.0f, 0.0f
//		};
//		glGenVertexArrays(1, &this->VAO);
//		glGenBuffers(1, &VBO);
//		glBindVertexArray(this->VAO);
//		// Fill mesh buffer
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
//		// Set mesh attributes
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
//		glBindVertexArray(0);
//
//		// Create this->amount default particle instances
//		for (GLuint i = 0; i < this->m_Amount; ++i)
//			this->m_Particles.push_back(Particle());
//	}
//
//	// Stores the index of the last particle used (for quick access to next dead particle)
//	GLuint lastUsedParticle = 0;
//	GLuint ParticleGenerator::firstUnusedParticle()
//	{
//		// First search from last used particle, this will usually return almost instantly
//		for (GLuint i = lastUsedParticle; i < this->m_Amount; ++i) {
//			if (this->m_Particles[i].life <= 0.0f) {
//				lastUsedParticle = i;
//				return i;
//			}
//		}
//		// Otherwise, do a linear search
//		for (GLuint i = 0; i < lastUsedParticle; ++i) {
//			if (i >= this->m_Particles.size())
//			{
//				std::cout << "THIS IS NOT GOOD" << std::endl;
//				lastUsedParticle = 0;
//				return 0;
//			}
//			if (this->m_Particles[i].life <= 0.0f) {
//				lastUsedParticle = i;
//				return i;
//			}
//		}
//		// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
//		lastUsedParticle = 0;
//		return 0;
//	}
//
//	void ParticleGenerator::respawnParticle(Particle& particle, Transform treeTransform, glm::vec3 offset)
//	{
//		GLfloat random = ((rand() % 1000) - 500) / 10.0f;
//		GLfloat rColor = 0.5 + ((rand() % 100) / 200.0f);
//		particle.position.x = treeTransform.GetPos().x;// +(((rand() % 100) / 600.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f);
//		particle.position.y = treeTransform.GetPos().y;// +(((rand() % 100) / 800.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f);
//		particle.position.z = treeTransform.GetPos().z;// +((rand() % 100) / 250.0f); //wyzej? jak mniejsza wartoœæ?
//		//particle.position = treeTransform.GetPos() + ((rand() % 100) / 350.0f);
//		//particle.position.z = m_Z + random + (34.5f/2);
//		particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
//		particle.life = 0.6f;
//		particle.velocity = initialVelocity + glm::vec3(((rand() % 100) / 3000.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f, ((rand() % 100) / 3000.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f, 0.0f);
//		particle.velocity *= 0.0001f;
//	}
//
//	//void ParticleGenerator::respawnParticle(Particle& particle, glm::vec3 offset)
//	//{
//	//	GLfloat random = ((rand() % 1000) -	500) / 10.0f;
//	//	GLfloat rColor = 0.5 + ((rand() % 100) / 200.0f);
//	//	particle.position.x = m_X + (((rand() % 100) / 800.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f);
//	//	particle.position.y = m_Y + (((rand() % 100) / 800.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f);
//	//	particle.position.z = m_Z + ((rand() % 100) / 350.0f);
//	//	//particle.position.z = m_Z + random + (34.5f/2);
//	//	particle.color = glm::vec4(rColor, rColor, rColor, 1.0f);
//	//	particle.life = 3.0f;
//	//	particle.velocity = initialVelocity + glm::vec3(((rand() % 100) / 3000.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f, ((rand() % 100) / 3000.0f) * (((rand() % 100) / 100.0f) - 0.5f) * 2.0f, 0.0f);
//	//	particle.velocity *= 0.01f;
//	//}
//
//}