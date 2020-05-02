#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Clumsy {

	class Model {
	public:
        std::vector<Texture> textures_loaded;	
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

		Model() {};
        Model(std::string const& path, bool gamma = false);
        void Draw(Shader shader);
        void loadModel(std::string const& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	private:
	};
}