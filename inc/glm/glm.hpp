#ifndef __glm_hpp__
#define __glm_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"

#include <cmath>

#undef near
#undef far

// opengl defaults to RH & [0,1]

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
  
  using log = sys::CLogger;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T, ushort cols, ushort rows> class CMatrix;
  
  template <typename T, ushort size> class CVector;

  template <typename T> class CQuaterion;
  
  template <typename T, ushort c, ushort r> using tmat = CMatrix<T,c,r>;
  
  typedef tmat<real,  4, 4>   mat4;
  typedef tmat<real,  4, 3>   mat4x3;
  typedef tmat<real,  3, 3>   mat3;
  typedef tmat<real,  2, 2>   mat2;
  typedef tmat<float,  4, 4> fmat4;
  typedef tmat<float,  4, 3> fmat4x3;
  typedef tmat<float,  3, 3> fmat3;
  typedef tmat<float,  2, 2> fmat2;
  typedef tmat<double, 4, 4> dmat4;
  typedef tmat<double, 4, 3> dmat4x3;
  typedef tmat<double, 3, 3> dmat3;
  typedef tmat<double, 2, 2> dmat2;
  typedef tmat<double, 4, 4> imat4;
  typedef tmat<double, 4, 3> imat4x3;
  typedef tmat<double, 3, 3> imat3;
  typedef tmat<double, 2, 2> imat2;
  
  template <typename T, ushort s> using tvec = CVector<T,s>;
  
  typedef tvec<real,  4>   vec4;
  typedef tvec<real,  3>   vec3;
  typedef tvec<real,  2>   vec2;  
  typedef tvec<float, 4>  fvec4;
  typedef tvec<float, 3>  fvec3;
  typedef tvec<float, 2>  fvec2;  
  typedef tvec<double, 4> dvec4;
  typedef tvec<double, 3> dvec3;
  typedef tvec<double, 2> dvec2;
  typedef tvec<int, 4>    ivec4;
  typedef tvec<int, 3>    ivec3;
  typedef tvec<int, 2>    ivec2;
  typedef tvec<uint, 4>   uvec4;
  typedef tvec<uint, 3>   uvec3;
  typedef tvec<uint, 2>   uvec2;
  typedef tvec<bool, 4>   bvec4;
  typedef tvec<bool, 3>   bvec3;
  typedef tvec<bool, 2>   bvec2;
  
  template <typename T> using tquat = CQuaterion<T>;
  
  typedef CQuaterion<real>    quat;
  typedef CQuaterion<float>  fquat;
  typedef CQuaterion<double> dquat;
  typedef CQuaterion<int>    iquat;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  constexpr real E        = real(2.71828182845904);
  constexpr real PI       = real(3.14159265358979);
  constexpr real RAD      = PI / real(180.0);
  
  // glm::epsilon<float>()
  template <typename T> using epsilon = decltype(std::numeric_limits<T>::epsilon);
  using epsilonf                      = decltype(std::numeric_limits<float>::epsilon);
  using epsilond                      = decltype(std::numeric_limits<double>::epsilon);
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
  
  template <typename T> inline void swap(T& lhs, T& rhs) { T tmp = lhs; lhs = rhs; rhs = tmp; }
  
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
  
  template <typename T> T inline abs(const T& val) { return val < T(0) ? val * T(-1) : val; }
  
  template <typename T> inline bool equals(const T& lhs, const T& rhs) { return glm::abs(lhs-rhs) < epsilon<T>(); } // eq
  
  template <typename T, ushort s> inline bool equals(const glm::tvec<T,s>& lhs, const glm::tvec<T,s>& rhs) { return glm::abs(lhs-rhs) < epsilon<T>(); } // eq
  
  template <typename T> inline bool eq(const T& lhs, const T& rhs) { return glm::equals(lhs,rhs); }
  
  template <typename T, ushort s> inline bool eq(const glm::tvec<T,s>& lhs, const glm::tvec<T,s>& rhs) { return glm::equals(lhs,rhs); }
  
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
    T D = glm::mix(A, B, t); // D = A + t(B - A)
    T E = glm::mix(B, C, t); // E = B + t(C - B)
    T P = glm::mix(D, E, t); // P = D + t(E - D)
    return P;
  }
  
  // cubic bezier (4 component interpolation)
  template <typename T, typename S> inline T mix(const T& A, const T& B, const T& C, const T& D, const S& t) { 
    
    T E = glm::mix(A, B, t);
    T F = glm::mix(B, C, t);
    T G = glm::mix(C, D, t);
    T P = glm::mix(E, F, G, t);
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
  template <typename T, const ushort n> T inline dot(const glm::CVector<T,n>& v1, const glm::CVector<T,n>& v2) {
    T res(0);
    for(ushort i = 0; i < n; i++)
      res += v1[i] * v2[i];
    return res;
  }  
  
  // glm::dot quat
  template <typename T> T inline dot(const glm::CQuaterion<T>& q1, const glm::CQuaterion<T>& q2) {
    T res(0);
    for(ushort i = 0; i < 4; ++i)
      res += q1[i] * q2[i];
    return res;
  }
  
  // glm::cross
  template <typename T> glm::CVector<T,3> inline cross(const glm::CVector<T, 3>& x, const glm::CVector<T,3>& y) {
    return glm::CVector<T,3>(
      (x.y * y.z - y.y * x.z),
      (x.z * y.x - y.z * x.x),
      (x.x * y.y - y.x * x.y));
  }
  
  // glm::length
  template <typename T, const ushort n> T inline length(const glm::CVector<T,n>& v) {
    T sum {0};
    for(ushort i = 0; i < n; i++)
      sum += v[i] * v[i];
    return (T)std::sqrt(sum);
  }
  
  // glm::normalize
  template <typename T, const ushort n> CVector<T,n> inline normalize(const glm::CVector<T,n>& v) {
    return v / glm::length(v);
  }
  
  // @todo glm::inverse
  // @todo glm::transpose
  // @todo glm::identity
  // @todo glm::det
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // glm::radian
  template <typename T> inline T radians(T degrees) { return degrees * static_cast<T>(RAD); } // return degrees * RAD;
  
  template <typename T> inline T deg2rad(T degrees) { return glm::radians(degrees); } // return degrees * RAD;
  
  // glm::angle
  template <typename T> inline T degrees(T radians) { return radians / static_cast<T>(RAD); } // return radians / RAD;
  
  template <typename T> inline T rad2deg(T radians) { return glm::degrees(radians); } // return radians / RAD;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // @todo glm::yaw
  // @todo glm::roll
  // @todo glm::pitch
  
  // glm::rotate // rotation matrix from axis and angle | R = cos*I + sin*[u]x + (1-cos)uXu | tensor product
  template <typename T> inline tmat<T, 4, 4> rotate(const T& a, const T& x, const T& y, const T& z) {
    // return glm::rotate(a, glm::tvec<T,3>{x,y,z});
    const T xx = x * x;
    const T yy = y * y;
    const T zz = z * z;
    const T xy = x * y;
    const T xz = x * z;
    const T yz = y * z;

    const T rad = glm::radians(a);  // float
    const T c   = (T) ::cos(rad);  // float
    const T s   = (T) ::sin(rad);  // float
    const T omc = T(1) - c;         // one minus cos

    return tmat<T, 4, 4>(
      tvec<T, 4>(T(xx * omc + c),     T(xy * omc + z * s), T(xz * omc - y * s), T(0)),
      tvec<T, 4>(T(xy * omc - z * s), T(yy * omc + c),     T(yz * omc + x * s), T(0)),
      tvec<T, 4>(T(xz * omc + y * s), T(yz * omc - x * s), T(zz * omc + c),     T(0)),
      tvec<T, 4>(T(0),                T(0),                T(0),                T(1))
    );
  }
  
  // glm::rotate // rotation matrix - vector
  template <typename T> inline glm::tmat<T, 4, 4> rotate(const T& a, const glm::tvec<T,3>& vec) {
    return glm::rotate(a, vec.x, vec.y, vec.z);
    // const T c = ::cos(a);
    // const T s = ::sin(a);
    //
    // glm::tvec<T,3> axis {glm::normalize(vec)};
    // glm::tvec<T,3> omca {(T(1) - c) * axis};
    //
    //
    // return tmat<T, 4, 4>(
    //  
    // );
  }
  
  // glm::rotate // matrix rotation using angles
  template <typename T> inline glm::tmat<T, 4, 4> rotate(const T& ax, const T& ay, const T& az) {
    return glm::rotate(ax, T(1), T(0), T(0)) * glm::rotate(ay, T(0), T(1), T(0)) * glm::rotate(az, T(0), T(0), T(1));
  }
  
  // rotate vector
  template <typename T, const ushort n> inline glm::tvec<T, n> rotateY(const T& a, const glm::tvec<T, n>& vec) {
    glm::tvec<T, n> res(vec);
    const T rads = glm::radians(a);
    const T cosa = ::cos(rads);
    const T sina = ::cos(rads);
    // calc x & z
    res.x = vec.x * cosa + vec.z * sina;
    res.z =-vec.x * sina + vec.z * cosa;
    // done
    return res;
  }
  
  // @todo glm::scale
  // @todo glm::reflect
  // @todo glm::refract
  
  // glm::translate // create translation matrix from a direction vector
  template <typename T> CMatrix<T,4,4> translate(const CVector<T,3>& v) {
    return CMatrix<T, 4, 4>{
      CVector<T,4> {T(1), T(0), T(0), T(0)},
      CVector<T,4> {T(0), T(1), T(0), T(0)},
      CVector<T,4> {T(0), T(0), T(1), T(0)},
      CVector<T,4> {v[0], v[1], v[2], T(1)}
    };
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // @todo glm::eq
  // @todo glm::gt
  // @todo glm::gte
  // @todo glm::lt
  // @todo glm::lte
  // @todo glm::ne
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // glm::ortho(T left, T right = screen.width, T bottom = screen.height, T top, T near, T far) //
  template <typename T> CMatrix<T,4,4> inline ortho(T left, T right, T bottom, T top, T near, T far) {
    return CMatrix<T,4,4> {
      T(2)/(right-left),          T(0),                        T(0),            T(0),
      T(0),                       T(2)/(top-bottom),           T(0),            T(0),
      T(0),                       T(0),                       -T(1)/(far-near), T(0),
      -(right+left)/(right-left), -(top+bottom)/(top-bottom), -near/(far-near), T(1),
    };
  } 
    
  // @todo glm::frustum(T left, T right, T bottom, T top, T near, T far) // return mat4
    // if((right == left) || (top == bottom) || (near == far) || (near < T(0)) || (far < T(0)))
    //   return identity<T, 4>();
    // return CMatrix<T, 4, 4>(
    //   tvec<T, 4>((T(2) * near) / (right - left), T(0) ,                          (right + left) / (right - left), T(0)),
    //   tvec<T, 4>(T(0),                           (T(2) * near) / (top - bottom), (top + bottom) / (top - bottom), T(0)),
    //   tvec<T, 4>(T(0),                           T(0),                           -(far + near)  / (far - near),    -(T(2) * far * near) / (far - near)),
    //   tvec<T, 4>(T(0),                           T(0),                           -T(1),                           T(0))
    // );
    
  // glm::perspective(T fov, T width, T hight, T near, T far)
  template <typename T> CMatrix<T,4,4> inline perspective(T fov, T width, T height, T near, T far) {
    assert(width  > T(0));
    assert(height > T(0));
    assert(fov    > T(0));
    assert(far    > near);
    // @todo: allow radians or degrees
    const T rad = glm::radians(fov)/T(2);
    const T m11 = ::cos(rad)/::sin(rad); // h
    const T m00 = m11 * height/width;    // w
    return CMatrix<T,4,4> {
      m00,  T(0),  T(0),                  T(0),
      T(0), m11,   T(0),                  T(0),
      T(0), T(0), -(far)/(far-near),     -T(1),
      T(0), T(0), -(far*near)/(far-near), T(0),
    };
  }

  // glm::perspective // return perspective matrix using field of view, aspect ratio, near & far planes
  template <typename T> CMatrix<T,4,4> inline perspective(T fovy, T ratio, T near, T far) {
    assert(far > near);
    assert(glm::abs(ratio - std::numeric_limits<T>::epsilon() > T(0)));
    const T thf = ::tan(glm::radians(fovy / T(2)));
    // @todo: allow radians AND degrees
    return CMatrix<T,4,4> {
      T(1)/(ratio * thf), T(0),       T(0),                  T(0),
      T(0),               T(1)/(thf), T(0),                  T(0),
      T(0),               T(0),      -(far)/(far-near),     -T(1),
      T(0),               T(0),      -(far*near)/(far-near), T(0),
    };
  }

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
  
  // glm::lookat(vec3 position, vec3 target, vec3 up) // eye, center, up
  template <typename T> inline CMatrix<T,4,4> lookat(glm::CVector<T,3> p/*position,eye*/, glm::CVector<T,3> t/*target,center*/, CVector<T,3> a/*up*/) {
    const CVector<T,3> f(glm::normalize(t - p));            // direction = target - position
    const CVector<T,3> s(glm::normalize(glm::cross(f, a))); // side = forward x up
    const CVector<T,3> u(glm::cross(s, f));                 // up - recomputed
    return CMatrix<T,4,4> {                              // glm::mat4 m{1}
      CVector<T,4>(-s.x,       u.x,      -f.x,       T(0)),
      CVector<T,4>(-s.y,       u.y,      -f.y,       T(0)),
      CVector<T,4>(-s.z,       u.z,      -f.z,       T(0)),
      CVector<T,4>(-dot(s, p),-dot(u, p), dot(f, p), T(1))
    };
  }
  
  // @todo glm::unproject(vec3 window, mat4 modelview, mat4 perspective, vec4 viewport)
    // tvec<T, 4> inverse = math::inverse(projection * modelview);
    // 
    // tvec<T, 4> temp(window, T(1));
    // temp.x = (temp.x - T(viewport[0])) / T(viewport[2]) ;
    // temp.x = (temp.y - T(viewport[1])) / T(viewport[3]) ;
    // temp = temp * T(2) - T(1);
    // 
    // tvec<T, 4> object = inverse * temp;
    // object /= object.w;
    // 
    // return tvec<T, 3>(object.x, object.y, object.z);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CRay { };
  
  enum class EShape {
      S0D = 0,
      S1D = 1,
      S2D = 2,
      S3D = 3,
      S4D = 4,
  };
  
  class BShape { };
  template <EShape shape> class CShape : public BShape { };
  
  class CPoint : public CShape<EShape::S0D> { };
  
  class CLine      : public CShape<EShape::S1D> { };
  class CCircle    : public CShape<EShape::S2D> { };
  class CEllipse   : public CShape<EShape::S2D> { };
  class CArc       : public CShape<EShape::S2D> { };
  class CSpline    : public CShape<EShape::S2D> { };
  class CSector    : public CShape<EShape::S2D> { };
  class CPolygon   : public CShape<EShape::S2D> { };
  class CRectangle : public CShape<EShape::S2D> { }; typedef CRectangle rect;
  class CPlane     : public CShape<EShape::S2D> { };
  class CTriangle  : public CPolygon { };
  
  class CPrism   : public CShape<EShape::S3D> { };
  class CPyramid : public CShape<EShape::S3D> { };
  class CCube    : public CShape<EShape::S3D> { };
  class CSphere  : public CShape<EShape::S3D> { };
  
  class CTesseract : public CShape<EShape::S4D> { }; // hypercube = 4(spacial)d  cube
}

#endif //__glm_hpp__
