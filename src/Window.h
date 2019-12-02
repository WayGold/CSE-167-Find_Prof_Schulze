#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "gl_wraps/gl.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "objects/Group.h"
#include "objects/Camera.h"
#include "objects/Skybox.h"
#include "objects/controls/FreeFlying.h"
#include "gl_wraps/Shader.h"
#include "gl_wraps/GLContext.h"
#include "objects/geometries/BezierCurve.h"
#include "objects/controls/ControlTriple.h"
#include "objects/animators/ConstraintAnimator.h"

class Window : public GLContext {
public:
    Group scene;

    Camera *camera;

    Skybox *skybox;

    std::array<std::shared_ptr<Shader>, 2> shaders;

//    BezierCurve *bezier;

//    std::vector<ControlTriple> controls;
//    int selected = 0;

    FreeFlying *flyControl;

//    ConstraintAnimator *animation;

    static Window *retrieve(GLFWwindow *w) { return reinterpret_cast<Window *>(glfwGetWindowUserPointer(w)); }

    Window();

    void loop();

    void setupCallbacks();

    void initializeProgram();

    void initializeObjects();

    void resizeCallback(int width, int height);

    void update();

    void draw();

    void keyCallback(int key, int scancode, int action, int mods);

    void mouseButtonCallback(int button, int action, int mods);

    void cursorPosCallback(double x, double y);

    void scrollCallback(double xoffset, double yoffset);
};

#endif
