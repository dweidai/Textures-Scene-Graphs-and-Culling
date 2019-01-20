//
//  Node.hpp
//  CSE 167
//
//  Created by Dwei on 10/30/18.
//  Copyright © 2018 Dwei. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <glm/mat4x4.hpp>
#include <vector>

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>


class Node{
public:
    //an abstract draw method: virtual void draw(Matrix4 C)=0
    //an abstract virtual void update()=0 method to separate bounding sphere updates from rendering (4 points)
    virtual void draw(GLint shader, glm::mat4 C) =0;
    virtual void update(int direction)=0;
    
};
#endif
