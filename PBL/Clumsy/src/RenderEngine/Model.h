#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>

#include "Mesh.h"

namespace Clumsy 
{
	class Model 
    {
	public:
        std::vector<Texture> textures_loaded;	
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;
		glm::mat4 m_GlobalInverseTransform;

		Model() {};
        Model(std::string const& path, bool gamma = false);
        void Draw(Shader shader);
        void loadModel(std::string const& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		inline glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4* from);
	
		std::map<std::string, unsigned int> m_BoneMapping;
		unsigned int numBones;
		glm::mat4 BoneOffset = glm::mat4(1.0f);
		glm::mat4 FinalTransformation = glm::mat4(1.0f);
	};
}