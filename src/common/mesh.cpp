#include "mesh.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"
#include "../api/opengl/types/textureGenerator.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    drawCommand.indexCount = indices.size();
    drawCommand.instancedCount = 1;
    drawCommand.firstIndex = OpenGLBackend::globalIndices.size();
    drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
    drawCommand.baseInstance = 0;

    OpenGLBackend::uploadMeshData(vertices, indices, drawCommand);
}

void Mesh::render(Shader* shader) {
	if (material.albedo.ID != -1)
	{
		shader->setInt("material.albedo", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material.albedo.ID);
	}
	if (material.roughness.ID != -1)
	{
	shader->setInt("material.roughness", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, material.roughness.ID);
	}
	if (material.metallic.ID != -1)
	{
	shader->setInt("material.metallic", 2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, material.metallic.ID);
	}
	if (material.ao.ID != -1)
	{
	shader->setInt("material.ao", 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, material.ao.ID);
	}
	OpenGLRenderer::renderMesh(drawCommand);
}