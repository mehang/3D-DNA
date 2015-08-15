#include "trianglefillrasterization.h"
#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include<iomanip>
#include "vector.h"
#include "transformation.h"
#include "object.h"

float* screenzbuffer;
float* shadowbuffer;


using namespace std;
unsigned int *framebuffer;


int main (int argc,char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "graphics", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        SCREENWIDTH,
        SCREENHEIGHT,
        SDL_WINDOW_SHOWN
    );

      SDL_Surface* screen=SDL_GetWindowSurface(window);
      framebuffer=(unsigned int*)screen->pixels;
int viewy=50,viewx=-190,viewz=-100;
int rotx=0,roty=0,rotz=0,viewrotx=0,viewroty=0,viewrotz=0;
float zoom=15.0f;
bool quit=false;
SDL_Event event;
object reddna("reddna.obj",color(1,0,0,1),true);
reddna.Readfile();
object bluedna("bluedna.obj",color(0,0,1,1),true);
bluedna.Readfile();
object ground("ground50.obj",color(1,1,0,1));
ground.Readfile();


   Clearscreen();
ground.Fillshadowbuffer(20,rotx,roty,rotz,vector3(0,-5,0));
reddna.Fillshadowbuffer(zoom,rotx,roty,rotz,vector3(0,-5,0));
bluedna.Fillshadowbuffer(zoom,rotx,roty,rotz,vector3(0,-5,0));

ground.Calculateshadow(20,rotx,roty,rotz,vector3(0,-5,0));
reddna.Calculateshadow(zoom,rotx,roty,rotz,vector3(0,-5,0));
bluedna.Calculateshadow(zoom,rotx,roty,rotz,vector3(0,-5,0));

while(!quit)
{

SDL_WaitEvent(&event);
while(SDL_PollEvent(&event))
{
switch (event.type)
         {
         case SDL_QUIT:
             quit = true;
             break;
         case SDL_KEYDOWN:
         switch (event.key.keysym.sym)
         {
         case SDLK_ESCAPE:
         quit = true;
         break;
         case SDLK_w:
         {
         viewy+=10;
         break;
         }
         case SDLK_s:
         {
           viewy-=10;
         break;
         }
         case SDLK_a:
         {
             viewx-=10;
         break;
         }
         case SDLK_d:
         {
          viewx+=10;
         break;
         }
         case SDLK_q:
         {
         viewz-=10;
         break;
         }
         case SDLK_e:
         {
         viewz+=10;
         break;
         }
         case SDLK_f:
         {
         viewrotx+=1;
         vector4 temp(viewx,viewy,viewz,1);
         temp=Rotatex(viewrotx)*temp;
         viewx=temp.x;
         viewy=temp.y;
         viewz=temp.z;
         break;
         }
         case SDLK_g:
         {
         viewroty+=1;
         vector4 temp(viewx,viewy,viewz,1);
         temp=Rotatey(viewroty)*temp;
         viewx=temp.x;
         viewy=temp.y;
         viewz=temp.z;
         break;
         }
         case SDLK_h:
         {
         viewrotz+=1;
         vector4 temp(viewx,viewy,viewz,1);
         temp=Rotatez(viewrotz)*temp;
         viewx=temp.x;
         viewy=temp.y;
         viewz=temp.z;
         break;
         }
         case SDLK_i:
         {
         zoom+=0.5f;

         break;
         }
         case SDLK_o:
         {
         zoom-=0.5f;
         if(zoom<1.0f)
         zoom=1.0f;



         break;
         }
         case SDLK_x:
         {
         rotx++;
         break;
         }
         case SDLK_y:
         {
         roty++;
         break;
         }
         case SDLK_z:
         {
         rotz++;
         break;
         }
         }
         break;
         }
}
    Clearscreen();
         ground.Clearshadow();
    //     dna.Clearshadow();
ground.Fillshadowbuffer(20,rotx,roty,rotz,vector3(0,-5,0));
reddna.Fillshadowbuffer(zoom,rotx,roty,rotz,vector3(0,-5,0));
bluedna.Fillshadowbuffer(zoom,rotx,roty,rotz,vector3(0,-5,0));
ground.Calculateshadow(20,rotx,roty,rotz,vector3(0,-5,0));
reddna.Calculateshadow(zoom,rotx,roty,rotz,vector3(0,-5,0));//2,-4,6
bluedna.Calculateshadow(zoom,rotx,roty,rotz,vector3(0,-5,0));
    // Clear window
    SDL_LockSurface(screen);
ground.Grounddraw(vector3(viewx,viewy,viewz),20,rotx,roty,rotz,vector3(0,-5,0));
reddna.Drawobject(vector3(viewx,viewy,viewz),zoom,rotx,roty,rotz,vector3(0,-1,0));
bluedna.Drawobject(vector3(viewx,viewy,viewz),zoom,rotx,roty,rotz,vector3(0,-1,0));

SDL_UnlockSurface(screen);
Freemem();
    SDL_UpdateWindowSurface(window);
}
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();

    return 0;
}
