#pragma once

#include "mesh.h"
#include "../common.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "aabb.hpp"

class Model {
    public:
        std::vector<Mesh> meshes;
        AABB localAABB;

        Model();
        Model(const std::string& path);
        
        void setMaterial(int meshIndex, const Material& material);
        void render(Shader* shader);

    private:
        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};