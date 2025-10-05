#ifndef PUZZLEDOOR_H
#define PUZZLEDOOR_H

#include "InteractableObject.h"
#include "Vector.h"

class PuzzleDoor : public InteractableObject {
public:
    //enum class Mode { Deadly, Winning };

    // NOVO: tipos de símbolo
    enum class Icon { None, Wave, Sun, Mountain };

    // Construtor: posição, modo, cor da porta, ÍCONE e cor do brilho do ícone
    /*PuzzleDoor(const Vector3f& position, Mode mode, const Vector3f& doorColor,
               Icon icon = Icon::None, const Vector3f& iconGlow = {1.0f, 1.0f, 1.0f},
               float radius = 1.5f);*/
    PuzzleDoor(const Vector3f& position, const Vector3f& doorColor,int nextRoomIndex = -1,
               Icon icon = Icon::None, const Vector3f& iconGlow = {1.0f, 1.0f, 1.0f},
               float radius = 1.5f);

    void update(float, GameStateManager&) override {}
    void render() override;
    void onClick(GameStateManager&) override;

    float getCollisionRadius() const override { return _collisionRadius; }
    BoundingBox getBoundingBox() const override { return {{0,0,0},{0,0,0}}; }

    //bool isDeadly() const { return _mode == Mode::Deadly; }
    //bool isWinning() const { return _mode == Mode::Winning; }
    const Vector3f& getPosition() const { return _position; }

private:
    Vector3f _position;
    Vector3f _doorColor;
    Vector3f _iconGlow;     // cor do “neon” do ícone
    //Mode _mode;
    int _nextRoomIndex;
    Icon _icon;
    float _collisionRadius;
};

#endif
