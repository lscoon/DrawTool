//
//  main.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/1.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include "display.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "menu.hpp"

int width = 800;
int height = 600;
int border = 6;

int position1x = border;
int position1y = border;
int width1 = (width * 3/4) - border * 3/2;
int height1 = height - 2*border;

int position2x =(width * 3/4) + border * 1/2;
int position2y = border;
int width2 = (width  * 1/4) - border * 3/2;
int height2 = height - 2*border;

int mainWindow, displayWindow, controlWindow;

void init(int window){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
}

int main(int argc,char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    mainWindow = glutCreateWindow("MyGLUT");
    
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderSceneAll);
    init(mainWindow);
    
    displayWindow = glutCreateSubWindow(mainWindow, position1x, position1y, width1, height1);
    glutDisplayFunc(renderDisplay);
    init(displayWindow);
    
    controlWindow = glutCreateSubWindow(mainWindow, position2x, position2y, width2, height2);
    glutDisplayFunc(renderControl);
    init(controlWindow);
    
    createPopupMenus();
    glutMainLoop();
    
    return 1;
}

