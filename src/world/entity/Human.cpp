#include "Human.hpp"
#include <algorithm>

void updateLookAtVectorFromMouse(Vector3 position, Vector3 *lookat) {
    const Vector3 up = {0.0f, 1.0f, 0.0f};
    Vector3 front = Vector3Subtract(*lookat, position);
    // Make the direction vector long so the calculation works correctly
    front = Vector3Scale(Vector3Normalize(front), 10);
    Vector3 left = Vector3Normalize(Vector3CrossProduct(up, front));
    front = Vector3RotateByAxisAngle(front, up, GetMouseDelta().x*-0.01);
    front = Vector3RotateByAxisAngle(front, left, GetMouseDelta().y*0.01);
    front = Vector3Add(position, front);
    *lookat = front;
}

Human::Human() {
    this->position = {1, 1, 1};
    this->velocity = {0, 0, 0};
    this->lookat = {0, 0, 0};
    this->head = {0, HEIGHT-0.25, 0};
}

void Human::draw() {
    Vector3 topCorner;
    topCorner.y = this->position.y + (HEIGHT/2.0);
    topCorner.x = this->position.x;
    topCorner.z = this->position.z;
    DrawCubeWires(topCorner, WIDTH, HEIGHT, WIDTH, RED);
    DrawCube(this->position, 0.1, 0.1, 0.1, GREEN);
    DrawLine3D(Vector3Add(this->position, this->head), this->lookat, GREEN);
}

void Human::update() {
    // Control look from mouse
    updateLookAtVectorFromMouse(this->position, &this->lookat);

    // Update positions
    Vector3 prevPosition = this->position;
    this->position = Vector3Add(this->position, this->velocity);

    // Ground Collition
    if (this->position.y < 0) {
        this->position.y = 0;
        this->velocity.y = 0;
    }

    this->lookat = Vector3Add(this->lookat, Vector3Subtract(this->position, prevPosition));

    // Friction
    int friction = 4;
    this->velocity.x = Lerp(this->velocity.x, 0, GetFrameTime() * friction);
    this->velocity.z = Lerp(this->velocity.z, 0, GetFrameTime() * friction);

    // Acceleration
    float acceleration = GetFrameTime() * 0.5;
    Vector3 lookAtRelative = Vector3Subtract(this->lookat, this->position);
    Vector3 right = Vector3Normalize(Vector3CrossProduct(lookAtRelative, { 0, 1, 0 }));
    Vector3 front = Vector3Scale(Vector3Normalize(Vector3CrossProduct(right, {0, 1, 0})), -1);

    if (IsKeyDown(KEY_W)) {
        Vector3 finalVector = Vector3Scale(front, acceleration);
        this->velocity = Vector3Add(this->velocity, finalVector);
    }

    if (IsKeyDown(KEY_D)) {
        Vector3 finalVector = Vector3Scale(right, acceleration);
        this->velocity = Vector3Add(this->velocity, finalVector);
    }

    if (IsKeyDown(KEY_A)) {
        Vector3 finalVector = Vector3Scale(right, -acceleration);
        this->velocity = Vector3Add(this->velocity, finalVector);
    }

    if (IsKeyDown(KEY_S)) {
        Vector3 finalVector = Vector3Scale(front, -acceleration);
        this->velocity = Vector3Add(this->velocity, finalVector);
    }

    if (IsKeyPressed(KEY_SPACE)) {
        this->velocity.y += 0.22;
    }

    // Gravity
    this->velocity.y -= GetFrameTime() * 0.9;

    // Limit Velocity (x and Z)
    Vector3 velocityXZ = this->velocity; velocityXZ.y = 0;
    if (Vector3Length(velocityXZ) > 0.05) {
        velocityXZ = Vector3Scale(Vector3Normalize(velocityXZ), 0.05);
        this->velocity.x = velocityXZ.x;
        this->velocity.z = velocityXZ.z;
    }
}
Human::~Human() {}
