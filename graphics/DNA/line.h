#pragma once
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include"point.h"

//using namespace std;
//class for our color red,green,blue and alpha for opaque

class line
{
    private:
float xstart,ystart,xend,yend;
float dx,dy,dx2,dy2,dydx2;
float xinc,yinc;
float p;
bool slopelessthan1;
SDL_Renderer* renderer;
color linecolor;

public:
float xupdate,yupdate;
line(SDL_Renderer* Renderer,point P1,point P2,color Linecolor):xstart(P1.x),ystart(P1.y),xend(P2.x),yend(P2.y),linecolor(Linecolor)
{
    renderer=Renderer;
    dx=fabs(xend-xstart);
    dy=fabs(yend-ystart);
    slopelessthan1=(dx>dy)?true:false;
    xinc = (xend>xstart ? 1 : -1);
	yinc = (yend>ystart ? 1 : -1);
    dx2=2*dx;
    dy2=2*dy;
    dydx2=dy2-dx2;
    p = (slopelessthan1) ? (dy2-dx) : (dx2 - dy);
    yupdate=ystart;
    xupdate=xstart;

}
line(SDL_Renderer* Renderer,float x1,float y1,float x2,float y2,color Linecolor):xstart(x1),ystart(y1),xend(x2),yend(y2),linecolor(Linecolor)
{
    renderer=Renderer;
    dx=fabs(xend-xstart);
    dy=fabs(yend-ystart);
    slopelessthan1=(dx>dy)?true:false;
    xinc = (xend>xstart ? 1 : -1);
	yinc = (yend>ystart ? 1 : -1);
    dx2=2*dx;
    dy2=2*dy;
    dydx2=dy2-dx2;
    p = (slopelessthan1) ? (dy2-dx) : (dx2 - dy);
    yupdate=ystart;
    xupdate=xstart;
}
bool Returnupdatedcoordinate() //return only if there is increase in y for filling triangle
{
    float x=xupdate;
     float y=yupdate;
while (yupdate==y)
 {

	    if (slopelessthan1)
	{
        if (p <= 0)
            p+= dy2;
        else
        {
            y+=yinc;
            p+=(dydx2);
        }
        x+=xinc;
	}
	else
	{
        if (p <= 0)
            p+= dx2;
        else
        {
            x+=xinc;
            p-=dydx2;
        }
        y+= yinc;
	}
}
xupdate=x;
yupdate=y;
return true;
}

void Drawline()
{

   float x =xstart;
   float y =ystart;
	Setpixel(renderer,(int) x,(int) y, linecolor);
	if (slopelessthan1)
	{

		for(int i=0;i<dx;i++)
		{
			if (p < 0)
				p+= dy2;
			else
			{
				y+=yinc;
				p+=(dydx2);
			}
			x+=xinc;
			Setpixel(renderer,(int)floor(x+0.5) , (int)floor(y+0.5), linecolor);
		}
	}
	else
	{

		for(int i=0;i<dy;i++)
		{
			if (p < 0)
				p+= dx2;
			else
			{
				x+=xinc;
				p-=dydx2; // twodydx = twody-twodx, we need twodx-twody so
			}
			y+= yinc;
			Setpixel(renderer, (int)floor(x+0.5), (int)floor(y+0.5), linecolor);
		}
	}
}

};
