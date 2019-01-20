#include <math.h>
#include "Window.h"
#include "OBJObject.h"
#include "Geometry.hpp"
#include "Transform.hpp"
#include "Node.hpp"

const char* window_title = "David CSE 167 HW3";
//Cube * cube;
OBJObject* cur;
Transform* army;
Transform* balls;
Geometry* sphere;
Transform* sphere_transform;
Transform* robot;
Geometry* body;
Transform* body_transform;
Geometry* head;
Transform* head_transform;
Geometry* arm_left;
Transform* arm_left_transform;
Geometry* arm_right;
Transform* arm_right_transform;
Geometry* leg_left;
Transform* leg_left_transform;
Geometry* leg_right;
Transform* leg_right_transform;
Geometry* eye_right;
Geometry* eye_left;
Transform* eye_right_transform;
Transform* eye_left_transform;
GLint shaderProgram;
glm::vec3 points[6];
glm::vec3 norms[6];


// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/shader.frag"


// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 100.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, -100.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;
int kb = 4;
int current = 1;
int changesize = 0;
int buttonsize = 0;
int scale = 1.5;
int pressed = 0;
int toggle_sphere = 0;
int rotate_grid = 0;
int culling = 0;
int EC = 0;
float normal_coloring = 0;
float angle;
float near = 0.1f;
float far = 1000.0f;
glm::vec3 last_position;
glm::vec3 current_position;
glm::vec3 move;
glm::mat4 Window::P;
glm::mat4 Window::V;

glm::mat4 sphere_matrix = glm::mat4(1.0f);
glm::mat4 body_matrix = glm::mat4(1.0f);
glm::mat4 head_matrix= glm::mat4(1.0f);
glm::mat4 arm_left_matrix= glm::mat4(1.0f);
glm::mat4 arm_right_matrix= glm::mat4(1.0f);
glm::mat4 leg_left_matrix= glm::mat4(1.0f);
glm::mat4 leg_right_matrix= glm::mat4(1.0f);
glm::mat4 eye_right_matrix = glm::mat4(1.0f);
glm::mat4 eye_left_matrix = glm::mat4(1.0f);
glm::vec3 location[100];

