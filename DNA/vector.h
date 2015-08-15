#pragma once
#include <iostream>


//for storing normal coordinate
class vector3
{
    public:

    struct{float x,y,z;};//struct stores data continuously in memory so it is easy to access

    vector3():x(0),y(0),z(0){}
    vector3(float xx,float yy,float zz):x(xx),y(yy),z(zz){}
     bool operator==(const vector3 &p)
  {
      return ((p.x==x)&&(p.y==y)&&(p.z==z));
  }
   vector3 operator+(const vector3 p)
   {
       return vector3(x+p.x,y+p.y,z+p.z);
   }
   vector3 operator+(float f)
   {
       return vector3(x+f,y+f,z+f);
   }
   vector3 operator-(const vector3 p)
   {
       return vector3(x-p.x,y-p.y,z-p.z);
   }
   vector3 operator-(float f)
   {
       return vector3(x-f,y-f,z-f);
   }
   vector3 operator-()
   {
       return vector3(-x,-y,-z);
   }
    vector3 operator*(float f)
   {
       return vector3(x*f,y*f,z*f);
   }
    vector3 operator/(float f)
   {
       return vector3(x/f,y/f,z/f);
   }
   float  operator[] (size_t i) const
	{
		if(i>=3)
		{
			throw "index access error";
		}
		return (&x)[i];//return variable of struct for reading
	}

	float & operator[] (size_t i)//returns variable of struct for writing
	{
		if(i>=3)
		{
			throw "index access error";
		}
		return (&x)[i];
	}
	vector3 Unitvector()
	{
	    float length =sqrtf(x*x+y*y+z*z);
	    return vector3(x/length,y/length,z/length);
	}
   float Dotproduct(const vector3& p)const
	{
	    return (x*p.x+y*p.y+z*p.z);
	}
       vector3 Crossproduct( const vector3& b)
	{
		return vector3(
				y * b.z - b.y * z,
				z * b.x - b.z * x,
				x * b.y - b.x * y
				);
	}


};


//for storing homogenous world coordinate
class vector4
{
   public:

    struct{float x,y,z,h;};

    vector4():x(0),y(0),z(0),h(1){}
    vector4(float xx,float yy,float zz,float hh=1):x(xx),y(yy),z(zz),h(hh){}
    vector4(vector3 v,float hh=1):x(v.x),y(v.y),z(v.z),h(hh){}
     bool operator==(const vector4 &p)
  {
      return ((p.x==x)&&(p.y==y)&&(p.z==z)&&(p.h==h));
  }
  vector4 operator+(const vector4 &p)
   {
       return vector4(x+p.x,y+p.y,z+p.z,h+p.h);
   }
   vector4 operator+(float f)
   {
       return vector4(x+f,y+f,z+f,h+f);
   }
   vector4 operator-(const vector4& p)
   {
       return vector4(x-p.x,y-p.y,z-p.z,h-p.h);
   }
   vector4 operator-(float f)
   {
       return vector4(x-f,y-f,z-f,h-f);
   }
   vector4 operator-()
   {
       return vector4(-x,-y,-z,-h);
   }
    vector4 operator*(float f)
   {
       return vector4(x*f,y*f,z*f,h*f);
   }
    vector4 operator/(float f)
   {
       return vector4(x/f,y/f,z/f,h/f);
   }
     float& operator[] (size_t i)
    {
        return (&x)[i];
    }
    float operator[] (size_t i) const
    {
        return (&x)[i];
    }
   float Length()
   {
       return sqrtf(x*x+y*y+z*z);
   }
   vector3 Unitvector()
   {
       if(Length()!=0)
     {
         return vector3(x/Length(),
     y/Length(),
     z/Length());
     }
     else
     std::cout<<"length=0"<<std::endl;
   }
   void Normalizeform()//used after perspective projection because there is change in h
   {
       if (h!=0 )
    {
     x=x/h;
     y=y/h;
     z=z/h;
     h=h/h;
    }
   }
   void Todevicecoordinate()//after perspective projection coordinates are taken to device coordinate form
   {
       x= (SCREENWIDTH/2)*x;
       y=(SCREENHEIGHT/2)*y;
   }
   vector3 Tovector3()
   {
     return  vector3(x/h,y/h,z/h);
   }

    float Dotproduct(const vector4& p)
	{
	    return (x*p.x+y*p.y+z*p.z);
	}


};
