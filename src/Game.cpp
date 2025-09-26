// src/Game.cpp

#include "../include/Game.h"
#include "../include/Config.h"
#include <GL/freeglut.h>
#include <string>

// --- A FUNÇÃO DO MUNDO DE TESTE ---
void drawTestbed() {
    // --- Desenha um Grid no Chão ---
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    for (int i = -20; i <= 20; i++) {
        glVertex3f((float)i, 0, -20);
        glVertex3f((float)i, 0, 20);
        glVertex3f(-20, 0, (float)i);
        glVertex3f(20, 0, (float)i);
    }
    glEnd();
    glEnable(GL_LIGHTING);

    // --- Desenha os Cubos de Referência (como antes) ---

    // Material do Cubo Vermelho
    GLfloat red_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat white_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 32.0f);

    glPushMatrix();
    glTranslatef(0, 1, -10);
    glutSolidCube(1.0);
    glPopMatrix();

    // Material do Cubo Verde
    GLfloat green_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green_diffuse);

    glPushMatrix();
    glTranslatef(10, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Material do Cubo Azul
    GLfloat blue_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue_diffuse);

    glPushMatrix();
    glTranslatef(-10, 1, 0);
    glutSolidCube(1.0);
    glPopMatrix();


    // --- ADICIONA NOVAS FORMAS GEOMÉTRICAS ---

    // 1. Esfera Amarela
    GLfloat yellow_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow_diffuse);
    glPushMatrix();
    glTranslatef(-5, 1, 5); // Posição nova
    // glutSolidSphere(raio, fatias, pilhas) - mais fatias/pilhas = mais suave
    glutSolidSphere(1.0, 32, 32);
    glPopMatrix();

    // 2. Cone Roxo
    GLfloat purple_diffuse[] = { 0.5f, 0.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, purple_diffuse);
    glPushMatrix();
    glTranslatef(5, 0, 5); // O cone é desenhado com a base no y=0
    glRotatef(-90, 1, 0, 0); // Rotaciona para ficar "em pé"
    // glutSolidCone(raio da base, altura, fatias, pilhas)
    glutSolidCone(1.0, 2.0, 32, 32);
    glPopMatrix();

    // 3. Torus (Rosquinha) Ciano
    GLfloat cyan_diffuse[] = { 0.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan_diffuse);
    glPushMatrix();
    glTranslatef(0, 1, 10); // Posição nova
    // glutSolidTorus(raio interno, raio externo, lados, anéis)
    glutSolidTorus(0.5, 1.0, 32, 32);
    glPopMatrix();
}

Game::Game() {
    currentState = PLAYING;
}

void Game::init() {
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // A única inicialização que precisamos agora é a do LightManager.
    // A chamada para level.init() foi removida.
    lightManager.init();
}

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

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    player.getCamera().updateView();
    lightManager.updateFlashlight(player.getCamera().getPosition(), player.getCamera().getFrontVector());
    drawTestbed();

    glutSwapBuffers();
}

void Game::processKeyDown(unsigned char key, int x, int y) {
    if (key == 27) { glutLeaveMainLoop(); }
    player.handleKeyDown(key);
}

void Game::processKeyUp(unsigned char key, int x, int y) {
    player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    player.handleMouseMotion(x, y);
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
