#ifndef FLOOR_H
#define FLOOR_H

#include "GameObject.h"
#include "Vector.h"

/**
 * @brief Representa o chão da sala.
 * Renderiza um paralelepípedo plano e fino.
 */
class Floor : public GameObject {
public:
    /**
     * @param position Posição do centro do chão no mundo.
     * @param size Largura (x) e profundidade (z) do chão.
     */
    Floor(const Vector3f& position, const Vector2f& size);

    virtual void update(float deltaTime) override;
    virtual void render() override;

private:
    Vector3f _position;
    Vector2f _size;
};

#endif // FLOOR_H
