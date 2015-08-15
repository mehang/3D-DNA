#pragma once
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include"point.h"


//class for our color red,green,blue and alpha for opaque

class line
{
    private:
float xstart,ystart,xend,yend;
float dx,dy,dx2,dy2,dydx2;
float xinc,yinc;
float p;

SDL_Renderer* renderer;
color linecolor;
color delcolor,colorstart,colorend,ycolorinc,xcolorinc;

public:
float xupdate,yupdate;
color ycolorupdate,xcolorupdate;
bool slopelessthan1;
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
    colorstart=P1.rgb;
    colorend=P2.rgb;
    delcolor=colorend-colorstart;
    if(dx!=0)
    xcolorinc=(delcolor/dx);
    if(dy!=0)
    ycolorinc=(delcolor/dy);
    ycolorupdate=colorstart;
    xcolorupdate=colorstart;

}
line(SDL_Renderer* Renderer,float x1,float y1,float x2,float y2,color Linecolor):linecolor(Linecolor)
{
    renderer=Renderer;
    xstart=(int)floor(x1+0.5);
    ystart=(int)floor(y1+0.5);
    xend=(int)floor(x2+0.5);
    yend=(int)floor(y2+0.5);
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
    if(xend==xstart and yend==ystart)
    return false;
    else
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
        xcolorupdate=xcolorupdate+xcolorinc;
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
        ycolorupdate=ycolorupdate+ycolorinc;
	}
}
xupdate=x;
yupdate=y;
return true;
    }
}

void Drawline()//bresenham algorithm of drawing line
{

   float x =xstart;
   float y =ystart;
	Setpixel(renderer,(int) x,(int) y, xcolorupdate);
	if (slopelessthan1)
	{

		for(int i=0;i<dx;i++)
		{
			if (p <= 0)
				p+= dy2;
			else
			{
				y+=yinc;
				p+=(dydx2);
			}
			x+=xinc;

			xcolorupdate=xcolorupdate+xcolorinc;
			Setpixel(renderer,(x) , (y), xcolorupdate);
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
				p-=dydx2;
			}
			y+= yinc;
			ycolorupdate=ycolorupdate+ycolorinc;
			Setpixel(renderer, (x), (y), ycolorupdate);
		}
	}
}

};
