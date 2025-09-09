#include "MeshLine.h"

MeshLine::MeshLine(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
: Mesh(vertices, indices) {
}

void MeshLine::Render(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}
