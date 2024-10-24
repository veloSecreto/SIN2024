#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
    public:
        static std::vector<Mesh> meshes;
        static std::vector<Texture> textures_loaded;

        Model(const std::string& path);
        std::vector<Mesh>& getMeshes();
        void render();
        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadTextureMaterials(aiMaterial* mat, aiTextureType type, std::string typeName);
};