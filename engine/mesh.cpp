#include "mesh.h"

Mesh::Mesh() {
    this->vertices = std::vector<Vector3>();
    this->faces = std::vector<Face>();
    this->rotation = Vector3();
}

Mesh Mesh::LoadFileObj(const char *fileName) {
    Mesh mesh = Mesh();

    return mesh;
}

Vector3* Mesh::GetVerticesForFace(const Face& face) {
    auto* faceVertices = new Vector3[3] {
            this->vertices[face.points[0]],
            this->vertices[face.points[1]],
            this->vertices[face.points[2]]
    };
    return faceVertices;
}

float* Mesh::GetAllFaceVertices() {
    float* vertices = new float[this->faces.size() * 9];

    for (int i = 0; i < this->faces.size(); i++) {
        Face face = this->faces[i];
        Vector3* faceVertices = this->GetVerticesForFace(face);

        for (int j = 0; j < 3; j++) {
            vertices[i * 9 + j * 3] = faceVertices[j].x;
            vertices[i * 9 + j * 3 + 1] = faceVertices[j].y;
            vertices[i * 9 + j * 3 + 2] = faceVertices[j].z;
        }
    }

    return vertices;

}
