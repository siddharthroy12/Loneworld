#include "Human.hpp"

void updateLookAtVectorFromMouse(Vector3 position, Vector3 *lookat) {
    const Vector3 up = {0.0f, 1.0f, 0.0f};
    Vector3 tmp = Vector3Subtract(*lookat, position);
    // Make the direction vector long so the calculation works correctly
    tmp = Vector3Scale(Vector3Normalize(tmp), 10);
    Vector3 left = Vector3Normalize(Vector3CrossProduct(up, tmp));
    tmp = Vector3RotateByAxisAngle(tmp, up, GetMouseDelta().x*-0.01);
    tmp = Vector3RotateByAxisAngle(tmp, left, GetMouseDelta().y*0.01);
    tmp = Vector3Add(position, tmp);
    *lookat = tmp;
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
    this->position = Vector3Add(this->position, this->velocity);
    updateLookAtVectorFromMouse(this->position, &this->lookat);
}
Human::~Human() {}
