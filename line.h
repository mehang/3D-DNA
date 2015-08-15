#pragma once
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include"point.h"

extern  float *screenzbuffer;//holds zbuffer value for every pixel
extern  float *shadowbuffer;

inline void Freemem()
{
free(screenzbuffer);
free(shadowbuffer);
}

inline void Clearscreen()
{

screenzbuffer=new float[(SCREENHEIGHT)*(SCREENWIDTH)];
shadowbuffer=new float[(SCREENHEIGHT)*(SCREENWIDTH)];//might be error here
 for(int i=0;i<((SCREENHEIGHT)*(SCREENWIDTH));i++)
 {
   screenzbuffer[i]=1.0f;
   shadowbuffer[i]=1.0f;
 }

for (int i = -SCREENWIDTH/2; i < SCREENWIDTH/2; ++i)
        for (int j = -SCREENHEIGHT/2; j < SCREENHEIGHT/2; ++j)
            {
             Setpixel(i,j,color(0.1,0.1,0.15,1));
            }
}

inline void UpdateShadowbuffer(const point& p)
{
if(p.depth<shadowbuffer[(int)(-(p.y-(SCREENHEIGHT/2)))*SCREENWIDTH+(int)(p.x+(SCREENWIDTH/2))])
{
shadowbuffer[(int)(-((p.y-(SCREENHEIGHT/2))))*SCREENWIDTH+(int)(p.x+(SCREENWIDTH/2))]=p.depth;
}
}

inline void Updatepixel(const point& p)
{

    if((p.x>=(SCREENWIDTH/2) or p.x<=(-SCREENWIDTH/2)) or ((p.y>=(SCREENHEIGHT/2)) or (p.y<=(-SCREENHEIGHT/2))))
        return;
        if(p.shadow)
        {
         UpdateShadowbuffer(p);
         return;
        }
else
{
if(p.depth<screenzbuffer[(int)(-(p.y-(SCREENHEIGHT/2)))*SCREENWIDTH+(int)(p.x+(SCREENWIDTH/2))])
{
screenzbuffer[(int)(-((p.y-(SCREENHEIGHT/2))))*SCREENWIDTH+(int)(p.x+(SCREENWIDTH/2))]=p.depth;
Setpixel(p.x,p.y,p.rgb);
}
}
}



//class for our color red,green,blue and alpha for opaque
class line
{
    private:
float xstart,ystart,xend,yend;
float dx,dy,dx2,dy2,dydx2;
float xinc,yinc;
float p;
bool shadowflag;

color delcolor,colorstart,colorend,ycolorinc,xcolorinc;

float delzbuffer,zbufferstart,zbufferend,yzbufferinc,xzbufferinc;

public:
float xupdate,yupdate;
color ycolorupdate,xcolorupdate;
long double yzbufferupdate,xzbufferupdate;
bool slopelessthan1;
line(point P1,point P2):xstart(P1.x),ystart(P1.y),xend(P2.x),yend(P2.y)
{
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
    zbufferstart=P1.depth;
    zbufferend=P2.depth;
    delcolor=colorend-colorstart;
    delzbuffer=zbufferend-zbufferstart;
    if(P1.shadow or P2.shadow)
    shadowflag=true;
    else
    shadowflag=false;
    if(dx!=0)
    {
       xcolorinc=(delcolor/dx);
       xzbufferinc=(delzbuffer/dx);
    }
    if(dy!=0)
    {
         ycolorinc=(delcolor/dy);
         yzbufferinc=(delzbuffer/dy);
    }
    ycolorupdate=colorstart;
    xcolorupdate=colorstart;
    yzbufferupdate=zbufferstart;
    xzbufferupdate=zbufferstart;

}
line(float x1,float y1,float x2,float y2)
{

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
        xzbufferupdate=xzbufferupdate+xzbufferinc;
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
        yzbufferupdate=yzbufferupdate+yzbufferinc;
	// x1, z1, x2, z2

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
	Updatepixel(point((int) x,(int) y, xcolorupdate,xzbufferupdate,shadowflag));
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
			xzbufferupdate=xzbufferupdate+xzbufferinc;
			Updatepixel(point((x) , (y), xcolorupdate,xzbufferupdate,shadowflag));
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
			yzbufferupdate=yzbufferupdate+yzbufferinc;
			Updatepixel(point((x), (y), ycolorupdate,yzbufferupdate,shadowflag));
		}
	}
}

void Drawhorizontalline()
{
 float x=xstart;
 if (xstart<xend)
 {
 while(x!=xend)
 {
  Updatepixel(point(x,ystart,xcolorupdate,xzbufferupdate,shadowflag));
  x++;
  xcolorupdate=xcolorupdate+xcolorinc;
  xzbufferupdate=xzbufferupdate+xzbufferinc;
 }
 Updatepixel(point(x,ystart,xcolorupdate,xzbufferupdate,shadowflag));
}
else
{
 while(x!=xend)
 {
  Updatepixel(point(x,ystart,xcolorupdate,xzbufferupdate,shadowflag));
  x--;
  xcolorupdate=xcolorupdate+xcolorinc;
  xzbufferupdate=xzbufferupdate+xzbufferinc;
 }
 Updatepixel(point(x,ystart,xcolorupdate,xzbufferupdate,shadowflag));
}
}
};
