#pragma once

class ShipMovementSettings {
public:
    float maxSpeed = 120000.0f;
    float maxRotation = 200.0f;
    float rotationSpeed = 1.0f;

    float mouseOffset = 0.15f;

    float forwardAcceleration = 0.0f;

    float rotationAccelerationZ = 0.0f;
    float rotationAccelerationX = 0.0f;
    float rotationAccelerationY = 0.0f;

    float rotationX = 17.06f;
    float rotationY = 44.62f;

    float speedX = 200, speedY = 200, speedZ = 200, rotationZ = 200;

    float drag = 800.0f;

    float life = 100.0f;
};