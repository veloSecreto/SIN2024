#pragma once

#include "mesh.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../physics/aabb.hpp"

struct Model {
    public:
        std::vector<Mesh> meshes;
        AABB localAABB;

        Model() = default;
        Model(const std::string& path);
        void setMaterial(int meshIndex, const Material& material);

    private:
        void loadModel(const std::string& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};