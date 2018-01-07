//
//  mouse.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>

#include "mouse.hpp"

Mouse myMouse = {0, 0, 0, 0, 0, 0, 0};
int zMove = 0;

void mouseButton(int button, int state, int x, int y){
    myMouse.x = x;
    myMouse.y = y;
    if(state == GLUT_DOWN){
        if(!(myMouse.lmb || myMouse.mmb || myMouse.rmb)){
            myMouse.xpress = x;
            myMouse.ypress = y;
        }
        switch(button){
            case GLUT_LEFT_BUTTON:myMouse.lmb = 1;break;
            case GLUT_MIDDLE_BUTTON:myMouse.mmb = 1;break;
            case GLUT_RIGHT_BUTTON:myMouse.rmb = 1;break;
        }
    }
    else{
        switch(button){
            case GLUT_LEFT_BUTTON:myMouse.lmb = 0;break;
            case GLUT_MIDDLE_BUTTON:myMouse.mmb = 0;break;
            case GLUT_RIGHT_BUTTON:myMouse.rmb = 0;break;
        }
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y){
    //int dx = x - myMouse.x;
    //int dy = y - myMouse.y;
    myMouse.x = x;
    myMouse.y = y;
    glutPostRedisplay();
}

void mousePassiveMove(int x, int y){
    //int dx = x - myMouse.x;
    //int dy = y - myMouse.y;
    myMouse.x = x;
    myMouse.y = y;
    glutPostRedisplay();
}
