#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Ray.h"
#include "../include/InteractableObject.h"
#include "../include/Door.h"
#include "../include/Wall.h" // Incluído para a colisão
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

// --- FUNÇÕES AUXILIARES GLOBAIS ---

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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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
        _player.update(deltaTime, _sceneManager.getCurrentRoomObjects(), _gameStateManager);
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
            Door* door = dynamic_cast<Door*>(closestObject);
            if (door) {
                ItemType requiredItem = door->getRequiredItem();
                if (requiredItem == ItemType::NENHUM || _gameStateManager.playerHasItem(requiredItem)) {
                    int targetRoom = door->getTargetRoomIndex();
                    _sceneManager.switchToRoom(targetRoom);
                    _player.setPosition(door->getSpawnPosition());
                    if (requiredItem != ItemType::NENHUM) {
                        // _gameStateManager.removeItemFromInventory(requiredItem); // Descomentado se quiser consumir a chave
                    }
                } else {
                    std::cout << "A porta esta trancada." << std::endl;
                }
            }
        }
    }
}

void Game::processKeyDown(unsigned char key, int x, int y) {
    if (_gameStateManager.isKeypadActive()) {
        if (key >= '0' && key <= '9') {
            _gameStateManager.appendToKeypadInput(key);
            if (_gameStateManager.getKeypadInput().length() == 3) {
                if (_gameStateManager.checkKeypadCode("742")) {
                    _gameStateManager.setPuzzleState(PuzzleID::Sala1_CodigoCaixa, true);
                }
                _gameStateManager.setActiveKeypad(false);
            }
        } else if (key == 27 || key == 'e') {
            _gameStateManager.setActiveKeypad(false);
        }
        return;
    }

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