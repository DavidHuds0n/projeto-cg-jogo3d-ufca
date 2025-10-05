/**
 * @file Room.cpp
 * @brief Implementa��o da classe Room.
 */
#include "../include/Room.h"
#include "../include/InteractableObject.h"
#include <algorithm>

Room::Room() {
    // O construtor est� vazio por enquanto. No futuro, ele poderia receber um
    // identificador ou nome para a sala, por exemplo.
}

Room::~Room() {
    // Este � um dos destrutores mais importantes do projeto.
    // Como o vetor `_objects` armazena ponteiros, n�s somos respons�veis
    // por liberar a mem�ria alocada para cada um deles.
    for (GameObject* obj : _objects) {
        delete obj; // Libera a mem�ria do objeto.
    }
    // Limpa o vetor para remover os ponteiros inv�lidos.
    _objects.clear();
}

void Room::addObject(GameObject* object) {
    if (object != nullptr) {
        _objects.push_back(object);

        // Tenta converter o GameObject para um InteractableObject
        InteractableObject* interactable = dynamic_cast<InteractableObject*>(object);
        if (interactable) {
            // Se a convers�o deu certo, adiciona na lista de interativos
            _interactables.push_back(interactable);
        }
    }
}

// ATUALIZE A ASSINATURA E A CHAMADA AQUI
void Room::update(float deltaTime, GameStateManager& gameStateManager) {
    // Delega a chamada de 'update' para cada objeto na sala,
    // agora passando tamb�m o gameStateManager.
    for (GameObject* obj : _objects) {
        obj->update(deltaTime, gameStateManager);
    }
}

void Room::render() {
    // Delega a chamada de 'render' para cada objeto na sala.
    // Cada objeto saber� como se desenhar.
    for (GameObject* obj : _objects) {
        obj->render();
    }
}

// ADICIONE ESTE M�TODO NO FINAL DO ARQUIVO:
std::vector<InteractableObject*>& Room::getInteractableObjects() {
    return _interactables;
}

const std::vector<GameObject*>& Room::getObjects() const { return _objects; }
