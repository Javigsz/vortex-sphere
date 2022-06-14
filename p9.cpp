#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdbool.h>
#include <cmath>
#include <iostream>

#define PI 3.141622
#define SCREEN_H 800
#define SCREEN_W 800

//Parametros de la efera
int nPart=16;
int limitmin=8;
int limitmax=256;

//Parametros de rotacion
float g=30.0;
int grados=0;

void display(void)
{

    glClearColor(0, 0, 0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(0,255,0);

    //Rotacion
    glRotatef(grados,1,1,1);

    //Vectores circuferencia vertical
    std::vector<float> vx;
    std::vector<float> vy;

    //Vectores de vectores circunferencias horizontales
    std::vector<std::vector<float> > vecx;
    std::vector<std::vector<float> > vecy;
    std::vector<std::vector<float> > vecz;

    int numcir = (nPart/2)+1;

    for(int i=0;i<=numcir;i++){
        vecx.push_back(std::vector<float>());
        vecy.push_back(std::vector<float>());
        vecz.push_back(std::vector<float>());
    }

    //Construyo circunferencia vertical
    glBegin(GL_LINE_STRIP);
        for(int i=0;i<nPart;i++){
            vx.push_back(sin(2*PI*i/nPart));
            vy.push_back(cos(2*PI*i/nPart));
            glVertex3f(sin(2*PI*i/nPart),cos(2*PI*i/nPart),0);
        }
    glEnd();

    //Construyo cirucnferencias horizontales
    for(int k=0;k<numcir;k++){

        float dist = vx[k];
        float alt = vy[k];

        glBegin(GL_LINE_STRIP);
        for(float j=0;j<=nPart;j++){
            glVertex3f(cos(2*PI*j/nPart)*dist,alt,sin(2*PI*j/nPart)*dist);
            vecx[k].push_back(cos(2*PI*j/nPart)*dist);
            vecy[k].push_back(alt);
            vecz[k].push_back(sin(2*PI*j/nPart)*dist);

        }
        glEnd();

    }

    //Construyo las mallas de triangulos
    for(int k=1;k<numcir;k++){

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLE_STRIP);

        for(int i=0;i<=nPart;i++){

            glVertex3f(vecx[k-1][i],vecy[k-1][i],vecz[k-1][i]);
            glVertex3f(vecx[k][i],vecy[k][i],vecz[k][i]);

       }

        glEnd();

    }

    glutSwapBuffers();

}

void moveWithKeys(int key, int x, int y){

    switch(key){

        case GLUT_KEY_F1:

            if(nPart < limitmax){
                nPart=nPart*2;
            }
        break;

        case GLUT_KEY_F2:

            if(nPart > limitmin){
                nPart=nPart/2;
            }
        break;

    }

    glutPostRedisplay();

}

void mouseClick(int button, int state, int x, int y){

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        grados=grados-g;
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        grados=grados+g;
    }

    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN ){
        nPart=16;
        grados=0;
    }

    glutPostRedisplay();

}

static void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-2, 2, -2, 2, 3.0, -3.0);
    glFlush();

}


int main(int argc, char **argv)
{

    srand (time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_W,SCREEN_H);
    glutCreateWindow("Practica 9.");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(moveWithKeys);
    glutMouseFunc(mouseClick);

    glutMainLoop();

}
