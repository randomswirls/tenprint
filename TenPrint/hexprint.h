void hexagonfacelines(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	double key = uniform();
	
	if(key<p1){
		glVertex2f(cx+(x1+x2)*.5*r,cy+(y1-y2)*.5*r);
		glVertex2f(cx+(x1+x3)*.5*r,cy+(-y1+y3)*.5*r);
	}else if(key<p2){
		glVertex2f(cx+x2*r,cy);
		glVertex2f(cx+x3*r,cy);
	}else{
		glVertex2f(cx+(x2+x1)*.5*r,cy+(y2-y1)*.5*r);
		glVertex2f(cx+(x3+x1)*.5*r,cy+(-y3+y1)*.5*r);
	}
}
void hexagonfacealllines(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+(x1+x2)*.5*r,cy+(y1-y2)*.5*r);
	glVertex2f(cx+(x1+x3)*.5*r,cy+(-y1+y3)*.5*r);

	glVertex2f(cx+x2*r,cy);
	glVertex2f(cx+x3*r,cy);

	glVertex2f(cx+(x2+x1)*.5*r,cy+(y2-y1)*.5*r);
	glVertex2f(cx+(x3+x1)*.5*r,cy+(-y3+y1)*.5*r);

	
	/*glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x2*r,cy-y2*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x1*r,cy-y1*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
	glVertex2f(cx+x3*r,cy-y3*r);	*/
}
void hexagondoublelines(double cx, double cy)
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
		glVertex2f(cx+x2*r,cy+y2*r);
		glVertex2f(cx+x1*r,cy-y1*r);
		glVertex2f(cx+x3*r,cy-y3*r);
	}else if(key<p2){
		glVertex2f(cx+x2*r,cy-y2*r);
		glVertex2f(cx+x1*r,cy-y1*r);
		glVertex2f(cx+x3*r,cy+y3*r);	
		glVertex2f(cx+x1*r,cy+y1*r);
	}else{
		glVertex2f(cx+x2*r,cy+y2*r);
		glVertex2f(cx+x3*r,cy+y3*r);	
		glVertex2f(cx+x3*r,cy-y3*r);	
		glVertex2f(cx+x2*r,cy-y2*r);	
	}
}
void hexagonalldoublelines(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x1*r,cy-y1*r);
	glVertex2f(cx+x3*r,cy-y3*r);	

	glVertex2f(cx+x2*r,cy-y2*r);
	glVertex2f(cx+x1*r,cy-y1*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
	glVertex2f(cx+x1*r,cy+y1*r);

	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
	glVertex2f(cx+x3*r,cy-y3*r);	
	glVertex2f(cx+x2*r,cy-y2*r);


	/*glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x2*r,cy-y2*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x1*r,cy-y1*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
	glVertex2f(cx+x3*r,cy-y3*r);	*/
}
void hexagonlines(double cx, double cy)
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
		glVertex2f(cx+x1*r,cy-y1*r);
		//cout<< '\t'<< cx+x1*r<< '\t'<<cy+y1*r << '\t'<<cx+x1*r<<'\t'<<cy-y1*r<<endl;

	}else if(key<p2){
		glVertex2f(cx+x2*r,cy-y2*r);
		glVertex2f(cx+x3*r,cy+y3*r);
	}else{
		glVertex2f(cx+x2*r,cy+y2*r);
		glVertex2f(cx+x3*r,cy-y3*r);
	}
}
void hexagonalllines(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x1*r,cy-y1*r);

	glVertex2f(cx+x2*r,cy-y2*r);
	glVertex2f(cx+x3*r,cy+y3*r);

	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x3*r,cy-y3*r);	
}
void hexagon(double cx, double cy)
{
	const double x1=0;
	const double y1=1;
	const double x2=-SQRT3/2;
	const double y2=-.5;
	const double x3=SQRT3/2;
	const double y3=-.5;

	glVertex2f(cx+x1*r,cy+y1*r);
	glVertex2f(cx+x2*r,cy-y2*r);
	glVertex2f(cx+x2*r,cy+y2*r);
	glVertex2f(cx+x1*r,cy-y1*r);
	glVertex2f(cx+x3*r,cy+y3*r);	
	glVertex2f(cx+x3*r,cy-y3*r);	
}
void debugHexagons()
{
	glColor3f(.1,.3,.3);


	bool offset=false;
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b*2){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagon(i+(offset?b/2:0),j*.5*SQRT3);
			glBegin(GL_POLYGON);
			hexagon(i,j*.5*SQRT3);
			glEnd();
		}
	}
}
void hexagonComboPattern()
{
	glLineWidth(1);

	bool offset=true;
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			if(uniform()<pc)
				hexagonlines(i+(offset?b/2:0),j*.5*SQRT3);
			else
				hexagondoublelines(i+(offset?b/2:0),j*.5*SQRT3);
		}
	}
	glEnd();
}
void hexagonDoublePattern()
{

	glLineWidth(.1);

	bool offset=true;
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagonalldoublelines(i+(offset?b/2:0),j*.5*SQRT3);
			hexagondoublelines(i+(offset?b/2:0),j*.5*SQRT3);
		}
	}
	glEnd();
}
void hexagonPattern2()
{
	glLineWidth(1);

	bool offset=true;
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagonfacealllines(i+(offset?b/2:0),j*.5*SQRT3);
			hexagonfacelines(i+(offset?b/2:0),j*.5*SQRT3);
		}
	}
	glEnd();
}

void hexagonPattern()
{
	glColor3f(.2,.8,1);
	glLineWidth(1);

	bool offset=true;
	glBegin(GL_LINES);
	for( int j=0;j<HEIGHT*2/SQRT3; j+=b){
		offset=!offset;
		for( int i=0; i<WIDTH; i+=b){
			//hexagonalllines(i+(offset?b/2:0),j*.5*SQRT3);
			hexagonlines(i+(offset?b/2:0),j*.5*SQRT3);		

		}
	}
	glEnd();
}

