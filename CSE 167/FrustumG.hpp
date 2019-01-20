//
//  FrustumG.hpp
//  CSE 167
//
//  Created by Dwei on 11/1/18.
//  Copyright © 2018 Dwei. All rights reserved.
//

#ifndef FrustumG_hpp
#define FrustumG_hpp
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


#ifndef _PLANE_
#include "Plane.hpp"
#endif

class Plane;



class FrustumG
{
private:
    
    enum {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEARP,
        FARP
    };
    
    
public:
    
    static enum {OUTSIDE, INTERSECT, INSIDE};
    
    Plane pl[6];
    
    
    glm::vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float nearD, farD, ratio, angle,tang;
    float nw,nh,fw,fh;
    
    FrustumG();
    ~FrustumG();
    
    void setCamInternals(float angle, float ratio, float nearD, float farD);
    void setCamDef(glm::vec3 &p, glm::vec3 &l, glm::vec3 &u);
    int sphereInFrustum(glm::vec3 &p, float raio);
};


#endif /* FrustumG_hpp */
