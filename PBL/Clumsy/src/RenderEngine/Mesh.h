#pragma once

#include "Shader.h"


namespace Clumsy 
{
    struct Vertex 
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
		unsigned int ID;
       // glm::vec3 Tangent;
        //glm::vec3 Bitangent;
    };

    struct Texture 
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

	struct VertexBoneData
	{
		unsigned int IDs[4];
		float Weights[4];

		void AddBoneData(unsigned int BoneID, float Weight)
		{
			for (unsigned int i = 0; i < (sizeof(IDs)/sizeof(IDs[0])); i++) {
				if (Weights[i] == 0.0) {
					IDs[i] = BoneID;
					Weights[i] = Weight;
					return;
				}
			}

			// should never get here - more bones than we have space for
			assert(0);
		}
	};

	class Mesh 
    {
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
			std::vector<Texture> textures, std::vector<VertexBoneData> bones);
        void Draw(Shader shader);

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
		std::vector<VertexBoneData> bones;
        unsigned int VAO;

    private:
        void setupMesh();
        unsigned int VBO, EBO, bonesBuffor;
	};
}