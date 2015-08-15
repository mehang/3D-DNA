#include "object.h"
void object::Readfile()
{
  char lineheader[128];
  FILE *fp;
  int i;
   fp=fopen(path,"r");
    while(1)
    {
        int res=fscanf(fp,"%s",lineheader);
        if(res==EOF)break;
        if(strcmp(lineheader,"v")==0)
        {
            vertices v1;
            fscanf(fp,"%f %f %f",&v1.x,&v1.y,&v1.z);
            modelvertex.push_back(v1);
        }
        else if(strcmp(lineheader,"f")==0)
        {
            faces f1;
            fscanf(fp,"%d %d %d ",&f1.vertex_indices[0],
                                                   &f1.vertex_indices[1],
                                                   &f1.vertex_indices[2]);
            modelface.push_back(f1);
        }

    }
    fclose(fp);
    Calculatenormal();
}
void object::Calculatenormal()
{


 for(int i=0;i<modelface.size();i++)
  {
    vector3 vertex1(modelvertex[modelface[i].vertex_indices[0]-1].x,modelvertex[modelface[i].vertex_indices[0]-1].y,modelvertex[modelface[i].vertex_indices[0]-1].z);
    vector3 vertex2(modelvertex[modelface[i].vertex_indices[1]-1].x,modelvertex[modelface[i].vertex_indices[1]-1].y,modelvertex[modelface[i].vertex_indices[1]-1].z);
    vector3 vertex3(modelvertex[modelface[i].vertex_indices[2]-1].x,modelvertex[modelface[i].vertex_indices[2]-1].y,modelvertex[modelface[i].vertex_indices[2]-1].z);
    vector3 AB=vertex2-vertex1;
    vector3 AC=vertex3-vertex1;
    vector3 normal((AB).Crossproduct(AC));
    normal=normal.Unitvector();

    modelvertex[modelface[i].vertex_indices[0]-1].pointnormal=modelvertex[modelface[i].vertex_indices[0]-1].pointnormal+normal;
    modelvertex[modelface[i].vertex_indices[0]-1].counter++;
    modelvertex[modelface[i].vertex_indices[1]-1].pointnormal=modelvertex[modelface[i].vertex_indices[1]-1].pointnormal+normal;
    modelvertex[modelface[i].vertex_indices[1]-1].counter++;
    modelvertex[modelface[i].vertex_indices[2]-1].pointnormal=modelvertex[modelface[i].vertex_indices[2]-1].pointnormal+normal;
    modelvertex[modelface[i].vertex_indices[2]-1].counter++;
    }

  for(int i=0;i<modelface.size();i++)
  {
    if(modelvertex[modelface[i].vertex_indices[0]-1].flag)
    {
    modelvertex[modelface[i].vertex_indices[0]-1].pointnormal=   modelvertex[modelface[i].vertex_indices[0]-1].pointnormal/modelvertex[modelface[i].vertex_indices[0]-1].counter;
    modelvertex[modelface[i].vertex_indices[0]-1].flag=false;
    }
     if(modelvertex[modelface[i].vertex_indices[1]-1].flag)
    {
    modelvertex[modelface[i].vertex_indices[1]-1].pointnormal=   modelvertex[modelface[i].vertex_indices[1]-1].pointnormal/modelvertex[modelface[i].vertex_indices[1]-1].counter;
    modelvertex[modelface[i].vertex_indices[1]-1].flag=false;
    }
    if(modelvertex[modelface[i].vertex_indices[2]-1].flag)
    {
    modelvertex[modelface[i].vertex_indices[2]-1].pointnormal=   modelvertex[modelface[i].vertex_indices[2]-1].pointnormal/modelvertex[modelface[i].vertex_indices[2]-1].counter;
    modelvertex[modelface[i].vertex_indices[2]-1].flag=false;
    }
  }

}

