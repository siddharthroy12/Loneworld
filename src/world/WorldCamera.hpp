#ifndef WORLD_CAMERA_HPP
#define WORLD_CAMERA_HPP

#include "../../libs/raylib/src/raylib.h"
#include "../../libs/raylib/src/raymath.h"

struct Plane {
    Plane(const Vector3& p1, const Vector3& norm);
    Plane();

    Vector3 normal;

    float distance;
    float getSignedDistanceToPlane(const Vector3& point);
    bool boundingBoxIsOrOnPlane(BoundingBox box);
};

struct Frustum {
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
};

class  WorldCamera {
    public:
    WorldCamera(float fovy, Vector3 position, Vector3 lookat);
    WorldCamera();

    void setFovy(float fovy);
    float getFovy();
    void setPosition(Vector3 position);
    Vector3 getPosition();
    void setLookAt(Vector3 position);
    Vector3 getLookAt();
    bool boundingBoxVisible(BoundingBox box);
    Vector2 worldToScreen(Vector3 position);
    void beginCamera();
    void endCamera();


    private:
    Camera camera;
    Frustum frustum;
    void calculateFrustum(float zNear, float zFar);
};

#endif
