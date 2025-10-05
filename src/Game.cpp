/**
 * @file Game.cpp
 * @brief Implementação da classe principal Game.
 */
#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h"
#include "../include/InteractableObject.h"
#include "../include/PuzzleDoor.h"
#include "../include/Door.h" // Incluído para a lógica de transição de sala
#include "../include/SceneManager.h"
#include "../include/GameStateManager.h"
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

// --- FUNÇÕES AUXILIARES ESTÁTICAS ---
static void drawCenteredBitmapText(const char* msg, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* p = msg; *p; ++p) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);
    }
}

// --- FUNÇÕES AUXILIARES DE RAY CASTING ---

/**
 * @brief Calcula um raio 3D a partir das coordenadas 2D da tela.
 * Usa gluUnProject para converter as coordenadas da tela para coordenadas do mundo.
 */
Ray calculateMouseRay(int mouseX, int mouseY, Player& player) {
    GLdouble modelviewMatrix[16];
    GLdouble projectionMatrix[16];
    GLint viewport[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    glGetIntegerv(GL_VIEWPORT, viewport);

    mouseY = viewport[3] - mouseY;

    GLdouble nearX, nearY, nearZ;
    GLdouble farX, farY, farZ;

    gluUnProject(mouseX, mouseY, 0.0, modelviewMatrix, projectionMatrix, viewport, &nearX, &nearY, &nearZ);
    gluUnProject(mouseX, mouseY, 1.0, modelviewMatrix, projectionMatrix, viewport, &farX, &farY, &farZ);

    Vector3f rayDirection = {
        (float)(farX - nearX),
        (float)(farY - nearY),
        (float)(farZ - nearZ)
    };

    float length = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
    if (length > 0) {
        rayDirection.x /= length;
        rayDirection.y /= length;
        rayDirection.z /= length;
    }

    return {player.getCamera().getPosition(), rayDirection};
}

/**
 * @brief Verifica se um raio intercepta uma esfera.
 * @return A distância da origem do raio até a interseção, ou um valor negativo se não houver.
 */
float rayIntersectsSphere(const Ray& ray, const Vector3f& sphereCenter, float sphereRadius) {
    Vector3f oc = {
        ray.origin.x - sphereCenter.x,
        ray.origin.y - sphereCenter.y,
        ray.origin.z - sphereCenter.z
    };
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
    float c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0f;
    } else {
        return (-b - sqrt(discriminant)) / (2.0f * a);
    }
}

// --- IMPLEMENTAÇÃO DA CLASSE GAME ---

Game::Game() {
    _currentState = PLAYING;
}

void Game::init() {
    glClearColor(Config::SKYBOX_R, Config::SKYBOX_G, Config::SKYBOX_B, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // --- ADICIONE ESTAS DUAS LINHAS AQUI ---
    // Habilita o descarte de faces
    glEnable(GL_CULL_FACE);
    // Especifica que as faces de TRÁS (GL_BACK) devem ser descartadas
    glCullFace(GL_BACK);
    // -----------------------------------------

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)Config::SCREEN_WIDTH / (float)Config::SCREEN_HEIGHT, Config::CAMERA_ZNEAR, Config::CAMERA_ZFAR);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _lightManager.init();
    _sceneManager.init();
}

void Game::update(float deltaTime) {
    if (_currentState == PLAYING) {
        // ATUALIZE ESTA LINHA para passar a lista de objetos
        _player.update(deltaTime, _sceneManager.getCurrentRoomObjects(), _gameStateManager);

        // PASSE O GAMESTATEMANAGER AQUI
        _sceneManager.update(deltaTime, _gameStateManager);
        _gameStateManager.processPending(_sceneManager);
        Vector3f currentColor = _gameStateManager.getCurrentFlashlightColor();
        _lightManager.setFlashlightColor(currentColor);
    }
    glutPostRedisplay();
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    _player.getCamera().updateView();
    _lightManager.updateFlashlight(_player.getCamera().getPosition(), _player.getCamera().getFrontVector());

    _sceneManager.render();

    // Overlay para estados finais
    if (_currentState != PLAYING) {
        // Modo 2D simples
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 600); // ajuste conforme sua resolução
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_DEPTH_TEST);

        const char* msg = (_currentState == GAME_OVER) ? "GAME OVER - Pressione ESC para sair"
                                                       : "VOCE VENCEU! - Pressione ESC para sair";
        glColor3f(1,1,1);
        drawCenteredBitmapText(msg, 200, 300); // posição simples

        glEnable(GL_DEPTH_TEST);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

    glutSwapBuffers();
}

