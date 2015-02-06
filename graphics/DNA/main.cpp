#include "trainglefillrasterization.h"
#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include "vector.h"
#include "transformation.h"
using namespace std;
int main (int argc,char* argv[])
{
    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "test", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
        SCREENWIDTH,
        SCREENHEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);


bool quit=false;
SDL_Event event;
	std::vector<vector3>cube={
	vector3(0.0f,0.0f,0.0f),
	vector3(50.0f,0.0f,0.0f),
	vector3(50.0f,50.0f,0.0f),
	vector3(0.0f,50.0f,0.0f),
    vector3(0.0f,0.0f,50.0f),
    vector3(0.0f,50.0f,50.0f),
    vector3(50.0f,0.0f,50.0f),
    vector3(50.0f,50.0f,50.0f)};
    std::vector<vector4>res;
	res.resize(cube.size());

	float angle=0;
	std::vector<point> points;
	points.resize(cube.size());
while(!quit)
{
matrix4 finaltransform=Perspective(60,(SCREENWIDTH/SCREENHEIGHT),1,1000)*Viewmatrix(vector3(0,0,0),vector3(0,0,3))*Rotatey(angle);
cout<<finaltransform<<endl;
cout<<endl;

for(int i=0; i<cube.size(); i++)
		{
		  	res[i] = finaltransform * vector4(cube[i],1);

			res[i].Normalizeform();
			points[i] = point(res[i].x, res[i].y);
			cout<<i<<points[i].x<<"      "<<points[i].y<<endl;
		}
		angle+=1;
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
         }
         break;
         }
}
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    // Clear winow
    SDL_RenderClear( renderer );


    SDL_Rect r={40,40,50,50};
    SDL_SetRenderDrawColor( renderer, 0, 0, 1, 0 );
    SDL_RenderFillRect( renderer, &r );
    point p1(.9,1.6);
     point p2(100,10);
     point p3(0.6,1.6);
    triangle(renderer,p1,p2,p3,color(0,0,1,1)).Filltriangle();
   std::vector<triangle> face={
    triangle(renderer, (points[0]), (points[1]), (points[2]), color(1,1,0,1)),
    triangle(renderer, (points[0]), (points[2]), (points[3]),  color(1,0,1,1)),
    triangle(renderer, (points[0]), (points[4]), (points[5]), color(1,1,1,1)),
    triangle(renderer, (points[0]), (points[3]), (points[5]),  color(1,0,1,1)),
    triangle(renderer, (points[0]), (points[6]), (points[4]),  color(1,0,0,1)),
    triangle(renderer, (points[0]), (points[6]), (points[1]), color(1,1,0.7,1)),
    triangle(renderer, (points[7]), (points[6]), (points[1]),  color(0.5,1,0,1)),
    triangle(renderer, (points[7]), (points[6]), (points[4]),  color(0.1,0,1,1)),
    triangle(renderer, (points[7]), (points[3]), (points[5]),  color(0,1,1,1)),
    triangle(renderer, (points[7]), (points[4]), (points[5]), color(1,1,1,1)),
    triangle(renderer, (points[7]), (points[2]), (points[3]),  color(1,0,0,1)),
    triangle(renderer, (points[7]), (points[1]), (points[2]),  color(1,0.5,0.7,1))};
		for(int i=0; i<face.size(); i++)
		{
			face[i].Createtriangle();
			cout<<" triangle  "<<i<<endl;
			//face[i].Filltriangle();
		}

    SDL_RenderPresent(renderer);
}
SDL_DestroyRenderer(renderer);
renderer=NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    SDL_Quit();

    return 0;
}
