//
//  menu.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#define CHOOSE 0
#define SHOW 1

#define RED 1
#define GREEN 2
#define BLUE 3

#define NOTHING 0
#define LINE 1
#define CIRCLE 2
#define OVAL 3
#define BEZIER 4
#define POLYGON 5

#define PANNING 1
#define ROTATE 2
#define ZOOM 3

#define INT_GLUT_BITMAP_8_BY_13 1
#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

void createPopupMenus();
void processMenuStatus(int status);

void processMainMenu(int option);
void processColorMenu(int option);
void processDrawMenu(int option);
void processTransformMenu(int option);
void processFontMenu(int option);

#endif /* menu_hpp */
