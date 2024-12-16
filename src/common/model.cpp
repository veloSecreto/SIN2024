#include "model.h"


Model::Model() = default;

Model::Model(const std::string& path) {
    loadModel(path);
}


void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0 || !scene->mRootNode) {
        std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene);
    std::cout << "Loaded Model from path: " << path << std::endl;
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texCoord = glm::vec2(0.0f);
        }
        vertices.push_back(vertex);
    }

    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    return Mesh(vertices, indices);
}

void Model::render(Shader* shader) {
    for (auto& mesh : meshes) {
        mesh.render(shader);
    }
}

void Model::setMaterial(int meshIndex, const Material& material) {
    if (meshIndex >= 0 && meshIndex < meshes.size())
    {
        meshes[meshIndex].material = material;
    }
    else std::cout << "Mesh Index not valid, couldn't set material" << std::endl;
}