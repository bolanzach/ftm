#include "mesh.h"

Mesh::Mesh() {
    this->vertices = std::vector<Vector3>();
    this->faces = std::vector<Face>();
    this->rotation = Vector3();
}

Mesh Mesh::LoadFileObj(const char *fileName) {
    FILE* file;
    file = fopen(fileName, "r");

    // TODO error handling

    printf("Reading .obj file: %s\n", fileName);
    Mesh mesh = Mesh();

    // Fix car rotation
    mesh.rotation.x = 9.45;

    char line[1024];
    while (fgets(line, 1024, file)) {
        // Vertex data
        if (strncmp(line, "v ", 2) == 0) {
            Vector3 vertex;
            sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            mesh.vertices.push_back(vertex);
        }

        // Face data
        if (strncmp(line, "f ", 2) == 0) {
            int vertexIndices[3];
            int textureIndices[3];
            int normalIndices[3];

            sscanf(
                    line,
                    "f %d/%d/%d %d/%d/%d %d/%d/%d",
                    &vertexIndices[0], &textureIndices[0], &normalIndices[0],
                    &vertexIndices[1], &textureIndices[1], &normalIndices[1],
                    &vertexIndices[2], &textureIndices[2], &normalIndices[2]
            );

            Face face = Face(vertexIndices[0], vertexIndices[1], vertexIndices[2]);
            mesh.faces.push_back(face);
        }
    }

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

float* Mesh::GetAllFaceVertexValues() {
    auto* faceVertexValues = new float[this->faces.size() * 9];

    for (int i = 0; i < this->faces.size(); i++) {
        Face face = this->faces[i];
        Vector3* faceVertices = this->GetVerticesForFace(face);

        for (int j = 0; j < 3; j++) {
            faceVertexValues[i * 9 + j * 3] = faceVertices[j].x;
            faceVertexValues[i * 9 + j * 3 + 1] = faceVertices[j].y;
            faceVertexValues[i * 9 + j * 3 + 2] = faceVertices[j].z;
        }

        delete[] faceVertices;
    }

    return faceVertexValues;

}
