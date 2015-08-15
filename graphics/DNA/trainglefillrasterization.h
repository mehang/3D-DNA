#pragma once
#include <iostream>
#include "line.h"
#include "point.h"
#include "vector.h"
#include <SDL2/SDL.h>

class triangle
{
    private:
    point p1,p2,p3,temppoint;
    color rgb;
    SDL_Renderer* renderer;

    public:
    triangle():p1(point(0,0)),p2(point(0,0)),p3(point(0,0)),temppoint(point(0,0)){}
    triangle(SDL_Renderer* Renderer,point P1,point P2,point P3,color RGB=color(0,0,0,1)):p1(P1),p2(P2),p3(P3),rgb(RGB)
    {
        renderer=Renderer;
        if (p1.y > p2.y) //sort out with greatest value of y in p3
        {
         Swap(p1.y,p2.y);
         Swap(p1.x,p2.x);
        }
         if (p1.y > p3.y)
         {
             Swap(p1.y,p3.y);
             Swap(p1.x,p3.x);
         }
         if (p2.y > p3.y)
          {
              Swap(p2.y,p3.y);
              Swap(p2.x,p3.x);
          }
     temppoint.x=p1.x+((p2.y-p1.y)/(p3.y-p1.y))*(p3.x-p1.x);
     temppoint.y=p2.y;
     }
   void Createtriangle()
   {
     line(renderer,p1,p2,rgb).Drawline();
     line(renderer,p2,p3,rgb).Drawline();
     line(renderer,p1,p3,rgb).Drawline();
     if ((p1==p2)||(p2==p3)||(p1==p3))
     std::cout<<"triangle can't be created";
   }

   void Filltriangle1()
   {
      point incpoint1,incpoint2;
      incpoint1=p2;
      incpoint2=temppoint;
      line e1(renderer,p2,p3,rgb);
      line e2(renderer,temppoint,p3,rgb);
      line horizontal(renderer,incpoint1,incpoint2,rgb);
      horizontal.Drawline();
      while(incpoint1!=p3 || incpoint2!=p3)
      {
         if(e1.Returnupdatedcoordinate())
         {
             if(e2.Returnupdatedcoordinate())
             {
                 incpoint1=point(e1.xupdate,e1.yupdate);
                 incpoint2=point(e2.xupdate,e2.yupdate);
                 line(renderer,incpoint1,incpoint2,rgb).Drawline();
             }
         }
      }
   }
 void Filltriangle2()
   {
      point incpoint1,incpoint2;
      incpoint1=p2;
      incpoint2=temppoint;
      line e1(renderer,p2,p1,rgb);
      line e2(renderer,temppoint,p1,rgb);
      line horizontal(renderer,incpoint1,incpoint2,rgb);
      horizontal.Drawline();
      while(incpoint1!=p1 || incpoint2!=p1)
      {
         if(e1.Returnupdatedcoordinate())
         {
             if(e2.Returnupdatedcoordinate())
             {
                 incpoint1=point(e1.xupdate,e1.yupdate);
                 incpoint2=point(e2.xupdate,e2.yupdate);
                 line(renderer,incpoint1,incpoint2,rgb).Drawline();
             }
         }
      }
   }
   void Filltriangle()
   {
       if ((p1!=p2) && (p2!=p3) && (p1!=p3))
      {

       Filltriangle2();
       Filltriangle1();
      }
   }

};

