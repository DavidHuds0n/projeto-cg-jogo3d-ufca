#ifndef PUZZLEDOOR_H
#define PUZZLEDOOR_H

#include "Door.h" // Herda diretamente de Door

class PuzzleDoor : public Door {
public:
    // Enum para os tipos de ícone
    enum class Icon { None, Wave, Sun, Mountain };

    PuzzleDoor(const Vector3f& position,
               int targetRoomIndex,
               const Vector3f& spawnPosition,
               const Vector3f& doorColor,
               Icon icon = Icon::None,
               const Vector3f& iconGlow = {1.0f, 1.0f, 1.0f});

    virtual void render() override;

private:
    Vector3f _doorColor;
    Vector3f _iconGlow;
    Icon _icon;
};

#endif // PUZZLEDOOR_H
