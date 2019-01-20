#ifndef Plane_hpp
#define Plane_hpp

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
class Plane
{
    
public:
    
    glm::vec3 normal,point;
    float d;
    
    
    Plane( glm::vec3 &v1,  glm::vec3 &v2,  glm::vec3 &v3);
    Plane(void);
    ~Plane();
    
    void set3Points( glm::vec3 &v1,  glm::vec3 &v2,  glm::vec3 &v3);
    void setNormalAndPoint(glm::vec3 &normal, glm::vec3 &point);
    void setCoefficients(float a, float b, float c, float d);
    float distance(glm::vec3 &p);
    
    void print();
    
};
#endif /* Plane_hpp */
