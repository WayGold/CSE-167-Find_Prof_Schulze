#ifndef SKYBOX_H
#define SKYBOX_H

#include "geometries/Mesh.h"
#include "../gl_wraps/GLTexture.h"

class Skybox : public Node {
public:
    Skybox();

    void
    draw(const glm::mat4 &world, const glm::mat4 &projection, const glm::mat4 &view, const glm::vec3 &eye) override;

    void update() override {}

    bool cull(const glm::mat4 &view_proj) override { return false; }

    std::shared_ptr<GLTexture> cubeMap;

protected:
    NodePtr clone() override { return std::make_unique<Skybox>(*this); }

private:
    std::shared_ptr<Mesh> cube;

    std::shared_ptr<Shader> shader;
};


#endif //SKYBOX_H
