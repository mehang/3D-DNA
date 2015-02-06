#pragma once

#define SCREENWIDTH 1080
#define SCREENHEIGHT 640
#include<iostream>
#include"vector.h"



class color
{
    public:
    uint8_t r,g,b,a;
    color(uint8_t rr=1,uint8_t gg=1,uint8_t bb=1,uint8_t aa=1)
    {
        r=rr*255;
        g=gg*255;
        b=bb*255;
        a=aa*255;
    }

};

//plot a pixel in screen
inline void Setpixel(SDL_Renderer *renderer,int x,int y,color rgba)
{

    x=(x+(SCREENWIDTH/2));
    y=(y-(SCREENHEIGHT/2));
    y=(-y);
    SDL_Rect pixel = {x, y, 1, 1};
    SDL_SetRenderDrawColor(renderer, rgba.r, rgba.g, rgba.b, rgba.a);
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
  float depth; //depth for depth buffering inatalized to zero
  vector3 attributes[3];//for all attributes of point

  point():x(0),y(0){}
  point(float xx,float yy):x(xx),y(yy){depth=0;}
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
      return ((x!=p.x)&&(y!=p.y));
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
