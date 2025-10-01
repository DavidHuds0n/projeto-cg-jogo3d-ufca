#ifndef FLOOR_H
#define FLOOR_H

#include "GameObject.h"
#include "Vector.h"

/**
 * @brief Representa o ch�o da sala.
 * Renderiza um paralelep�pedo plano e fino.
 */
class Floor : public GameObject {
public:
    /**
     * @param position Posi��o do centro do ch�o no mundo.
     * @param size Largura (x) e profundidade (z) do ch�o.
     */
    Floor(const Vector3f& position, const Vector2f& size);

    virtual void update(float deltaTime) override;
    virtual void render() override;

private:
    Vector3f _position;
    Vector2f _size;
};

#endif // FLOOR_H
