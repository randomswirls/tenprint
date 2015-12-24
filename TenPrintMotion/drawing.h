// Laura Murphy

// drawing.h
// Drawing Utilities and Image Manipulation

#ifndef _drawing_h_                   // include file only once
#define _drawing_h_

#include <sstream>
#include <iostream>
#include <cmath>
#include "CImg.h"

// Draws the scene
class FrameBuffer{
public:

	// the time it took to render the image
	int t;

	int width;
	int height;
	float * framebuffer;

	FrameBuffer(){
		framebuffer=0;
	}
	void init(int w, int h)
	{
		if(framebuffer !=0)
			delete framebuffer;

		width = w;
		height = h;

		framebuffer = new float[h*w*3];
	}
	void draw(void)
	{
	   glDrawPixels(width,height,GL_RGB,GL_FLOAT,framebuffer);
	   glFlush();
	}

	// Clears framebuffer to black
	void clear()
	{
		for(int i=0;i<height*width*3;i++) {
			framebuffer[i] = 0.0;
		}
	}
	int index(int x,int y,int c)
	{
		return y*width*3+x*3+c;
	}
	double get(int x, int y, int c)
	{
		return framebuffer[index(x%width,y%height,c)];
	}
	// Sets pixel x,y to the color RGB
	void set(int x, int y, float R, float G, float B)
	{
		framebuffer[index(x,y,0)] = R;
		framebuffer[index(x,y,1)] = G;
		framebuffer[index(x,y,2)] = B;
	}
};

void saveImage(FrameBuffer * fb, std::string label = "", int key = -1)
{
	int h = fb->height;
	int w = fb->width;

	// put frame data into image class temporarily
	cimg_library::CImg<unsigned char> img(w,h,1,3);
	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++)
			for(int c=0;c<3;c++)
				img(i,j,0,c)=fb->get(i,h-j-1,c)*255.0;

	// create file name: currentTime_elapsedTime[_randomNumber].bmp
	std::stringstream ss;
	ss<<label<<"_";
	if(key==-1)
		ss<<time(0);
	else
		ss<<key;
	//if(fb->t<1)
		//ss<<'_'<<rand()%1000;
	ss<<".bmp";

	// convert string stream to string
	std::string name;
	ss>>name;

	// save the image
	img.save_bmp(name.c_str());
}

void loadImage(FrameBuffer * fb, std::string s)
{

	// put frame data into image class temporarily
	cimg_library::CImg<unsigned char> img(s.c_str());
	fb->init(img.width(), img.height());

	int h = fb->height;
	int w = fb->width;

	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++)
			fb->set(i,h-j-1,
				img(i,j,0,0)/255.0, img(i,j,0,1)/255.0, img(i,j,0,2)/255.0 );
}

float maxChannel(FrameBuffer * fb, int i, int j)
{
	return fb->get(i,j,0);//max(fb->get(i,j,0),max(fb->get(i,j,1),fb->get(i,j,2)));
}

#endif