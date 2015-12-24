#include <iostream>
#include <ctime>
#include <GL/glut.h>

#include "drawing.h"

using namespace std;

///////////////////////// CONSTANTS ///////////////////////////////////////
const int WIDTH = 640;
const int HEIGHT = 360;
const int b = 20; // block size
const double SQRT3 = sqrt(3.0);
const double r = b/SQRT3; // radius
const int refreshMS =1; // refresh rate in milliseconds

//////////////////////// TRIANGLE CONSTANTS ////////////////////////////////
const double x4=0;
const double y4=1;
const double x5=-SQRT3/2;
const double y5=-.5;
const double x6=SQRT3/2;
const double y6=-.5;

/////////////////////// GLOBAL VARIABLES ////////////////////////////////
bool play=true; // Play/Pause control
int framenumber = 1000;
int maxframes = framenumber + 1800;
bool saving = true;
double p = .5;
double p1 = 1.0/3.0;
double p2 = 2.0/3.0;
double pc = .5;

int gOffsetX = 0;
int gOffsetY = 0;
double offsetX = 0;
double offsetY = 0;

double ax=0;
double ay=1;
double vx = 1;
double vy = 0;

double vp = 0;
double vpc = 0;

const int GWIDTH=1280/b+2;
const int GHEIGHT=832/b+3; // must be an odd number? 832/b-5
int grid[GHEIGHT][GWIDTH];

FrameBuffer * imageFrame;

////////////////////////// UTILS //////////////////////////////////////
double uniform(double min=0, double max=1)
{
	return (rand()/(double)RAND_MAX)*(max-min)+min;
}

double uniformAtSeed(int seed, double min=0, double max=1)
{
	srand(seed);
	double ret = (rand()/(double)RAND_MAX)*(max-min)+min;
	srand(time(NULL));

	return ret;
}

////////////////////////// DATA MANIP /////////////////////////////////////
void regenerateRow(int y)
{
	//cout<< "REGENERATE ROW: " << y<<endl;

	for( int x=0; x < GWIDTH; x++)
	{
		double key = uniform();
		double key2 =  uniform();

		int v=0;
		if(key<pc)
			v = 0;
		else
			v = 1;

		int v2 = 0;
		if(key2<p1)
			v2=0;
		else if(key2<p2)
			v2=1;
		else
			v2=2;

		grid[y][x] = v2+3*v;
	}
}
void regenerateColumn(int x)
{
	//cout<< "REGENERATE COLUMN: " << x<<endl;
	for ( int y = 0; y< GHEIGHT; y++)
	{
		double key = uniform();
		double key2 =  uniform();

		int v=0;
		if(key<pc)
			v = 0;
		else
			v = 1;

		int v2 = 0;
		if(key2<p1)
			v2=0;
		else if(key2<p2)
			v2=1;
		else
			v2=2;

		grid[y][x] = v2+3*v;
	}
}
void randomGrid()
{
	for ( int y = 0; y< GHEIGHT; y++){
		for( int x=0; x < GWIDTH; x++){
			double key = uniform();
			double key2 =  uniform();

			int v=0;
			if(key<pc)
				v = 0;
			else
				v = 1;

			int v2 = 0;
			if(key2<p1)
				v2=0;
			else if(key2<p2)
				v2=1;
			else
				v2=2;

			grid[y][x] = v2+3*v;
		}
	}
}
void init()
{
	randomGrid();
	imageFrame = new FrameBuffer();
	imageFrame->init(WIDTH,HEIGHT);
}
void threeProbs(int i, double amt)
{
	double prob[3];
	double old[3];

	old[0] = p1;
	old[1] = p2-p1;
	old[2] = 1.0-p2;

	// increment probability component
	prob[i]=max(0.0,min(1.0,old[i]+amt));

	int i1 = (i+1)%3;
	int i2 = (i+2)%3;

	// check special cases with zeros
	if(old[i1]<.001 && old[i2]<.001){
		prob[i1] = prob[i2] = (1.0-prob[i])/2.0;
	}
	else if(old[i1]<.001){
		prob[i1] = 0;
		prob[i2] = 1.0 - prob[i];
	}
	else if(old[i2]<.001){
		prob[i2] = 0;
		prob[i1] = 1.0 - prob[i];
	}
	else{
		prob[i2] = (1.0-prob[i])/(1.0+old[i1]/old[i2]);
		prob[i1] = 1.0-prob[i]-prob[i2];
	}

	// set global variables
	p1 = prob[0];
	p2 = prob[0]+prob[1];

}

