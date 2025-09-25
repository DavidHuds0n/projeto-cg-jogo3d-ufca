#ifndef INTERACTABLE_H
#define INTERACTABLE_H

// Enum para identificar o tipo de objeto
enum InteractableType {
    TORCH,
    BATTERY
};

struct Interactable {
    InteractableType type;
    float posX, posY, posZ;
    bool isActive; // Ex: para saber se a tocha já foi acesa
};

#endif
