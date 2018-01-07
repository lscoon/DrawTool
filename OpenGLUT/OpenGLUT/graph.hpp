//
//  graph.cpp
//  OpenGLUT
//
//  Created by Apple on 2018/1/7.
//  Copyright © 2018年 lsc. All rights reserved.
//

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "menu.hpp"

extern int width, height;
class Point{
public:
    int x;
    int y;
    unsigned char loc;
    
    Point(){
        x = 0;
        y = 0;
        loc = 0;
    }
    
    Point(int a, int b){
        x = a;
        y = b;
        loc = 0;
    }
    
    Point(int a, int b, unsigned char c){
        x = a;
        y = b;
        loc = c;
    }
    
    Point(const Point& src){
        x = src.x;
        y = src.y;
        loc = src.loc;
    }
    
    Point& operator=(const Point &src) {
        if (this != &src) {
            x = src.x;
            y = src.y;
            loc = src.loc;
        }
        return *this;
    }
};

class graph{
public:
    int existing;
    int dx;
    int dy;
    int angle;
    float scale;
    int type;
    
    graph(){
        existing = 0;
        dx = 0;
        dy = 0;
        angle = 0;
        scale = 1;
        type = NOTHING;
    }
    
    int exist(){
        return existing;
    }
    
    void drawBefore(){
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glTranslated(dx, dy, 0);
        glRotatef(angle, 0, 0, 1);
        glScaled(scale, scale, scale);
    }
    
    void drawAfter(){
        glPopMatrix();
    }
    
    Point line_begin;
    Point line_end;
    
    graph(Point p1, Point p2){
        line_begin = p1;
        line_end = p2;
        existing = 1;
        dx = 0;
        dy = 0;
        angle = 0;
        scale = 1;
        type = LINE;
    }
    
    void drawLine(){
        drawBefore();
        if(line_begin.x > line_end.x){
            Point temp = line_begin;
            line_begin = line_end;
            line_end = temp;
        }
            
        glPointSize(3);
        int startx = line_begin.x;
        int starty = line_begin.y;
        int endx = line_end.x;
        int endy = line_end.y;
        
        glBegin(GL_POINTS);
        float dx,dy,k;
        dx = endx - startx;
        dy = endy - starty;
        if(dx == 0)
            dx = 1;
        k = dy/dx;
        if(k <= 1){
            float y = starty;
            for(int x = startx; x <= endx; x++){
                glVertex2i(x, int(y + 0.5));
                y = y+k;
            }
        }
        else{
            if (k == 0)
                k = 0;
            else k = dx/dy;
            float x = startx;
            for(int y = starty; y <= endy; y++){
                glVertex2i(int(x + 0.5), y);
                x = x + k;
            }
        }
        glEnd();
        drawAfter();
    }
    
    Point centre;
    float r;
    
    graph(Point c ,float rr){
        centre = c;
        r = rr;
        existing = 1;
        dx = 0;
        dy = 0;
        angle = 0;
        scale = 1;
        type = CIRCLE;
    }
    
    void drawCircle(){
        int x0 = centre.x;
        int y0 = centre.y;
        glBegin(GL_POINTS);
        int x = 0;
        int y = r;
        int d = 1 - r;
        glVertex2i(x0 + x, y0 + y);
        glVertex2i(x0 + y, y0 + x);
        glVertex2i(x0 + y, y0 - x);
        glVertex2i(x0 + x, y0 - y);
        glVertex2i(x0 - x, y0 - y);
        glVertex2i(x0 - y, y0 - x);
        glVertex2i(x0 - y, y0 + x);
        glVertex2i(x0 - x, y0 + y);
        while(x < y){
            if(d < 0)
                d += 2*x + 3;
            else{
                d += 2*(x - y) + 5;
                y--;
            }
            x++;
            glVertex2i(x0 + x, y0 + y);
            glVertex2i(x0 + y, y0 + x);
            glVertex2i(x0 + y, y0 - x);
            glVertex2i(x0 + x, y0 - y);
            glVertex2i(x0 - x, y0 - y);
            glVertex2i(x0 - y, y0 - x);
            glVertex2i(x0 - y, y0 + x);
            glVertex2i(x0 - x, y0 + y);
        };
        glEnd();
    }
    
