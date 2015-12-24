#include<iostream>
#include <ctime>
#include <GL/glut.h>
using namespace std;

enum mymodes {TENPRINT,TRIANGLEWEIRD,TRIANGLEPRINT,HEXPRINT,HEXPRINTFACE,HEXDOUBLE,HEXCOMBO};
mymodes MYMODE = HEXCOMBO;


const int WIDTH = 1280;
const int HEIGHT = 720;
const int b = 30; // block size
int lw = 2; // line width
const double SQRT3 = sqrt(3.0);
const double r = b/SQRT3; // radius

double p = .5;
double p1 = 1.0/3.0;
double p2 = 2.0/3.0;
double pc = .5;

double uniform(double min=0, double max=1)
{
	return (rand()/(double)RAND_MAX)*(max-min)+min;
}



#include "hexprint.h"
#include "stated.h"



void trianglelines(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+(x2+x3)*.5*r,cy+(y2+y3)*.5*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+(x1+x3)*.5*r,cy+(y1+y3)*.5*r);
	glVertex2f(cx+x3*r,cy+y3*r);
	glVertex2f(cx+(x2+x1)*.5*r,cy+(y2+y1)*.5*r);

}
void trianglelinesuprand(double cx, double cy)

{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	double key = uniform();
	
	if(key<p1){
		glVertex2f(cx+x1*r,cy+y1*r);
		glVertex2f(cx+(x2+x3)*.5*r,cy+(y2+y3)*.5*r);
	}else if(key<p2){
		glVertex2f(cx+x2*r,cy+y2*r);
		glVertex2f(cx+(x1+x3)*.5*r,cy+(y1+y3)*.5*r);
	}else{
		glVertex2f(cx+x3*r,cy+y3*r);
		glVertex2f(cx+(x2+x1)*.5*r,cy+(y2+y1)*.5*r);
	}
}
void trianglelinesdownrand(double cx, double cy)

{
	const double x1=0;
	const double y1=-1;
	const double x3=-SQRT3/2;
	const double y3=.5;
	const double x2=SQRT3/2;
	const double y2=.5;

	double key = uniform();
	
	if(key<p1){
		glVertex2f(cx+x1*r,cy+y1*r);
		glVertex2f(cx+(x2+x3)*.5*r,cy+(y2+y3)*.5*r);
	}else if(key<p2){
		glVertex2f(cx+x2*r,cy+y2*r);
		glVertex2f(cx+(x1+x3)*.5*r,cy+(y1+y3)*.5*r);
	}else{
		glVertex2f(cx+x3*r,cy+y3*r);
		glVertex2f(cx+(x2+x1)*.5*r,cy+(y2+y1)*.5*r);
	}
}
void triangleup(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
}
void trianglePattern()
{
	bool offset=false;
	glBegin(GL_TRIANGLES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//triangleup(i+(offset?b/2:0),j*.5*SQRT3);			
		}
	}
	glEnd();

	glColor3f(.2,.8,1);
	glLineWidth(1);

	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			trianglelinesuprand(i+(offset?b/2:0),j*.5*SQRT3);
			trianglelinesdownrand(i+(offset?0:b/2),(j+b/3)*.5*SQRT3);			

		}
	}
	glEnd();
}
void triangleWeirdPattern()
{
	glColor3f(.1,.3,.3);
	bool offset=false;
	glBegin(GL_TRIANGLES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			triangleup(i+(offset?b/2:0),j*.5*SQRT3);			
		}
	}
	glEnd();

	glColor3f(.2,.8,1);
	glLineWidth(1);
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			trianglelines(i+(offset?b/2:0),j*.5*SQRT3);			
		}
	}
	glEnd();
}
void displaytenprint()
{
	glLineWidth(lw*2+1);
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT; j+=b){
		for( int i=0; i<WIDTH; i+=b){
			if(uniform()<p){
				glVertex2f(i,j);
				glVertex2f(i+b,j+b);
			}
			else{
				glVertex2f(i+b,j);
				glVertex2f(i,j+b);
			}

			/*if(uniform()<.5){
				glVertex2f(i-lw,j-lw);
				glVertex2f(i+b+lw,j+b+lw);
			}
			else{
				glVertex2f(i+b+lw,j-lw);
				glVertex2f(i-lw,j+b+lw);
			}*/
		}
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(.2,.8,1);

	switch(MYMODE){
		case TENPRINT: displaytenprint(); break;
		case TRIANGLEWEIRD: triangleWeirdPattern(); break;
		case TRIANGLEPRINT: trianglePattern(); break;
		case HEXPRINT: hexagonPattern(); break;
		case HEXPRINTFACE: hexagonPattern2(); break;
		case HEXDOUBLE: hexagonDoublePattern(); break;
		case HEXCOMBO: hexagonComboPattern(); break;
	};

	glutSwapBuffers();
	cout<<"Drew"<<endl;
}
void adjustProbabilities(unsigned char key, int x, int y)
{
	const double incr = .1;
	if(key=='q'){
		p+=incr;
		p=min(1.0,p);

		double pprev = p1;

		p1+=incr;
		p1=min(1.0,p1);

		double change = (p1-pprev)/2.0;
		p2+=change;
		p2=max(0.0,min(1.0,p2));

	}
	if(key=='a'){
		p-=incr;
		p=max(0.0,p);

		double pprev = p1;

		p1-=incr;
		p1=max(0.0,p1);

		double change = (p1-pprev)/2.0;
		p2+=change;
		p2=max(p1,min(1.0,p2));

	} 
	if(key=='w'){
		double pprev = p2;

		p2+=incr;
		p2=min(1.0,p2);

		double change = (p2-pprev)/2.0;
		p1+=change;
		p1=max(0.0,min(1.0,p1));

	}
	if(key=='s'){
		double pprev = p2;

		p2-=incr;
		p2=max(0.0,p2);

		double change = (p2-pprev)/2.0;
		p1+=change;
		p1=max(0.0,min(1.0,p1));
	}
	if(key=='e'){
		double pprev = p2;

		p2+=incr;
		p2=min(1.0,p2);

		double change = (p2-pprev)/2.0;
		p1-=change;
	}
	if(key=='r'){
		pc+=incr;
		pc=min(1.0,pc);
	}
	if(key=='f'){
		pc-=incr;
		pc=max(0.0,pc);
	}

	int k = (int)key - 49;
	if( k >=0 && k <=9){
		MYMODE = (mymodes) k;
		cout << "change mode: " << k <<endl;
	}
	cout<< "k " << k << endl;
	cout<< p <<'\t'<< p1 <<'\t'<< p2 <<endl;
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	srand(time(NULL));
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Ten Print");

	//make it smooth
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	
	//init();
	//initCreatures();
	 glutDisplayFunc(display);


	glutKeyboardFunc(adjustProbabilities);
	//glutMotionFunc(dragFunction);
	//glutMouseFunc(mouseFunction);
	//glutTimerFunc(10,creatureMove,0);
	
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	//specify window clear (background) color to be white
	glClearColor(0, .2, .2, 0);

	glutMainLoop(); //start main loop
	return 0;
}