#pragma once

#include "vector.h"

class matrix3
{
    public:
    float mat[3][3];

    matrix3(float temp=1.0f)
    {
      (*this)[0]=vector3(temp,0,0);
      (*this)[1]=vector3(0,temp,0);
      (*this)[2]=vector3(0,0,temp);
    }
    matrix3(const vector3& v0,const vector3& v1, const vector3& v2)
    {
        (*this)[0]=v0;
        (*this)[1]=v1;
        (*this)[2]=v2;
    }
      matrix3(float m11, float m12, float m13,
         float m21, float m22, float m23,
         float m31, float m32, float m33)
    {
        mat[0][0] = m11; mat[0][1] = m12; mat[0][2] = m13;
        mat[1][0] = m21; mat[1][1] = m22; mat[1][2] = m23;
        mat[2][0] = m31; mat[2][1] = m32; mat[2][2] = m33;
    }
      vector3& operator[] (int n)
    {
        return *((vector3*)&mat[n]);
    }

    vector3& operator[] (int n) const
    {
        return *((vector3*)&mat[n]);
    }

    matrix3 operator+ (const matrix3& m) const
    {
        return matrix3(
            mat[0][0] + m.mat[0][0], mat[0][1] + m.mat[0][1], mat[0][2] + m.mat[0][2],
            mat[1][0] + m.mat[1][0], mat[1][1] + m.mat[1][1], mat[1][2] + m.mat[1][2],
            mat[2][0] + m.mat[2][0], mat[2][1] + m.mat[2][1], mat[2][2] + m.mat[2][2]
        );
    }

    matrix3 operator- (const matrix3& m) const
    {
        return matrix3(
            mat[0][0] - m.mat[0][0], mat[0][1] - m.mat[0][1], mat[0][2] - m.mat[0][2],
            mat[1][0] - m.mat[1][0], mat[1][1] - m.mat[1][1], mat[1][2] - m.mat[1][2],
            mat[2][0] - m.mat[2][0], mat[2][1] - m.mat[2][1], mat[2][2] - m.mat[2][2]
        );
    }

    matrix3 operator* (const matrix3& m) const
    {
        return matrix3(
            (mat[0][0]*m.mat[0][0] + mat[0][1]*m.mat[1][0] + mat[0][2]*m.mat[2][0]),
            (mat[0][0]*m.mat[0][1] + mat[0][1]*m.mat[1][1] + mat[0][2]*m.mat[2][1]),
            (mat[0][0]*m.mat[0][2] + mat[0][1]*m.mat[1][2] + mat[0][2]*m.mat[2][2]),
            (mat[1][0]*m.mat[0][0] + mat[1][1]*m.mat[1][0] + mat[1][2]*m.mat[2][0]),
            (mat[1][0]*m.mat[0][1] + mat[1][1]*m.mat[1][1] + mat[1][2]*m.mat[2][1]),
            (mat[1][0]*m.mat[0][2] + mat[1][1]*m.mat[1][2] + mat[1][2]*m.mat[2][2]),
            (mat[2][0]*m.mat[0][0] + mat[2][1]*m.mat[1][0] + mat[2][2]*m.mat[2][0]),
            (mat[2][0]*m.mat[0][1] + mat[2][1]*m.mat[1][1] + mat[2][2]*m.mat[2][1]),
            (mat[2][0]*m.mat[0][2] + mat[2][1]*m.mat[1][2] + mat[2][2]*m.mat[2][2])
        );
    }
    vector3 operator* (const vector3& v) const
    {
        return vector3(
            (mat[0][0]*v.x + mat[0][1]*v.y + mat[0][2]*v.z),
            (mat[1][0]*v.x + mat[1][1]*v.y + mat[1][2]*v.z),
            (mat[2][0]*v.x + mat[2][1]*v.y + mat[2][2]*v.z)
        );
    }
    matrix3 operator* (float f) const
    {
        return matrix3(
            mat[0][0]*f, mat[0][1]*f, mat[0][2]*f,
            mat[1][0]*f, mat[1][1]*f, mat[1][2]*f,
            mat[2][0]*f, mat[2][1]*f, mat[2][2]*f
                  );
    }




};
class matrix4
{
    public:
  float mat[4][4];
  matrix4(const vector4& v0,const vector4& v1,const vector4& v2,const vector4 &v3)
  {
      (*this)[0]=v0;
      (*this)[1]=v1;
      (*this)[2]=v2;
      (*this)[3]=v3;
  }
  matrix4(float temp=1.0f)
  {
      (*this)[0]=vector4(temp,0,0,0);
      (*this)[1]=vector4(0,temp,0,0);
      (*this)[2]=vector4(0,0,temp,0);
      (*this)[3]=vector4(0,0,0,temp);
  }
 matrix4(const matrix3& m)
 {
     (*this)[0]=vector4(m[0],0);
     (*this)[1]=vector4(m[1],0);
     (*this)[2]=vector4(m[2],0);
     (*this)[3]=vector4(0,0,0,1);
 }
 matrix4(float m11, float m12, float m13, float m14,
         float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34,
         float m41, float m42, float m43, float m44)
    {
        mat[0][0] = m11; mat[0][1] = m12; mat[0][2] = m13; mat[0][3] = m14;
        mat[1][0] = m21; mat[1][1] = m22; mat[1][2] = m23; mat[1][3] = m24;
        mat[2][0] = m31; mat[2][1] = m32; mat[2][2] = m33; mat[2][3] = m34;
        mat[3][0] = m41; mat[3][1] = m42; mat[3][2] = m43; mat[3][3] = m44;
    }

