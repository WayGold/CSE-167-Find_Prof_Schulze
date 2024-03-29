#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "gl.h"

using CreateFunc = GLuint (*)();
using DelFunc = void (*)(GLuint);

template<CreateFunc create, DelFunc del>
class GLObject {
public:
    GLuint id = 0;

    GLObject() : id(create()) {}

    virtual ~GLObject() { del(id); }

    GLObject(const GLObject &) = delete;

    GLObject(GLObject &&other) noexcept { *this = std::move(other); }

    GLObject &operator=(const GLObject &) = delete;

    GLObject &operator=(GLObject &&other) noexcept {
        id = other.id;
        other.id = 0;
        return *this;
    }
};

#endif //GLOBJECT_H
