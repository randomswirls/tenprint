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
		((x+gOffsetX)%GWIDTH*b-b)+(offset?b/2:0)+offsetX,
		((y+gOffsetY)%GHEIGHT*b-b)*.5*SQRT3+offsetY
		); // Why an extra -b... no idea
	
}
class hexprintrasterizer{

	// v should be normalized, returns dist squared
	double linedist(vec2 p, vec2 p0, vec2 v, float len){
		vec2 r = p-p0;

		float t1 = r.x*v.x+r.y*v.y; //glm::dot(r,v);
		t1 = min(len,max(0.0f,t1));

		vec2 d = p0+v*t1 - p; // vector to closest point 
		return d.x*d.x+d.y*d.y;
		
	}
	double thex(int x,int y, vec2 & p,double & t1, double & t2)
	{
		float weird = 1;
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
			t= linedist(p,indexToPoint(x,y)+tp[k]*(float)r,(tp[k+2]-tp[k])/(float)SQRT3/weird,SQRT3*r*weird);
			if(t<t1) t1=t; else if(t<t2) t2=t;
			t= linedist(p,indexToPoint(x,y)+tp[(k+5)%6]*(float)r,(tp[(k+3)%6]-tp[(k+5)%6])/(float)SQRT3/weird,SQRT3*r*weird);
			if(t<t1) t1=t; else if(t<t2) t2=t;
		}

		return t;
	}
	unsigned int time;
public:
	hexprintrasterizer(){time=0;};
	void rasterize()
	{
		//time++;

		for(int j = 0; j<HEIGHT; j++){
			for(int i = 0; i<WIDTH; i++){
			
				//if(uniform()>.1)
				//if((++time%3)!=0)//||uniform()>.9)
				//	continue;
				int y = ((int)floor((j + (1.0+.5)*b*.5*SQRT3-offsetY)/b*2.0/SQRT3 - gOffsetY)+GHEIGHT)%GHEIGHT;
				bool offset = y%2;
				int x = ((int)floor((i + (1.0+.5)*b-(offset?b/2:0)-offsetX)/b-gOffsetX)+GWIDTH)%GWIDTH;
				
				double t1=1000;
				double t2=1000;
				double t;

				//center
				t=thex(x,y,vec2(i,j),t1,t2);
				//t = linedist(vec2(i,j),indexToPoint(x,y)+tp[k]*(float)r,(tp[k+3]-tp[k])*.5f,2.0*r);
				//if(t<t1) t1=t; else if(t<t2) t2=t;

				//sides
				t=thex(x-1,y,vec2(i,j),t1,t2);
				t=thex(x+1,y,vec2(i,j),t1,t2);

				//above
				t=thex(x-1+(offset?1:0),y+1,vec2(i,j),t1,t2);
				t=thex(x+(offset?1:0),y+1,vec2(i,j),t1,t2);

				//below
				t=thex(x-1+(offset?1:0),y-1,vec2(i,j),t1,t2);
				t=thex(x+(offset?1:0),y-1,vec2(i,j),t1,t2);

				double g = 0;
				//double thingy = abs(sqrt(t1)+sqrt(t2)-.5*r);
				//if(thingy<10)
				//	g=(10.0-thingy)/10.0;
				double grad = r*.1/(sqrt(t1)+1.0);

				double pink =1.0-abs(2.0*min(1.0,max(0.0,grad-.2)/.8)-1.0); 
				double cyan = min(1.0,max(0.0,grad*.5-.5)/.5);

				//imageFrame->set( i, j,1.0-abs(2.0*min(1.0,max(0.0,r*.1/(sqrt(t1)+1.0)-.2)/.8)-1.0),g,0 );
				imageFrame->set( i, j,
					min(1.0,	pink*1.0*((float)i/WIDTH*.5+.5)),
					min(1.0,								cyan*1.0),
					min(1.0,	pink*.8*((float)j/HEIGHT*.5+.5)		+cyan*1.0*((float)i/WIDTH*.5+.5)));
				
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