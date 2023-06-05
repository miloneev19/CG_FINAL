#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

void init(void)
{
   glClearColor(0.0,0.0,0.0,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   gluOrtho2D(-500,500,-500,500);
   glFlush();
}



int main(int argc , char **argv)
{
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
      glutInitWindowSize(1000,1000);
      glutInitWindowPosition(0,0);
      glutCreateWindow("DDA");
      init();
      glutMainLoop();
      return 0;
}
