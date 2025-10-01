/**
 * @file Config.h
 * @brief Centraliza todas as constantes e par�metros de configura��o do Jogo 3D.
 *
 * @note Este arquivo atua como um "painel de controle" para o jogo, permitindo
 * ajustes r�pidos de jogabilidade e apar�ncia sem a necessidade de alterar
 * a l�gica nos arquivos .cpp.
 */
#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // --- Janela e Display ---
    /** @brief Largura da tela em pixels. */
    static const int SCREEN_WIDTH = 1280;
    /** @brief Altura da tela em pixels. */
    static const int SCREEN_HEIGHT = 720;
    /** @brief T�tulo que aparecer� na janela do jogo. */
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
    /** @brief Vida m�xima que o jogador pode ter. */
    static const float PLAYER_MAX_HEALTH = 100.0f;
    /** @brief Raio da esfera de colis�o do jogador. */
    static const float PLAYER_COLLISION_RADIUS = 0.3f;
    /** @brief Dist�ncia m�xima em que o jogador pode interagir com objetos. */
    static const float PLAYER_INTERACTION_DISTANCE = 3.0f;


    // --- C�mera ---
    /** @brief Sensibilidade do mouse para a rota��o da c�mera. */
    static const float CAMERA_SENSITIVITY = 0.05f;
    /** @brief Dist�ncia m�nima de renderiza��o da c�mera (plano de corte pr�ximo). */
    static const float CAMERA_ZNEAR = 0.01f;
    /** @brief Dist�ncia m�xima de renderiza��o da c�mera (plano de corte distante). */
    static const float CAMERA_ZFAR = 100.0f;

    // --- Ilumina��o ---
    /** @brief Intensidade da luz ambiente global. */
    static const float AMBIENT_LIGHT_INTENSITY = 0.1f;
    /** @brief �ngulo de abertura do cone de luz da lanterna. */
    static const float FLASHLIGHT_CUTOFF = 25.0f;
    /** @brief Expoente que define a suavidade da borda do cone de luz. */
    // AJUSTE AQUI: Diminua este valor para uma borda mais suave.
    static const float FLASHLIGHT_EXPONENT = 40.0f; // <--- Mude de 40.0f para 15.0f
    /** @brief Fator de atenua��o constante da luz da lanterna. */
    static const float FLASHLIGHT_ATT_CONSTANT = 1.0f;
    /** @brief Fator de atenua��o linear da luz da lanterna. */
    static const float FLASHLIGHT_ATT_LINEAR = 0.05f;
    /** @brief Fator de atenua��o quadr�tica da luz da lanterna. */
    static const float FLASHLIGHT_ATT_QUADRATIC = 0.01f;

    // --- Geometria do Mundo ---
    /** @brief Tamanho (largura e profundidade) de cada bloco do labirinto. */
    static const float TILE_SIZE = 2.0f;
    /** @brief Altura das paredes do labirinto. */
    static const float WALL_HEIGHT = 3.0f;
}

#endif // CONFIG_H
