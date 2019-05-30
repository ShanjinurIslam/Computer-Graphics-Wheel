//
//  main.cpp
//  Wheel
//
//  Created by Shanjinur Islam on 5/29/19.
//  Copyright © 2019 Shanjinur Islam. All rights reserved.
//

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/GLUT.h>
#include <cmath>

double cameraHeight = 80.0;
double cameraAngle  = 1.0;
double rotateAngle = 3 ;
double forwardAngle = 3 ;
double forwardLength = 0 ;
double radius ;

class Point{
public:
    double x,y,z ;
    
    Point(){
        x = 0 ;
        y = 0 ;
        z = 0 ;
    }
    Point(double x,double y,double z){
        this->x = x ;
        this->y = y ;
        this->z = z ;
    }
    Point(const Point &p){
        this->x = p.x ;
        this->y = p.y ;
        this->z = p.z ;
    }
};

void drawAxes(){
    glPushMatrix();
    glBegin(GL_LINES);{
        glColor3f(1.0, 0, 0);
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);
        
        glColor3f(0, 1.0, 0);
        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);
        
        glColor3f(0, 0, 1.0);
        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();
    glPopMatrix() ;
}

void drawGrid()
{
    int i;
    
        glColor3f(0.6, 0.6, 0.6);    //grey
        glBegin(GL_LINES);{
            for(i=-8;i<=8;i++){
                
                if(i==0)
                    continue;    //SKIP the MAIN axes
                
                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);
                
                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }glEnd();
}

void wheel(double radius,double height,int segments){
    
    glPushMatrix() ;
    glTranslatef(0,0,+radius);
    glRotatef(90,0,1,0) ;
    Point p[segments+2] ;
    double angle ;
    double h = height / 2 ;
    for(int i=0;i<=segments;i++){
        angle = ((1.0*i)/(1.0*segments))*acos(-1.0)*2 ;
        p[i].x = radius*cos(angle) ;
        p[i].y = radius*sin(angle) ;
        p[i].z = h/2 ;
    }
    glTranslatef(0,forwardLength, 0) ;
    glPushMatrix() ;
    glRotatef(forwardAngle,0,0,1) ;
    double shade = 0.0 ;
    for(int i=0;i<segments;i++){
        
        if(i<segments/2)  shade=((double)i/(double)segments);
        else  shade=(1-(double)i/(double)segments);
        
        glColor3f(shade,shade,shade);
        
        glBegin(GL_LINES) ;
        
        glVertex3f(p[i].x,p[i].y,p[i].z) ;
        glVertex3f(p[i+1].x,p[i+1].y,p[i+1].z) ;
        glVertex3f(p[i].x,p[i].y,-p[i].z) ;
        glVertex3f(p[i+1].x,p[i+1].y,-p[i+1].z) ;
        
        glEnd() ;
        
        glBegin(GL_QUADS) ;
        glVertex3f(p[i].x,p[i].y,p[i].z) ;
        glVertex3f(p[i+1].x,p[i+1].y,p[i+1].z) ;
        glVertex3f(p[i+1].x,p[i+1].y,-p[i+1].z) ;
        glVertex3f(p[i].x,p[i].y,-p[i].z) ;
        
        glEnd() ;
    }
    glPopMatrix() ;
    
    glPopMatrix() ;
}



void init(){
    radius = 15.0 ;
    glClearColor(0,0,0,0) ;
    glMatrixMode(GL_PROJECTION) ;
    glLoadIdentity() ;
    gluPerspective(80,1,1,1000.0) ;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    glClearColor(0,0,0,0) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
    
    glMatrixMode(GL_MODELVIEW) ;
    glLoadIdentity() ;
    gluLookAt(100*cos(cameraAngle), 100*sin(cameraAngle), cameraHeight,        0,0,0,        0,0,1);
    
    glMatrixMode(GL_MODELVIEW) ;
    
    glPushMatrix();
    drawAxes() ;
    drawGrid() ;
    wheel(radius,12,30) ;
    glPopMatrix();
    
    glutSwapBuffers() ;
}
void animate(){
    glutPostRedisplay() ;
}
void keyboardListener(unsigned char key,int x,int y){
    switch (key) {
        case 'w': forwardAngle -= 15 ;
            forwardLength += 2*acos(-1.0)*radius * (15.0/360.0) ;
            break;
        case 's': forwardAngle += 15 ;
            forwardLength -= 2*acos(-1.0)*radius * (15.0/360.0) ;
            break;
        default:
            break;
    }
}
void specialKeyListener(int key,int x,int y){
    switch (key) {
        case GLUT_KEY_DOWN:        //down arrow key
            cameraHeight -= 3.0;
            break;
        case GLUT_KEY_UP:        // up arrow key
            cameraHeight += 3.0;
            break;
            
        case GLUT_KEY_RIGHT:
            cameraAngle += 0.03;
            break;
        case GLUT_KEY_LEFT:
            cameraAngle -= 0.03;
            break;
        default:
            break;
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Offline 1");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMainLoop();
    
    return 0;
}
