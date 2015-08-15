#pragma once

#define SCREENWIDTH 1080
#define SCREENHEIGHT 640
#include<iostream>
#include"vector.h"


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

};

//plot a pixel in screen
inline void Setpixel(SDL_Renderer *renderer,int x,int y,color rgba)
{

    x=(x+(SCREENWIDTH/2));
    y=(y-(SCREENHEIGHT/2));
    y=(-y);
    SDL_Rect pixel = {x, y, 1, 1};
    SDL_SetRenderDrawColor(renderer, static_cast<int>(rgba.r*255),static_cast<int>( rgba.g*255),static_cast<int>( rgba.b*255),static_cast<int> (rgba.a));
    SDL_RenderFillRect(renderer, &pixel);
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
  float depth; //depth for depth buffering inatalized to zero
  vector3 attributes[3];//for all attributes of point

  point():x(0),y(0){}
  point(float xx,float yy,color RGB=color(0,0,1,1)):rgb(RGB)
  {
      depth=0;
      x=(float)floor(xx+0.5);
      y=(float)floor(yy+0.5);

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
inline std::ostream& operator << (std::ostream &os, const color &p)
{

        os << std::endl;

            os << p.r<<","<<p.g<<","<<p.b<<","<<p.a<<std::endl;

    return os;
}
