
#include "../pch.h"

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "Mesh.h"

namespace Clumsy 
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, 
		std::vector<Texture> textures, std::vector<VertexBoneData> bones)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
		this->bones = bones;

		
        setupMesh();
    }

    void Mesh::Draw(Shader shader)
    {
        // bind appropriate textures
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if (name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
            else if (name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        // draw mesh
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    void Mesh::setupMesh()
    {
		if (bones.size() == 0)
		{
			VertexBoneData bonesTEST;
			for (int i = 0; i < 1000; i++)
			{
				bonesTEST.IDs[i] = 0;
				bonesTEST.Weights[i] = 0.0f;
			}
			bones.push_back(bonesTEST);
			//std::fill(bones.begin(), bones.end(), VertexBoneData());
			std::cout << "SIZE OF BONES LATER: " << bones.size() << '\n';
		}
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        //glGenBuffers(1, &bonesBuffor);
		

        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, bonesBuffor);
		
		std::cout << "BONES SIZE LATER LATER: " << bones.size() << '\n';
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, bones.size() * sizeof(VertexBoneData), &bones[0], GL_STATIC_DRAW);
        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		////bones
		//glEnableVertexAttribArray(3);
		//glVertexAttribIPointer(3, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
		////weights
		//glEnableVertexAttribArray(4);
		//glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (void*)offsetof(VertexBoneData, Weights));

        //// vertex tangent
        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        //// vertex bitangent
        //glEnableVertexAttribArray(4);
        //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

        glBindVertexArray(0);
    }
}