#ifndef KEY_H
#define KEY_H

#include "InteractableObject.h"
#include "PrimitiveObject.h"
#include "GameData.h" // Inclua para o ItemType
#include <string>

class Key : public InteractableObject {
public:
    // Construtor atualizado para receber um ItemType
    Key(const Vector3f& position, ItemType keyType, const std::string& puzzleIdRequired = "", bool form = false);

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
    ItemType _keyType; // Armazena o tipo desta chave
};

#endif // KEY_H