void object::Fillshadowbuffer(float s,int rotx,int roty,int rotz,vector3 trans)
{
matrix4 shadowmatrix=Perspective(60,(SCREENWIDTH/SCREENHEIGHT),5,1000)*Viewmatrix(lightvector,vector3(0,0,0)) *Rotatex(rotx)*Rotatey(roty)*Rotatez(rotz)* Scale(s)*Translate(trans);
for(int i=0;i<modelface.size();i++)
 {
  transformedvertex1=(shadowmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[0]-1].x,modelvertex[modelface[i].vertex_indices[0]-1].y,modelvertex[modelface[i].vertex_indices[0]-1].z),1));
  transformedvertex2=(shadowmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[1]-1].x,modelvertex[modelface[i].vertex_indices[1]-1].y,modelvertex[modelface[i].vertex_indices[1]-1].z),1));
  transformedvertex3=(shadowmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[2]-1].x,modelvertex[modelface[i].vertex_indices[2]-1].y,modelvertex[modelface[i].vertex_indices[2]-1].z),1));
  transformedvertex1.Normalizeform();
  transformedvertex2.Normalizeform();
  transformedvertex3.Normalizeform();
   if(
  Clip(transformedvertex1.x) or Clip(transformedvertex2.x) or Clip(transformedvertex3.x)
    )
  if(
     Clip(transformedvertex1.y) or Clip(transformedvertex2.y) or Clip(transformedvertex3.y)
    )
    {
        transformedvertex1.Todevicecoordinate();
  transformedvertex2.Todevicecoordinate();
  transformedvertex3.Todevicecoordinate();
    if(((transformedvertex2.x-transformedvertex1.x)*(transformedvertex3.y-transformedvertex1.y)-(transformedvertex3.x-transformedvertex1.x)*(transformedvertex2.y-transformedvertex1.y))<0)
    {
  triangle t(
  point(transformedvertex1.x,transformedvertex1.y,color(0.4,0.4,0.4,1),transformedvertex1.z,true),
  point(transformedvertex2.x,transformedvertex2.y,color(0.4,0.4,0.4,1),transformedvertex2.z,true),
  point(transformedvertex3.x,transformedvertex3.y,color(0.4,0.4,0.4,1),transformedvertex3.z,true)
    );

 t.Filltriangle();
    }
  }
 }
}

void object::Calculateshadow(float s,int rotx,int roty,int rotz,vector3 trans)
{

 tempmatrix=Perspective(60,(SCREENWIDTH/SCREENHEIGHT),5,1000)*Viewmatrix(lightvector,vector3(0,0,0)) *Rotatex(rotx)*Rotatey(roty)*Rotatez(rotz)* Scale(s)*Translate(trans);
for(int i=0;i<modelface.size();i++)
{
  transformedvertex1=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[0]-1].x,modelvertex[modelface[i].vertex_indices[0]-1].y,modelvertex[modelface[i].vertex_indices[0]-1].z),1));
  transformedvertex2=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[1]-1].x,modelvertex[modelface[i].vertex_indices[1]-1].y,modelvertex[modelface[i].vertex_indices[1]-1].z),1));
  transformedvertex3=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[2]-1].x,modelvertex[modelface[i].vertex_indices[2]-1].y,modelvertex[modelface[i].vertex_indices[2]-1].z),1));
  transformedvertex1.Normalizeform();
  transformedvertex2.Normalizeform();
  transformedvertex3.Normalizeform();
  n1=   modelvertex[modelface[i].vertex_indices[0]-1].pointnormal;
  n2=   modelvertex[modelface[i].vertex_indices[1]-1].pointnormal;
  n3=   modelvertex[modelface[i].vertex_indices[2]-1].pointnormal;
  if(
  Clip(transformedvertex1.x) or Clip(transformedvertex2.x) or Clip(transformedvertex3.x)
    )
  if(
     Clip(transformedvertex1.y) or Clip(transformedvertex2.y) or Clip(transformedvertex3.y)
    )
  {

{
  transformedvertex1.Todevicecoordinate();
  transformedvertex2.Todevicecoordinate();
  transformedvertex3.Todevicecoordinate();
if(((transformedvertex2.x-transformedvertex1.x)*(transformedvertex3.y-transformedvertex1.y)-(transformedvertex3.x-transformedvertex1.x)*(transformedvertex2.y-transformedvertex1.y))>0)
{
 if((transformedvertex1.x<(SCREENWIDTH/2) and transformedvertex1.x>(-SCREENWIDTH/2)) and ((transformedvertex1.y<(SCREENHEIGHT/2)) and (transformedvertex1.y>(-SCREENHEIGHT/2))))
if(transformedvertex1.z>shadowbuffer[(int)(-(transformedvertex1.y-(SCREENHEIGHT/2)))*SCREENWIDTH+(int)(transformedvertex1.x+(SCREENWIDTH/2))])
  modelvertex[modelface[i].vertex_indices[0]-1].shadow=true;

  if((transformedvertex2.x<(SCREENWIDTH/2) and transformedvertex2.x>(-SCREENWIDTH/2)) and ((transformedvertex2.y<(SCREENHEIGHT/2)) and (transformedvertex2.y>(-SCREENHEIGHT/2))))
  if(transformedvertex2.z>shadowbuffer[(int)(-(transformedvertex2.y-(SCREENHEIGHT/2)))*SCREENWIDTH+(int)(transformedvertex2.x+(SCREENWIDTH/2))])
  modelvertex[modelface[i].vertex_indices[1]-1].shadow=true;

  if((transformedvertex3.x<(SCREENWIDTH/2) and transformedvertex3.x>(-SCREENWIDTH/2)) and ((transformedvertex3.y<(SCREENHEIGHT/2)) and (transformedvertex3.y>(-SCREENHEIGHT/2))))
  if(transformedvertex3.z>shadowbuffer[(int)(-(transformedvertex3.y-(SCREENHEIGHT/2)))*SCREENWIDTH+(int)(transformedvertex3.x+(SCREENWIDTH/2))])
  modelvertex[modelface[i].vertex_indices[2]-1].shadow=true;

 }
 }
 }
}


}

