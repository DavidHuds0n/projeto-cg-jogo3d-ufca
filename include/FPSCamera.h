/**
 * @file FPSCamera.h
 * @brief Define uma struct Vector3f e a classe FPSCamera para uma câmera em primeira pessoa.
 */
#ifndef FPSCAMERA_H
#define FPSCAMERA_H

/**
 * @struct Vector3f
 * @brief Estrutura para representar um vetor ou ponto no espaço 3D com coordenadas x, y, z.
 */
struct Vector3f {
    float x, y, z;
};

/**
 * @class FPSCamera
 * @brief Gerencia a posição, orientação e projeção de uma câmera estilo FPS (First-Person Shooter).
 *
 * Esta classe calcula os vetores de direção com base na rotação (yaw/pitch) e
 * prepara a matriz de visualização para ser usada pelo OpenGL (via gluLookAt).
 */
class FPSCamera {
public:
    /**
     * @brief Construtor padrão da câmera.
     * Inicializa a câmera em uma posição e orientação padrão.
     */
    FPSCamera();

    /**
     * @brief Define a posição da câmera no mundo.
     * @param [in] pos Um Vector3f contendo as novas coordenadas (x, y, z) da câmera.
     */
    void setPosition(const Vector3f& pos);

    /**
     * @brief Obtém a posição atual da câmera.
     * @return Uma referência constante para o vetor da posição da câmera.
     */
    const Vector3f& getPosition() const;

    /**
     * @brief Obtém o vetor que aponta para a frente da câmera.
     * @return Uma referência constante para o vetor "frente" normalizado.
     */
    const Vector3f& getFrontVector() const;

    /**
     * @brief Obtém o vetor que aponta para a direita da câmera.
     * @return Uma referência constante para o vetor "direita" normalizado.
     */
    const Vector3f& getRightVector() const;

    /**
     * @brief Aplica a transformação da câmera na pipeline gráfica.
     * @note Esta função deve ser chamada a cada quadro (frame) antes de desenhar os objetos do mundo.
     * Internamente, utiliza o comando gluLookAt.
     */
    void updateView();

    /**
     * @brief Processa o movimento do mouse para rotacionar a câmera.
     * @param [in] x A nova coordenada X do cursor do mouse.
     * @param [in] y A nova coordenada Y do cursor do mouse.
     */
    void processMouseMotion(int x, int y);

private:
    /**
     * @brief Recalcula os vetores de direção (_front, _right, _up) com base nos ângulos _yaw e _pitch.
     * Chamado internamente sempre que a orientação da câmera muda.
     */
    void updateCameraVectors();

    Vector3f _position; ///< Posição da câmera no espaço 3D.
    Vector3f _front;    ///< Vetor que aponta para frente da câmera.
    Vector3f _up;       ///< Vetor "para cima" da câmera.
    Vector3f _right;    ///< Vetor que aponta para a direita da câmera.
    Vector3f _worldUp;  ///< Vetor "para cima" do mundo, usado para cálculos.

    float _yaw;   ///< Rotação horizontal (em torno do eixo Y).
    float _pitch; ///< Rotação vertical (em torno do eixo X).

    float _mouseSensitivity; ///< Multiplicador para a sensibilidade do mouse.
};

#endif // FPSCAMERA_H
