//
//  keyboard.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/3.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <stdlib.h>
#include <math.h>

#include "keyboard.hpp"

extern float deltaAngle,deltaMove;
extern int mainMenu, colorMenu, fillMenu, shrinkMenu;
extern int menuFlag;

float x = 0.0f, z = 5.0f;
float lx = 0.0f, lz = -1.0f;
float angle = 0.0f;

void processNormalKeys(unsigned char key, int xx, int yy){
    glutSetMenu(mainMenu);
    switch(key){
        case 27:
            glutDestroyMenu(mainMenu);
            glutDestroyMenu(colorMenu);
            glutDestroyMenu(fillMenu);
            glutDestroyMenu(shrinkMenu);
            exit(0);break;
        case 's':
            if(!menuFlag)
                glutChangeToSubMenu(1, "Shrink", shrinkMenu);
            break;
        case 'c':
            if(!menuFlag)
                glutChangeToSubMenu(1, "Color", colorMenu);
            break;
    }
}

void pressKey(int key,int xx,int yy){
    switch(key){
        //case GLUT_KEY_LEFT:deltaAngle = -0.01f;break;
        //case GLUT_KEY_RIGHT:deltaAngle = 0.01f;break;
        case GLUT_KEY_UP:deltaMove = 0.5f;break;
        case GLUT_KEY_DOWN:deltaMove = -0.5f;break;
    }
}
void releaseKey(int key,int xx,int yy){
    switch(key){
        //case GLUT_KEY_LEFT:
        //case GLUT_KEY_RIGHT:deltaAngle = 0.0f;break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:deltaMove = 0.0f;break;
    }
}
