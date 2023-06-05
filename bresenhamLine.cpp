#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>
using namespace std;

class Point
{
     public: 
     int x, y;
    
      Point()
        {
          x=0;
          y=0;
        }
    
       Point(int x, int y)
        {
           this->x=x;
           this->y = y;
        }
};

   Point points[20];
   int count =0;

int abs(int x)
{
    if(x<0)
         return -x;
    else 
         return x;
}

void drawPoints(int x, int y, bool plot)
{
     glBegin(GL_POINTS);
      if(plot)
              { 
                 glVertex2i(x,y);
                }
     glEnd();
     glFlush();
} 

void gentleSlope ( Point a, Point b, int type)
{
    int dx,dy;
    int Dx,Dy;
    int p; //decision parameter 
    bool draw=true;
int counter =1;
     
    dx = abs(b.x-a.x);
    dy = abs(b.y-a.y);
 
    if ( b.x>a.x)
    {
         Dx = 1;
     }
     else 
       { 
            Dx=-1;
        }

    
    if ( b.y>a.y)
    {
         Dy = 1;
     }
     else 
       { 
            Dy=-1;
        }

     p=(2*dy) -dx;

     for(int i=0; i<dx; i++)
     { 
         if(p<0)
              {
                  p = p + 2*dy;
                  a.x = a.x + Dx;
               }
        else 
                {
                     p  = p + 2*(dy-dx);
                     a.x = a.x + Dx;
                     a.y = a.y + Dy;
                 }
          
          if(type == 0)   //simple line
              {
                    drawPoints(a.x,a.y,true);
               }
          else if(type == 1)   //dotted line
               { 
                     if(counter % 7 ==0)
                     { 
                           drawPoints(a.x,a.y,true);
                      }
                }

             else if(type==2)  //dashed line
                {
                      if(counter % 20 ==0 ) 
                      {
                            if(draw==true)
                                    { draw= false;  }
                             else 
                                  { draw=true; }
                      }
                   drawPoints(a.x,a.y,draw);
                }
            counter++;
      }
 
}

void harshSlope ( Point a, Point b, int type)
{
    int dx,dy;
    int Dx,Dy;
    int p; //decision parameter 
    bool draw=true;
     int counter =1;
    dx = abs(b.x-a.x);
    dy = abs(b.y-a.y);
 
    if ( b.x>a.x)
    {
         Dx = 1;
     }
     else 
       { 
            Dx=-1;
        }

    
    if ( b.y>a.y)
    {
         Dy = 1;
     }
     else 
       { 
            Dy=-1;
        }

     p=(2*dx) -dy;

     for(int i=0; i<dy; i++)
     { 
         if(p<0)
              {
                  p = p +2*dx;
                  a.y = a.y+ Dy;
               }
        else 
                {
                     p = p+ 2*(dx-dy);
                     a.x = a.x + Dx;
                     a.y = a.y + Dy;
                 }
          
          if(type == 0)   //simple line
              {
                    drawPoints(a.x,a.y,true);
               }
          else if(type == 1)   //dotted line
               { 
                     if(counter % 7 ==0)
                     { 
                           drawPoints(a.x,a.y,true);
                      }
                }

             else if(type==2)  //dashed line
                {
                      if(counter % 20 ==0 ) 
                      {
                            if(draw==true)
                                    { draw= false;  }
                             else 
                                  { draw=true; }
                      }
                   drawPoints(a.x,a.y,draw);
                }
            counter++;
      }
 
}
     
void bresenham ( Point a, Point b , int type)
{
      int dx = abs (b.x-a.x) ;
       int dy = abs(b.y -a.y);
          if(dx>dy)
              {
                  gentleSlope(a,b,type);
                }
         else 
                 {
                     harshSlope(a,b,type);
                 }
}

void axes()
{
   Point a(-500,0), b(500,0), c(0,-500);
   Point d(0,500);
   bresenham( a,b,0);
   bresenham(c,d,0);
}

void init()
{
     glClearColor(0.0,0.0,0.0,0.0);
     glClear(GL_COLOR_BUFFER_BIT);
     gluOrtho2D(-500,500,-500,500);
       axes();
        glFlush();
 }

void mouse( int button, int state, int x, int y)
{
   y=500-y;
   x=x-500;
     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
     {
          Point p(x,y);
          points[count++] = p;
        }
}

 void keyboard(unsigned char key, int x, int y)
{
    if(key == 'd')  //dashed 
       {
           bresenham(points[0],points[1],2);
           count =0;
        }

      else  if(key == 'z')    //dotted
       {
          bresenham(points[0],points[1],1);
           count =0;
        }

        else if(key == 's')    //simple line 
       {
           bresenham(points[0],points[1],0);
           count =0;
        }
       else if(key == 'l')    //solid line 
       {
           glPointSize(3);
           bresenham(points[0],points[1],0);
           count =0;
        }

}
  int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham");
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
        return 0;
}
