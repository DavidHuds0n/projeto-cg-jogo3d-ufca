#include "../include/Keypad.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

static PrimitiveObject visualKeypad(PrimitiveShape::TEAPOT, {0,0,0}, {0.3f, 0.3f, 0.3f}, {0.5f, 0.5f, 0.5f});

Keypad::Keypad(const Vector3f& position) : InteractableObject(position) {}

void Keypad::update(float deltaTime, GameStateManager& gameStateManager) {
    // Keypad é estático, não precisa reagir a estados no update.
}

void Keypad::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    visualKeypad.render();
    glPopMatrix();
}

void Keypad::onClick(GameStateManager& gameStateManager) {
    if (gameStateManager.isKeypadActive()) {
        gameStateManager.setActiveKeypad(false);
        std::cout << "Keypad desativado." << std::endl;
    } else {
        gameStateManager.setActiveKeypad(true);
        std::cout << "Keypad ativado! Digite o codigo de 3 digitos." << std::endl;
    }
}

float Keypad::getCollisionRadius() const { return 0.5f; }

BoundingBox Keypad::getBoundingBox() const {
    float radius = 0.5f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
