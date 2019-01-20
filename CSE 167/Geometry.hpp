

#ifndef Geometry_hpp
#define Geometry_hpp

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <list>
#include <stdio.h>
#include "Transform.hpp"
#include "OBJObject.h"


class Geometry : public Node{
public:
    //set the modelview matrix to the current C matrix
    //an initialization method to load a 3D model (OBJ file) whose filename is passed to it (init(string filename). Your OBJ loader from project 2 should work.
    //have a class method which draws the 3D model associated with this node.
    Geometry(const char* filename);
    ~Geometry();
    OBJObject* obj;
    glm::mat4 C;
    void init(const char* filename);
    void draw(GLint shader, glm::mat4 C);
    void update(int direction);
};

#endif /* Geometry_hpp */
