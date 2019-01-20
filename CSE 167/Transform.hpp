#ifndef Transform_hpp
#define Transform_hpp


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
#include "Node.hpp"


class Transform: public Node{
public:
    Transform();
    ~Transform();
    //store a 4x4 transformation matrix M
    glm::mat4 M;
    std::list<Node*> nodelist;
    int timer;
    //store a list of pointers to child nodes (std::list<Node*>)
    //provide class methods to add and remove child nodes (addChild(), removeChild()) from the list
    void addChild(Node* node);
    void removeChild(Node* node);
    //its draw method needs to traverse the list of children and call each child node's draw function
    //when draw(C) is called, multiply matrix M with matrix C.
    void draw(GLint Shader, glm::mat4 C);
    void update(int direction);
    
};
#endif /* Transform_hpp */
