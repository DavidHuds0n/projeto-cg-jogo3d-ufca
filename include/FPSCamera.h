/**
 * @file FPSCamera.h
 * @brief Define uma struct Vector3f e a classe FPSCamera para uma c�mera em primeira pessoa.
 */
#ifndef FPSCAMERA_H
#define FPSCAMERA_H

/**
 * @struct Vector3f
 * @brief Estrutura para representar um vetor ou ponto no espa�o 3D com coordenadas x, y, z.
 */
struct Vector3f {
    float x, y, z;
};

/**
 * @class FPSCamera
 * @brief Gerencia a posi��o, orienta��o e proje��o de uma c�mera estilo FPS (First-Person Shooter).
 *
 * Esta classe calcula os vetores de dire��o com base na rota��o (yaw/pitch) e
 * prepara a matriz de visualiza��o para ser usada pelo OpenGL (via gluLookAt).
 */
class FPSCamera {
public:
    /**
     * @brief Construtor padr�o da c�mera.
     * Inicializa a c�mera em uma posi��o e orienta��o padr�o.
     */
    FPSCamera();

    /**
     * @brief Define a posi��o da c�mera no mundo.
     * @param [in] pos Um Vector3f contendo as novas coordenadas (x, y, z) da c�mera.
     */
    void setPosition(const Vector3f& pos);

    /**
     * @brief Obt�m a posi��o atual da c�mera.
     * @return Uma refer�ncia constante para o vetor da posi��o da c�mera.
     */
    const Vector3f& getPosition() const;

    /**
     * @brief Obt�m o vetor que aponta para a frente da c�mera.
     * @return Uma refer�ncia constante para o vetor "frente" normalizado.
     */
    const Vector3f& getFrontVector() const;

    /**
     * @brief Obt�m o vetor que aponta para a direita da c�mera.
     * @return Uma refer�ncia constante para o vetor "direita" normalizado.
     */
    const Vector3f& getRightVector() const;

    /**
     * @brief Aplica a transforma��o da c�mera na pipeline gr�fica.
     * @note Esta fun��o deve ser chamada a cada quadro (frame) antes de desenhar os objetos do mundo.
     * Internamente, utiliza o comando gluLookAt.
     */
    void updateView();

    /**
     * @brief Processa o movimento do mouse para rotacionar a c�mera.
     * @param [in] x A nova coordenada X do cursor do mouse.
     * @param [in] y A nova coordenada Y do cursor do mouse.
     */
    void processMouseMotion(int x, int y);

private:
    /**
     * @brief Recalcula os vetores de dire��o (_front, _right, _up) com base nos �ngulos _yaw e _pitch.
     * Chamado internamente sempre que a orienta��o da c�mera muda.
     */
    void updateCameraVectors();

    Vector3f _position; ///< Posi��o da c�mera no espa�o 3D.
    Vector3f _front;    ///< Vetor que aponta para frente da c�mera.
    Vector3f _up;       ///< Vetor "para cima" da c�mera.
    Vector3f _right;    ///< Vetor que aponta para a direita da c�mera.
    Vector3f _worldUp;  ///< Vetor "para cima" do mundo, usado para c�lculos.

    float _yaw;   ///< Rota��o horizontal (em torno do eixo Y).
    float _pitch; ///< Rota��o vertical (em torno do eixo X).

    float _mouseSensitivity; ///< Multiplicador para a sensibilidade do mouse.
};

#endif // FPSCAMERA_H
