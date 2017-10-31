//
//  shader.cpp
//  LearnOpenGL
//
//  Created by Apple on 2017/10/29.
//  Copyright © 2017年 Apple. All rights reserved.
//

#include "SHADER/shader.hpp"
using namespace std;

Shader::Shader(const char* vertexPath,const char* fragmentPath,const char* geometryPath){
    string vertexCode;
    string fragmentCode;
    string geometryCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream gShaderFile;
    vShaderFile.exceptions(ifstream::failbit|ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit|ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit|ifstream::badbit);
    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream,fShaderStream,gShaderStream;
        vShaderStream<<vShaderFile.rdbuf();
        fShaderStream<<fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode=vShaderStream.str();
        fragmentCode=fShaderStream.str();
        if(geometryPath!=nullptr){
            gShaderFile.open(geometryPath);
            stringstream gShaderStream;
            gShaderStream<<gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode=gShaderStream.str();
        }
    }
    catch(ifstream::failure e){
        cout<<"ERROR:SHADER:FILE_NOT_SUCCESSFULLY_READ"<<endl;
    }
    const char* vShaderCode=vertexCode.c_str();
    const char* fShaderCode=fragmentCode.c_str();
    unsigned int vertex,fragment;
    //vertex shader
    vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex,"VERTEX");
    //fragment shader
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment,"FRAGMENT");
    //geometry shader
    unsigned int geometry;
    if(geometryPath!=nullptr){
        const char* gShaderCode=geometryCode.c_str();
        geometry=glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry,1,&gShaderCode,NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry,"GEOMETRY");
    }
    //shader program
    ID=glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    if(geometryPath!=nullptr)
        glAttachShader(ID,geometry);
    glLinkProgram(ID);
    checkCompileErrors(ID,"PROGRAM");
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath!=nullptr)
        glDeleteShader(geometry);
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const string &name,bool value) const{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::setInt(const string &name,int value) const{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setFloat(const string &name,float value) const{
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}
/*
 void setVec2(const string &name,const glm::vec2 &value) const{
 glUniform2f(glGetUniformLocation(ID,name.c_str()),1,&value[0]);
 }
 
 void setVec2(const string &name,float x,float y) const{
 glUniform2f(glGetUniformLocation(ID,name.c_str()),x,y);
 }
 
 void setVec3(const string &name,const glm::vec3 &value) const{
 glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);
 }
 
 void setVec3(const string &name,float x,float y,float z) const{
 glUniform3f(glGetUniformLocation(ID,name.c_str()),x,y,z);
 }
 
 void setVec4(const string &name,const glm::vec4 &value) const{
 glUniform4fv(glGetUniformLocation(ID,name.c_str()),1,&value[0]);
 }
 
 void setVec4(const string &name,float x,float y,float z,float w) const{
 glUniform4f(glGetUniformLocation(ID,name.c_str()),x,y,z,w);
 }
 
 void setMat2(const string &name,const glm::mat2 &mat) const{
 glUniformMatrix2fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&mat[0][0]);
 }
 
 void setMat3(const string &name,const glm::mat3 &mat) const{
 glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()),1,GL_FALSE,&mat[0][0]);
 }
 
 void setMat4(const string &name,const glm::mat4 &mat) const{
 glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&mat[0][0]);
 }*/
void Shader::checkCompileErrors(GLuint shader,string type){
    GLint success;
    GLchar infoLog[1024];
    if(type!="PROGRAM"){
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        if(!success){
            glGetShaderInfoLog(shader,1024,NULL,infoLog);
            cout<<"ERROR::SHADER_COMPILATION_FAILED of type: "<<type<<"\n"<<infoLog<<endl;
        }
    }
    else{
        glGetProgramiv(shader,GL_LINK_STATUS,&success);
        if(!success){
            glGetProgramInfoLog(shader,1024,NULL,infoLog);
            cout<<"ERROR::PROGRAM_LINKING_ERROR of type: "<<type<<"\n"<<infoLog<<endl;
        }
    }
}

