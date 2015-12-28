#include <glm/glm.hpp>
using glm::vec2;

const vec2 tp[6] = {
	vec2(0,1),
	vec2(-SQRT3/2.0,.5),
	vec2(-SQRT3/2.0,-.5),
	vec2(0,-1),
	vec2(SQRT3/2.0,-.5),
	vec2(SQRT3/2.0,.5)
}; // hexagon points
vec2 pointToIndex(vec2 p)
{
	return p;
}

vec2 indexToPoint(int x, int y)
{
	bool offset = (int)(y)%2;
	return vec2(
		((x+gOffsetX-1)%GWIDTH*b)+(offset?b/2:0)+offsetX,
		((y+gOffsetY-1)%GHEIGHT*b)*.5*SQRT3+offsetY
		);
	
}
class hexprintrasterizer{

	// v should be normalized, returns dist squared
	double linedist(vec2 p, vec2 p0, vec2 v, float len){
		vec2 r = p-p0;
		//v=glm::normalize(v);
		float t1 = r.x*v.x+r.y*v.y; //glm::dot(r,v);
		//float t1 = glm::dot(r,v);
		t1 = min(len,max(0.0f,t1));

		vec2 d = p0+v*t1 - p; // vector to closest point 
		//vec2 d = c-p;
		return d.x*d.x+d.y*d.y;
		
	}
	double thex(int x,int y, vec2 & p,double & t1, double & t2)
	{
		x=(x+GWIDTH)%GWIDTH;
		y=(y+GHEIGHT)%GHEIGHT;
		int k= grid[y][x];
		double t;
		if(k<=2){
			t= linedist(p,indexToPoint(x,y)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
			if(t<t1) t1=t; else if(t<t2) t2=t;
		}
		else{
			k=k-3;
			t= linedist(p,indexToPoint(x,y)+tp[k]*(float)r,(tp[k+2]-tp[k])/(float)SQRT3,SQRT3*r);
			if(t<t1) t1=t; else if(t<t2) t2=t;
			t= linedist(p,indexToPoint(x,y)+tp[(k+5)%6]*(float)r,(tp[(k+3)%6]-tp[(k+5)%6])/(float)SQRT3,SQRT3*r);
			if(t<t1) t1=t; else if(t<t2) t2=t;
		}

		return t;
	}
public:
	hexprintrasterizer(){};
	void rasterize()
	{
		//int hi,hj;
		//int k=0;

		
		for(int j = 0; j<HEIGHT; j++){
			for(int i = 0; i<WIDTH; i++){
			
				int y = ((int)floor((j + (1.0+.5)*b*.5*SQRT3-offsetY)/b*2.0/SQRT3 - gOffsetY)+GHEIGHT)%GHEIGHT;
				bool offset = y%2;
				int x = (i + (1.0+.5)*b-(offset?b/2:0)-offsetX)/b-gOffsetX;
				//int x= GWIDTH/2;
				//int y = GHEIGHT/2;
				//int y = (j + (1.0+.5)*b*.5*SQRT3)/b*2.0/SQRT3;
				///bool offset = y%2;
				//int x = (i + (1.0+.5)*b-(offset?b/2:0))/b;

				
				double t1=1000;
				double t2=1000;
				double t;

				//k= grid[y][x];
				//double g=0;

				//if(k<=2){

					//hi=((x+gOffsetX-1)%GWIDTH*b)+(offset?b/2:0)+offsetX;
					//hj=((y+gOffsetY-1)%GHEIGHT*b)*.5*SQRT3+offsetY;
					
					//center
					//t = linedist(vec2(i,j),indexToPoint(x,y)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x,y,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;

					//sides
					//k= grid[y][x-1];
					//t = linedist(vec2(i,j),indexToPoint(x-1,y)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x-1,y,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;
					
					//if(x<GWIDTH-1){
						//k= grid[y][x+1];
						//t = linedist(vec2(i,j),indexToPoint(x+1,y)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
						
					t=thex(x+1,y,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;
					//}

					//above
					//k = grid[(y+1)%GHEIGHT][(x-1+(offset?1:0)+GWIDTH)%GWIDTH];
					//t = linedist(vec2(i,j),indexToPoint(x-1+(offset?1:0),y+1)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x-1+(offset?1:0),y+1,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;
					//k=  max(0,min(5,grid[y+1][x+(offset?1:0)]));
					//t = linedist(vec2(i,j),indexToPoint(x+(offset?1:0),y+1)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x+(offset?1:0),y+1,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;

					//below
					//k=  grid[(y-1+GHEIGHT)%GHEIGHT][(x-1+(offset?1:0)+GWIDTH)%GWIDTH];
					//t = linedist(vec2(i,j),indexToPoint(x-1+(offset?1:0),y-1)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x-1+(offset?1:0),y-1,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;
					//k=  grid[(y-1+GHEIGHT)%GHEIGHT][(x+(offset?1:0))%GWIDTH];
					//t = linedist(vec2(i,j),indexToPoint(x+(offset?1:0),y-1)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
					t=thex(x+(offset?1:0),y-1,vec2(i,j),t1,t2);
					//if(t<t1) t1=t; else if(t<t2) t2=t;

					//double g = 0;
					//if(abs(sqrt(t1)+sqrt(t2)-.5*r)<2)
					//	g=1.0;

					imageFrame->set( i, j,r*.05/(sqrt(t1)+1.0),0,0 );
				//}
				//else
					//imageFrame->set( i, j, 0,((double)(k-3))/3.0,.5 );
				
				//if(k<=2)
				//	imageFrame->set( i, j, ((double)(k))/3.0,0,.5 );
				//else
				//	imageFrame->set( i, j, 0,((double)(k-3))/3.0,.5 );
				
				
				//imageFrame->set( i, j, ((double)(x%3))/3.0, ((double)(y%3))/3.0, .5 );

				//imageFrame->set( i, j,1.0,1.0, .5 );
			}
		}
	
	}
};