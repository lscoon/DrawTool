//
//  font.cpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#include <GLUT/GLUT.h>

#include "font.hpp"

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void renderBitmapString(float x, float y, float z, void *font, char *string){
    char *c;
    glRasterPos3f(x, y, z);
    for(c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void renderStrokeFontString(float x, float y, float z, void *font, char *string){
    char *c;
    glPushMatrix();
    glTranslated(x, y, z);
    glScaled(0.002f, 0.002f, 0.002f);
    
    for(c = string; *c != '\0';c++)
        glutStrokeCharacter(font, *c);
    glPopMatrix();
}