void Game::processInteraction() {
    std::cout << "Tecla 'E' pressionada! Calculando Ray Casting..." << std::endl;

    Ray ray = calculateMouseRay(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2, _player);

    InteractableObject* closestObject = nullptr;
    float closestHitDistance = std::numeric_limits<float>::max();

    std::vector<InteractableObject*>& interactables = _sceneManager.getInteractableObjects();

    for (auto* obj : interactables) {
        if (obj->isInteractable()) {
            float hitDistance = rayIntersectsSphere(ray, obj->getPosition(), obj->getCollisionRadius());
            if (hitDistance > 0 && hitDistance < closestHitDistance) {
                closestHitDistance = hitDistance;
                closestObject = obj;
            }
        }
    }

    if (closestObject) {
        if (closestHitDistance <= Config::PLAYER_INTERACTION_DISTANCE) {
            closestObject->onClick(_gameStateManager);
            // Verifica se é uma PuzzleDoor (puzzle de 3 portas)
            /*if (auto* pz = dynamic_cast<PuzzleDoor*>(closestObject)) {
                if (pz->isDeadly()) {
                    _currentState = GAME_OVER;
                    return; // não deixa continuar
                }
                if (pz->isWinning()) {
                    _currentState = WIN;
                    return;
                }*/

            // --- LÓGICA DE TRANSIÇÃO COM VERIFICAÇÃO ---
            Door* door = dynamic_cast<Door*>(closestObject);
            if (door) {
                ItemType requiredItem = door->getRequiredItem();

                // --- LÓGICA ATUALIZADA AQUI ---
                // A porta abre se não requer item OU se o jogador tem o item.
                if (requiredItem == ItemType::NENHUM || _gameStateManager.playerHasItem(requiredItem)) {

                    std::cout << "Porta aberta!" << std::endl;
                    int targetRoom = door->getTargetRoomIndex();
                    _sceneManager.switchToRoom(targetRoom);
                    _player.setPosition(door->getSpawnPosition());

                    // Não vamos remover o item NENHUM do inventário
                    if (requiredItem != ItemType::NENHUM) {
                       // _gameStateManager.removeItemFromInventory(requiredItem); // Descomente se quiser que a chave seja consumida
                    }

                } else {
                    std::cout << "A porta esta trancada. Voce precisa de um item." << std::endl;
                }
            }
        } else {
            std::cout << "Objeto encontrado, mas esta longe demais para interagir!" << std::endl;
        }
    } else {
        std::cout << "Nenhum objeto interativo na mira." << std::endl;
    }
}
// --- Processamento de Entrada ---

void Game::processKeyDown(unsigned char key, int x, int y) {
    // Se o keypad está ativo, a entrada do teclado é para o código
    if (_gameStateManager.isKeypadActive()) {
        if (key >= '0' && key <= '9') {
            _gameStateManager.appendToKeypadInput(key);
            // Se o código tem 3 dígitos, verifica
            if (_gameStateManager.getKeypadInput().length() == 3) {
                if (_gameStateManager.checkKeypadCode("742")) { // O código correto!
                    _gameStateManager.setPuzzleState(PuzzleID::Sala1_CodigoCaixa, true);
                    std::cout << "CAIXA DESTRANCADA!" << std::endl;
                }
                _gameStateManager.setActiveKeypad(false); // Desativa o keypad após a tentativa
            }
        } else if (key == 27 || key == 'e') { // Permite sair do modo keypad com ESC ou E
            _gameStateManager.setActiveKeypad(false);
            std::cout << "Keypad desativado." << std::endl;
        }
        return; // Impede que o jogador ande enquanto digita
    }

    // Lógica normal de input se o keypad não estiver ativo
    key = tolower(key);
    if (key == 27) {
        glutLeaveMainLoop();
    }
    if (key == 'e') {
        processInteraction();
    }
    _player.handleKeyDown(key);
}

void Game::processKeyUp(unsigned char key, int x, int y) {
    key = tolower(key);
    _player.handleKeyUp(key);
}

void Game::processMouseMotion(int x, int y) {
    if (x == Config::SCREEN_WIDTH / 2 && y == Config::SCREEN_HEIGHT / 2) {
        return;
    }
    _player.handleMouseMotion(x, y);
    glutWarpPointer(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT / 2);
}
