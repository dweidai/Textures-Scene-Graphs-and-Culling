
#include "Transform.hpp"
#include <iterator>
#include <iostream>
#include <list>


Transform::Transform(){
    M = glm::mat4(1.0f);
    timer = 0;
}
Transform::~Transform(){
}
void Transform::addChild(Node* node){
    nodelist.push_back(node);
}
void Transform::removeChild(Node* node){
    for (std::list<Node*>::iterator it = nodelist.begin(); it != nodelist.end(); it++)
        if(node == *it){
            nodelist.erase(it);
        }
}
//its draw method needs to traverse the list of children and call each child node's draw function
//when draw(C) is called, multiply matrix M with matrix C.
void Transform:: draw(GLint Shader, glm::mat4 C){
    //first multiply matrix M with matrix C
    glm::mat4 Matrix = C*M;
    //now we traverse the list and call each node's draw function.
    for(Node* child: nodelist){
        child->draw(Shader,Matrix);
    }
}

void Transform::update(int direction){
    if(direction == 1){
        if(timer>=0 && timer <50){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), 0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer == 50){
            timer = -199;
        }
        if(timer < -100){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), -0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer >= -100 && timer <-1){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), 0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer == -1){
            timer = -199;
        }
    }
    else{
        if(timer>=0 && timer <50){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), -0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer == 50){
            timer = -199;
        }
        if(timer<-100){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), 0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer >= -100 && timer <-1){
            M = glm::translate(M, glm::vec3(0.0f,1.5f,0.0f));
            M = M* glm::mat4(glm::rotate(glm::mat4(1.0f), -0.008f, glm::vec3(1,0,0)));
            M = glm::translate(M, glm::vec3(0.0f, -1.5f,0.0f));
            timer = timer + 1;
        }
        if(timer == -1){
            timer = -199;
        }
    }
}
