/**
 * @file Config.h
 * @brief Centraliza todas as constantes e parâmetros de configuração do Jogo 3D.
 *
 * @note Este arquivo atua como um "painel de controle" para o jogo, permitindo
 * ajustes rápidos de jogabilidade e aparência sem a necessidade de alterar
 * a lógica nos arquivos .cpp.
 */
#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // --- Janela e Display ---
    /** @brief Largura da tela em pixels. */
    static const int SCREEN_WIDTH = 1280;
    /** @brief Altura da tela em pixels. */
    static const int SCREEN_HEIGHT = 720;
    /** @brief Título que aparecerá na janela do jogo. */
    static const char* GAME_TITLE = "Jogo 3D";

    // --- Cores e Ambiente ---
    /** @brief Componente Vermelho (R) da cor de fundo (skybox). */
    static const float SKYBOX_R = 0.0f;
    /** @brief Componente Verde (G) da cor de fundo (skybox). */
    static const float SKYBOX_G = 0.0f;
    /** @brief Componente Azul (B) da cor de fundo (skybox). */
    static const float SKYBOX_B = 0.0f;

    // --- Jogador ---
    /** @brief Velocidade de movimento do jogador em unidades por segundo. */
    static const float PLAYER_SPEED = 5.0f;
    /** @brief Vida máxima que o jogador pode ter. */
    static const float PLAYER_MAX_HEALTH = 100.0f;
    /** @brief Raio da esfera de colisão do jogador. */
    static const float PLAYER_COLLISION_RADIUS = 0.3f;
    /** @brief Distância máxima em que o jogador pode interagir com objetos. */
    static const float PLAYER_INTERACTION_DISTANCE = 3.0f;


    // --- Câmera ---
    /** @brief Sensibilidade do mouse para a rotação da câmera. */
    static const float CAMERA_SENSITIVITY = 0.05f;
    /** @brief Distância mínima de renderização da câmera (plano de corte próximo). */
    static const float CAMERA_ZNEAR = 0.01f;
    /** @brief Distância máxima de renderização da câmera (plano de corte distante). */
    static const float CAMERA_ZFAR = 100.0f;

    // --- Iluminação ---
    /** @brief Intensidade da luz ambiente global. */
    static const float AMBIENT_LIGHT_INTENSITY = 0.1f;
    /** @brief Ângulo de abertura do cone de luz da lanterna. */
    static const float FLASHLIGHT_CUTOFF = 25.0f;
    /** @brief Expoente que define a suavidade da borda do cone de luz. */
    // AJUSTE AQUI: Diminua este valor para uma borda mais suave.
    static const float FLASHLIGHT_EXPONENT = 40.0f; // <--- Mude de 40.0f para 15.0f
    /** @brief Fator de atenuação constante da luz da lanterna. */
    static const float FLASHLIGHT_ATT_CONSTANT = 1.0f;
    /** @brief Fator de atenuação linear da luz da lanterna. */
    static const float FLASHLIGHT_ATT_LINEAR = 0.05f;
    /** @brief Fator de atenuação quadrática da luz da lanterna. */
    static const float FLASHLIGHT_ATT_QUADRATIC = 0.01f;

    // --- Geometria do Mundo ---
    /** @brief Tamanho (largura e profundidade) de cada bloco do labirinto. */
    static const float TILE_SIZE = 2.0f;
    /** @brief Altura das paredes do labirinto. */
    static const float WALL_HEIGHT = 3.0f;
}

#endif // CONFIG_H
