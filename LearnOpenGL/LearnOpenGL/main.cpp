//
//  main.cpp
//  LearnOpenGL
//
//  Created by Apple on 2017/10/29.
//  Copyright © 2017年 Apple. All rights reserved.
//

#include <iostream>
#include <cmath>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <SHADER/shader.hpp>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow *window);

// settings
using namespace std;
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;

int main(int argc,const char * argv[]){
    //init GLWF
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    
    //create window object
    GLFWwindow* window=glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window==NULL){
        cout<<"Failed to create GLFW window"<<endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    
    //init GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout<<"Failed to initialize GLAD"<<endl;
        return -1;
    }
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    Shader ourShader("/Users/apple/Documents/OpenGL/LearnOpenGL/LearnOpenGL/Extras/Include/SHADER/VertexShader.glsl",
                     "/Users/apple/Documents/OpenGL/LearnOpenGL/LearnOpenGL/Extras/Include/SHADER/FragmentShader.glsl");
    
    //set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[]={
        0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f,
        -0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
        0.0f,0.5f,0.0f,   0.0f,0.0f,1.0f
    };
    
    //Vertex Array Object,Vertex Buffer Object
    unsigned int VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ARRAY_BUFFER,0);
    //glBindVertexArray(VAO);
    
    //Render Loop
    while(!glfwWindowShouldClose(window)){
        processInput(window);
        
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        ourShader.use();
        glBindVertexArray(VAO);
        /*float timeValue=glfwGetTime();
        float greenValue=sin(timeValue)/2.0f+0.5f;
        int vertexColorLocation=glGetUniformLocation(shaderProgram,"ourColor");
        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);*/
        glDrawArrays(GL_TRIANGLES,0,3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //release resources
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

