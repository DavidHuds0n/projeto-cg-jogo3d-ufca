// src/Game.cpp

// --- INCLUDES ESSENCIAIS ---
#include "../include/Game.h"      // PRECISA saber sobre a classe Game que estamos implementando.
#include <GL/freeglut.h>         // PRECISA saber sobre as fun��es do OpenGL/GLUT.

// --- INCLUDES PARA AS NOVAS CLASSES ---
#include "../include/Player.h"
#include "../include/Level.h"
#include "../include/LightManager.h"

void drawTestbed() {
    // --- Desenha um Grid no Ch�o (Plano XZ) ---
    glColor3f(0.3f, 0.3f, 0.3f); // Cor cinza para o grid
    glBegin(GL_LINES);
    for (int i = -20; i <= 20; i++) {
        // Linhas paralelas ao eixo X
        glVertex3f((float)i, 0, -20);
        glVertex3f((float)i, 0, 20);
        // Linhas paralelas ao eixo Z
        glVertex3f(-20, 0, (float)i);
        glVertex3f(20, 0, (float)i);
    }
    glEnd();

    // --- Desenha Cubos de Refer�ncia ---
    // Cubo Vermelho na dire��o +Z
    glPushMatrix();
    glTranslatef(0, 1, -10);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cubo Verde na dire��o +X
    glPushMatrix();
    glTranslatef(10, 1, 0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Cubo Azul na dire��o -X
    glPushMatrix();
    glTranslatef(-10, 1, 0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

// O construtor da classe Game
Game::Game() {
    currentState = PLAYING;
}

// O m�todo de inicializa��o da classe Game
void Game::init() {
    // Configura��es do OpenGL
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Configura��o da proje��o
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1280.0 / 720.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicializa��o dos nossos sistemas
    level.loadFromFile("res/levels/maze01.txt");
    lightManager.init();
}

// O m�todo de atualiza��o da classe Game
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

// O m�todo de renderiza��o da classe Game
void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 1. Aplica a c�mera do jogador
    player.getCamera().updateView();

    // --- MUNDO DE TESTE PARA A PESSOA 2 ---
    drawTestbed();
    // ------------------------------------

    // O c�digo abaixo ficar� comentado enquanto a Pessoa 2 trabalha:
    // level.render();
    // player.render();

    glutSwapBuffers();
}
// O m�todo de input (tecla pressionada) da classe Game
void Game::processKeyDown(unsigned char key, int x, int y) {
    if (key == 27) { // ESC
        glutLeaveMainLoop();
    }
    player.handleKeyDown(key);
}

// O m�todo de input (tecla solta) da classe Game
void Game::processKeyUp(unsigned char key, int x, int y) {
    player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    // Adicionamos esta verifica��o para ignorar o evento de movimento gerado pelo glutWarpPointer
    if (x == 1280 / 2 && y == 720 / 2) {
        return;
    }

    player.handleMouseMotion(x, y); // Repassa o input para o jogador

    // For�a o cursor a voltar para o centro da tela
    glutWarpPointer(1280 / 2, 720 / 2);
}
