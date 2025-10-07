#ifndef KEY_H
#define KEY_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "GameData.h"
#include <string>

class Key : public InteractableObject {
public:
    // --- CONSTRUTOR ATUALIZADO ---
    // A declaração agora corresponde à implementação no .cpp, com 6 parâmetros.
    Key(const Vector3f& position,
        ItemType keyType,
        const std::string& puzzleIdRequired = "",
        bool form = false,
        const Vector3f& color = {1.0f, 0.9f, 0.8f},
        const Vector3f& scale = {0.4f, 0.4f, 0.4f}); // <-- PARÂMETRO QUE FALTAVA

    virtual void update(float deltaTime, GameStateManager& gameStateManager) override;
    virtual void render() override;
    virtual void onClick(GameStateManager& gameStateManager) override;
    virtual float getCollisionRadius() const override;
    virtual BoundingBox getBoundingBox() const override;

private:
    PrimitiveObject _visual;
    float _collisionRadius;
    bool _isCollected;
    std::string _puzzleIdRequired;
    bool _isVisible;
    ItemType _keyType;
    Vector3f _color;
};

#endif // KEY_H