///////////////////////////// DRAWING SINGLE////////////////////////////////
void hexagondoublelines(double cx, double cy, int k)
{
	if(k==0){
		glVertex2f(cx+x4*r,cy+y4*r);
		glVertex2f(cx+x5*r,cy+y5*r);
		glVertex2f(cx+x4*r,cy-y4*r);
		glVertex2f(cx+x6*r,cy-y6*r);
	}else if(k==1){
		glVertex2f(cx+x5*r,cy-y5*r);
		glVertex2f(cx+x4*r,cy-y4*r);
		glVertex2f(cx+x6*r,cy+y6*r);	
		glVertex2f(cx+x4*r,cy+y4*r);
	}else{
		glVertex2f(cx+x5*r,cy+y5*r);
		glVertex2f(cx+x6*r,cy+y6*r);	
		glVertex2f(cx+x6*r,cy-y6*r);	
		glVertex2f(cx+x5*r,cy-y5*r);	
	}
}
void hexagonalldoublelines(double cx, double cy)
{
	glVertex2f(cx+x4*r,cy+y4*r);
	glVertex2f(cx+x5*r,cy+y5*r);
	glVertex2f(cx+x4*r,cy-y4*r);
	glVertex2f(cx+x6*r,cy-y6*r);	

	glVertex2f(cx+x5*r,cy-y5*r);
	glVertex2f(cx+x4*r,cy-y4*r);
	glVertex2f(cx+x6*r,cy+y6*r);	
	glVertex2f(cx+x4*r,cy+y4*r);

	glVertex2f(cx+x5*r,cy+y5*r);
	glVertex2f(cx+x6*r,cy+y6*r);	
	glVertex2f(cx+x6*r,cy-y6*r);	
	glVertex2f(cx+x5*r,cy-y5*r);
}
void hexagonlines(double cx, double cy, int k)
{
	if(k==0){
		glVertex2f(cx+x4*r,cy+y4*r);
		glVertex2f(cx+x4*r,cy-y4*r);
	}else if(k==1){
		glVertex2f(cx+x5*r,cy-y5*r);
		glVertex2f(cx+x6*r,cy+y6*r);
	}else{
		glVertex2f(cx+x5*r,cy+y5*r);
		glVertex2f(cx+x6*r,cy-y6*r);
	}
}
void hexagonalllines(double cx, double cy)
{
	glVertex2f(cx+x4*r,cy+y4*r);
	glVertex2f(cx+x4*r,cy-y4*r);

	glVertex2f(cx+x5*r,cy-y5*r);
	glVertex2f(cx+x6*r,cy+y6*r);

	glVertex2f(cx+x5*r,cy+y5*r);
	glVertex2f(cx+x6*r,cy-y6*r);	
}
void hexagon(double cx, double cy)
{
	glVertex2f(cx+x4*r,cy+y4*r);
	glVertex2f(cx+x5*r,cy-y5*r);
	glVertex2f(cx+x5*r,cy+y5*r);
	glVertex2f(cx+x4*r,cy-y4*r);
	glVertex2f(cx+x6*r,cy+y6*r);	
	glVertex2f(cx+x6*r,cy-y6*r);	
}


