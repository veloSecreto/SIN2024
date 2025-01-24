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

    OpenGLBackend::uploadMeshData(vertices, indices);
}

void Mesh::render(Shader* shader) {
	
	shader->setInt("material.albedo", 0);
	glBindTextureUnit(0, material.albedo.ID);

	shader->setInt("material.roughness", 1);
	glBindTextureUnit(1, material.roughness.ID);

	shader->setInt("material.metallic", 2);
	glBindTextureUnit(2, material.metallic.ID);

	shader->setInt("material.ao", 3);
	glBindTextureUnit(3, material.ao.ID);
	
	OpenGLRenderer::renderMesh(drawCommand);
}