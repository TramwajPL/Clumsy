#pragma once
#include "Mesh.h"
#include <string>
#include <vector>

namespace Clumsy {

	class Model {
	public:
        std::vector<Texture> textures_loaded;	
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

        Model(std::string const& path, bool gamma);
        void Draw(Shader shader);
        void loadModel(std::string const& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	private:
	};
}