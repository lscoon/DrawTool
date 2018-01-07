//
//  mouse.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>

#include "mouse.hpp"
#include "graph.hpp"

extern std::vector<graph> allgraph;
extern graph nowgraph;
extern int lineFlag, height;
Mouse myMouse = {0, 0, 0, 0, 0, 0, 0};
int zMove = 0;

void mouseButton(int button, int state, int x, int y){
    myMouse.x = x;
    myMouse.y = y;
    if(state == GLUT_DOWN){
        if(button == GLUT_LEFT_BUTTON){
            switch(nowgraph.type){
                case NOTHING:break;
                case LINE:{
                    if(lineFlag == 1){
                        myMouse.xpress = x;
                        myMouse.ypress = y;
                        lineFlag = 2;
                    }
                    else if(lineFlag == 2){
                        nowgraph = graph(Point(myMouse.xpress,height - myMouse.ypress), Point(myMouse.x,height - myMouse.y));
                        allgraph.push_back(nowgraph);
                        //nowgraph = graph();
                        lineFlag = 0;
                    }
                }break;
                default:break;
            }
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
