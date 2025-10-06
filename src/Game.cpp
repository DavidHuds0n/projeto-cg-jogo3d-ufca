/**
 * @file Game.cpp
 * @brief Implementa��o da classe principal Game.
 */
#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h"
#include "../include/InteractableObject.h"
#include "../include/Door.h" // Inclu�do para a l�gica de transi��o de sala
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

// --- FUN��ES AUXILIARES DE RAY CASTING ---

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
    if (closestObject) {
        if (closestHitDistance <= Config::PLAYER_INTERACTION_DISTANCE) {
            closestObject->onClick(_gameStateManager);

            // --- LÓGICA DE TRANSIÇÃO COM SUPORTE A PUZZLE ---
            Door* door = dynamic_cast<Door*>(closestObject);
            if (door) {
                if (door->requiresPuzzle()) {
                    // Porta depende de puzzle
                    if (_gameStateManager.isPuzzleSolved(door->getRequiredPuzzle())) {
                        std::cout << "Porta aberta! (puzzle resolvido)" << std::endl;
                        int targetRoom = door->getTargetRoomIndex();
                        _sceneManager.switchToRoom(targetRoom);
                        _player.setPosition(door->getSpawnPosition());
                    } else {
                        std::cout << "A porta está trancada. Resolva o puzzle para abrir." << std::endl;
                    }
                } else {
                    // Porta depende de item
                    ItemType requiredItem = door->getRequiredItem();
                    if (requiredItem == ItemType::NENHUM || _gameStateManager.playerHasItem(requiredItem)) {
                        std::cout << "Porta aberta!" << std::endl;
                        int targetRoom = door->getTargetRoomIndex();
                        _sceneManager.switchToRoom(targetRoom);
                        _player.setPosition(door->getSpawnPosition());
                        if (requiredItem != ItemType::NENHUM) {
                            // _gameStateManager.removeItemFromInventory(requiredItem); // Descomente se quiser que a chave seja consumida
                        }
                    } else {
                        std::cout << "A porta esta trancada. Voce precisa de um item." << std::endl;
                    }
                }
            }
        } else {
            std::cout << "Objeto encontrado, mas esta longe demais para interagir!" << std::endl;
        }
    } else {
        std::cout << "Nenhum objeto interativo na mira." << std::endl;
    }
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
    // Especifica que as faces de TR�S (GL_BACK) devem ser descartadas
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

            // --- L�GICA DE TRANSI��O COM VERIFICA��O ---
            Door* door = dynamic_cast<Door*>(closestObject);
            if (door) {
                ItemType requiredItem = door->getRequiredItem();

                // --- L�GICA ATUALIZADA AQUI ---
                // A porta abre se n�o requer item OU se o jogador tem o item.
                if (requiredItem == ItemType::NENHUM || _gameStateManager.playerHasItem(requiredItem)) {

                    std::cout << "Porta aberta!" << std::endl;
                    int targetRoom = door->getTargetRoomIndex();
                    _sceneManager.switchToRoom(targetRoom);
                    _player.setPosition(door->getSpawnPosition());

                    // N�o vamos remover o item NENHUM do invent�rio
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
    // Se o keypad est� ativo, a entrada do teclado � para o c�digo
    if (_gameStateManager.isKeypadActive()) {
        if (key >= '0' && key <= '9') {
            _gameStateManager.appendToKeypadInput(key);
            // Se o c�digo tem 3 d�gitos, verifica
            if (_gameStateManager.getKeypadInput().length() == 3) {
                if (_gameStateManager.checkKeypadCode("742")) { // O c�digo correto!
                    _gameStateManager.setPuzzleState(PuzzleID::Sala1_CodigoCaixa, true);
                    std::cout << "CAIXA DESTRANCADA!" << std::endl;
                }
                _gameStateManager.setActiveKeypad(false); // Desativa o keypad ap�s a tentativa
            }
        } else if (key == 27 || key == 'e') { // Permite sair do modo keypad com ESC ou E
            _gameStateManager.setActiveKeypad(false);
            std::cout << "Keypad desativado." << std::endl;
        }
        return; // Impede que o jogador ande enquanto digita
    }

    // L�gica normal de input se o keypad n�o estiver ativo
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
