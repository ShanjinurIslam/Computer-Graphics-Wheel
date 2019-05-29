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

double cameraHeight = 150.0;
double cameraAngle  = 1.0;

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
    void print(){
        printf("(%lf,%lf,%lf)\n\n",x,y,z) ;
    }
} pos,r,u,l ;

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

void init(){
    pos = Point(100,100,100) ;
    u = Point(0,0,1) ; //z axis is up vector
    l = Point(-1/(sqrt(2)),-1/sqrt(2),0) ;
    r = Point(-1/(sqrt(2)),1/sqrt(2),0) ;
    
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
    gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,        0,0,0,        0,0,1);
    
    glMatrixMode(GL_MODELVIEW) ;
    
    glPushMatrix();
    drawAxes() ;
    drawGrid() ;
    glPopMatrix();
    
    glutSwapBuffers() ;
}
void animate(){
    glutPostRedisplay() ;
}
void keyboardListener(unsigned char key,int x,int y){
    switch (key) {
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
