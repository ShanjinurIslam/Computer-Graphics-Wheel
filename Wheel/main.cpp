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
} pos ;

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

void drawCircle(double radius,int segments,int z)
{
    int i;
    double pi = acos(-1.0) ;
    Point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x= pos.x + radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y= pos.y + radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x,points[i].y,pos.z+z);
            glVertex3f(points[i+1].x,points[i+1].y,pos.z+z);
        }
        glEnd();
    }
}

void wheel(double height){

    glPushMatrix() ;
    glRotatef(90, 0,1,0) ;
    for(double i=0;i<=height ;i+= 0.005){
        glColor3f(1, 0, 0) ;
        drawCircle(20,50,i) ;
    }
    glPopMatrix() ;
}



void init(){
    pos = Point(-20,0,0) ;
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
    wheel(10) ;
    glPopMatrix();
    
    glutSwapBuffers() ;
}
void animate(){
    glutPostRedisplay() ;
}
void keyboardListener(unsigned char key,int x,int y){
    switch (key) {
        case 'w':pos.y += 5 ;
            break ;
        case 's':pos.y -= 5 ;
            break ;
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
