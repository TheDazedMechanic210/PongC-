#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <windows.h>
#include<conio.h>

float width=1080,height=720;
float racket_speed=0.9f;

float racket_width=15.0f;
float racket_height = 60.0f;

float racket_left_x=100.0f;
float racket_left_y=360.f;

float racket_right_x=width-racket_left_x-racket_width;
float racket_right_y=racket_left_y;

float ball_x = width / 2;
float ball_y = height / 2;
float ball_dir_x = -0.6f;
float ball_dir_y = 0.0f;
int ball_radius = 12;
int ball_speed = 2;

void drawRect(float x,float y,float width,float height) {
        glBegin(GL_QUADS);
        glVertex2f(x,y);
        glVertex2f(x+width,y);
        glVertex2f(x+width,y+height);
        glVertex2f(x,y+height);
        glEnd();
}


void Draw(GLFWwindow* window) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.5f,1,1);
    drawRect(width/2,0,15,720);
    glColor3f(1.0f,1.0f,1.0f);
    drawRect(racket_left_x,racket_left_y,racket_width,racket_height);
    drawRect(racket_right_x, racket_right_y, racket_width, racket_height);
    drawRect(ball_x - ball_radius/2,ball_y - ball_radius/2,ball_radius,ball_radius);
    glfwSwapBuffers(window);

}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        racket_right_y+=racket_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        racket_right_y-=racket_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        racket_left_y+=racket_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        racket_left_y-=racket_speed;
    }
}

void Update() {
    ball_x+=ball_dir_x;
    ball_y+=ball_dir_y;
    if (ball_x < racket_left_x + racket_width &&
        ball_x > racket_left_x &&
        ball_y < racket_left_y + racket_height &&
        ball_y > racket_left_y) {
        float t = ((ball_y - racket_left_y) / racket_height) - 0.5f;
        ball_dir_x = fabs(ball_dir_x); 
        ball_dir_y = t;
    }
    if (ball_x < racket_right_x + racket_width &&
        ball_x > racket_right_x &&
        ball_y < racket_right_y + racket_height &&
        ball_y > racket_right_y) {
        float t = ((ball_y - racket_right_y) / racket_height) - 0.5f;
        ball_dir_x = -fabs(ball_dir_x); 
        ball_dir_y = t;
    }

    if (ball_x < 0) {
        ball_x = width / 2;
         ball_y = height / 2;
         ball_dir_x = fabs(ball_dir_x); 
         ball_dir_y = 0;
    }

    if (ball_x > width) {
        ball_x = width / 2;
        ball_y = height / 2;
        ball_dir_x = -fabs(ball_dir_x);
        ball_dir_y = 0;
    }

    if (ball_y > height) {
        ball_dir_y = -fabs(ball_dir_y);
    }
    if (ball_y < 0) {
        ball_dir_y = fabs(ball_dir_y);
    }
   
}

void enable2D(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(void)
{
    GLFWwindow* window;


    if (!glfwInit())
        return -1;

    
    window = glfwCreateWindow(width,height, "Shitty Pong", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    enable2D(width,height);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
       Update();
       Draw(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}