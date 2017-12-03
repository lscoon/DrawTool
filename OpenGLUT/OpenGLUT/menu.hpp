//
//  menu.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#define RED 1
#define GREEN 2
#define BLUE 3

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

void createPopupMenus();
void processMenuStatus(int status);

void processMainMenu(int option);
void processColorMenu(int option);
void processFillMenu(int option);
void processShrinkMenu(int option);

#endif /* menu_hpp */
