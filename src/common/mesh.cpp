#include "mesh.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"
#include "../api/opengl/types/textureGenerator.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures) {
    this->textures = textures;

    drawCommand.indexCount = indices.size();
    drawCommand.instancedCount = 1;
    drawCommand.firstIndex = OpenGLBackend::globalIndices.size();
    drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
    drawCommand.baseInstance = 0;

    OpenGLBackend::uploadMeshData(vertices, indices, drawCommand);
}

void Mesh::render(Shader* shader) {
	for (const auto& texture : textures) {
		if (texture.type == TextureType::DIFFUSE)
		{
			shader->setInt("diffuseTexture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.ID);
			continue;
		}
		else if (texture.type == TextureType::SPECULAR)
		{
			shader->setInt("specularTexture", 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture.ID);
			continue;
		}
	}

	OpenGLRenderer::renderMesh(drawCommand);
}