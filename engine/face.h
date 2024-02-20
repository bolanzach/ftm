#ifndef FTM_FACE_H
#define FTM_FACE_H

#include "vector.h"

//class Indices {
//public:
//    int a;
//    int b;
//    int c;
//
//    Indices(int a, int b, int c);
//
//    Indices();
//};

// A Face is a 3D Triangle. It contains an array of 3 indices to the Mesh's vertices. These 3
// Vertices are the 3 indices of the Triangle Face.
class Face {
public:
    int indices[3];
//    Indices indices;

    Face(int a, int b, int c);
};

#endif //FTM_FACE_H
