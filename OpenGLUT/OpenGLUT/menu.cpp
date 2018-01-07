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
extern void *font;

int mainMenu, colorMenu, fillMenu, shrinkMenu, fontMenu;
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
    
    fontMenu = glutCreateMenu(processFontMenu);
    glutAddMenuEntry("BITMAP_8_BY_13 ", INT_GLUT_BITMAP_8_BY_13);
    glutAddMenuEntry("BITMAP_9_BY_15", INT_GLUT_BITMAP_9_BY_15);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ", INT_GLUT_BITMAP_TIMES_ROMAN_10);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_24", INT_GLUT_BITMAP_TIMES_ROMAN_24);
    glutAddMenuEntry("BITMAP_HELVETICA_10 ", INT_GLUT_BITMAP_HELVETICA_10);
    glutAddMenuEntry("BITMAP_HELVETICA_12", INT_GLUT_BITMAP_HELVETICA_12);
    glutAddMenuEntry("BITMAP_HELVETICA_18", INT_GLUT_BITMAP_HELVETICA_18);
    
    mainMenu = glutCreateMenu(processMainMenu);
    glutAddSubMenu("Color", colorMenu);
    glutAddSubMenu("Polygon Mode", fillMenu);
    glutAddSubMenu("Shrink", shrinkMenu);
    glutAddSubMenu("Font", fontMenu);
    
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

void processFontMenu(int option){
    switch(option){
        case INT_GLUT_BITMAP_8_BY_13:font = GLUT_BITMAP_8_BY_13;break;
        case INT_GLUT_BITMAP_9_BY_15:font = GLUT_BITMAP_9_BY_15;break;
        case INT_GLUT_BITMAP_TIMES_ROMAN_10:font = GLUT_BITMAP_TIMES_ROMAN_10;break;
        case INT_GLUT_BITMAP_TIMES_ROMAN_24:font = GLUT_BITMAP_TIMES_ROMAN_24;break;
        case INT_GLUT_BITMAP_HELVETICA_10:font = GLUT_BITMAP_HELVETICA_10;break;
        case INT_GLUT_BITMAP_HELVETICA_12:font = GLUT_BITMAP_HELVETICA_12;break;
        case INT_GLUT_BITMAP_HELVETICA_18:font = GLUT_BITMAP_HELVETICA_18;break;
    }
}

