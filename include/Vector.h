#ifndef VECTOR_H
#define VECTOR_H

struct Vector2f {
    float x, y;
};

struct Vector3f {
    float x, y, z;
};

// --- ADICIONE ISTO ---
struct BoundingBox {
    Vector3f min; // O canto (x,y,z) com os menores valores
    Vector3f max; // O canto (x,y,z) com os maiores valores
};

#endif // VECTOR_H
