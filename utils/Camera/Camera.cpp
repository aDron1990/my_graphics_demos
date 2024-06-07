#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const CameraParams& params_)
    : params{params_} {}

glm::mat4 Camera::getViewMatrix() const
{
    auto direction = glm::normalize(params.position - params.target);
    auto right = glm::cross(direction, params.up);
    auto up = glm::cross(right, direction);
    return glm::lookAt(params.position, params.target, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(params.fov), params.aspect, 0.1f, 100.0f);
}