////////////////////////// DRAWING ///////////////////////////////
void debugHexagons()
{
	glColor3f(.1,.3,.3);


	bool offset=false;
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b*2){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagon(i+(offset?b/2:0),j*.5*SQRT3);
			glBegin(GL_POLYGON);
			hexagon(i+(gOffsetY%2==1?b/2:0),j*.5*SQRT3);
			glEnd();
		}
	}
		glColor3f(.2,.8,1);

}
void randomHexagons()
{
	double cr = .1;
	double cg = .3;
	double cb = .3;
	double var = .1;

	bool offset=true;
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagon(i+(offset?b/2:0),j*.5*SQRT3);

			glColor3f(cr*uniformAtSeed((i+j*WIDTH)/30*1.177345,.8,1),cg*uniformAtSeed((i+j*WIDTH)/30*1.177345,.8,1),cb*uniformAtSeed((i+j*WIDTH)/30*1.177345,.8,1));

			cout<< "sseed: " << i+j*WIDTH << '\t' << uniformAtSeed((i+j*WIDTH)/30*1.177345,.8,1)<<endl;
			glBegin(GL_POLYGON);
			hexagon(i+(gOffsetY%2==1?b/2:0)+(offset?b/2:0),j*.5*SQRT3);
			glEnd();
		}
	}
		glColor3f(.2,.8,1);

}

///////////////////////////// MAIN DRAW /////////////////////////////
void hexagonComboPattern()
{
	//glScalef(1.2,1.2,1);
	glTranslatef(-b,-b*.5*SQRT3,0);
	glTranslatef(offsetX,offsetY,0);
	
	//if(play)	randomHexagons();

	glLineWidth(1);

	int k=0;
	int i = 0;
	int j = 0;
	bool offset=true;
	glBegin(GL_LINES);
	for( int y=0;y<GHEIGHT; y+=1){
		offset=!offset;
		for( int x=0; x<GWIDTH; x+=1){

			i=(x+gOffsetX)%GWIDTH*b;
			j=(y+gOffsetY)%GHEIGHT*b;
			k= grid[y][x];
			if(k<=2)
				hexagonlines(i+(offset?b/2:0),j*.5*SQRT3,k);
			else
				hexagondoublelines(i+(offset?b/2:0),j*.5*SQRT3,k-3);
		}
	}
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(.2,.8,1);
	
	glPushMatrix();
	hexagonComboPattern(); 
	glPopMatrix();


	if(saving && play){
		glReadPixels(0,0,WIDTH,HEIGHT,GL_RGB,GL_FLOAT,imageFrame->framebuffer);
		saveImage(imageFrame,"movie/prototype",framenumber++);
	}
	if(framenumber>=maxframes)
		exit(0);

	glutSwapBuffers();
	//cout<<"Drew"<<endl;
}

