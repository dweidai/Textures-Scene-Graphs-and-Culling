#include "Geometry.hpp"
#include <string>

Geometry::Geometry(const char* filename){
    obj = new OBJObject(filename);
}
Geometry::~Geometry(){
    delete obj;
}

void Geometry:: init(const char* filename){
    obj = new OBJObject(filename);
    
}
void Geometry::draw(GLint shader, glm::mat4 C)
{
    //matrix is passed in with the Matrix from Transform
    obj->toWorld = C;
    obj->draw(shader);
}

void Geometry::update(int direction){
    
}
