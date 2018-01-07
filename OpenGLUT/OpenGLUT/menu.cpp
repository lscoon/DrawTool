//
//  menu.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <vector>

#include "menu.hpp"
#include "graph.hpp"

extern std::vector<graph> allgraph;
extern graph nowgraph;
extern float scale, red, green, blue;
extern void *font;

int mainMenu, colorMenu, drawMenu, transformMenu, fontMenu;
int menuFlag = 0;
int chooseFlag, showFlag;
int lineFlag, circleFlag, ovalFlag, bezierFlag, polygonFlag;
int panningFlag, rotateFlag, zoomFlag;

void createPopupMenus(){
    chooseFlag = 0;
    showFlag = 0;
    lineFlag = 0;
    circleFlag = 0;
    ovalFlag = 0;
    bezierFlag = 0;
    polygonFlag = 0;
    
    panningFlag = 0;
    rotateFlag = 0;
    zoomFlag = 0;
    
    colorMenu = glutCreateMenu(processColorMenu);
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    
    drawMenu = glutCreateMenu(processDrawMenu);
    glutAddMenuEntry("Line", LINE);
    glutAddMenuEntry("Circle", CIRCLE);
    glutAddMenuEntry("Oval", OVAL);
    glutAddMenuEntry("Bezier", BEZIER);
    glutAddMenuEntry("Polygon", POLYGON);
    
    transformMenu = glutCreateMenu(processTransformMenu);
    glutAddMenuEntry("Panning", PANNING);
    glutAddMenuEntry("Rotate", ROTATE);
    glutAddMenuEntry("Zoom", ZOOM);
    
    fontMenu = glutCreateMenu(processFontMenu);
    glutAddMenuEntry("BITMAP_8_BY_13 ", INT_GLUT_BITMAP_8_BY_13);
    glutAddMenuEntry("BITMAP_9_BY_15", INT_GLUT_BITMAP_9_BY_15);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ", INT_GLUT_BITMAP_TIMES_ROMAN_10);
    glutAddMenuEntry("BITMAP_TIMES_ROMAN_24", INT_GLUT_BITMAP_TIMES_ROMAN_24);
    glutAddMenuEntry("BITMAP_HELVETICA_10 ", INT_GLUT_BITMAP_HELVETICA_10);
    glutAddMenuEntry("BITMAP_HELVETICA_12", INT_GLUT_BITMAP_HELVETICA_12);
    glutAddMenuEntry("BITMAP_HELVETICA_18", INT_GLUT_BITMAP_HELVETICA_18);
    
    mainMenu = glutCreateMenu(processMainMenu);
    glutAddMenuEntry("Choose", CHOOSE);
    glutAddMenuEntry("Show", SHOW);
    glutAddSubMenu("Color", colorMenu);
    glutAddSubMenu("Draw", drawMenu);
    glutAddSubMenu("Transform", transformMenu);
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
    if(option == CHOOSE){
        chooseFlag = 1;
        
        lineFlag = 0;
        circleFlag = 0;
        ovalFlag = 0;
        bezierFlag = 0;
        
        panningFlag = 0;
        rotateFlag = 0;
        zoomFlag = 0;
    }
    if(option == SHOW){
        showFlag = 1;
    }
}

void processColorMenu(int option){
    red = green = blue = 0.0f;
    
    switch(option){
        case RED:red = 1.0f;break;
        case GREEN:green = 1.0f;break;
        case BLUE:blue = 1.0f;break;
    }
}

void processDrawMenu(int option){
    lineFlag = 0;
    circleFlag = 0;
    ovalFlag = 0;
    bezierFlag = 0;
    polygonFlag = 0;
    switch(option){
        case LINE:{
            lineFlag = 1;
            nowgraph.type = LINE;
        }break;
        case CIRCLE:circleFlag = 1;break;
        case OVAL:ovalFlag = 1;break;
        case BEZIER:bezierFlag = 1;break;
        case POLYGON:polygonFlag = 1;break;
    }
}

void processTransformMenu(int option){
    panningFlag = 0;
    rotateFlag = 0;
    zoomFlag = 0;
    switch(option){
        case PANNING:panningFlag = 1;break;
        case ROTATE:rotateFlag = 1;break;
        case ZOOM:zoomFlag = 1;break;
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

