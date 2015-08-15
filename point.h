#pragma once
//#include<iomanip>
#include<iostream>
#include"vector.h"
extern  unsigned int *framebuffer;//holds the pixelfor whole screen


//color class for storing value of color index with alpha for transparency
class color
{
    public:
    float r,g,b,a;
    color(float rr=1.f,float gg=1.f,float bb=1.f,float aa=1.f)
    {
        r=rr;
        g=gg;
        b=bb;
        a=aa;
    }
    color operator-(const color& ref)//operator overloaded for interpolation of color in traingle fill
    {
        return color(r-ref.r,g-ref.g,b-ref.b,1);
    }
    color operator+(const color& ref)
    {
        return color(r+ref.r,g+ref.g,b+ref.b,1);
    }
    color operator/(float f)
    {
        return color(r/f,g/f,b/f,1);
    }
    color operator*(float f)
    {
        return color(r*f,g*f,b*f,1);
    }

};

//plot a pixel in screen
inline void Setpixel(int x,int y,color rgba)
{
    if((x>=(SCREENWIDTH/2) or x<=(-SCREENWIDTH/2)) or ((y>=(SCREENHEIGHT/2)) or (y<=(-SCREENHEIGHT/2))))
        return;//clips the point  out of screen
    x=(x+(SCREENWIDTH/2));
    y=(y-(SCREENHEIGHT/2));
    y=(-y);//orients the origin to center of screen
       // Create the color for given rgb values: the format for integer in hex is aarrggbb
    // e.g. for white all r,g,b are FFH: FFFFFFFF
    //      for black, all are 00H:  FF000000
    unsigned int colorpixel=(static_cast<int>(rgba.a*255)<<24) | (static_cast<int>(rgba.r*255)<<16) | (static_cast<int>(rgba.g*255)<<8) | static_cast<int>(rgba.b*255);
    framebuffer[y*SCREENWIDTH+x]=colorpixel;

}



template<class T>
inline void Swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}

template<class T>
inline T Max(const T &a, const T &b)
{
    if (a > b)
        return a;
    return b;
}

template<class T>
inline T Min(const T &a, const T &b)
{
    if (a < b)
        return a;
    return b;
}

//for storing 2d point
class point
{
  public:
  struct{float x,y;};
  color rgb;
 float depth;//depth for depth buffering inatalized to zero
 bool shadow;
  vector3 attributes[3];//for all attributes of point

  point():x(0),y(0){}
  point(float xx,float yy,color RGB=color(1,1,1,1),float ddepth=(1.0f),bool Shadow=false):rgb(RGB)
  {
      shadow=Shadow;
      depth=ddepth;
      x=(float)floor(xx+0.5);//roundabout needed for near points
      y=(float)floor(yy+0.5);


//std::cout<<std::setprecision(16)<<depth<<std::endl;
  }
  bool operator==(const point &p)
  {
      return (p.x==x)&&(p.y==y);
  }
  bool operator>(const point &p)
  {
      return (x>p.x) || ((x>p.x) && (y>p.y));
  }
  bool operator<(const point &p)
  {
      return (x<p.x) || ((x<p.x) && (y<p.y));
  }
  point operator+(const point& p)
  {
    return point(x+p.x,y+p.y);
  }
  point operator-(const point& p)
  {
     return point(x-p.x,y-p.y);
  }
  bool operator!=(const point& p)
  {
      return ((x!=p.x) || (y!=p.y));
  }
  point operator+(float f)
  {
      return point(x+f,y+f);
  }
  point operator-(float f)
  {

      return point(x-f,y-f);
  }
  point operator-()
  {
      return point(-x,-y);
  }

  void operator=(const point& p)
  {
      x=p.x;
      y=p.y;
      rgb=p.rgb;
      depth=p.depth;
      shadow=p.shadow;
  }
  float &operator[] (size_t i)
    {
        return (&x)[i];
    }
    float operator[] (size_t i) const
    {
        return (&x)[i];
    }



};
inline std::ostream& operator << (std::ostream &os, const vector3& p)
{



            os << p.x<<"  "<<p.y<<"   "<<p.z<<"  "<<std::endl;

    return os;
}