void object::Drawobject(vector3 Viewvector,float s,int rotx,int roty,int rotz,vector3 trans )
{
tempmatrix=Perspective(60,(SCREENWIDTH/SCREENHEIGHT),5,1000)*Viewmatrix(Viewvector,vector3(0,0,0)) *Rotatex(rotx)*Rotatey(roty)*Rotatez(rotz)* Scale(s)*Translate(trans);
Viewvector=Viewvector.Unitvector();
vector3 light=lightvector.Unitvector();


for(int i=0;i<modelface.size();i++)
{
  transformedvertex1=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[0]-1].x,modelvertex[modelface[i].vertex_indices[0]-1].y,modelvertex[modelface[i].vertex_indices[0]-1].z),1));
  transformedvertex2=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[1]-1].x,modelvertex[modelface[i].vertex_indices[1]-1].y,modelvertex[modelface[i].vertex_indices[1]-1].z),1));
  transformedvertex3=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[2]-1].x,modelvertex[modelface[i].vertex_indices[2]-1].y,modelvertex[modelface[i].vertex_indices[2]-1].z),1));
  transformedvertex1.Normalizeform();
  transformedvertex2.Normalizeform();
  transformedvertex3.Normalizeform();

  n1=   modelvertex[modelface[i].vertex_indices[0]-1].pointnormal;
  n2=   modelvertex[modelface[i].vertex_indices[1]-1].pointnormal;
  n3=   modelvertex[modelface[i].vertex_indices[2]-1].pointnormal;

  if(
  Clip(transformedvertex1.x) or Clip(transformedvertex2.x) or Clip(transformedvertex3.x)
    )
  if(
     Clip(transformedvertex1.y) or Clip(transformedvertex2.y) or Clip(transformedvertex3.y)
    )
  {

{
  transformedvertex1.Todevicecoordinate();
  transformedvertex2.Todevicecoordinate();
  transformedvertex3.Todevicecoordinate();
if(((transformedvertex2.x-transformedvertex1.x)*(transformedvertex3.y-transformedvertex1.y)-(transformedvertex3.x-transformedvertex1.x)*(transformedvertex2.y-transformedvertex1.y))>0)
{
reflectedray1=n1*(light.Dotproduct((n1*2)))-light;
reflectedray2=n2*(light.Dotproduct((n2*2)))-light;
reflectedray3=n3*(light.Dotproduct((n3*2)))-light;

intensity1=Ka*Ia+Kd*Il*((light.Dotproduct(n1)))+Ks*Il*pow(Viewvector.Dotproduct(reflectedray1),ns);
intensity2=Ka*Ia+Kd*Il*((light.Dotproduct(n2)))+Ks*Il*pow(Viewvector.Dotproduct(reflectedray2),ns);
intensity3=Ka*Ia+Kd*Il*((light.Dotproduct(n3)))+Ks*Il*pow(Viewvector.Dotproduct(reflectedray3),ns);

if(intensity1>1 )
intensity1=1;
if(intensity2>1 )
intensity2=1;
if(intensity3>1 )
intensity3=1;

if(intensity1<0)
intensity1=0;
if(intensity2<0)
intensity2=0;
if(intensity3<0)
intensity3=0;


color temp=rgb;

if(modelvertex[modelface[i].vertex_indices[0]-1].shadow)
if(lightshadow)
{
 temp=(temp);
}
else
intensity1=0;

if(modelvertex[modelface[i].vertex_indices[1]-1].shadow)
if(lightshadow)
{
  temp=(temp/10)*10;
}
else
intensity2=0;

if(modelvertex[modelface[i].vertex_indices[2]-1].shadow)
if(lightshadow)
{
 temp=(temp/10)*10;
}
else
 intensity3=0;


triangle t(
 point(transformedvertex1.x,transformedvertex1.y,(temp*intensity1),transformedvertex1.z),
 point(transformedvertex2.x,transformedvertex2.y,(temp*intensity2),transformedvertex2.z),
 point(transformedvertex3.x,transformedvertex3.y,(temp*intensity3),transformedvertex3.z)
   );
  //t.Createtriangle();
 t.Filltriangle();
 }
 }
 }
}
//for(int i=0;i<modelface.size();i++)
//{
// modelvertex[modelface[i].vertex_indices[0]-1].counter=0;
// modelvertex[modelface[i].vertex_indices[1]-1].counter=0;
// modelvertex[modelface[i].vertex_indices[2]-1].counter=0;
//}
}

