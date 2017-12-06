//
//  font.hpp
//  OpenGLUT
//
//  Created by Apple on 2017/12/6.
//  Copyright © 2017年 lsc. All rights reserved.
//

#ifndef font_hpp
#define font_hpp

#include <stdio.h>

void renderBitmapString(float x, float y, float z, void *font, char *string);
void renderStrokeFontString(float x, float y, float z, void *font, char *string);

#endif /* font_hpp */
