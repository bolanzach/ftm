#include "face.h"

//Indices::Indices(int a, int b, int c) {
//    this->a = a;
//    this->b = b;
//    this->c = c;
//}
//
//Indices::Indices() {
//    this->a = 0;
//    this->b = 0;
//    this->c = 0;
//}

Face::Face(int a, int b, int c) {
    this->indices[0] = a;
    this->indices[1] = b;
    this->indices[2] = c;
}
