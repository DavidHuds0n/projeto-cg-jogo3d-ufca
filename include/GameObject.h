#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/**
 * @file GameObject.h
 * @brief Define a classe base abstrata para qualquer entidade no mundo do jogo.
 *
 * Esta classe serve como uma interface, garantindo que qualquer objeto que
 * exista na cena tenha, no mínimo, uma função de atualização e uma de renderização.
 */
class GameObject {
public:
    // Um destrutor virtual é crucial em classes base. Ele garante que, ao deletar
    // um ponteiro para GameObject, o destrutor da classe derivada (ex: Wall, Key)
    // seja chamado corretamente, evitando vazamentos de memória.
    virtual ~GameObject() {}

    // Método para atualizar a lógica do objeto (movimento, animação, etc.).
    // É "virtual puro" (= 0), o que significa que as classes derivadas SÃO OBRIGADAS
    // a implementar sua própria versão desta função.
    virtual void update(float deltaTime) = 0;

    // Método para desenhar o objeto na tela.
    // Também é "virtual puro".
    virtual void render() = 0;
};

#endif // GAMEOBJECT_H
