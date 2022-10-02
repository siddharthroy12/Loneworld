#include "WorldCamera.hpp"
#include "../helper.hpp"

Plane::Plane() {
    this->normal = { 0.0f, 1.0f, 0.0f };
    this->distance = 0.0f;
}

Plane::Plane(const Vector3& p1, const Vector3& norm) {
    this->normal = Vector3Normalize(norm);
    this->distance = Vector3DotProduct(normal, p1);
}

float Plane::getSignedDistanceToPlane(const Vector3 &point) {
    return Vector3DotProduct(normal, point) - distance;
}

bool Plane::boundingBoxIsOrOnPlane(BoundingBox box) {
    Vector3 size = { box.max.x - box.min.x, box.max.y - box.min.y, box.max.z - box.min.z };
    Vector3 center = { box.min.x + size.x/2, box.min.y + size.y/2, box.min.z + size.z/2 };
    Vector3 extents = { size.x/2, size.y/2, size.z/2 };
    // Compute the projection interval radius of b onto L(t) = b.c + t * p.n
    const float r = extents.x * std::abs(this->normal.x) +
        extents.y * std::abs(this->normal.y) + extents.z * std::abs(this->normal.z);

    return -r <= this->getSignedDistanceToPlane(center);
}

Camera createCamera(float fovy, Vector3 position, Vector3 lookat) {
    Camera camera;
    camera.fovy = fovy;
    camera.position = position;
    camera.target = lookat;
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FREE);
    return camera;
}

WorldCamera::WorldCamera() {
    this->camera = createCamera(45.0f, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
}

WorldCamera::WorldCamera(float fovy, Vector3 position, Vector3 lookat) {
    this->camera = createCamera(fovy, position, lookat);
}

void WorldCamera::setFovy(float fovy) {
    this->camera.fovy = fovy;
}

float WorldCamera::getFovy() {
    return this->camera.fovy;
}

Vector3 WorldCamera::getPosition() {
    return this->camera.position;
}

void WorldCamera::setPosition(Vector3 position) {
    this->camera.position = position;
}

Vector3 WorldCamera::getLookAt() {
    return this->camera.target;
}

void WorldCamera::setLookAt(Vector3 position) {
    this->camera.target = position;
}

bool WorldCamera::boundingBoxVisible(BoundingBox box) {
    return ((this->frustum.topFace.boundingBoxIsOrOnPlane(box) &&
             this->frustum.bottomFace.boundingBoxIsOrOnPlane(box) &&
             this->frustum.leftFace.boundingBoxIsOrOnPlane(box) &&
             this->frustum.rightFace.boundingBoxIsOrOnPlane(box) &&
             this->frustum.nearFace.boundingBoxIsOrOnPlane(box) &&
             this->frustum.farFace.boundingBoxIsOrOnPlane(box)
    ));
}

Vector2 WorldCamera::worldToScreen(Vector3 position) {
    return GetWorldToScreen(position, this->camera);
}

void WorldCamera::beginCamera() {
    this->calculateFrustum(1, 500);
    BeginMode3D(this->camera);
}

void WorldCamera::endCamera() {
    EndMode3D();
}

void WorldCamera::calculateFrustum(float zNear, float zFar) {
    float aspect = (float)getWindowWidth()/getWindowHeight();
    const Vector3 front = Vector3Normalize(Vector3Subtract(this->camera.target, this->camera.position));
    const Vector3 direction = Vector3Normalize(Vector3Subtract(this->camera.position, this->camera.target));
    const Vector3 right = Vector3Normalize(Vector3CrossProduct(this->camera.up, direction));
    const float halfVSide = zFar * tanf(this->camera.fovy * .5f);
    const float halfHSide = halfVSide * aspect;
    const Vector3 frontMultFar = Vector3Scale(front, zFar);

    frustum.nearFace = { Vector3Add(this->camera.position, Vector3Scale(front, zNear)), front };
    frustum.farFace = { Vector3Add(this->camera.position, frontMultFar), Vector3Scale(front, -1) };
    frustum.rightFace = { this->camera.position, Vector3CrossProduct(this->camera.up, Vector3Add(frontMultFar, Vector3Scale(right, halfHSide))) };
    frustum.leftFace = { this->camera.position, Vector3CrossProduct(Vector3Subtract(frontMultFar, Vector3Scale(right, halfHSide)), this->camera.up) };
    frustum.topFace = { this->camera.position, Vector3CrossProduct(right, Vector3Subtract(frontMultFar, Vector3Scale(this->camera.up, halfVSide))) };
    frustum.bottomFace = { this->camera.position, Vector3CrossProduct(Vector3Add(frontMultFar, Vector3Scale(this->camera.up, halfVSide)), right) };
}

