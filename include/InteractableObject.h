#ifndef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include "GameObject.h"
#include "Vector.h" // Incluímos para usar Vector3f

/**
 * @file InteractableObject.h
 * @brief Define a classe base para qualquer objeto no jogo com o qual o jogador pode interagir.
 */
class InteractableObject : public GameObject {
public:
    // Construtor que recebe a posição inicial do objeto.
    InteractableObject(const Vector3f& position) : _position(position), _isInteractable(true) {}

    // Destrutor virtual, como em toda classe base.
    virtual ~InteractableObject() {}

    // Método que será chamado quando o jogador clicar neste objeto.
    // É virtual puro (= 0), forçando as classes filhas (Key, Button, etc.)
    // a implementarem sua própria lógica de interação.
    virtual void onClick() = 0;

    // Métodos para controlar se um objeto pode ser interagido.
    void setInteractable(bool interactable) { _isInteractable = interactable; }
    bool isInteractable() const { return _isInteractable; }

    // Método para obter a posição do objeto, útil para o Ray Casting.
    const Vector3f& getPosition() const { return _position; }

    // ADICIONE ESTE MÉTODO:
    // Retorna o raio da esfera de colisão do objeto.
    virtual float getCollisionRadius() const = 0;

protected:
    Vector3f _position;
    bool _isInteractable;
};

#endif // INTERACTABLEOBJECT_H
