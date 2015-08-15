#pragma once
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <cmath>
#include "vector.h"
#include "transformation.h"
#include "matrix.h"
#include "trianglefillrasterization.h"
#include <SDL2/SDL.h>

#define Clip(x) (((x<(-1)) or x>(1))?false:true)
#define Ka 0.1
#define Ia 1
#define Kd 0.6
#define Il 1
#define Ks 0.5
#define ns 8

class object
{
 private:
 const char* path;
 struct vertices
 {
  float x,y,z;
  int counter=0;
  vector3 pointnormal;
  bool flag=true;
  bool shadow=false;
 };
  struct faces
    {
        int vertex_indices[3];
    };
 std::vector<vertices>modelvertex;
 std::vector<faces>modelface;
 vector4 transformedvertex1,transformedvertex2,transformedvertex3;

 color rgb;
 bool lightshadow;
 vector3 lightvector;
 vector3 reflectedray1,reflectedray2,reflectedray3,n1,n2,n3;
 matrix4 tempmatrix;
 float intensity1,intensity2,intensity3;

 public:
 object():path(nullptr){}
 object(char* str,color RGB=color(1,1,1,1),bool Lightshadow=false):rgb(RGB),lightshadow(Lightshadow)
 {
  path=str;
  lightvector=vector3(-100,100,10);
 }
 void Fillshadowbuffer(float s=10.0f,int rotx=0,int roty=0,int rotz=0,vector3 trans=vector3(0,0,0));
void Calculateshadow(float s=10.0f,int rotx=0,int roty=0,int rotz=0,vector3 trans=vector3(0,0,0));
void Readfile();
void Calculatenormal();
void Drawobject(vector3 Viewvector=vector3(-100,100,-100),float s=10.0f,int rotx=0,int roty=0,int rotz=0,vector3 trans=vector3(0,0,0));
void Grounddraw(vector3 Viewvector=vector3(-100,100,-100),float s=10.0f,int rotx=0,int roty=0,int rotz=0,vector3 trans=vector3(0,0,0));
void Clearshadow();
};

