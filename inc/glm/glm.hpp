#ifndef __glm_hpp__
#define __glm_hpp__

#include "sys/sys.hpp"

#include <cmath>

namespace glm {
#ifdef GLM_DOUBLE_PRECISION
  typedef double real;
#else
  typedef float real;
#endif
  
  using byte   = sys::byte;
  using ubyte  = sys::ubyte;
  using tiny   = sys::tiny;
  using utiny  = sys::utiny;
  using ushort = sys::ushort;
  using uint   = sys::uint;
  using ulong  = sys::ulong;
  
  template <typename T, ushort cols, ushort rows> class CMatrix;
  
  template <typename T, ushort size> class CVector;

  template <typename T> class CQuaterion;
  
  typedef CMatrix<float, 4, 4>  mat4;
  typedef CMatrix<float, 4, 3>  mat4x3;
  typedef CMatrix<float, 3, 3>  mat3;
  typedef CMatrix<float, 2, 2>  mat2;
  typedef CMatrix<double, 4, 4> dmat4;
  typedef CMatrix<double, 4, 3> dmat4x3;
  typedef CMatrix<double, 3, 3> dmat3;
  typedef CMatrix<double, 2, 2> dmat2;
  
  typedef CVector<float, 4>   vec4;
  typedef CVector<float, 3>   vec3;
  typedef CVector<float, 2>   vec2;  
  typedef CVector<double, 4> dvec4;
  typedef CVector<double, 3> dvec3;
  typedef CVector<double, 2> dvec2;
  typedef CVector<int, 4>    ivec4;
  typedef CVector<int, 3>    ivec3;
  typedef CVector<int, 2>    ivec2;
  typedef CVector<uint, 4>   uvec4;
  typedef CVector<uint, 3>   uvec3;
  typedef CVector<uint, 2>   uvec2;
  typedef CVector<bool, 4>   bvec4;
  typedef CVector<bool, 3>   bvec3;
  typedef CVector<bool, 2>   bvec2;
  
  typedef CQuaterion<float>   quat;
  typedef CQuaterion<double> dquat;
  typedef CQuaterion<int>    iquat;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> struct SRange {
    T min;
    T max;
  };
  
  template <typename T> void swap(T& lhs, T& rhs) { T tmp = lhs; lhs = rhs; rhs = tmp; }
  
  inline real loop(real& fVal, real fStep = 0.1f, real fFirst = -1.0f, real fLast = 1.0f) {
    bool bRevRange = fLast < fFirst;
    bool bRevStep  = fStep < 0.0f;
    int dir = 1;
    bRevRange && (dir *= -1);
    bRevStep  && (dir *= -1);
    // @todo: fix this for reverse cases
      // loop(val,-0.1f, -1.0f,+1.0f)
      // loop(val,-0.1f, +1.0f,-1.0f)
      // loop(val, 0.1f, +1.0f,-1.0f)
    fVal = fVal + dir * fStep;
    fVal = fVal > fLast ? fFirst : fVal;
    return fVal;
  }
  
  template <typename T> inline T log2(T value) { return static_cast<T>(std::log2(value)); }
  
  template <typename T> inline T floor(T value) { return static_cast<T>(std::floor(value)); }
  
  template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
  
  template <typename T> inline T max(T a, T b) { return a >= b ? a : b; }
  
  // @todo: glm::epsilon
    // std::numeric_limits<T>::epsilon()
  
  
  // OGL is RightHanded + Negative Z
  
  // @todo glm::refract
  // @todo glm::abs
  // @todo glm::sign
  // @todo glm::floor
  // @todo glm::ceil
  // @todo glm::fract // fraction
  // @todo glm::mod   // modulus, reminder
  // @todo glm::min
  // @todo glm::max
  // @todo glm::clamp
  // @todo glm::step  // 
  // @todo glm::sstep // smoothstep
  // @todo glm::mix   // linear blend
  // @todo glm::lerp  // linear interpolation
  // @todo glm::slerp // spherical linear interpolation
  // @todo glm::isnan
  // @todo glm::isinf
  // @todo glm::pow
  // @todo glm::exp
  // @todo glm::log
  // @todo glm::sqrt
  // @todo glm::isqrt OR rsqrt
  
  // @todo glm::eq
  // @todo glm::gt
  // @todo glm::gte
  // @todo glm::lt
  // @todo glm::lte
  // @todo glm::ne
  
  // @todo glm::ortho(T left, T right, T bottom, T top, T near, T far) // 
    // CMatrix<T, 4, 4> result;
    // result[0][0] = + T(2) / (right - left);
    // result[1][1] = + T(2) / (top - bottom);
    // result[2][2] = - T(2) / (far - near);               // == // 2 / (near - far)
    // result[3][0] = - (right + left) / (right - left);   // == // (left + right) / (left - right)
    // result[3][1] = - (bottom + top) / (top - bottom);   // == // (bottom + top) / (bottom - top)
    // result[3][2] = - (far + near) / (far - near);       // == // (near + far) / (near - far)
    // result[3][3] = + T(1);
    // return result; 
  // @todo glm::frustum(T left, T right, T bottom, T top, T near, T far) // return mat4
    // if((right == left) || (top == bottom) || (near == far) || (near < T(0)) || (far < T(0)))
    //   return identity<T, 4>();
    // return CMatrix<T, 4, 4>(
    //   CVector<T, 4>((T(2) * near) / (right - left), T(0) ,                          (right + left) / (right - left), T(0)),
    //   CVector<T, 4>(T(0),                           (T(2) * near) / (top - bottom), (top + bottom) / (top - bottom), T(0)),
    //   CVector<T, 4>(T(0),                           T(0),                           -(far + near)  / (far - near),    -(T(2) * far * near) / (far - near)),
    //   CVector<T, 4>(T(0),                           T(0),                           -T(1),                           T(0))
    // );
  // @todo glm::perspective(T fov, T width, T hight, T near, T far)
  // @todo glm::perspective(T fovy, T ratio, T near, T far)
    // assert(far > near);
    // assert(ratio - epsilon > 0)
    // T q = T(1) / tan(radians(fovy / T(2)));      // tanhfov = 1/tan(fovy/2)
    // T A = q / ratio;                             // 1/(ratio*tanhfov)
    // T B = (near + far) / (near - far);           // -(far+near)/(far-near)
    // T C = (T(2) * near *  far) / (near - far);   // -(2*far*near)/(far-near)
    // return CMatrix<T, 4, 4>(
    //   CVector<T, 4>(   A, T(0), T(0), T(0)),
    //   CVector<T, 4>(T(0),    q, T(0), T(0)),
    //   CVector<T, 4>(T(0), T(0),    B, T(-1)),
    //   CVector<T, 4>(T(0), T(0),    C, T(0))
    // );
  // @todo glm::perspective(T fovy, T ratio, T near) = infinite perspective
  // @todo glm::lookat(vec3 position, vec3 target, vec3 up)
    //
  // @todo glm::unproject(vec3 window, mat4 modelview, mat4 perspective, vec4 viewport)
    //
}

#endif //__glm_hpp__
