#pragma once
#include <iostream>
#include "line.h"
#include "point.h"
#include "vector.h"
#include <SDL2/SDL.h>
#include <cmath>

class triangle
{
    private:
    point p1,p2,p3;

    public:
    triangle():p1(point(0,0)),p2(point(0,0)),p3(point(0,0)){}
    triangle(point P1,point P2,point P3):p1(P1),p2(P2),p3(P3)
    {
        if (p1.y > p2.y) //sort out with greatest value of y in p3
        {
        Swap(p1,p2);
        }
         if (p1.y > p3.y)
         {
            Swap(p1,p3);
         }
         if (p2.y > p3.y)
          {
              Swap(p2,p3);
          }
    // temppoint.x=p1.x+((p2.y-p1.y)/(p3.y-p1.y))*(p3.x-p1.x);
    // temppoint.y=p2.y;
     }
   void Createtriangle();

   void Filltriangle();

};