/////////////////////////////// CONTROLS ///////////////////////////////////
void randomTranslates()
{
	ax+=uniform(-.05,.05);
	ay+=uniform(-.05,.05);

	double amag = sqrt(ax*ax+ay*ay);

	ax/=amag;
	ay/=amag;

	vx+=ax;
	vy+=ay;

	double speed = sqrt(vx*vx+vy*vy)/4.0;

	vx/=speed;
	vy/=speed;

	offsetX+=vx;
	offsetY+=vy;
	
}
void randomProbs()
{
	vp+=uniform(0,.02);
	vpc+=uniform(-.1,.1);

	vp = fmod(3.0+vp,3.0);
	vpc = max(-1.0,min(1.0,vpc));

	threeProbs(floor(vp),(1.0-fmod(vp,1.0))*.01);
	threeProbs(fmod(3.0+ceil(vp),3.0),fmod(vp,1.0)*.01);
	pc+=uniform(-.01,.01);
	//pc+=vpc*.01;
	pc = max(0.0,min(1.0,pc));

		cout<<'\t'<< p1 <<'\t'<< p2-p1 <<'\t'<< 1.0-p2 <<'\t'<<'\t'<< pc <<endl;


};
void moveAround(int tag)
{

	glutTimerFunc(refreshMS,moveAround,0);
	
	if(play){
		
		randomTranslates();
		randomProbs();

		if(offsetX>b)
		{
			offsetX=offsetX-(double)b;
			gOffsetX+=1;
			gOffsetX=gOffsetX%GWIDTH;
			//cout<< gOffsetX <<'\t'<<GWIDTH<<'\t' << offsetX <<endl;
			regenerateColumn((GWIDTH-gOffsetX)%GWIDTH);
		}
		if(offsetX<-b)
		{
			offsetX=offsetX+(double)b;
			gOffsetX-=1;
			gOffsetX=(gOffsetX+GWIDTH)%GWIDTH;
			//cout<< gOffsetX <<'\t'<<GWIDTH<<'\t' << offsetX <<endl;
			regenerateColumn((GWIDTH-gOffsetX)%GWIDTH);
		}
		if(offsetY>b*.5*SQRT3)
		{
			offsetY=offsetY-((double)b)*.5*SQRT3;
			gOffsetY+=1;
			gOffsetY=gOffsetY%GHEIGHT;
			//cout<< gOffsetY <<'\t'<<GHEIGHT<<'\t' << offsetY <<endl;
			regenerateRow((GHEIGHT-gOffsetY)%GHEIGHT);
		}
		if(offsetY<-b*.5*SQRT3)
		{
			offsetY=offsetY+((double)b)*.5*SQRT3;
			gOffsetY-=1;
			gOffsetY=(gOffsetY+GHEIGHT)%GHEIGHT;
			//cout<< gOffsetY <<'\t'<<GHEIGHT<<'\t' << offsetY <<endl;
			regenerateRow((GHEIGHT-gOffsetY)%GHEIGHT);
		}
	}

	glutPostRedisplay(); 
}
void adjustTranslation(int key, int x, int y)
{
	double incr = .1;

	switch(key){
	case GLUT_KEY_UP: ay+=incr; break;
	case GLUT_KEY_DOWN: ay-=incr; break;
	case GLUT_KEY_LEFT: ax-=incr; break;
	case GLUT_KEY_RIGHT: ax+=incr; break;
	};

	double amag = sqrt(ax*ax+ay*ay);

	ax/=amag;
	ay/=amag;
}
void adjustProbabilities(unsigned char key, int x, int y)
{
	const double incr = .1;
	if(key=='q'){
		threeProbs(0,incr);
	}
	if(key=='a'){
		threeProbs(0,-incr);
	} 
	if(key=='w'){
		threeProbs(1,incr);
	}
	if(key=='s'){
		threeProbs(1,-incr);
	}
	if(key=='e'){
		threeProbs(2,incr);
	}
	if(key=='d'){
		threeProbs(2,-incr);
	}
	if(key=='r'){
		pc+=incr;
		pc=min(1.0,pc);
	}
	if(key=='f'){
		pc-=incr;
		pc=max(0.0,pc);
	}

	if(key=='p' || key=='P')
		play=!play;

	/*int k = (int)key - 49;
	if( k >=0 && k <=9){
		MYMODE = (mymodes) k;
		cout << "change mode: " << k <<endl;
	}
	cout<< "k " << k << endl;*/
	cout<<'\t'<< p1 <<'\t'<< p2-p1 <<'\t'<< 1.0-p2 <<'\t'<<'\t'<< pc <<endl;
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	srand(time(NULL));
	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Ten Print Motion");

	//make it smooth
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	
	//init();
	//initCreatures();
	glutDisplayFunc(display);


	glutKeyboardFunc(adjustProbabilities);
	glutSpecialFunc(adjustTranslation);
	//glutMotionFunc(dragFunction);
	//glutMouseFunc(mouseFunction);
	glutTimerFunc(refreshMS,moveAround,0);
	
	gluOrtho2D(0, WIDTH, 0, HEIGHT);

	//specify window clear (background) color to be white
	glClearColor(0, .2, .2, 0);

	init();

	glutMainLoop(); //start main loop
	return 0;
}