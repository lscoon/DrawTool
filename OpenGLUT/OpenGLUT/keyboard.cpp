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

extern int mainMenu, colorMenu, fillMenu, shrinkMenu;
extern int menuFlag;
extern float x, z, lx, lz;

int xMove = 0;
int yMove = 0;

void processNormalKeys(unsigned char key, int xx, int yy){
    glutSetMenu(mainMenu);
    switch(key){
        case 27:
            glutDestroyMenu(mainMenu);
            glutDestroyMenu(colorMenu);
            glutDestroyMenu(fillMenu);
            glutDestroyMenu(shrinkMenu);
            exit(0);break;
    }
}

void pressKey(int key,int xx,int yy){
    switch(key){
        case GLUT_KEY_LEFT:xMove = 1;break;
        case GLUT_KEY_RIGHT:xMove = -1;break;
        case GLUT_KEY_UP:yMove = -1;break;
        case GLUT_KEY_DOWN:yMove = 1;break;
    }
}
void releaseKey(int key,int xx,int yy){
    switch(key){
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:xMove = 0;break;
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:yMove = 0;break;
    }
}
