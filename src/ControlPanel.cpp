#include "../include/ControlPanel.h"
#include "../include/PrimitiveObject.h"
#include <GL/freeglut.h>
#include <iostream>

static PrimitiveObject visual(PrimitiveShape::SPHERE, {0,0,0}, {0.1f, 0.1f, 0.8f}, {0.8f, 0.8f, 0.1f});

ControlPanel::ControlPanel(const Vector3f& position) : InteractableObject(position) {}

void ControlPanel::update(float deltaTime, GameStateManager& gameStateManager) {
    // Painel é estático, não precisa reagir a estados no update.
}

void ControlPanel::render() {
    glPushMatrix();
    glTranslatef(_position.x, _position.y, _position.z);
    visual.render();
    glPopMatrix();
}

void ControlPanel::onClick(GameStateManager& gameStateManager) {
    std::cout << "Painel de controle clicado! Mudando a cor da lanterna." << std::endl;
    gameStateManager.cycleFlashlightColor();
}

float ControlPanel::getCollisionRadius() const { return 1.0f; }

BoundingBox ControlPanel::getBoundingBox() const {
    float radius = 1.0f;
    return {{_position.x - radius, _position.y - radius, _position.z - radius},
            {_position.x + radius, _position.y + radius, _position.z + radius}};
}