void object::Grounddraw(vector3 Viewvector,float s,int rotx,int roty,int rotz,vector3 trans )
{
tempmatrix=Perspective(60,(SCREENWIDTH/SCREENHEIGHT),5,1000)*Viewmatrix(Viewvector,vector3(0,0,0)) *Rotatex(rotx)*Rotatey(roty)*Rotatez(rotz)* Scale(s)*Translate(trans);
Viewvector=Viewvector.Unitvector();

for(int i=0;i<modelface.size();i++)
{
  transformedvertex1=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[0]-1].x,modelvertex[modelface[i].vertex_indices[0]-1].y,modelvertex[modelface[i].vertex_indices[0]-1].z),1));
  transformedvertex2=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[1]-1].x,modelvertex[modelface[i].vertex_indices[1]-1].y,modelvertex[modelface[i].vertex_indices[1]-1].z),1));
  transformedvertex3=(tempmatrix*vector4(vector3(modelvertex[modelface[i].vertex_indices[2]-1].x,modelvertex[modelface[i].vertex_indices[2]-1].y,modelvertex[modelface[i].vertex_indices[2]-1].z),1));
  transformedvertex1.Normalizeform();
  transformedvertex2.Normalizeform();
  transformedvertex3.Normalizeform();

  n1=   modelvertex[modelface[i].vertex_indices[0]-1].pointnormal;
  n2=   modelvertex[modelface[i].vertex_indices[1]-1].pointnormal;
  n3=   modelvertex[modelface[i].vertex_indices[2]-1].pointnormal;

  if(
  Clip(transformedvertex1.x) or Clip(transformedvertex2.x) or Clip(transformedvertex3.x)
    )
  if(
     Clip(transformedvertex1.y) or Clip(transformedvertex2.y) or Clip(transformedvertex3.y)
    )
  {

{
  transformedvertex1.Todevicecoordinate();
  transformedvertex2.Todevicecoordinate();
  transformedvertex3.Todevicecoordinate();
if(((transformedvertex2.x-transformedvertex1.x)*(transformedvertex3.y-transformedvertex1.y)-(transformedvertex3.x-transformedvertex1.x)*(transformedvertex2.y-transformedvertex1.y))>0)
{




if(modelvertex[modelface[i].vertex_indices[0]-1].shadow)
intensity1=0;
else
intensity1=1;

if(modelvertex[modelface[i].vertex_indices[1]-1].shadow)
intensity2=0;
else
intensity2=1;

if(modelvertex[modelface[i].vertex_indices[2]-1].shadow)
intensity3=0;
else
intensity3=1;

triangle t(
 point(transformedvertex1.x,transformedvertex1.y,(rgb*intensity1),transformedvertex1.z),
 point(transformedvertex2.x,transformedvertex2.y,(rgb*intensity2),transformedvertex2.z),
 point(transformedvertex3.x,transformedvertex3.y,(rgb*intensity3),transformedvertex3.z)
   );
 t.Filltriangle();
 }
 }
 }
}
}



void object::Clearshadow()
{
 for(int i=0;i<modelface.size();i++)
  modelvertex[modelface[i].vertex_indices[0]-1].shadow=false;
}

