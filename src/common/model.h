#pragma once

#include "mesh.h"
#include "../common.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
    public:
        Model();
        Model(const std::string& path);

        std::vector<Mesh>& getMeshes();
        void setMaterial(int meshIndex, const Material& material);
        void render(Shader* shader);

    private:
        std::vector<Mesh> meshes;

        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};