    vector4& operator[] (int n)
    {
        return *((vector4*)&mat[n]);
    }

    const vector4& operator[] (int n) const
    {
        return *((vector4*)&mat[n]);
    }
     operator matrix3() const
    {
        return matrix3(
            mat[0][0], mat[0][1], mat[0][2],
            mat[1][0], mat[1][1], mat[1][2],
            mat[2][0], mat[2][1], mat[2][2]
                   );
    }
      matrix4 operator* (const matrix4& m) const
    {
        return matrix4(
            (mat[0][0]*m.mat[0][0] + mat[0][1]*m.mat[1][0] + mat[0][2]*m.mat[2][0] + mat[0][3]*m.mat[3][0]),
            (mat[0][0]*m.mat[0][1] + mat[0][1]*m.mat[1][1] + mat[0][2]*m.mat[2][1] + mat[0][3]*m.mat[3][1]),
            (mat[0][0]*m.mat[0][2] + mat[0][1]*m.mat[1][2] + mat[0][2]*m.mat[2][2] + mat[0][3]*m.mat[3][2]),
            (mat[0][0]*m.mat[0][3] + mat[0][1]*m.mat[1][3] + mat[0][2]*m.mat[2][3] + mat[0][3]*m.mat[3][3]),
            (mat[1][0]*m.mat[0][0] + mat[1][1]*m.mat[1][0] + mat[1][2]*m.mat[2][0] + mat[1][3]*m.mat[3][0]),
            (mat[1][0]*m.mat[0][1] + mat[1][1]*m.mat[1][1] + mat[1][2]*m.mat[2][1] + mat[1][3]*m.mat[3][1]),
            (mat[1][0]*m.mat[0][2] + mat[1][1]*m.mat[1][2] + mat[1][2]*m.mat[2][2] + mat[1][3]*m.mat[3][2]),
            (mat[1][0]*m.mat[0][3] + mat[1][1]*m.mat[1][3] + mat[1][2]*m.mat[2][3] + mat[1][3]*m.mat[3][3]),
            (mat[2][0]*m.mat[0][0] + mat[2][1]*m.mat[1][0] + mat[2][2]*m.mat[2][0] + mat[2][3]*m.mat[3][0]),
            (mat[2][0]*m.mat[0][1] + mat[2][1]*m.mat[1][1] + mat[2][2]*m.mat[2][1] + mat[2][3]*m.mat[3][1]),
            (mat[2][0]*m.mat[0][2] + mat[2][1]*m.mat[1][2] + mat[2][2]*m.mat[2][2] + mat[2][3]*m.mat[3][2]),
            (mat[2][0]*m.mat[0][3] + mat[2][1]*m.mat[1][3] + mat[2][2]*m.mat[2][3] + mat[2][3]*m.mat[3][3]),
            (mat[3][0]*m.mat[0][0] + mat[3][1]*m.mat[1][0] + mat[3][2]*m.mat[2][0] + mat[3][3]*m.mat[3][0]),
            (mat[3][0]*m.mat[0][1] + mat[3][1]*m.mat[1][1] + mat[3][2]*m.mat[2][1] + mat[3][3]*m.mat[3][1]),
            (mat[3][0]*m.mat[0][2] + mat[3][1]*m.mat[1][2] + mat[3][2]*m.mat[2][2] + mat[3][3]*m.mat[3][2]),
            (mat[3][0]*m.mat[0][3] + mat[3][1]*m.mat[1][3] + mat[3][2]*m.mat[2][3] + mat[3][3]*m.mat[3][3])
        );
    }
    vector4 operator* (const vector4& v) const
    {
        return vector4(
            (mat[0][0]*v.x + mat[0][1]*v.y + mat[0][2]*v.z + mat[0][3]*v.h),
            (mat[1][0]*v.x + mat[1][1]*v.y + mat[1][2]*v.z + mat[1][3]*v.h),
            (mat[2][0]*v.x + mat[2][1]*v.y + mat[2][2]*v.z + mat[2][3]*v.h),
            (mat[3][0]*v.x + mat[3][1]*v.y + mat[3][2]*v.z + mat[3][3]*v.h)
        );
    }
    matrix4 operator* (float f) const
    {
        return matrix4(
            mat[0][0]*f, mat[0][1]*f, mat[0][2]*f, mat[0][3]*f,
            mat[1][0]*f, mat[1][1]*f, mat[1][2]*f, mat[1][3]*f,
            mat[2][0]*f, mat[2][1]*f, mat[2][2]*f, mat[2][3]*f,
            mat[3][0]*f, mat[3][1]*f, mat[3][2]*f, mat[3][3]*f
        );
    }
};
//overload << for 3x3 matrix
inline std::ostream& operator << (std::ostream &os, const matrix3 &m)
{
    for (int i=0; i<3; ++i)
    {
        os << std::endl;
        for (int j=0; j<3; ++j)
            os << m.mat[i][j] << "  ";
    }
    return os;
}

//overload << for 4x4 matrix
inline std::ostream& operator << (std::ostream &os, const matrix4 &m)
{
    for (int i=0; i<4; ++i)
    {
        os << std::endl;
        for (int j=0; j<4; ++j)
            os << m.mat[i][j] << "  ";
    }
    return os;
}
