#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/**
 * @file GameObject.h
 * @brief Define a classe base abstrata para qualquer entidade no mundo do jogo.
 *
 * Esta classe serve como uma interface, garantindo que qualquer objeto que
 * exista na cena tenha, no m�nimo, uma fun��o de atualiza��o e uma de renderiza��o.
 */
class GameObject {
public:
    // Um destrutor virtual � crucial em classes base. Ele garante que, ao deletar
    // um ponteiro para GameObject, o destrutor da classe derivada (ex: Wall, Key)
    // seja chamado corretamente, evitando vazamentos de mem�ria.
    virtual ~GameObject() {}

    // M�todo para atualizar a l�gica do objeto (movimento, anima��o, etc.).
    // � "virtual puro" (= 0), o que significa que as classes derivadas S�O OBRIGADAS
    // a implementar sua pr�pria vers�o desta fun��o.
    virtual void update(float deltaTime) = 0;

    // M�todo para desenhar o objeto na tela.
    // Tamb�m � "virtual puro".
    virtual void render() = 0;
};

#endif // GAMEOBJECT_H