//and update the Transform matrix M to body_matrix
void Window::initialize_objects()
{
    //this is body
    //grid is trnasform array and each M assign to draw matrix
    army = new Transform();
    balls = new Transform();
    robot = new Transform();
    body = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/body_s.obj");
    body_transform = new Transform();
    body_transform->addChild(body);
    body_matrix = body_matrix * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f));
    body_transform->M = body_matrix;
    robot->addChild(body_transform);
    robot->addChild(body);
    
    head = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/head_s.obj");
    head_transform = new Transform();
    head_transform->addChild(head);
    head_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,6.5f,0.0f)) *head_matrix;
    head_matrix = head_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(2.0f,2.0f,2.0f));
    head_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-4.0f,0.0f)) *head_matrix;
    head_transform->M = head_matrix;
    robot->addChild(head_transform);
    robot->addChild(head);
    
    arm_left = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/limb_s.obj");
    arm_left_transform = new Transform();
    arm_left_transform->addChild(arm_left);
    arm_left_matrix = arm_left_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(3.0f,3.5f,3.0f));
    arm_left_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.5f,0.0f,0.0f)) *arm_left_matrix;
    arm_left_transform->M = arm_left_matrix;
    robot->addChild(arm_left_transform);
    robot->addChild(arm_left);
    
    arm_right = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/limb_s.obj");
    arm_right_transform = new Transform();
    arm_right_transform->addChild(arm_right);
    arm_right_matrix = arm_right_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(3.0f,3.5f,3.0f));
    arm_right_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.5f,0.0f,0.0f)) *arm_right_matrix;
    arm_right_transform->M = arm_right_matrix;
    robot->addChild(arm_right_transform);
    robot->addChild(arm_right);
     
    leg_right = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/limb_s.obj");
    leg_right_transform = new Transform();
    leg_right_transform->addChild(leg_right);
    leg_right_matrix = leg_right_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(3.0f,3.0f,3.0f));
    leg_right_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f,-3.2f,0.0f)) *leg_right_matrix;
    leg_right_transform->M = leg_right_matrix;
    robot->addChild(leg_right_transform);
    robot->addChild(leg_right);
    
    leg_left = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/limb_s.obj");
    leg_left_transform = new Transform();
    leg_left_transform->addChild(leg_left);
    leg_left_matrix = leg_left_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(3.0f,3.0f,3.0f));
    leg_left_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f,-3.2f,0.0f)) *leg_left_matrix;
    leg_left_transform->M = leg_left_matrix;
    robot->addChild(leg_left_transform);
    robot->addChild(leg_left);
    
    eye_left = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/eyeball_s.obj");
    eye_left_transform = new Transform();
    eye_left_transform->addChild(eye_left);
    eye_left_matrix = eye_left_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(2.8f,2.8f,2.8f));
    eye_left_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f,2.7f,1.8f)) *eye_left_matrix;
    eye_left_transform->M = eye_left_matrix;
    robot->addChild(eye_left_transform);
    robot->addChild(eye_left);
    
    eye_right = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/eyeball_s.obj");
    eye_right_transform = new Transform();
    eye_right_transform->addChild(eye_right);
    eye_right_matrix = eye_right_matrix*glm::scale(glm::mat4(1.0f), glm::vec3(2.8f,2.8f,2.8f));
    eye_right_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f,2.7f,1.8f)) *eye_right_matrix;
    eye_right_transform->M = eye_right_matrix;
    robot->addChild(eye_right_transform);
    robot->addChild(eye_right);
    
    //the sphere around it
    sphere = new Geometry("/Users/apple/Desktop/CSE 167/CSE 167 hw3/CSE 167/eyeball_s.obj");
    sphere_transform = new Transform();
    sphere_transform->addChild(sphere);
    sphere_matrix = sphere_matrix * glm::scale(glm::mat4(1.0f), glm::vec3(65.0f,65.0f,65.0f));
    sphere_transform->M = sphere_matrix;
    
    for(int i=-5; i<5; i++){
        for(int j=-5; j<5; j++){
            Transform * temprobot = new Transform();
            Transform * tempsphere = new Transform();
            temprobot->addChild(body);
            temprobot->addChild(body_transform);
            temprobot->addChild(head);
            temprobot->addChild(head_transform);
            temprobot->addChild(leg_left);
            temprobot->addChild(leg_left_transform);
            temprobot->addChild(leg_right);
            temprobot->addChild(leg_right_transform);
            temprobot->addChild(arm_left);
            temprobot->addChild(arm_left_transform);
            temprobot->addChild(arm_right);
            temprobot->addChild(arm_right_transform);
            temprobot->addChild(eye_left);
            temprobot->addChild(eye_left_transform);
            temprobot->addChild(eye_right);
            temprobot->addChild(eye_right_transform);
            tempsphere->addChild(sphere);
            tempsphere->addChild(sphere_transform);
            temprobot->M  = glm::translate(glm::mat4(1.0f),glm::vec3(10.f*i,0,-10.f*j)) *temprobot->M;
            tempsphere->M = glm::translate(glm::mat4(1.0f), glm::vec3(10.f*i,0,-10.f*j)) * tempsphere->M;
            location[(i+5)*10+(j+5)] =glm::vec3(10.f*i,0,-10.f*j);
            army->addChild(temprobot);
            balls->addChild(tempsphere);
        }
    }
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
    delete(body);
    delete(head);
    delete(arm_left);
    delete(arm_right);
    delete(leg_left);
    delete(leg_right);
    delete(eye_left);
    delete(eye_right);
    delete(robot);
	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);
	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	// Call the update function the cube
    //body->update();
    leg_left_transform->update(1);
    leg_right_transform->update(-1);
    arm_left_transform->update(1);
    arm_right_transform->update(-1);
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    calculatepoints();
    //int count = 0;
	// Use the shader of programID
	glUseProgram(shaderProgram);
    if(culling == 1){
        for(int i =0;i<100; i++){
            glm::mat4 mat = glm::translate(glm::mat4(1.0f), location[i]);
            if(checkinfrustum(location[i], 2)){
                robot->draw(shaderProgram, mat);
                if(toggle_sphere == 1){
                    sphere_transform->draw(shaderProgram, mat);
                }
            }
        }
    }
    else if(culling == 0){
        for(int i =0;i<100; i++){
            glm::mat4 mat = glm::translate(glm::mat4(1.0f), location[i]);
            robot->draw(shaderProgram, mat);
            if(toggle_sphere == 1){
                sphere_transform->draw(shaderProgram, mat);
            }
        }
        
    }
    //std::cout << count << std::endl;
    // Render objects
    // Gets events, including input such as keyboard and mouse or window resizing
    glfwPollEvents();
    // Swap buffers
    glfwSwapBuffers(window);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if(yoffset>0){
        cam_pos = cam_pos + (0.01f) * glm::vec3(cam_look_at-cam_pos);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
    else{
        cam_pos = cam_pos - (0.01f) * glm::vec3(cam_look_at-cam_pos);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
        if (key == GLFW_KEY_S){
            if(toggle_sphere == 0){
                toggle_sphere = 1;
            }
            else{
                toggle_sphere = 0;
            }
        }
        if (key == GLFW_KEY_Q){
            if(rotate_grid == 0){
                //rotate the grid now
                rotate_grid =1;
            }
            else if(rotate_grid == 1){
                rotate_grid =0;
            }
        }
        if (key == GLFW_KEY_C){
            if(culling == 0){
                culling = 1;
            }
            else if(culling ==1){
                culling = 0;
            }
        }
        if (key == GLFW_KEY_Z){
            if(EC == 0){
                EC = 1;
            }
            else if(EC == 1){
                EC = 0;
            }
        }
	}
}

