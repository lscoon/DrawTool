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
#include <vector>

#include "keyboard.hpp"
#include "graph.hpp"

using namespace std;
extern graph nowgraph;

extern int mainMenu, colorMenu, drawMenu, transformMenu, fontMenu;
extern int panningFlag, rotateFlag, zoomFlag;
extern float x, z, lx, lz;

int xMove = 0;
int yMove = 0;

void processNormalKeys(unsigned char key, int xx, int yy){
    glutSetMenu(mainMenu);
    switch(key){
        case 27:
            glutDestroyMenu(mainMenu);
            glutDestroyMenu(colorMenu);
            glutDestroyMenu(drawMenu);
            glutDestroyMenu(transformMenu);
            glutDestroyMenu(fontMenu);
            exit(0);break;
    }
}

void pressKey(int key,int xx,int yy){
    if(panningFlag == 1){
        switch(key){
            case GLUT_KEY_LEFT:nowgraph.dx += 5;break;
            case GLUT_KEY_RIGHT:nowgraph.dx -= 5;break;
            case GLUT_KEY_UP:nowgraph.dy += 5;break;
            case GLUT_KEY_DOWN:nowgraph.dy -=  5;break;
        }
    }
    else if(rotateFlag){
        switch(key){
            case GLUT_KEY_LEFT:nowgraph.angle += 5;break;
            case GLUT_KEY_RIGHT:nowgraph.angle -= 5;break;
        }
    }
    else if(zoomFlag){
        switch(key){
            case GLUT_KEY_LEFT:nowgraph.scale = nowgraph.scale*0.9;break;
            case GLUT_KEY_RIGHT:nowgraph.scale = nowgraph.scale*1.1;break;
        }
    }
    
}
void releaseKey(int key,int xx,int yy){
}
