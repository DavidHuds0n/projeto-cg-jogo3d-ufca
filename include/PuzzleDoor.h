#ifndef PUZZLEDOOR_H
#define PUZZLEDOOR_H

#include "Door.h" // Herda diretamente de Door

class PuzzleDoor : public Door {
public:
    // Enum para os tipos de ícone
    enum class Icon { None, Wave, Sun, Mountain };

    // Construtor atualizado para ser consistente com a classe Door,
    // recebendo targetRoomIndex e spawnPosition, além dos parâmetros visuais.
    PuzzleDoor(const Vector3f& position,
               int targetRoomIndex,
               const Vector3f& spawnPosition,
               const Vector3f& doorColor,
               Icon icon = Icon::None,
               const Vector3f& iconGlow = {1.0f, 1.0f, 1.0f});

    // Sobrescreve apenas a função render para ter uma aparência customizada.
    // As outras funções (onClick, getCollisionRadius, etc.) são herdadas de Door.
    virtual void render() override;

private:
    // Apenas os membros exclusivos da PuzzleDoor.
    // _position, _targetRoomIndex, _spawnPosition, _collisionRadius são herdados de Door.
    Vector3f _doorColor;
    Vector3f _iconGlow;
    Icon _icon;
};

#endif // PUZZLEDOOR_H
