#pragma once
#include "../RenderEngine/Shader.h"
#include "../RenderEngine/TextureClass.h"
#include <vector>

namespace Clumsy {

	/*Patrz�c na przyk�ad ognia, emiter cz�steczek prawdopodobnie generuje ka�d� cz�stk� z pozycj� blisk� emiterowi i 
	z pr�dko�ci� w g�r� tak, aby ka�da cz�stka porusza�a si� w pozytywnym kierunku y.Wydaje si�, �e ma 3 r�ne regiony, 
	wi�c prawdopodobnie daje cz�stkom wi�ksz� pr�dko�� ni� inne.Widzimy tak�e, �e im wy�sza pozycja cz�stki y, tym mniej jasny /
	��ty staje si� jej kolor.Po osi�gni�ciu przez cz�steczki okre�lonej wysoko�ci ich �ycie zostaje wyczerpane, a cz�steczki zostaj� 
	zabite; nigdy nie docieraj� do gwiazd.*/

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
		ParticleGenerator(Shader* shader, TextureClass texture, GLuint amount);
		void Update(GLfloat dt, GLuint newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));
		//na razie do pozycji ?
		void Draw();
	private:
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