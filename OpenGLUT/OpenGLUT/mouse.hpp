//
//  mouse.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/4.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef mouse_hpp
#define mouse_hpp

typedef struct Mouse{
    int x;
    int y;
    int lmb;
    int mmb;
    int rmb;
    
    int xpress;
    int ypress;
}Mouse;

void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);
void mousePassiveMove(int x, int y);
#endif /* mouse_hpp */
