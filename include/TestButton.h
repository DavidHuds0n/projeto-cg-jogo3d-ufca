#ifndef TESTBUTTON_H
#define TESTBUTTON_H

#include "InteractableObject.h"
#include "PrimitiveObject.h" // Usaremos para a parte visual

class TestButton : public InteractableObject {
public:
    TestButton(const Vector3f& position);

    // Sobrescrevendo os m�todos da classe base
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void onClick() override;
    virtual float getCollisionRadius() const override;

private:
    // Um objeto primitivo para a representa��o visual do bot�o
    PrimitiveObject _visual;
    // Raio para o teste de colis�o (assumindo uma esfera)
    float _collisionRadius;
};

#endif // TESTBUTTON_H
