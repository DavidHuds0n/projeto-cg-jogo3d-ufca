#ifndef SIGN_H
#define SIGN_H

#include "InteractableObject.h"
#include "Vector.h"
#include <string>

class Sign : public InteractableObject {
public:
    Sign(const Vector3f& pos, const std::string& text);

    void update(float /*dt*/, GameStateManager& /*gsm*/) override {}
    void render() override;
    void onClick(GameStateManager& /*gsm*/) override {}

    float getCollisionRadius() const override { return 0.0f; }
    BoundingBox getBoundingBox() const override { return {{0,0,0},{0,0,0}}; }

private:
    Vector3f _pos;
    std::string _text;
};

#endif
