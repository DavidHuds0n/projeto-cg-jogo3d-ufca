#ifndef RAY_H
#define RAY_H

#include "Vector.h"

/**
 * @brief Representa um raio no espa�o 3D, com uma origem e uma dire��o.
 */
struct Ray {
    Vector3f origin;
    Vector3f direction;
};

#endif // RAY_H
