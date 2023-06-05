#include<GL/glut.h>
#include<GL/gl.h>
#include<cmath> 
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
         this->x = x;
         this->y = y;
    }
}; 

Point points[20];
int count=0;

int abs(int x){
	return (x < 0)? -x : x;
}

void drawPoints(Point a){
	glBegin(GL_POINTS);
		glVertex2i(a.x, a.y);
	glEnd();
	glFlush();	
}

void gentleLine(Point a, Point b){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	int Dx = (b.x > a.x)? 1 : -1;
	int Dy = (b.y > b.x)? 1 : -1;
	
	int pk = (2 * dy) - dx;
	
	for(int i = 0; i < dx; i++){
		if(pk < 0){
			pk += 2 * dy;
			a.x += Dx;
		}
		
		else{
			pk += 2 * (dy - dx);
			a.x += Dx;
			a.y += Dy;
		}
		
		drawPoints(a);
		
	}
}

void harshLine(Point a, Point b){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	int Dx = (b.x > a.x)? 1 : -1;
	int Dy = (b.y > b.x)? 1 : -1;
	
	int pk = (2 * dx) - dy;
	
	for(int i = 0; i < dy; i++){
		if(pk < 0){
			pk += 2 * dx;
			a.y += Dy;
		}
		
		else{
			pk += 2 * (dx - dy);
			a.x += Dx;
			a.y += Dy;
		}
		
		drawPoints(a);
		
	}
}


void bresenham(Point a, Point b){
	int dx = abs(b.x - a.x);
	int dy = abs(b.y - a.y);
	
	(dx > dy) ? gentleLine(a,b) : harshLine(a,b);
}

void axes(){
	bresenham(Point(500,0),Point(-500,0));
	bresenham(Point(0,500),Point(0,-500));
}


void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500,500,-500,500);
	glFlush();
}

void plotCompletely( Point centre, Point a)
{
   drawPoints(Point(a.x + centre.x, a.y + centre.y));
   drawPoints(Point(a.y + centre.x, a.x + centre.y));
   drawPoints(Point(-a.x + centre.x, a.y + centre.y));
   drawPoints(Point(-a.y + centre.x, a.x + centre.y));
   drawPoints(Point(a.x + centre.x, -a.y + centre.y));
   drawPoints(Point(a.y + centre.x, -a.x + centre.y));
   drawPoints(Point(-a.x + centre.x, -a.y + centre.y));
   drawPoints(Point(-a.y + centre.x, -a.x + centre.y));

   }

void circle(Point centre, double radius)
{
   glColor3f(0,0,1);
   double p = 3 - 2*radius;
    double x=0, y = radius;

       while(x<=y)
         {
                  if(p<0)
                   {
                      x++;
                      p += (4*x) + 6;
                    }

                    else 
                    {
                         x++;
                         y--;
                         p += (4*(x-y)) + 10;
                    }
             plotCompletely(centre,Point(x,y));
         }
}

void mouse(int button, int state, int x, int y){
	x = x - 500;
	y = 500 - y;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		points[count++] = Point(x,y);
	}
	
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		int dist = pow((points[1].x - points[0].x),2) + pow((points[1].y - points[0].y),2);
		double r = pow(dist, 0.5);
		
		circle(points[0],r);
		count = 0;
	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bresenham Circle ");
	init();
	axes();
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
