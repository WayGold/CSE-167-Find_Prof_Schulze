#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <glm/glm.hpp>

#include "../Node.h"

class Trackball : public Node {
public:
    using Node::Node;

    // x,y should be normalized
    void start(float x, float y);

    // x,y should be normalized
    void move(float x, float y);

    void stop();

    void scale(float offset);

protected:
    NodePtr clone() override { return std::make_unique<Trackball>(*this); }

private:
    static glm::vec3 viewportToTrackball(float x, float y);

    bool started = false;
    glm::mat4 orientation{1.0f};
    glm::vec3 initial;
};


#endif // TRACKBALL_H
