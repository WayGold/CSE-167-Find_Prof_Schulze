#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/norm.hpp>

#include "SurfaceWalker.h"
#include "../Camera.h"
#include "../../Time.h"
#include "FreeRotator.h"
#include "../geometries/PerlinNoiseTerrain.h"

SurfaceWalker::SurfaceWalker(ParametricSurface *t, Camera *cam, const glm::vec3 &body)
        : terrain(t), body(body), u(terrain->size() / 2), v(terrain->size() / 2) {
    foot = addChild(Group());
    head = addChild(FreeRotator(cam, glm::translate(body)));
    set();
}

void SurfaceWalker::update() {
    auto rotation = glm::mat3(head->transform.model);
    auto foward_vec = -rotation[2];
    auto left_vec = -rotation[0];
    auto movement = forward * foward_vec + left * left_vec;

    auto sensitivity = speed * Time::delta();
    auto du = terrain->derivativeU(u, v);
    auto dv = terrain->derivativeV(u, v);
    u += sensitivity * glm::dot(movement, du) / glm::length2(du);
    v += sensitivity * glm::dot(movement, dv) / glm::length2(dv);

    set();
    Group::update();
}

void SurfaceWalker::set() {
    u = glm::clamp(u, 0.2f, float(terrain->size()) - 1.2f);
    v = glm::clamp(v, 0.2f, float(terrain->size()) - 1.2f);
    transform.model = glm::translate(terrain->position(u, v));
}

void SurfaceWalker::onKeyPress(Key key, int mods) {
    if (key == forwardKey) {
        forward = 1.0f;
    } else if (key == leftKey) {
        left = 1.0f;
    } else if (key == backwardKey) {
        forward = -1.0f;
    } else if (key == rightKey) {
        left = -1.0f;
    }
    Group::onKeyPress(key, mods);
}

void SurfaceWalker::onKeyRelease(int key, int mods) {
    if (key == forwardKey || key == backwardKey) {
        forward = 0.0f;
    } else if (key == leftKey || key == rightKey) {
        left = 0.0f;
    }
    Group::onKeyRelease(key, mods);
}

void SurfaceWalker::onMouseMove(float x, float y) {
    Group::onMouseMove(x, y);

    // use FreeRotator to update foot
    float euler_x, euler_y, euler_z;
    glm::extractEulerAngleYXZ(head->transform.model, euler_y, euler_x, euler_z);
    foot->transform.model = glm::eulerAngleY(euler_y);
    head->transform.model[3] = glm::eulerAngleY(euler_y) * glm::vec4(body, 1.0f);
}
