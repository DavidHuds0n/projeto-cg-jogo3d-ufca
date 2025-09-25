// src/Game.cpp

// --- INCLUDES ESSENCIAIS ---
#include "../include/Game.h"      // PRECISA saber sobre a classe Game que estamos implementando.
#include <GL/freeglut.h>         // PRECISA saber sobre as funções do OpenGL/GLUT.

// --- INCLUDES PARA AS NOVAS CLASSES ---
#include "../include/Player.h"
#include "../include/Level.h"
#include "../include/LightManager.h"

// O construtor da classe Game
Game::Game() {
    currentState = PLAYING;
}

// O método de inicialização da classe Game
void Game::init() {
    // Configurações do OpenGL
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Configuração da projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1280.0 / 720.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicialização dos nossos sistemas
    level.loadFromFile("res/levels/maze01.txt");
    lightManager.init();
}

// O método de atualização da classe Game
void Game::update(float deltaTime) {
    switch (currentState) {
        case PLAYING:
            player.update(deltaTime);
            break;
        case GAME_OVER:
            break;
        case WIN:
            break;
    }
    glutPostRedisplay();
}

// O método de renderização da classe Game
void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 1. Aplica a câmera
    player.getCamera().updateView();

    // 2. Renderiza o nível
    level.render();

    // 3. Renderiza o jogador
    // player.render();

    glutSwapBuffers();
}

// O método de input (tecla pressionada) da classe Game
void Game::processKeyDown(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        glutLeaveMainLoop();
    }
    player.handleKeyDown(key);
}

// O método de input (tecla solta) da classe Game
void Game::processKeyUp(unsigned char key, int x, int y) {
    player.handleKeyUp(key);
}

// O método de input (movimento do mouse) da classe Game
void Game::processMouseMotion(int x, int y) {
    player.handleMouseMotion(x, y);
}
