#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Vector.h"

/**
 * @brief Representa uma parede na sala.
 * Renderiza um paralelepípedo com as dimensões especificadas.
 */
class Wall : public GameObject {
public:
    /**
     * @param position Posição do centro da parede no mundo.
     * @param size Largura (x), altura (y) e profundidade (z) da parede.
     */
    Wall(const Vector3f& position, const Vector3f& size);

    virtual void update(float deltaTime) override;
    virtual void render() override;

private:
    Vector3f _position;
    Vector3f _size;
};

#endif // WALL_H
