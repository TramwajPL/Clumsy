#pragma once
#include "Shader.h"
#include <string>
#include <vector>

namespace Clumsy {

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        glm::vec3 Bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };

	class Mesh {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader shader);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int VAO;

    private:
        void setupMesh();
        unsigned int VBO, EBO;
	};
}