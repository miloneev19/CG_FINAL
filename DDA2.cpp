
#include<GL/glut.h>
#include<GL/gl.h>
#include<iostream>

using namespace std;

class Point{
	int x;
	int y;

	public:
	Point(){
		x = 0;
		y = 0;
	}
	
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
	
	int getX(){
		return x;
	}
	
	int getY(){
		return y;
	}
	
	void setX(int x){
		this->x = x;
	}
	
	void setY(int y){
		this->y = y;
	}
};

Point points[20];
int count = 0;

int abs(int x){
	return (x < 0)? -x : x;
}

void DDA(Point, Point, int);

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-500,500,-500,500);
	glFlush();
}

void axes(){
	Point a(-500,0), b(500,0), c(0,-500), d(0,500);
	DDA(a,b,0);
	DDA(c,d,0);
}

void drawPoint(int x, int y, bool plot) {
	glBegin(GL_POINTS);
	if(plot)
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void DDA(Point a, Point b, int type){
	int dx, dy, step;
	float Dx, Dy, x = a.getX(), y = a.getY();
	int counter = 1;
	bool draw = true;
	
	dx = b.getX() - a.getX();
	dy = b.getY() - a.getY();
	
	step = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
	
	Dx = ((float)dx)/step;
	Dy = ((float)dy)/step;
	
	drawPoint(x,y, true);
	for(int i = 0; i <= step; i++){
		x += Dx;
		y += Dy;
		a.setX(x);
		a.setY(y);
		
		//dotted
		if(type == 1){
			drawPoint(a.getX(), a.getY(), counter % 7 == 0);
			counter++;
		}
		//dashed
		else if(type == 2){
			if(counter % 20 == 0){
				if(draw == false){
					draw = true;
				}
				else
					draw = false;
			}
			drawPoint(a.getX(), a.getY(), draw);
			counter++;	
		}
		//simple line
		else
			drawPoint(a.getX(), a.getY(), true);
	}
	
	glFlush();
}

void mouse(int button, int state, int x, int y){
	y = 500 - y;
	
	x = x - 500;
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	
		Point point(x,y);
		
		points[count++] = point;
	}
}

void keyboard(unsigned char key, int x, int y){
	if(key == '0'){
		
		DDA(points[0], points[1],0);
		count = 0;
	}
	
	if (key == '1'){
		DDA(points[0], points[1],1);
		count = 0;
		}
	
	if(key == '2'){
		DDA(points[0], points[1],2);
		count = 0;
	}
        if(key=='3')
          {
                 glPointSize(2);
                DDA(points[0],points[1],0);
                count=0;
            }
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("DDA");
	init();
	axes();
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
