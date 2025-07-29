// ICamera.h
#pragma once

#include <glm/glm.hpp>

struct ICamera {
    virtual ~ICamera() = default;

    /// Called when view matrix needs recomputing (e.g. after movement/rotation).
    virtual void updateView() {};

    /// Called when projection matrix needs recomputing (e.g. on resize).
    virtual void updateProjection(float aspectRatio, float nearZ = 0.1f, float farZ = 100.f) = 0;

    /// Query the current view matrix.
    virtual glm::mat4 getViewMatrix() const = 0;

    /// Query the current projection matrix.
    virtual glm::mat4 getProjectionMatrix() const = 0;

    virtual glm::vec3 getPosition() const = 0;

    virtual glm::mat4 getInverseViewMatrix() const = 0;
};