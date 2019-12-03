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
  
  template <typename T, ushort c, ushort r> using  mat = CMatrix<T,c,r>;
  template <typename T, ushort c, ushort r> using tmat = mat<T,c,r>;
  
  typedef CMatrix<float,  4, 4>  mat4;
  typedef CMatrix<float,  4, 3>  mat4x3;
  typedef CMatrix<float,  3, 3>  mat3;
  typedef CMatrix<float,  2, 2>  mat2;
  typedef CMatrix<float,  4, 4> fmat4;
  typedef CMatrix<float,  4, 3> fmat4x3;
  typedef CMatrix<float,  3, 3> fmat3;
  typedef CMatrix<float,  2, 2> fmat2;
  typedef CMatrix<double, 4, 4> dmat4;
  typedef CMatrix<double, 4, 3> dmat4x3;
  typedef CMatrix<double, 3, 3> dmat3;
  typedef CMatrix<double, 2, 2> dmat2;
  typedef CMatrix<double, 4, 4> imat4;
  typedef CMatrix<double, 4, 3> imat4x3;
  typedef CMatrix<double, 3, 3> imat3;
  typedef CMatrix<double, 2, 2> imat2;
  
  template <typename T, ushort s> using vec  = CVector<T,s>;
  template <typename T, ushort s> using tvec = vec<T,s>;
  
  typedef CVector<float, 4>   vec4;
  typedef CVector<float, 3>   vec3;
  typedef CVector<float, 2>   vec2;  
  typedef CVector<float, 4>  fvec4;
  typedef CVector<float, 3>  fvec3;
  typedef CVector<float, 2>  fvec2;  
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
  
  template <typename T> using tquat = CQuaterion<T>;
  
  typedef CQuaterion<float>   quat;
  typedef CQuaterion<float>  fquat;
  typedef CQuaterion<double> dquat;
  typedef CQuaterion<int>    iquat;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /// glm::epsilon<float>()
  template <typename T> using epsilon = decltype(std::numeric_limits<T>::epsilon); 
  using epsilond                      = decltype(std::numeric_limits<double>::epsilon);
  using epsilonf                      = decltype(std::numeric_limits<float>::epsilon);
  using epsilonl                      = decltype(std::numeric_limits<long>::epsilon);
  using epsilonul                     = decltype(std::numeric_limits<unsigned long>::epsilon);
  using epsiloni                      = decltype(std::numeric_limits<int>::epsilon);
  using epsiloni32                    = epsiloni;
  using epsilonui                     = decltype(std::numeric_limits<unsigned int>::epsilon);
  using epsilonui32                   = decltype(std::numeric_limits<uint32_t>::epsilon);
  
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
  
  template <typename T> T abs(const T& val) { return val < T(0) ? val * T(-1) : val; }
  
  template <typename T> inline bool equals(const T& lhs, const T& rhs) { return glm::abs(lhs-rhs) < epsilon<T>(); } // eq
  
  template <typename T, ushort s> inline bool equals(const glm::vec<T,s>& lhs, const glm::vec<T,s>& rhs) { return glm::abs(lhs-rhs) < epsilon<T>(); } // eq
  
  template <typename T> inline bool eq(const T& lhs, const T& rhs) { return glm::equals(lhs,rhs); }
  
  template <typename T, ushort s> inline bool eq(const glm::vec<T,s>& lhs, const glm::vec<T,s>& rhs) { return glm::equals(lhs,rhs); }
  
  // linear interpolation
  template <typename T, typename S> inline T mix(const T& A, const T& B, const S& t) { 
    return B + t * (B - A); 
  } 
  
  // linear interpolation
  template <typename T, typename S> inline T lerp(const T& A, const T& B, const S& t) { 
    return glm::mix(A,B,t); 
  } 
  
  // quadratic bezier (3 component interpolation)
  template <typename T, typename S> inline T mix(const T& A, const T& B, const T& C, const S& t)  {
    T D = mix(A, B, t); // D = A + t(B - A)
    T E = mix(B, C, t); // E = B + t(C - B)
    T P = mix(D, E, t); // P = D + t(E - D)
    return P;
  }
  
  // cubic bezier (4 component interpolation)
  template <typename T, typename S> inline T mix(const T& A, const T& B, const T& C, const T& D, const S& t) { 
    
    T E = mix(A, B, t);
    T F = mix(B, C, t);
    T G = mix(C, D, t);
    T P = mix(E, F, G, t);
    return P;
  }
  
  //
  
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
  // @todo glm::slerp // spherical linear interpolation
  // @todo glm::isnan
  // @todo glm::isinf
  // @todo glm::pow
  // @todo glm::exp
  // @todo glm::log
  // @todo glm::sqrt
  // @todo glm::isqrt OR rsqrt
  // @todo glm::wrap
  
  // @todo glm::distance // between 2 vecs
  // @todo glm::conjugate
  // @todo glm::axis // ret q rotation axis
  
  
  // glm::dot
  template <typename T, const ushort n> T dot(const tvec<T, n>& v1, const tvec<T, n>& v2) {
    T res(0);
    for(ushort i = 0; i < n; i++)
      res += v1[i] * v2[i];
    return res;
  }  
  
  // glm::dot quat
  template <typename T> T dot(const tquat<T>& q1, const tquat<T>& q2) {
    T res(0);
    for(ushort i = 0; i < 4; ++i)
      res += q1[i] * q2[i];
    return res;
  }
  
  // glm::cross
  template <typename T> tvec<T, 3> cross(const tvec<T, 3>& v1, const tvec<T, 3>& v2) {
    return tvec<T,3>(
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x);
  }
  
  // glm::length
  template <typename T, const ushort n> T length(const CVector<T, n>& v) {
    T sum {0};
    for(ushort i = 0; i < n; i++)
      sum += v[i] * v[i];
    return (T)std::sqrt(sum);
  }
  
  // glm::normalize
  template <typename T, const ushort n> vec<T, n> normalize(const vec<T, n>& v) {
    return v / glm::length(v);
  }
  
  
  
  // @todo glm::inverse
  // @todo glm::transpose
  // @todo glm::identity
  // @todo glm::det
  
  // @todo glm::angle
  // @todo glm::radian
  
  // @todo glm::yaw
  // @todo glm::roll
  // @todo glm::pitch
  // @todo glm::rotate
  // @todo glm::scale
  // @todo glm::reflect
  // @todo glm::refract
  // @todo glm::translate
  
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
    // assert(width > 0)
    // assert(height > 0)
    // assert(fov > 0)
    // rad = fov
    // m11 = cos(0.5 * rad)/sin(0.5 * rad)
    // m00 = m11 * height/width 
    // mat4 m{0}
    // m[0][0] = m00
    // m[1][1] = m11
    // m[2][2] = - (far + near)/(far - near)
    // m[2][2] = - 1
    // m[3][2] = - (2 * far * near)/(far - near)
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
    // range = tan(fovy, 2) * near
    // left  = -range * ratio
    // right = range * ratio
    // bottom = -range
    // top    = range
    // mat4 m{0}
    // m[0][0] = (2 * near)/(right-left)
    // m[1][1] = (2 * near)/(top - bottom)
    // m[2][2] = 1
    // m[2][3] = 1
    // m[3][2] = 2 * near
  // @todo glm::lookat(vec3 position, vec3 target, vec3 up) // eye, center, up
  
  template <typename T> inline tmat<T,4,4> lookat(vec<T,3> p/*position,eye*/, tvec<T,3> t/*target,center*/, tvec<T,3> a/*up*/) {
    const tvec<T,  3> f(glm::normalize(t - p));
    const tvec<T,  3> s(glm::normalize(glm::cross(f,a)));
    const tvec<T,  3> u(glm::cross(s,f));
    const tmat<T,4,4> m {T(1)};
    
    m[0][0] = +s.x;
    m[1][0] = +s.y;
    m[2][0] = +s.z;
    m[3][0] = -dot(s,t);
    m[0][1] = +u.x;
    m[1][1] = +u.y;
    m[2][1] = +u.z;
    m[3][1] = -dot(u,t);
    m[0][2] = -f.x;
    m[1][2] = -f.y;
    m[2][2] = -f.z;
    m[3][2] = -dot(f,t);
    
    return m;
  }
  
    // const CVector<T, 3> f(normalize(target - position)); // direction = target - position
    // const CVector<T, 3> s(normalize(cross(f, up)));      // side = forward x up
    // const CVector<T, 3> u(cross(s, f));                  // up - recomputed
    // const CMatrix<T, 4, 4> M = CMatrix<T, 4, 4>(                                     // glm::mat4 m{1}
    //   CVector<T, 4>(-s.x,  u.x, -f.x, T(0)),                                         // [0][0] +s.x      | [0][1] +u.x      | [0][2] -f.x
    //   CVector<T, 4>(-s.y,  u.y, -f.y, T(0)),                                         // [1][0] +s.y      | [1][1] +u.y      | [1][2] -f.y
    //   CVector<T, 4>(-s.z,  u.z, -f.z, T(0)),                                         // [2][0] +s.z      | [2][1] +u.z      | [2][2] -f.z
    //   CVector<T, 4>(T(0), T(0), T(0), T(1))                                          // [3][0] -dot(s,e) | [3][1] -dot(s,e) | [3][2] +dot(f,e)
    //   //CVector<T, 4>(-dot(s, position), -dot(u, position), dot(f, position), T(1))
    // );
    // return M * translate(-position);
  // @todo glm::unproject(vec3 window, mat4 modelview, mat4 perspective, vec4 viewport)
    // CVector<T, 4> inverse = math::inverse(projection * modelview);
    // 
    // CVector<T, 4> temp(window, T(1));
    // temp.x = (temp.x - T(viewport[0])) / T(viewport[2]) ;
    // temp.x = (temp.y - T(viewport[1])) / T(viewport[3]) ;
    // temp = temp * T(2) - T(1);
    // 
    // CVector<T, 4> object = inverse * temp;
    // object /= object.w;
    // 
    // return CVector<T, 3>(object.x, object.y, object.z);
}

#endif //__glm_hpp__
