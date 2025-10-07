#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Vector.h"
#include <string>
#include <GL/freeglut.h>

class Wall : public GameObject {
public:
    // Construtor original (com textura)
    Wall(const Vector3f& position, const Vector3f& size, const std::string& textureFile);

    // --- NOVO CONSTRUTOR ---
    // Permite criar uma parede sem especificar uma textura, para simplificar o código.
    Wall(const Vector3f& position, const Vector3f& size);

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual BoundingBox getBoundingBox() const override;

private:
    Vector3f _position;
    Vector3f _size;
    GLuint _textureID = 0; // ID da textura OpenGL
};

#endif // WALL_H
