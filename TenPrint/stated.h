//int states[HEIGHT*2/SQRT3];
const int GRIDWIDTH=1478;
const int GRIDHEIGHT=832;
int grid[GRIDHEIGHT][GRIDWIDTH];
/*
void linestate(double i, double j, int s)
{
	if(s==0){
		glVertex2f(i,j);
		glVertex2f(i+b,j+b);
	}
	else{
		glVertex2f(i+b,j);
		glVertex2f(i,j+b);
	}
}
void drawTenPrintState()
{
	int k=0;
	for ( int y = 0; y< GRIDHEIGHT; y++){
		for( int x=0; x < GRIDWIDTH; x++){
			k= grid[y][x];
			linestate(x*b,y*b,k);
		
		}
	}
}
void randomStates()
{
	for ( int y = 0; y< GRIDHEIGHT; y++){
		for( int x=0; x < GRIDWIDTH; x++){
			double key = uniform();
			if(key<p)
				grid[y][x] = 0;
			else
				grid[y][x] = 1;

		}
	}
}*/


