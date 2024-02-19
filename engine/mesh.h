#ifndef FTM_MESH_H
#define FTM_MESH_H

#include <vector>
#include "vector.h"
#include "face.h"

// A Mesh is a collection of Vertices, Faces, and Textures arranged in 3D space.
class Mesh {
public:
    Mesh();

    static Mesh LoadFileObj(const char* fileName);

    // All the 3D Vertices in the Mesh
    std::vector<Vector3> vertices;

    // All the 3D Faces in the Mesh
    std::vector<Face> faces;

    // The Mesh's rotation
    Vector3 rotation;

    Vector3* GetVerticesForFace(const Face& face);

    float* GetAllFaceVertexValues();
};

#endif //FTM_MESH_H
