#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement: uint8_t {
    Forward,
    Backward,
    Left,
    Right
};

const float kYaw = -90.0f;
const float kPitch = 0.0f;
const float kSpeed = 2.5f;
const float kSensitivity = 0.1f;
const float kFov = 45.0f;

class Camera {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = kYaw, float pitch = kPitch):
           front_(glm::vec3(0.0f, 0.0f, -1.0f)),
           speed_(kSpeed),
           sensitivity_(kSensitivity),
           fov_(kFov) {
            position_ = position; 
            worldUp_ = up;
            yaw_ = yaw;
            pitch_ = pitch;
           }
    
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(position_, position_ + front_, up_);
    }

    float GetFov() const {
        return fov_;
    }

    void ProcessKeyboard(CameraMovement direction, float deltaTime) {
        float offset = speed_ * deltaTime;
        if(direction == CameraMovement::Forward)
            position_ += front_ * offset;
        if(direction == CameraMovement::Backward)
            position_ -= front_ * offset;
        if(direction == CameraMovement::Left)
            position_ -= right_ * offset;
        if(direction == CameraMovement::Right)
            position_ += right_ * offset;
    }

    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
        xoffset *= sensitivity_;
        yoffset *= sensitivity_;

        yaw_ += xoffset;
        pitch_ += yoffset;

        if(constrainPitch) {
            if(pitch_ > 89.0f) pitch_ = 89.0f;
            if(pitch_ < -89.0f) pitch_ = -89.0f;
        }

        UpdateCameraVector();
    }

    void ProcessMouseScroll(float yoffset) {
        fov_ -= yoffset;
        if(fov_ < 1.0f) fov_ = 1.0f;
        if(fov_ > 45.0f) fov_ = 45.0f;
    }

private:
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;
    glm::vec3 worldUp_;

    float yaw_;
    float pitch_;
    float speed_;
    float sensitivity_;
    float fov_;

    void UpdateCameraVector()
    {
        glm::vec3 front;
        front.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
        front.y = std::sin(glm::radians(pitch_));
        front.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
        front_ = glm::normalize(front);
        right_ = glm::normalize(glm::cross(front_, worldUp_));
        up_ = glm::normalize(glm::cross(right_, front_));
    }
};

#endif