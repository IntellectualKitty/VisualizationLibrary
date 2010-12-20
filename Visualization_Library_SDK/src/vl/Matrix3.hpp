/**************************************************************************************/
/*                                                                                    */
/*  Visualization Library                                                             */
/*  http://www.visualizationlibrary.com                                               */
/*                                                                                    */
/*  Copyright (c) 2005-2010, Michele Bosi                                             */
/*  All rights reserved.                                                              */
/*                                                                                    */
/*  Redistribution and use in source and binary forms, with or without modification,  */
/*  are permitted provided that the following conditions are met:                     */
/*                                                                                    */
/*  - Redistributions of source code must retain the above copyright notice, this     */
/*  list of conditions and the following disclaimer.                                  */
/*                                                                                    */
/*  - Redistributions in binary form must reproduce the above copyright notice, this  */
/*  list of conditions and the following disclaimer in the documentation and/or       */
/*  other materials provided with the distribution.                                   */
/*                                                                                    */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND   */
/*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED     */
/*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE            */
/*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR  */
/*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES    */
/*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      */
/*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON    */
/*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT           */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS     */
/*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      */
/*                                                                                    */
/**************************************************************************************/

#ifndef Matrix3_INCLUDE_ONCE
#define Matrix3_INCLUDE_ONCE

#include <vl/Vector3.hpp>
#include <vl/Matrix2.hpp>

