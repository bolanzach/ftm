#ifndef FTM_FACE_H
#define FTM_FACE_H

#include "vector.h"

// A Face is a 3D Triangle. It contains an array of 3 indices to the Mesh's vertices. These 3
// Vertices are the 3 points of the Triangle Face.
class Face {
public:
    int points[3];

    Face(int a, int b, int c);
};

#endif //FTM_FACE_H
