#pragma once
#include "../RenderEngine/Shader.h"
#include "../RenderEngine/TextureClass.h"
#include <vector>

namespace Clumsy {

	/*Patrz¹c na przyk³ad ognia, emiter cz¹steczek prawdopodobnie generuje ka¿d¹ cz¹stkê z pozycj¹ blisk¹ emiterowi i 
	z prêdkoœci¹ w górê tak, aby ka¿da cz¹stka porusza³a siê w pozytywnym kierunku y.Wydaje siê, ¿e ma 3 ró¿ne regiony, 
	wiêc prawdopodobnie daje cz¹stkom wiêksz¹ prêdkoœæ ni¿ inne.Widzimy tak¿e, ¿e im wy¿sza pozycja cz¹stki y, tym mniej jasny /
	¿ó³ty staje siê jej kolor.Po osi¹gniêciu przez cz¹steczki okreœlonej wysokoœci ich ¿ycie zostaje wyczerpane, a cz¹steczki zostaj¹ 
	zabite; nigdy nie docieraj¹ do gwiazd.*/

	class GameObject;

	struct Particle
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 color;

		GLfloat life;

		Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
	};

	class ParticleGenerator
	{
	public:
		ParticleGenerator(Shader* shader, TextureClass texture, GLuint amount, float x, float y);
		void Update(GLfloat dt, GLuint newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
		//na razie do pozycji ?
		void Draw();
	private:
		float m_X, m_Y;
		std::vector<Particle> m_Particles;
		GLuint m_Amount;
		Shader* m_Shader;
		TextureClass m_Texture;
		GLuint VAO;
		void init();
		GLuint firstUnusedParticle();
		glm::vec2 initialVelocity = glm::vec2(100.0f, 350.0f);
		void respawnParticle(Particle& particle, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
	};
}