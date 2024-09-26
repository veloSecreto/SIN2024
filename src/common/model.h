#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
    public:
        Model(const std::string& path) {
            loadModel(path);
        }

        void draw(Shader& shader) {
            for (int i = 0; i < meshes.size(); i++) {
                meshes[i].draw(shader);
            }
        }

        std::vector<Mesh>& getMeshes() {
            return meshes;
        }

    private:
        std::string directory;
        std::vector<Mesh> meshes;
        std::vector<Texture> textures_loaded;
        
        void loadModel(std::string path) {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

            if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0 || !scene->mRootNode) {
                std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
                return; 
            }

            directory = path.substr(0, path.find_last_of('/'));
            processNode(scene->mRootNode, scene);
        }

        void processNode(aiNode* node, const aiScene* scene) {
            for (int i = 0; i < node->mNumMeshes; i++) {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(mesh, scene));
            }

            for (int i = 0; i < node->mNumChildren; i++) {
                processNode(node->mChildren[i], scene);
            }
        }

        Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
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

        std::vector<Texture> loadTextureMaterials(aiMaterial* mat, aiTextureType type, std::string typeName) {
            std::vector<Texture> textures;

            for (int i = 0; i < mat->GetTextureCount(type); i++) {
                aiString str;
                mat->GetTexture(type, i, &str);
                bool skip = false;
                for (int j = 0; j < textures_loaded.size(); j++) {
                    if (std::strcmp(textures_loaded[j].getPath().data(), str.C_Str()) == 0) {
                        textures.push_back(textures_loaded[j]);
                        skip = true;
                        break;
                    }
                }
                if (!skip) {
                    Texture texture(directory + str.C_Str(), typeName, str.C_Str());
                    textures.push_back(texture);
                    textures_loaded.push_back(texture);
                }
            }

            return textures;
        }
};