namespace vl
{
  //-----------------------------------------------------------------------------
  // Matrix3
  //-----------------------------------------------------------------------------
  /**
   * The Matrix3 class is a template class that implements a generic 3x3 matrix, see also vl::dmat3, vl::fmat3, vl::umat3, vl::imat3.
   * \sa Vector4, Vector3, Vector2, Matrix4, Matrix2
   */
  template<typename T_scalar>
  class Matrix3
  {
  public:
    typedef T_scalar scalar_type;
    //-----------------------------------------------------------------------------
    template<typename T>
    explicit Matrix3(const T& m)
    {
      e(0,0) = (T_scalar)m.e(0,0); e(1,0) = (T_scalar)m.e(1,0); e(2,0) = (T_scalar)m.e(2,0);
      e(0,1) = (T_scalar)m.e(0,1); e(1,1) = (T_scalar)m.e(1,1); e(2,1) = (T_scalar)m.e(2,1);
      e(0,2) = (T_scalar)m.e(0,2); e(1,2) = (T_scalar)m.e(1,2); e(2,2) = (T_scalar)m.e(2,2);
    }
    //-----------------------------------------------------------------------------
    Matrix3()
    {
      setIdentity();
    }
    //-----------------------------------------------------------------------------
    Matrix3(T_scalar n)
    {
      setIdentity();
      e(0,0) = n; e(1,1) = n; e(2,2) = n;
    }
    //-----------------------------------------------------------------------------
    explicit Matrix3( T_scalar e00, T_scalar e01, T_scalar e02,
                      T_scalar e10, T_scalar e11, T_scalar e12,
                      T_scalar e20, T_scalar e21, T_scalar e22 )
    {
      e(0,0) = e00; e(1,0) = e01; e(2,0) = e02; 
      e(0,1) = e10; e(1,1) = e11; e(2,1) = e12; 
      e(0,2) = e20; e(1,2) = e21; e(2,2) = e22; 
    }
    //-----------------------------------------------------------------------------
    Matrix3& fill(T_scalar val)
    {
      e(0,0) = e(1,0) = e(2,0) = 
      e(0,1) = e(1,1) = e(2,1) = 
      e(0,2) = e(1,2) = e(2,2) = val;
      return *this;
    }
    //-----------------------------------------------------------------------------
    T_scalar diff(const Matrix3& other)
    {
      T_scalar err = 0;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          if ( e(j,i) > other.e(j,i) ) // avoid fabs/abs
            err += e(j,i) - other.e(j,i);
          else
            err += other.e(j,i) - e(j,i);
      return err;
    }
    //-----------------------------------------------------------------------------
    Vector2<T_scalar> getX() const
    {
      Vector2<T_scalar> v;
      v.x() = e(0,0);
      v.y() = e(1,0);
      return v;
    }
    //-----------------------------------------------------------------------------
    Vector2<T_scalar> getY() const
    {
      Vector2<T_scalar> v;
      v.x() = e(0,1);
      v.y() = e(1,1);
      return v;
    }
    //-----------------------------------------------------------------------------
    Vector2<T_scalar> getT() const
    {
      Vector2<T_scalar> v;
      v.x() = e(0,2);
      v.y() = e(1,2);
      return v;
    }
    //-----------------------------------------------------------------------------
    Matrix3& setX(const Vector2<T_scalar>& v) 
    {
      e(0,0) = v.x();
      e(1,0) = v.y();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3& setY(const Vector2<T_scalar>& v) 
    {
      e(0,1) = v.x();
      e(1,1) = v.y();
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3& setT(const Vector2<T_scalar>& v) 
    {
      e(0,2) = v.x();
      e(1,2) = v.y();
      return *this;
    }
    //-----------------------------------------------------------------------------
    bool operator==(const Matrix3& m) const 
    {
      return memcmp(m.mVec, mVec, sizeof(T_scalar)*9) == 0;
    }
    //-----------------------------------------------------------------------------
    bool operator!=(const Matrix3& m) const 
    {
      return !operator==(m);
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator=(const Matrix3& m) 
    {
      memcpy(mVec, m.mVec, sizeof(T_scalar)*9);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator+(const Matrix3& m) const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) + m[i][j];

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator+=(const Matrix3& m)
    {
      return *this = *this + m;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator-(const Matrix3& m) const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) - m[i][j];

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator-=(const Matrix3& m)
    {
      return *this = *this - m;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator*=(const Matrix3& m)
    {
      return *this = *this * m;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator-() const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = -e(j,i);

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator+(T_scalar d) const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) + d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator+=(T_scalar d)
    {
      return *this = *this + d;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator-(T_scalar d) const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) - d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator-=(T_scalar d)
    {
      return *this = *this - d;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator*(T_scalar d) const
    {
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) * d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator*=(T_scalar d)
    {
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          e(j,i) *= d;

      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3 operator/(T_scalar d) const
    {
      d = (T_scalar)1 / d;
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          t[i][j] = e(j,i) * d;

      return t;
    }
    //-----------------------------------------------------------------------------
    Matrix3& operator/=(T_scalar d)
    {
      d = (T_scalar)1 / d;
      Matrix3 t;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          e(j,i) *= d;

      return *this;
    }
    //-----------------------------------------------------------------------------
    bool isIdentity() const
    {
      Matrix3 i;
      return memcmp( ptr(), i.ptr(), sizeof(T_scalar)*9 ) == 0;
    }
    //-----------------------------------------------------------------------------
    Matrix2<T_scalar> get2x2() const
    {
      Matrix2<T_scalar> t;
      t.e(0,0) = e(0,0); t.e(1,0) = e(1,0);
      t.e(0,1) = e(0,1); t.e(1,1) = e(1,1);
      return t;
    }
    //-----------------------------------------------------------------------------
    //! This writes only on the upper 2x2 part of the matrix without touching the last row and column. 
    void set2x2(const Matrix2<T_scalar>& m)
    {
      e(0,0) = m.e(0,0); e(1,0) = m.e(1,0);
      e(0,1) = m.e(0,1); e(1,1) = m.e(1,1);
    }
    //-----------------------------------------------------------------------------
    T_scalar* ptr()
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    const T_scalar* ptr() const
    {
      return &e(0,0);
    }
    //-----------------------------------------------------------------------------
    Matrix3& transpose()
    {
      T_scalar tmp;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
        {
          tmp = e(j,i);
          e(j,i) = e(i,j);
          e(i,j) = tmp;
        }
        return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3 getTransposed() const
    {
      Matrix3 m;
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          m.e(j,i) = e(i,j);
      return m;
    }
    //-----------------------------------------------------------------------------
    Matrix3& getTransposed(Matrix3& dest) const
    {
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          dest.e(j,i) = e(i,j);
      return dest;
    }
    //-----------------------------------------------------------------------------
    bool isNull() const
    {
      for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
          if( mVec[j][i] != 0 )
            return false;
      return true;
    }
    //-----------------------------------------------------------------------------
    Matrix3& setNull() 
    {
      fill(0);
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix3& getNull(Matrix3& out)
    {
      out.fill(0);
      return out;
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getNull()
    {
      return Matrix3().fill(0);
    }
    //-----------------------------------------------------------------------------
    Matrix3& setIdentity()
    {
      static const T_scalar I3d[] = 
      { 
        (T_scalar)1, (T_scalar)0, (T_scalar)0,  
        (T_scalar)0, (T_scalar)1, (T_scalar)0, 
        (T_scalar)0, (T_scalar)0, (T_scalar)1, 
      };
      memcpy( mVec, I3d, sizeof(T_scalar)*9 );
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getIdentity()
    {
      return Matrix3();
    }
    //-----------------------------------------------------------------------------
    static Matrix3& getIdentity(Matrix3& out)
    {
      out.setIdentity();
      return out;
    }
    //-----------------------------------------------------------------------------
    T_scalar getInverse(Matrix3& dest) const;
    //-----------------------------------------------------------------------------
    Matrix3 getInverse(T_scalar *determinant=NULL) const
    {
      Matrix3 tmp;
      T_scalar det = getInverse(tmp);
      if (determinant)
        *determinant = det;
      return tmp;
    }
    //-----------------------------------------------------------------------------
    Matrix3& invert(T_scalar *determinant=NULL)
    {
      T_scalar det = getInverse(*this);
      if (determinant)
        *determinant = det;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getRotation( T_scalar degrees );
    //-----------------------------------------------------------------------------
    Matrix3& rotate( T_scalar degrees )
    {
      *this = getRotation(degrees) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getTranslation( const Vector2<T_scalar>& v )
    {
      return getTranslation( v.x(), v.y() );
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getTranslation( T_scalar x, T_scalar y )
    {
      Matrix3 tr;
      tr.e(0,2) = x;
      tr.e(1,2) = y;
      return tr;
    }
    //-----------------------------------------------------------------------------
    Matrix3& translate( T_scalar x, T_scalar y )
    {
      *this = *this * getTranslation(x,y);
      return *this;
    }
    //-----------------------------------------------------------------------------
    Matrix3& translate( const Vector2<T_scalar>& v )
    {
      *this = getTranslation(v) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------
    static Matrix3 getScaling( T_scalar x, T_scalar y )
    {
      Matrix3 sc;
      sc.e(0,0) = x;
      sc.e(1,1) = y;
      return sc;
    }
    //-----------------------------------------------------------------------------
    Matrix3& scale( T_scalar x, T_scalar y )
    {
      *this = getScaling(x,y) * *this;
      return *this;
    }
    //-----------------------------------------------------------------------------

    const T_scalar& e(int i, int j) const { return mVec[j][i]; }
    T_scalar& e(int i, int j) { return mVec[j][i]; }

  private:
    const Vector3<T_scalar>& operator[](unsigned int i) const { VL_CHECK(i<3); return mVec[i]; }
    Vector3<T_scalar>& operator[](unsigned int i) { VL_CHECK(i<3); return mVec[i]; }

  protected:
    Vector3<T_scalar> mVec[3];
  };

  //-----------------------------------------------------------------------------
  // OPERATORS
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix3<T_scalar> operator*(const Matrix3<T_scalar>& m2, const Matrix3<T_scalar>& m1)
  {
    Matrix3<T_scalar> t;
    t.e(0,0) = m1.e(0,0)*m2.e(0,0) + m1.e(1,0)*m2.e(0,1) + m1.e(2,0)*m2.e(0,2);
    t.e(0,1) = m1.e(0,1)*m2.e(0,0) + m1.e(1,1)*m2.e(0,1) + m1.e(2,1)*m2.e(0,2);
    t.e(0,2) = m1.e(0,2)*m2.e(0,0) + m1.e(1,2)*m2.e(0,1) + m1.e(2,2)*m2.e(0,2);

    t.e(1,0) = m1.e(0,0)*m2.e(1,0) + m1.e(1,0)*m2.e(1,1) + m1.e(2,0)*m2.e(1,2);
    t.e(1,1) = m1.e(0,1)*m2.e(1,0) + m1.e(1,1)*m2.e(1,1) + m1.e(2,1)*m2.e(1,2);
    t.e(1,2) = m1.e(0,2)*m2.e(1,0) + m1.e(1,2)*m2.e(1,1) + m1.e(2,2)*m2.e(1,2);

    t.e(2,0) = m1.e(0,0)*m2.e(2,0) + m1.e(1,0)*m2.e(2,1) + m1.e(2,0)*m2.e(2,2);
    t.e(2,1) = m1.e(0,1)*m2.e(2,0) + m1.e(1,1)*m2.e(2,1) + m1.e(2,1)*m2.e(2,2);
    t.e(2,2) = m1.e(0,2)*m2.e(2,0) + m1.e(1,2)*m2.e(2,1) + m1.e(2,2)*m2.e(2,2);

    return t;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix3<T_scalar> operator+(T_scalar d, const Matrix3<T_scalar>& m)
  {
    return m + d;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  inline Matrix3<T_scalar> operator*(T_scalar d, const Matrix3<T_scalar>& m)
  {
    return m * d;
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  template<typename T_scalar>
  inline Vector3<T_scalar> operator*(const Matrix3<T_scalar>& m, const Vector3<T_scalar>& v)
  {
    Vector3<T_scalar> t;
    t.x() = v.x()*m.e(0,0) + v.y()*m.e(0,1) + v.z()*m.e(0,2);
    t.y() = v.x()*m.e(1,0) + v.y()*m.e(1,1) + v.z()*m.e(1,2);
    t.z() = v.x()*m.e(2,0) + v.y()*m.e(2,1) + v.z()*m.e(2,2);
    return t;
  }
  //-----------------------------------------------------------------------------
  //! Post multiplication: matrix * column vector
  //! The incoming vector is considered a Vector3<T_scalar> with the component z = 0
  template<typename T_scalar>
  inline Vector2<T_scalar> operator*(const Matrix3<T_scalar>& m, const Vector2<T_scalar>& v)
  {
    Vector2<T_scalar> t;
    t.x() = v.x()*m.e(0,0) + v.y()*m.e(0,1) /*+ 0*m.e(0,2)*/;
    t.y() = v.x()*m.e(1,0) + v.y()*m.e(1,1) /*+ 0*m.e(1,2)*/;
    return t;
  }
  //-----------------------------------------------------------------------------
  //! pre-multiplication: row vector * matrix
  template<typename T_scalar>
  inline Vector3<T_scalar> operator*(const Vector3<T_scalar>& v, const Matrix3<T_scalar>& m)
  {
    Vector3<T_scalar> t;
    t.x() = v.x()*m.e(0,0) + v.y()*m.e(1,0) + v.z()*m.e(2,0);
    t.y() = v.x()*m.e(0,1) + v.y()*m.e(1,1) + v.z()*m.e(2,1);
    t.z() = v.x()*m.e(0,2) + v.y()*m.e(1,2) + v.z()*m.e(2,2);
    return t;
  }
  //-----------------------------------------------------------------------------
  //! pre-multiplication: row vector * matrix
  //! The incoming vector is considered a Vector3<T_scalar> with the component z = 0
  template<typename T_scalar>
  inline Vector2<T_scalar> operator*(const Vector2<T_scalar>& v, const Matrix3<T_scalar>& m)
  {
    Vector2<T_scalar> t;
    t.x() = v.x()*m.e(0,0) + v.y()*m.e(1,0) /*+ 0*m.e(2,0)*/;
    t.y() = v.x()*m.e(0,1) + v.y()*m.e(1,1) /*+ 0*m.e(2,1)*/;
    return t;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  Matrix3<T_scalar> Matrix3<T_scalar>::getRotation( T_scalar degrees )
  {
    Matrix3<T_scalar> rot;
    degrees = degrees * (T_scalar)dDEG_TO_RAD;
    T_scalar s = (T_scalar) sin( degrees );
    T_scalar c = (T_scalar) cos( degrees );
    rot.e(0,0) = (T_scalar)c;
    rot.e(1,1) = (T_scalar)c;
    rot.e(1,0) = (T_scalar)s;
    rot.e(0,1) = -(T_scalar)s;
    return rot;
  }
  //-----------------------------------------------------------------------------
  template<typename T_scalar>
  T_scalar Matrix3<T_scalar>::getInverse(Matrix3<T_scalar>& dest) const
  {
    if (&dest == this)
    {
      Matrix3<T_scalar> tmp;
      T_scalar det = getInverse(tmp);
      dest = tmp;
      return det;
    }
    else
    {
      const T_scalar& a11 = e(0,0);
      const T_scalar& a12 = e(1,0);
      const T_scalar& a13 = e(2,0);
      const T_scalar& a21 = e(0,1);
      const T_scalar& a22 = e(1,1);
      const T_scalar& a23 = e(2,1);
      const T_scalar& a31 = e(0,2);
      const T_scalar& a32 = e(1,2);
      const T_scalar& a33 = e(2,2);

      T_scalar A = a33*a22-a32*a23;
      T_scalar B = a32*a13-a33*a12;
      T_scalar C = a23*a12-a22*a13;

      T_scalar det = a11*(A)+a21*(B)+a31*(C);

      if ( det == 0 )
      {
        dest.fill(0);
      }
      else
      {
        dest = Matrix3<T_scalar>( A,               B,               C, 
                                       a31*a23-a33*a21, a33*a11-a31*a13, a21*a13-a23*a11,
                                       a32*a21-a31*a22, a31*a12-a32*a11, a22*a11-a21*a12) / det;
      }

      return det;
    }
  }
  //-----------------------------------------------------------------------------

  //! A 3x3 matrix using \p GLdouble precision.
  typedef Matrix3<GLdouble> dmat3;
  //! A 3x3 matrix using \p GLfloat precision.
  typedef Matrix3<GLfloat>  fmat3;
  //! A 3x3 matrix using \p GLint precision.
  typedef Matrix3<GLint>    imat3;
  //! A 3x3 matrix using \p GLuint precision.
  typedef Matrix3<GLuint>  umat3;

  #if VL_PIPELINE_PRECISION == 2
    //! Defined as: \p 'typedef \p dmat3 \p mat3'. See also \ref VL_PIPELINE_PRECISION.
    typedef dmat3 mat3;
  #else
    //! Defined as: \p 'typedef \p fmat3 \p mat3'. See also \ref VL_PIPELINE_PRECISION.
    typedef fmat3 mat3;
  #endif
}

#endif