    Point oval_centre;
    float a;
    float b;
    
    graph(Point c, float aa, float bb){
        oval_centre = c;
        a = aa;
        b = bb;
        existing = 1;
        dx = 0;
        dy = 0;
        angle = 0;
        scale = 1;
        type = OVAL;
    }
    
    void drawOval(){
        int x0 = oval_centre.x;
        int y0 = oval_centre.y;
        glBegin(GL_POINTS);
        int aa = a*a;
        int bb = b*b;
        int twoaa = 2*aa;
        int twobb = 2*bb;
        int p;
        int x = 0;
        int y = b;
        int px = 0;
        int py = twoaa * y;
        glVertex2i(x0 + x, y0 + y);
        glVertex2i(x0 - x, y0 + y);
        glVertex2i(x0 + x, y0 - y);
        glVertex2i(x0 - x, y0 - y);
        
        p = (bb-(aa * b)+(0.25 * aa)) + 0.5;
        while(px < py){
            x++;
            px += twobb;
            if(p < 0)
                p += bb + px;
            else{
                y--;
                py -= twoaa;
                p += bb + px - py;
            }
            glVertex2i(x0 + x, y0 + y);
            glVertex2i(x0 - x, y0 + y);
            glVertex2i(x0 + x, y0 - y);
            glVertex2i(x0 - x, y0 - y);
        }
        
        p = (bb*(x + 0.5)*(x + 0.5) + aa*(y -1)*(y - 1)- aa*bb) + 0.5;
        while(y > 0){
            y--;
            py -= twoaa;
            if(p > 0)
                p += aa - py;
            else{
                x++;
                px += twobb;
                p += aa - py + px;
            }
            glVertex2i(x0 + x, y0 + y);
            glVertex2i(x0 - x, y0 + y);
            glVertex2i(x0 + x, y0 - y);
            glVertex2i(x0 - x, y0 - y);
        }
        
        glEnd();
    }
    
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    
    graph(Point pp1, Point pp2, Point pp3, Point pp4){
        p1 = pp1;
        p2 = pp2;
        p3 = pp3;
        p4 = pp4;
        existing = 1;
        dx = 0;
        dy = 0;
        angle = 0;
        scale = 1;
        type = BEZIER;
    }
    
    void drawBezier(){
        int x0 = p1.x;
        int x1 = p2.x;
        int x2 = p3.x;
        int x3 = p4.x;
        int y0 = p1.x;
        int y1 = p2.x;
        int y2 = p3.x;
        int y3 = p4.x;
        /*
         glBegin(GL_LINE_STRIP);
         glVertex2i(x0, y0);
         glVertex2i(x1, y1);
         glVertex2i(x2, y2);
         glVertex2i(x3, y3);
         glEnd();*/
        
        GLfloat ps1[11][2];
        GLfloat ps2[11][2];
        GLint i = 0;
        for(double t = 0.0; t <= 1.0; t += 0.1){
            double a1 = pow((1 - t), 2)/2;
            double a2 = (1 + 2*t - 2*t*t)/2;
            double a3 = t*t/2;
            ps1[i][0] = a1 * x0 + a2 * x1 + a3 * x2;
            ps1[i][1] = a1 * y0 + a2 * y1 + a3 * y2;
            ps2[i][0] = a1 * x1 + a2 * x2 + a3 * x3;
            ps2[i][1] = a1 * y1 + a2 * y2 + a3 * y3;
            i = i + 1;
        }
        
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 11; i++)
            glVertex2fv(ps1[i]);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < 11; i++)
            glVertex2fv(ps2[i]);
        glEnd();
    }
    
};

