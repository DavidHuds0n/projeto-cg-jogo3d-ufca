#ifndef CONFIG_H
#define CONFIG_H

namespace Config {
    // --- Janela e Display ---
    static const int SCREEN_WIDTH = 1280;
    static const int SCREEN_HEIGHT = 720;
    static const char* GAME_TITLE = "Jogo 3D";

    // --- Cores e Ambiente ---
    static const float SKYBOX_R = 0.0f; // Vamos deixar o fundo preto para a iluminação se destacar
    static const float SKYBOX_G = 0.0f;
    static const float SKYBOX_B = 0.0f;

    // --- Jogador ---
    static const float PLAYER_SPEED = 5.0f;
    static const float PLAYER_COLLISION_RADIUS = 0.3f; // Deixamos aqui para o futuro

    // --- Câmera ---
    static const float CAMERA_SENSITIVITY = 0.05f;
    static const float CAMERA_ZNEAR = 0.01f; // << ADICIONE AQUI
    static const float CAMERA_ZFAR = 100.0f; // << ADICIONE AQUI

    // --- Iluminação ---
    static const float AMBIENT_LIGHT_INTENSITY = 0.1f;
    static const float FLASHLIGHT_CUTOFF = 25.0f;
    static const float FLASHLIGHT_EXPONENT = 40.0f;
    static const float FLASHLIGHT_ATT_CONSTANT = 1.0f;
    static const float FLASHLIGHT_ATT_LINEAR = 0.05f;
    static const float FLASHLIGHT_ATT_QUADRATIC = 0.01f;

    // --- Geometria do Mundo ---
    static const float TILE_SIZE = 1.0f;
    static const float WALL_HEIGHT = 1.5f;
}

#endif // CONFIG_H
