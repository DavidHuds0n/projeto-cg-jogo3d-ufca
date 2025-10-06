/**
 * @file Room.cpp
 * @brief Implementação da classe Room.
 */
#include "../include/Room.h"
#include "../include/InteractableObject.h"
#include <algorithm>

Room::Room() {
    // O construtor está vazio por enquanto. No futuro, ele poderia receber um
    // identificador ou nome para a sala, por exemplo.
}

Room::~Room() {
    // Este é um dos destrutores mais importantes do projeto.
    // Como o vetor `_objects` armazena ponteiros, nós somos responsáveis
    // por liberar a memória alocada para cada um deles.
    for (GameObject* obj : _objects) {
        delete obj; // Libera a memória do objeto.
    }
    // Limpa o vetor para remover os ponteiros inválidos.
    _objects.clear();
}

void Room::addObject(GameObject* object) {
    if (object != nullptr) {
        _objects.push_back(object);

        // Tenta converter o GameObject para um InteractableObject
        InteractableObject* interactable = dynamic_cast<InteractableObject*>(object);
        if (interactable) {
            // Se a conversão deu certo, adiciona na lista de interativos
            _interactables.push_back(interactable);
        }
    }
}

// ATUALIZE A ASSINATURA E A CHAMADA AQUI
void Room::update(float deltaTime, GameStateManager& gameStateManager) {
    // Delega a chamada de 'update' para cada objeto na sala,
    // agora passando também o gameStateManager.
    for (GameObject* obj : _objects) {
        obj->update(deltaTime, gameStateManager);
    }
}

void Room::render() {
    // Delega a chamada de 'render' para cada objeto na sala.
    // Cada objeto saberá como se desenhar.
    for (GameObject* obj : _objects) {
        obj->render();
    }
}

// ADICIONE ESTE MÉTODO NO FINAL DO ARQUIVO:
std::vector<InteractableObject*>& Room::getInteractableObjects() {
    return _interactables;
}

const std::vector<GameObject*>& Room::getObjects() const { return _objects; }
