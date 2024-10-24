#include "model.h"
#include "../core/asset_manager.h"


std::vector<Mesh> Model::meshes;
std::vector<Texture> Model::textures_loaded;

Model::Model(const std::string& path) {
    loadModel(path);
}

std::vector<Mesh>& Model::getMeshes() {
    return meshes;
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0 || !scene->mRootNode) {
        std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
        return; 
    }

    processNode(scene->mRootNode, scene);
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
    std::vector<Texture> textures;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }
        else {
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

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuseMaps = loadTextureMaterials(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Texture> specularMaps = loadTextureMaterials(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTextureMaterials(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for (int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        std::string name = str.C_Str();
<<<<<<< HEAD
        name = name.substr(name.find_last_of('\\') + 1, name.length()); // I can't do this in one line
=======
        name = name.substr((name.find('/') != std::string::npos ? name.find_last_of('/') : name.find_last_of('\\')) + 1, name.length()); // I can't do this in one line
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
        name = name.substr(0, name.find_last_of('.')); // fuck, literally find_last_of is buggy
        for (int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].getName().data(), name.c_str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture = AssetManager::getTextureByName(name);
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
<<<<<<< HEAD
=======
}

void Model::render() {
    for (auto& mesh : meshes) {
        mesh.render();
    }
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}