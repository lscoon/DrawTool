//
//  display.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/3.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef display_hpp
#define display_hpp

void display();
void drawSnowMan();
void reshape(int w, int h);

void computePos(float deltaMove);
void computeDir(float deltaAngle);

#endif /* display_hpp */