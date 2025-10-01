#ifndef INTERACTABLEOBJECT_H
#define INTERACTABLEOBJECT_H

#include "GameObject.h"
#include "Vector.h" // Inclu�mos para usar Vector3f

/**
 * @file InteractableObject.h
 * @brief Define a classe base para qualquer objeto no jogo com o qual o jogador pode interagir.
 */
class InteractableObject : public GameObject {
public:
    // Construtor que recebe a posi��o inicial do objeto.
    InteractableObject(const Vector3f& position) : _position(position), _isInteractable(true) {}

    // Destrutor virtual, como em toda classe base.
    virtual ~InteractableObject() {}

    // M�todo que ser� chamado quando o jogador clicar neste objeto.
    // � virtual puro (= 0), for�ando as classes filhas (Key, Button, etc.)
    // a implementarem sua pr�pria l�gica de intera��o.
    virtual void onClick() = 0;

    // M�todos para controlar se um objeto pode ser interagido.
    void setInteractable(bool interactable) { _isInteractable = interactable; }
    bool isInteractable() const { return _isInteractable; }

    // M�todo para obter a posi��o do objeto, �til para o Ray Casting.
    const Vector3f& getPosition() const { return _position; }

    // ADICIONE ESTE M�TODO:
    // Retorna o raio da esfera de colis�o do objeto.
    virtual float getCollisionRadius() const = 0;

protected:
    Vector3f _position;
    bool _isInteractable;
};

#endif // INTERACTABLEOBJECT_H
