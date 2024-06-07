#pragma once

#include <glm/glm.hpp>

struct CameraParams
{
    glm::vec3 position;
    glm::vec3 target = {0.0f, 0.0f, 0.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
    float aspect;
    float fov;
};

class Camera
{
public:

    Camera(const CameraParams& params);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    
    CameraParams params;

};