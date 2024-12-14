#include "mesh.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"


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
			shader->setInt("diffuseIndex", texture.index);
			continue;
		}
		else if (texture.type == TextureType::SPECULAR)
		{
			shader->setInt("specularIndex", texture.index);
			continue;
		}
	}

	OpenGLRenderer::renderMesh(drawCommand);
}