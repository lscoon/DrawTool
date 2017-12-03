//
//  menu.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "menu.hpp"

extern float scale, red, green, blue;

int mainMenu, colorMenu, fillMenu, shrinkMenu;
int menuFlag = 0;


void createPopupMenus(){
    colorMenu = glutCreateMenu(processColorMenu);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    
    fillMenu = glutCreateMenu(processFillMenu);
    glutAddMenuEntry("Fill", FILL);
    glutAddMenuEntry("Line", LINE);
    
    shrinkMenu = glutCreateMenu(processShrinkMenu);
    glutAddMenuEntry("Shrink", SHRINK);
    glutAddMenuEntry("Normal", NORMAL);
    
    mainMenu = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Color", colorMenu);
    glutAddSubMenu("Polygon Mode", fillMenu);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMenuStateFunc(processMenuStatus);
}

void processMenuStatus(int status){
    if(status == GLUT_MENU_IN_USE)
        menuFlag = 1;
    else menuFlag = 0;
}

void processMainMenu(int option){
    
}

void processColorMenu(int option){
    red = green = blue = 0.0f;
    
    switch(option){
        case RED:red = 1.0f;break;
        case GREEN:green = 1.0f;break;
        case BLUE:blue = 1.0f;break;
    }
}

void processFillMenu(int option){
    switch(option){
        case FILL:glPolygonMode(GL_FRONT, GL_FILL);break;
        case LINE:glPolygonMode(GL_FRONT, GL_LINE);break;
    }
}

void processShrinkMenu(int option){
    switch(option){
        case SHRINK:scale = 0.5f;break;
        case NORMAL:scale = 1.0f;break;
    }
}


