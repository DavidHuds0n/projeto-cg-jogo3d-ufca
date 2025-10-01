#ifndef RAY_H
#define RAY_H

#include "Vector.h"

/**
 * @brief Representa um raio no espaço 3D, com uma origem e uma direção.
 */
struct Ray {
    Vector3f origin;
    Vector3f direction;
};

#endif // RAY_H
