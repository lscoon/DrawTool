//
//  main.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/1.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

float angle = 0.0f;
float red = 1.0f, blue = 1.0f, green = 1.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;


void display();
void reshape(int w, int h);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

void drawSnowMan();

int main(int argc,char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("MyGLUT");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
    return 1;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt(x, 0.0f, z,
              x+lx, 1.0f, z+lz,
              0.0f, 1.0f, 0.0f);
    
    glColor3f( 0.9f, 0.9f, 0.9f);
    
    //glRotatef(angle, 0.0f, 1.0f, 0.0f);
    /*
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();
    /*
    for(int i = -3; i < 3; i ++)
        for(int j = -3; j < 3; j ++){
            glPushMatrix();
            glTranslatef(i * 10.0f, 0.0f, j * 10.0f);
            drawSnowMan();
            glPopMatrix();
        }
    */
    //angle += 0.1f;
    glutSwapBuffers();
}

void reshape(int w,int h){
    if(h == 0)
        h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void processNormalKeys(unsigned char key, int x, int y){
    if(key == 27)
        exit(0);
}

void processSpecialKeys(int key, int x, int y){
    float fraction = 0.1f;
    switch(key){
        case GLUT_KEY_LEFT:
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT:
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP:
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN:
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void drawSnowMan(){
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);
    
    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();
    
    // Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glutSolidCone(0.08f,0.5f,10,2);
}
