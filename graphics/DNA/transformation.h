#pragma once

#include"matrix.h"
#include<iostream>
#include<cmath>
#define PI 3.14159265359

inline matrix4 Translate(const vector3& v)
{
    return matrix4(
        1.0f, 0.0f, 0.0f, v.x,
        0.0f, 1.0f, 0.0f, v.y,
        0.0f, 0.0f, 1.0f, v.z,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

inline matrix4 Scale(float scale)
{
    return matrix4(
        scale, 0, 0, 0,
        0, scale, 0, 0,
        0, 0, scale, 0,
        0, 0, 0, 1
    );
}

inline matrix4 Scale(const vector3& v)
{
    return matrix4(
        v.x, 0, 0, 0,
        0, v.y, 0, 0,
        0, 0, v.z, 0,
        0, 0, 0, 1
    );
}

inline matrix4 Fixedscale(const vector3& scale, const vector3& fixedpoint)
	{
		return matrix4(
					scale.x, 0, 0, (1-scale.x)*fixedpoint.x,
					0, scale.y, 0, (1-scale.y)*fixedpoint.y,
					0, 0, scale.z, (1-scale.z)*fixedpoint.z,
					0, 0, 0, 1
					);
	}

inline matrix4 Rotatex(float angle)
{
     angle=(PI/180)*angle;
    return matrix4(
        1, 0, 0, 0,
        0, cosf(angle), -sinf(angle), 0,
        0, sinf(angle), cosf(angle), 0,
        0, 0, 0, 1
    );
}
inline matrix4 Rotatey(float angle)
{
     angle=(PI/180)*angle;
    return matrix4(
        cosf(angle), 0, sinf(angle), 0,
        0, 1, 0, 0,
        -sinf(angle), 0, cosf(angle), 0,
        0, 0, 0, 1
    );
}

inline matrix4 Rotatez(float angle)
	{
	    angle=(PI/180)*angle;
		return matrix4(
					cosf(angle), -sinf(angle), 0, 0,
					sinf(angle), cosf(angle), 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
					);
	}

//fov=field of view (angle) aspect ratio=width/height
inline matrix4 Perspective(float fov, float aspect, float near, float far)
{
    fov=(PI/180)*fov;//doubt over here
    float temp = 1.0f / tanf(0.5f * fov);
    return matrix4(
        temp/aspect, 0, 0, 0,
        0, temp, 0, 0,
        0, 0, (far+near)/(near-far), (2*far*near)/(near-far),
        0, 0, -1.0f, 0
    );
}
matrix4 Viewmatrix(vector3 position, vector3 target,vector3 upvector=vector3(0,1,0))
{
    vector3 n=position-target;
    n=n.Unitvector();
    vector3 v=upvector;
    v=v.Unitvector();
    matrix4 translation=Translate(-(position));
    vector3 u=v.Crossproduct(n);
    u=u.Unitvector();
    v=n.Crossproduct(u);
    v=v.Unitvector();
    matrix4 alignrotation(vector4(u,0),vector4(v,0),vector4(n,0),vector4(0,0,0,1));
    std::cout<<"aksdfksjfkl"<<alignrotation<<std::endl;
    return (alignrotation*translation);
}