glm::vec3 Window::trackBallMapping(double x, double y){
    glm::vec3 v = glm::vec3(0,0,0);
    double d;
    v.x = (2.0*x-width)/width;
    v.y = (height-2.0*y)/height;
    
    v.z = 0.0;
    d = glm::length(v);
    d = (d<1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d*d);
    v = glm::normalize(v);
    return v;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(pressed == 0 && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        //glfwGetCursorPos(window, &x, &y);
        pressed = 1;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        pressed = 0;
    }
}
void Window::cursor_callback( GLFWwindow *window, double x, double y ){
    //only continue if the mouse is pressed
    if(pressed == 1){
        last_position = Window::trackBallMapping(x, y);
        pressed = -1;
    }
    else if(pressed == 0){
        //do nothing
        return;
    }
    current_position = Window::trackBallMapping(x, y);
    move = glm::cross(last_position, current_position);
    angle = asin(glm::length(move));
    angle = angle/50;
    if(glm::length(current_position-last_position) < 0.01){
        return; //do nothing
    }
    // here we rotate the grid
    if(rotate_grid == 1){
        glm::mat4 rotationMatrix = glm::rotate(army->M, angle, move);
        for(int i =0; i<100; i++){
            glm::vec4 templocation = glm::vec4(location[i], 1.0f);
            templocation = rotationMatrix * templocation;
            location[i] = glm::vec3(templocation);
        }
        army->M = glm::rotate(army->M, angle, move);
        balls->M = glm::rotate(balls->M, angle, move);
    }
    //here we rotate the camera
    else if(rotate_grid == 0){
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, move);
        glm::vec3 d = cam_pos-cam_look_at; ////comment
        glm::vec4 temp = rotation*glm::vec4(d,0.0f);
        cam_look_at = glm::vec3(cam_pos.x-temp.x,cam_pos.y-temp.y, cam_pos.z-temp.z);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}
void Window::calculatepoints(){
    float ratio = (float)width / (float)height;
    glm::vec3 up = cam_up;
    glm::vec3 p = cam_pos;
    glm::vec3 d = cam_look_at-cam_pos;
    glm::vec3 right = glm::normalize(glm::cross(d, up));
    float Hnear;
    if(EC == 0){
        Hnear = near *glm::tan(glm::radians( 25.5f)) *2;
    }
    else if(EC == 1){
        Hnear = near *glm::tan(glm::radians(13.4f)) *2;
    }
    float Wnear = Hnear*ratio;
    float Hfar;
    if(EC == 0){
       Hfar = far*glm::tan(glm::radians(25.5f)) *2;
    }
    else if(EC == 1){
        Hfar = far*glm::tan(glm::radians(13.4f)) *2;
    }
    float Wfar = Hfar*ratio;
    glm::vec3 fc = p +d*far;
    glm::vec3 ftl = fc + (up * Hfar/2.0f) - (right * Wfar/2.0f);
    glm::vec3 ftr = fc + (up * Hfar/2.0f) + (right * Wfar/2.0f);
    glm::vec3 fbl = fc - (up * Hfar/2.0f) - (right * Wfar/2.0f);
    glm::vec3 fbr = fc - (up * Hfar/2.0f) + (right * Wfar/2.0f);
    glm::vec3 nc = p + d * near;
    glm::vec3 ntl = nc + (up * Hnear/2.0f) - (right * Wnear/2.0f);
    glm::vec3 ntr = nc + (up * Hnear/2.0f) + (right * Wnear/2.0f);
    glm::vec3 nbl = nc - (up * Hnear/2.0f) - (right * Wnear/2.0f);
    glm::vec3 nbr = nc - (up * Hnear/2.0f) + (right * Wnear/2.0f);
    
    createplane(ntr, ntl, ftl, 0);
    createplane(nbl, nbr, fbr, 1);
    createplane(ntl, nbl, fbl, 2);
    createplane(nbr, ntr, fbr, 3);
    createplane(ntl, ntr, nbr, 4);
    createplane(ftr, ftl, fbl, 5);
    /*std::cout << "this is norms" << std::endl;
    for(int i =0; i<6; i++){
         std::cout << points[i].x << " "<<points[i].y << " "<< points[i].z <<std::endl;
    }
    for(int i =0; i< 6; i++){
         std::cout << norms[i].x << " "<<norms[i].y << " "<< norms[i].z <<std::endl;
    }*/
}
void Window::createplane(glm::vec3 &x, glm::vec3 &y, glm::vec3 &z, int id){
    glm::vec3 aux1 = x - y;
    glm::vec3 aux2 = z - y;
    glm::vec3 normal = glm::normalize(glm::cross(aux2,aux1));
    norms[id] = normal;
    points[id] = y;
}
bool Window::checkinfrustum(glm::vec3 &p, float radius){
    for(int i=0; i<6; i++){
        float dist = glm::dot((p-points[i]),norms[i]);
        if (dist < -radius){
            return false;
        }
    }
    return true;
}

