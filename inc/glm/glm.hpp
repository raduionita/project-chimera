#ifndef __glm_hpp__
#define __glm_hpp__

#include "sys/sys.hpp"
#include "sys/CLogger.hpp"

#include <cmath>
#include <cassert>

#undef NEAR
#undef FAR
#undef near
#undef far

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
  
  // OGL (here) is RightHanded + Negative Z (at horizon/distance) ////////////////////////////////////////////////////
  // OGL defaults to RH & [0,1] //////////////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: these should be done as bitfields, where OVERLAP = (OUTSIDE | INTERSECT)
  enum class ECompare : int { BEHIND = -1, INSIDE = 0, INTERSECT, OUTSIDE, FRONT = OUTSIDE, OVERLAP = 9/*=INTERSECT+OUTSIDE*/ };
  
  enum class EInterpolate : uint { LINEAR = 0, EASE_IN, EASE_IN_CIRCLE, EASE_OUT, EASE_OUT_CURCLE, EASE_IN_OUT, EASE_IN_OUT_CIRCLE, BOUNCE, ELASTIC, };
  
  enum class EDot : int { BEHIND = -1, INSIDE = 0, FRONT = 1 };
  
  enum EPlane { LEFT=0, L = LEFT, RIGHT=1, R = RIGHT, BOTTOM=2, B = BOTTOM, TOP=3, T = TOP, FAR=4, F = FAR, NEAR=5, N = NEAR };
  
  enum ECorner { LBN = 0, RBN, LTN, RTN, LBF, RBF, LTF, RTF/*=7*/ };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T, ushort cols, ushort rows> class CMatrix;
  
  template<typename T, ushort size> class CVector;
  
  template<typename T> class CQuaternion;
  
  template<typename T> class CTransform;
  
  template<typename T> class CRay;
  template<typename T> class TPlane;
  
  class CAABB;
  class CFrustum;
  
  template<typename T, ushort c, ushort r> using tmat = CMatrix<T,c,r>;
  template<typename T> using tmat4 = CMatrix<T,4,4>;
  // concrete
  typedef tmat<real,   2, 2>  mat2;
  typedef tmat<real,   4, 3>  mat4x3;
  typedef tmat<real,   3, 3>  mat3;
  typedef tmat<real,   4, 4>  mat4;
  typedef tmat<float,  2, 2> fmat2;
  typedef tmat<float,  3, 3> fmat3;
  typedef tmat<float,  4, 3> fmat4x3;
  typedef tmat<float,  4, 4> fmat4;
  typedef tmat<double, 2, 2> dmat2;
  typedef tmat<double, 3, 3> dmat3;
  typedef tmat<double, 4, 3> dmat4x3;
  typedef tmat<double, 4, 4> dmat4;
  typedef tmat<int,    2, 2> imat2;
  typedef tmat<int,    3, 3> imat3;
  typedef tmat<int,    4, 3> imat4x3;
  typedef tmat<int,    4, 4> imat4;
  
  template<typename T, ushort s> using tvec = CVector<T,s>;
  template<typename T> using tvec2 = CVector<T,2>;
  template<typename T> using tvec3 = CVector<T,3>;
  template<typename T> using tvec4 = CVector<T,4>;
  // concrete
  typedef tvec<real,  4>   vec4; typedef tvec<real,  4>    real4;
  typedef tvec<real,  3>   vec3; typedef tvec<real,  3>    real3;
  typedef tvec<real,  2>   vec2; typedef tvec<real,  2>    real2;  
  typedef tvec<float, 4>  fvec4; typedef tvec<float, 4>   float4;
  typedef tvec<float, 3>  fvec3; typedef tvec<float, 3>   float3;
  typedef tvec<float, 2>  fvec2; typedef tvec<float, 2>   float2;  
  typedef tvec<double, 4> dvec4; typedef tvec<double, 4> double4;
  typedef tvec<double, 3> dvec3; typedef tvec<double, 3> double3;
  typedef tvec<double, 2> dvec2; typedef tvec<double, 2> double2;
  typedef tvec<int, 4>    ivec4; typedef tvec<int, 4>       int4;
  typedef tvec<int, 3>    ivec3; typedef tvec<int, 3>       int3;
  typedef tvec<int, 2>    ivec2; typedef tvec<int, 2>       int2;
  typedef tvec<uint, 4>   uvec4; typedef tvec<uint, 4>     uint4;
  typedef tvec<uint, 3>   uvec3; typedef tvec<uint, 3>     uint3; 
  typedef tvec<uint, 2>   uvec2; typedef tvec<uint, 2>     uint2;
  typedef tvec<bool, 4>   bvec4; typedef tvec<bool, 4>     bool4; 
  typedef tvec<bool, 3>   bvec3; typedef tvec<bool, 3>     bool3; 
  typedef tvec<bool, 2>   bvec2; typedef tvec<bool, 2>     bool2;
  
  template<typename T> using tquat = CQuaternion<T>;
  // concrete
  typedef CQuaternion<real>    quat;
  typedef CQuaternion<float>  fquat;
  typedef CQuaternion<double> dquat;
  typedef CQuaternion<int>    iquat;
  
  template<typename T> using txform = CTransform<T>;
  // concrete
  typedef txform<real> xform;
  
  template<typename T> using tray = CRay<T>;
  // concrete
  typedef CRay<real>    ray;
  typedef CRay<float>  fray;
  typedef CRay<double> dray;
  
  template<typename T> using tplane = TPlane<T>;
  // concrete
  typedef TPlane<real> CPlane;
  typedef CPlane plane;
  
  typedef CAABB    aabb;
  typedef CFrustum frustum;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> struct TRange { union { struct { T min, max; }; struct { T start, end; }; }; };
  
  typedef TRange<real> SRange; 
  typedef TRange<real>  range; 
  typedef TRange<uint> irange; 
  
  enum class EShape : ushort { S0D = 0, S1D = 1, S2D = 2, S3D = 3, S4D = 4, };
  
  struct SShape { };
  
  template <EShape shape> struct TShape : public SShape { };
    
  struct SPoint     : TShape<EShape::S0D> { /* this is a purly mathematical construct, NOT a position in space */ };
  
  struct SLine      : TShape<EShape::S1D> { union {struct{real l;}; struct {real length;};}; };
  
  struct SCircle    : TShape<EShape::S2D> { union {struct{real r;}; struct {real radius;};}; };
  struct SEllipse   : TShape<EShape::S2D> { union {struct{real a,b;}; struct {real semiMajorAxis, semiMinorAxis;};};}; // a > b // x^2/a^2 + y^2/b^2 = 1
  struct SArc       : TShape<EShape::S2D> { };
  struct SSpline    : TShape<EShape::S2D> { };
  struct SSector    : TShape<EShape::S2D> { };
  struct SPolygon   : TShape<EShape::S2D> { };
  
  struct CRectangle : TShape<EShape::S2D> { union {struct{real w, h;}; struct {real width, height;};}; CRectangle(real w, real h) : width{w}, height{h} {} }; 
  
  struct STriangle  : SPolygon {  };
  
  struct SPrism       : TShape<EShape::S3D> { };
  struct SPyramid     : TShape<EShape::S3D> { };
  struct STetrahedron : TShape<EShape::S3D> { }; // = 3 point base pyramid // = 4 echilateral triangles
    // p0 = (0, l*(sqrt(2)-sqrt(3))/(sqrt(3), 0)
    // p1 = (-l/2, -l/3, l/2*sqrt(3))
    // p2 = (0, -l/3, -l/sqrt(3))
    // p3 = (l/2, -l/3, l/2*sqrt(3))
  struct SCube        : TShape<EShape::S3D> { union {struct {real l;}; struct {real length;};}; SCube(real l) : length{l} {} };
  struct SCuboid      : TShape<EShape::S3D> { union {struct {real l,h,d;}; struct {real length,height,depth;};}; SCuboid(real l, real h, real d) : length{l}, height{h}, depth{d} {} };
  struct SSphere      : TShape<EShape::S3D> { union {struct{real r;}; struct {real radius;};}; };
  
  struct STesseract   : TShape<EShape::S4D> { union {struct {real l;}; struct {real length;};}; }; // hypercube = 4(spacial)d  cube
  
  using shape  = SShape;
  using point  = SPoint;
  using line   = SLine;
  using poly   = SPolygon;
  using rect   = CRectangle; using rectangle = CRectangle;
  using cube   = SCube;
  using vol    = SCuboid; using volume = SCuboid; using SVolume = SCuboid;
  using cuboid = SCuboid; using box = SCuboid;
  using sphere = SSphere;
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  constexpr real E        = static_cast<real>(2.71828182845904);
  constexpr real PI       = static_cast<real>(3.14159265358979);
  constexpr real HPI      = static_cast<real>(3.14159265358979) / static_cast<real>(2);
  
  constexpr real MONE     = static_cast<real>(-1);
  constexpr real ZERO     = static_cast<real>(0);
  constexpr real HALF     = static_cast<real>(0.5f);
  constexpr real ONE      = static_cast<real>(1);
  constexpr real TWO      = static_cast<real>(2);
  constexpr real ONE80    = static_cast<real>(180);
  
  constexpr real RAD      = PI / static_cast<real>(180);
  constexpr real DEG2RAD  = RAD;
  constexpr real DEG      = static_cast<real>(180) / PI;
  constexpr real RAD2DEG  = DEG;
  
  constexpr real SQRT_2   = static_cast<real>(1.41421356237309);
  constexpr real SQRT_3   = static_cast<real>(1.73205080756887);
  
  // glm::epsilon<float>()
  template <typename T> inline const T      EPSILON()                   { return static_cast<T>(0); }     // until variable templates
  template <>           inline const float  EPSILON<float>()            { return 0.0000001f; }            // 10^-7  // or FLT_EPSILON      = 1.19209e-07
  template <>           inline const double EPSILON<double>()           { return 0.000000000000001; }     // 10^-15  // or DBL_EPSILON      = 2.22045e-16
  template <>           inline const long double EPSILON<long double>() { return 0.000000000000000001l; } // 10^-18 // or LDBL_EPSILON     = 1.0842e-19
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* float = glm::radian(float) // degrees to radians // return degrees * RAD */
  template<typename T> inline T radians(T degrees) { return degrees * static_cast<T>(DEG2RAD); }
  
  /* float = glm::deg2rad(float) // degrees to radians // return degrees * RAD */
  template<typename T> inline T deg2rad(T degrees) { return glm::radians(degrees); } 
  /* float = glm::degrees(float) // radians to degrees // return radians / RAD */
  template<typename T> inline T degrees(T radians) { return radians * static_cast<T>(RAD2DEG); }
  
  /* float = glm::degrees(float) // radians to degrees // return radians / RAD */
  template<typename T> inline T rad2deg(T radians) { return glm::degrees(radians); }
  
  /* auto r = 90.0_deg2rad; */
  constexpr long double operator "" _deg2rad(long double d) {
    long double r = d * PI/180;
    return r;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> inline void swap(T& lhs, T& rhs) { T tmp = lhs; lhs = rhs; rhs = tmp; }
  
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
  
  template<typename T> inline T log2(T value) { return static_cast<T>(std::log2(value)); }
  
  template<typename T> inline T floor(T value) { return static_cast<T>(std::floor(value)); }
  
  // @note: std::fabs = return absolute value of a float
  
// @todo glm::sin   // takes in degrees
// @todo glm::cos   // std::cos takes in radians
// @todo glm::acos
// @todo glm::asin

// @todo glm::atan
  
  template<typename T> inline T              min(T a, T b) { return a < b ? a : b; }
  template<typename T> inline glm::tvec<T,2> min(const glm::tvec<T,2>& a, const glm::tvec<T,2>& b) { return glm::tvec<T,2>{glm::min(a.x,b.x),glm::min(a.y,b.y)}; }
  template<typename T> inline glm::tvec<T,3> min(const glm::tvec<T,3>& a, const glm::tvec<T,3>& b) { return glm::tvec<T,3>{glm::min(a.x,b.x),glm::min(a.y,b.y),glm::min(a.z,b.z)}; }
  template<typename T> inline glm::tvec<T,4> min(const glm::tvec<T,4>& a, const glm::tvec<T,4>& b) { return glm::tvec<T,4>{glm::min(a.x,b.x),glm::min(a.y,b.y),glm::min(a.z,b.z),glm::min(a.w,b.w)}; }
  
  template<typename T> inline T              max(T a, T b) { return a >= b ? a : b; }
  template<typename T> inline glm::tvec<T,2> max(const glm::tvec<T,2>& a, const glm::tvec<T,2>& b) { return glm::tvec<T,2>{glm::max(a.x,b.x),glm::max(a.y,b.y)}; }
  template<typename T> inline glm::tvec<T,3> max(const glm::tvec<T,3>& a, const glm::tvec<T,3>& b) { return glm::tvec<T,3>{glm::max(a.x,b.x),glm::max(a.y,b.y),glm::max(a.z,b.z)}; }
  template<typename T> inline glm::tvec<T,4> max(const glm::tvec<T,4>& a, const glm::tvec<T,4>& b) { return glm::tvec<T,4>{glm::max(a.x,b.x),glm::max(a.y,b.y),glm::max(a.z,b.z),glm::max(a.w,b.w)}; }
  
  template<typename T> T inline abs(const T& val) { return val < T(0) ? val * T(-1) : val; }
  
  template<typename T> inline bool equals(const T& lhs, const T& rhs) { return glm::abs(lhs-rhs) < std::numeric_limits<T>::epsilon(); } // eq
  template<typename T> inline bool eq(const T& lhs, const T& rhs) { return glm::equals(lhs,rhs); }
  
  template<typename T> inline bool nequals(const T& lhs, const T& rhs) { return !glm::equals(lhs,rhs); }
  template<typename T> inline bool ne(const T& lhs, const T& rhs) { return !glm::equals(lhs,rhs); }
  
  template<typename T, ushort s> inline bool equals(const glm::tvec<T,s>& lhs, const glm::tvec<T,s>& rhs) { return glm::abs(lhs-rhs) < std::numeric_limits<T>::epsilon(); } // eq
  template<typename T, ushort s> inline bool eq(const glm::tvec<T,s>& lhs, const glm::tvec<T,s>& rhs) { return glm::equals(lhs,rhs); }
  
  // Lesser (a < b) compare using EPSILON tolerance
  template<typename T> inline bool lesser(T a, T b) { return (b - a) > std::numeric_limits<T>::epsilon(); }  // lt <
  template<typename T> inline bool lt(T a, T b) { return lesser(a,b); }
  
  // Greater (a > b) compare using EPSILON tolerance
  template<typename T> inline bool greater(T a, T b) { return (a - b) > std::numeric_limits<T>::epsilon(); } // gt >
  template<typename T> inline bool gt(T a, T b) { return greater(a,b); } // gt >
  
  // Greater or equal (a <= b) compare using EPSILON tolerance
  template<typename T> inline bool gequal(T a, T b) { return greater(a, b) || equals(a, b); } // gte >=
  template<typename T> inline bool gte(T a, T b) { return gequal(a,b); } // gte >=
  
  // Less or equal (a >= b) compare using EPSILON tolerance
  template<typename T> inline bool lequal(T a, T b) { return lesser(a, b) || equals(a, b); } // lte <=
  template<typename T> inline bool lte(T a, T b) { return lequal(a,b); } // lte <=
  
  /* float = glm::dot(tvec,tvec) dot > 0 -> same direction, dot = 0 -> perpendicular, dot < 0 -> opposite direction */
  template<typename T, const ushort n> T inline dot(const glm::CVector<T,n>& v1, const glm::CVector<T,n>& v2) {
    T res(0);
    for(ushort i = 0; i < n; i++)
      res += v1[i] * v2[i];
    // (a.x * b.x) + (a.y * b.y)
    return res;
    // dot shows how much of v2 is in the direction of v1 // ex: id dot = 0, v1 is perpendicular to v2
  }  
  
  /* glm::real = glm::dot(quat,quat) */
  template<typename T> T inline dot(const glm::tquat<T>& q1, const glm::tquat<T>& q2) {
    T res(0);
    for(ushort i = 0; i < 4; ++i)
      res += q1[i] * q2[i];
    return res;
  }
  
  /* glm::vec3 = glm::cross(vec3,vec3) */
  template<typename T> glm::tvec<T,3> inline cross(const glm::tvec<T, 3>& x, const glm::tvec<T,3>& y) {
    return glm::tvec<T,3>{/*x*/(x.y * y.z) - (y.y * x.z),
                          /*y*/(x.z * y.x) - (y.z * x.x),
                          /*z*/(x.x * y.y) - (y.x * x.y)};
  }
  
  /* glm::quat = glm::cross(quat,quat) */
  template<typename T> glm::tquat<T> inline cross(const glm::tquat<T>& q1, const glm::tquat<T>& q2) {
    return glm::tquat<T>{/*w*/T(0), 
                         /*x*/(q1.y * q2.z - q1.z * q2.y), 
                         /*y*/(q1.z * q2.x - q1.x * q2.z), 
                         /*z*/(q1.x * q2.y - q1.y - q2.x)}; 
  }
  
  /* linear interpolation */
  template<typename T, typename S> inline T mix(const T& A, const T& B, const S& t) { 
    return B + t * (B - A); 
  }
  // quadratic bezier (3 component interpolation)
  template<typename T, typename S> inline T mix(const T& A, const T& B, const T& C, const S& t)  {
    T D {glm::mix(A, B, t)}; // D = A + t(B - A)
    T E {glm::mix(B, C, t)}; // E = B + t(C - B)
    // T P = glm::mix(D, E, t); // P = D + t(E - D)
    return glm::mix(D, E, t); // P;
  }
  // cubic bezier (4 component interpolation)
  template<typename T, typename S> inline T mix(const T& A, const T& B, const T& C, const T& D, const S& t) {
    T E {glm::mix(A, B, t)};
    T F {glm::mix(B, C, t)};
    T G {glm::mix(C, D, t)};
    // T P {glm::mix(E, F, G, t};
    return glm::mix(E, F, G, t); // P
  }
  
  /* linear interpolation */
  template<typename T, typename S> inline T lerp(const T& A, const T& B, const S& t) { 
    return glm::mix(A,B,t); 
  } 
  
  // clamp value between a min(left) and a max(right)
  template<typename T> inline T clamp(T value, T left, T right) {
    return std::min(std::max(value, left), right);
  }  
  // clamp value between a min(left) and a max(right)
  template<typename T> inline T clamp(T value, T limit = T(0)) {
    return value < limit ? limit : value;
  }
  
  /* glm::aabb = glm::extend(glm::aabb,glm::aabb) // merge 2 aabbs */
  inline extern glm::aabb extend(const glm::aabb& lhs, const glm::aabb& rhs);
  /* glm::aabb = glm::extend(glm::aabb, glm::vec3) // extend aabb by vector (position) */
  template<typename T> inline extern glm::aabb extend(const glm::aabb& lhs, const glm::tvec3<T>& rhs);
  
  // clamp vector between 2 vector limits
  template<typename T, const ushort n> inline glm::tvec<T,n> clamp(const glm::tvec<T, n>& v, const glm::tvec<T, n>& left, const glm::tvec<T, n>& right) {
    return min(max(v, left), right);
  }
  
  template<typename T> T interpolate(const T& from, const T& to, real alpha, EInterpolate i) {
    switch (i) {
      default:
      case EInterpolate::LINEAR: /* keep as is*/
      break;
      case EInterpolate::EASE_IN: { /* x^3 */
        alpha = alpha*alpha*alpha;
        // alpha = 1 - cos(PI/2 * alpha)
      } break;
      case EInterpolate::EASE_IN_CIRCLE: { /* hemispeher - bottom half */
        alpha = 1 - std::sqrt(1 - alpha*alpha);
      } break;
      case EInterpolate::EASE_OUT: { /* 1 - (1-x)^3 */
        real beta = 1-alpha;
        alpha = 1 - beta*beta*beta;
        // alpha = sin(PI/2 * alpha)
      } break;
      case EInterpolate::EASE_OUT_CURCLE: { /* sqrt (1-(1-x)^2) */ /* hemispehere - top half */
        alpha = std::sqrt(1 - (1 -alpha)*(1-alpha));
      } break;
      case EInterpolate::EASE_IN_OUT: {
        real beta = 1 - alpha;
        real scale = real(4.0);
        alpha = (alpha < real(0.5)) ? alpha*alpha*alpha*scale 
                                    : 1 - (beta*beta*beta*scale); 
      } break;
      case EInterpolate::EASE_IN_OUT_CIRCLE: {
        alpha = (alpha < real(0.5)) ? real(0.5) * (1 - std::sqrt(1 - alpha*alpha))
                                    : real(0.5) * std::sqrt(1 - (1-alpha)*(1-alpha)) + real(0.5);
      } break;
      case EInterpolate::BOUNCE:
        // @todo
      case EInterpolate::ELASTIC:
        // @todo
      break;
    }
    
    return from + alpha * /*delta*/(to - from);
  }
  
// @todo glm::sign
// @todo glm::ceil
// @todo glm::fract // fraction
// @todo glm::mod   // modulus, reminder
// @todo glm::step  // 
// @todo glm::sstep // smoothstep

  /* glm::vec3 = glm::slerp(from,to,alpha,mode) // slerp // spherical linear interpolation */
  template<typename T, const ushort n> inline glm::tvec<T,n> slerp(const glm::tvec<T,n>& A, const glm::tvec<T,n>& B, T t, EInterpolate i = EInterpolate::LINEAR) {
    T zero {static_cast<T>(0)};
    T one  {static_cast<T>(1)};
    // interpolate t // default to LINEAR
    t = glm::interpolate(zero,one,t,i);
    // angle
    T coss  {glm::dot(A,B) / (A.length() * B.length())};
    T angle {std::acos(coss)};
    T isin  {one / std::sin(angle)};
    // scale
    T scale0 {std::sin((one - t) * angle) * isin};
    T scale1 {std::sin(t * angle) * isin};
    return {(A * scale0) + (B * scale1)};
  }

  /* glm::quat = glm::slerp(from,to,alpha,mode) // spherical linear interpolation */
  template<typename T> glm::tquat<T> slerp(const glm::tquat<T>& A, const glm::tquat<T>& B, T t, EInterpolate i = EInterpolate::LINEAR) {
    T zero {static_cast<T>(0)};
    T one  {static_cast<T>(1)};
    
    // interpolating, defaults to LINEAR
    t = glm::interpolate(zero, one, t, i);
    
    const T epsilon {std::numeric_limits<T>::epsilon()};
    T       C[4]; // basically = B
    T       omega, sinom, scale0, scale1;
    T       cosom = (A.x*B.x) + (A.y*B.y) + (A.z*B.z) + (A.w*B.w); // 4D dot product
    // cosom = glm::dot(A, B);
    
    assert(cosom < static_cast<T>(1.1)); // they should be unit quaterions <= 1.0f
    
    // adjust signs if necessary
    if(cosom < zero) {
      cosom = -cosom;
      C[0] = -B.x;
      C[1] = -B.y;
      C[2] = -B.z;
      C[3] = -B.w;
    } else {
      C[0] = B.x;
      C[1] = B.y;
      C[2] = B.z;
      C[3] = B.w;
    }
    
    // @if: fabs(1+cosom) < 0.001f ?
    
    // calculate coefficients // if 
    if (epsilon < (one - cosom)) {
      // standard case: slerp
      omega  = std::acos(cosom);
      sinom  = std::sin(omega);
      scale0 = std::sin((one - t) * omega) / sinom;
      scale1 = std::sin(t * omega) / sinom;
    } else {
      // A & B are very close: linear interpolation
      scale0 = one - t;
      scale1 = t;
    }
    
    return {
      /*w=*/scale0 * A.w + scale1 * C[3],
      /*x=*/scale0 * A.x + scale1 * C[0],
      /*y=*/scale0 * A.y + scale1 * C[1],
      /*z=*/scale0 * A.z + scale1 * C[2]
    };
  }

// @todo glm::isnan
// @todo glm::isinf
// @todo glm::pow
// @todo glm::exp
// @todo glm::log
// @todo glm::sqrt
// @todo glm::isqrt OR rsqrt
// @todo glm::wrap

// @todo glm::axis // ret q rotation axis

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* l = glm::length(vec3) */
  template<typename T, const ushort n> inline T length(const glm::tvec<T,n>& v) {
    T sum {0};
    for(ushort i = 0; i < n; i++)
      sum += v[i] * v[i];
    return (T)std::sqrt(sum);
  }
  /* l = glm::length(glm::plane) */
  template<typename T> inline T length(const glm::tplane<T>& p) { return static_cast<T>(std::sqrt(p.x*p.x + p.y*p.y + p.z*p.z)); } 
  
  /* float = glm::distance(vec3,vec3) // distance between 2 vectors | length(v1 - v0) */
  template<typename T, const ushort n> inline T distance(const glm::tvec<T,n>& v1, const glm::tvec<T,n>& v2) { return length(v2 - v1); }
  /* glm::real = glm::distance(glm::plane, glm::vec3) // distance from plane to point // < 0 (behinf) // = 0 (inside) // > 0 (front) */
  template<typename T> inline T distance(const glm::tplane<T>& p, const glm::tvec3<T>& v) {
    return p.x*v.x + p.y*v.y + p.z*v.z + p.d; // dot(p,v) + p.d
  }
  
  /* float = glm::angle(vec3,vec3) // angle between vectors | arccos(dot(v2, v1)) | needs normalized v1,v2 */
  template<typename T, const ushort n> T angle(const glm::tvec<T,n>& v1, const glm::tvec<T,n>& v2) { return static_cast<T>(std::acos(glm::dot(v1,v2))); }
  
  /* glm::vec3 = glm::normalize(glm::vec3) */
  template<typename T, const ushort n> glm::tvec<T,n> inline normalize(const glm::tvec<T,n>& v) {
    return v / glm::length(v);
  }
  /* glm::quat = glm::normalize(glm::quat) */
  template<typename T> glm::tquat<T> inline normalize(const glm::tquat<T>& q) { return q / glm::length(glm::tvec<T,4>(q)); }
  /* glm::aabb = glm::normalize(glm::aabb) // ensures min/max are correct(min < max) */
  extern inline glm::aabb normalize(const glm::aabb& a);
  /* glm::plane = glm::normalize(glm::plane) // normalize plane */
  template<typename T> inline glm::tplane<T> normalize(const glm::tplane<T>& p) { return p / glm::length(p); }
  
  /* glm::mat4 = glm::transpose(glm::mat4) // return matrix transpose */
  template <typename T, const ushort c, const ushort r> glm::tmat<T,r,c> transpose(const glm::tmat<T,c,r>& S) {
    glm::tmat<T,r,c> R;
    for (ushort j = 0; j < c; j++)
      for (ushort i = 0; i < r; i++)
        R[i][j] = S[j][i];
    return R;
  }
  
  /* glm::identity(glm::mat4) // return identity matrix from src matrix */
  template<typename T, const ushort c, const ushort r> glm::tmat<T,c,r>& identity(glm::tmat<T,c,r>& M) {
    M = glm::ZERO;
    for (ushort j = 0; j < r; j++)
      M[j][j] = glm::ONE;
    return M;
  }
  /* glm::identity(glm::quat) */
  template<typename T> glm::tquat<T>& identity(glm::tquat<T>& Q) { Q.w = glm::ONE; Q.x = Q.y = Q.z = glm::ZERO; return Q; }
  
  /* glm::mat3 = glm::shrink(glm::mat4,1,0) // shring matrix by elimination row & column */
  template<typename T, const ushort c, const ushort r> glm::tmat<T,c-1,r-1> shrink(const glm::tmat<T,c,r>& M, const ushort y = c-1, const ushort x = r-1) {
    assert((x < r) && (y < c) && r > 2 && c > 2);
    glm::tmat<T,c-1,r-1> R;
    for (ushort j1 = 0, j2 = 0; j1 < c; j1++) {
      if (y == j1) continue;
      for (ushort i1 = 0, i2 = 0; i1 < r; i1++) {
        if (x == i1) continue;
        R[j2][i2] = M[j1][i1];
        i2++;
      }
      j2++;
    }
    return R;
  }
  
  /* float = glm::det(glm::mat2) // determinant */
  template <typename T> inline T det(const glm::tmat<T,2,2>& M) { return (M[0][0] * M[1][1]) - (M[1][0] * M[0][1]); }
  /* float = glm::det(glm::mat4) // determinant */
  template<typename T, const ushort c, const ushort r> T det(const glm::tmat<T,c,r>& M) {
    static_assert((r > 1) && (c > 1), "1x1 Matrix not allowed!");
    T d {0};
    for(ushort j = 0; j < c; j++)
      d += (j % 2 == 0 ? 1 : -1) * M[j][0] * glm::det(glm::shrink(M, j, 0)); // glm::tmat<T,c-1,r-1>
    return d;
  }
  
  /* glm::vec4 = glm::row(glm::mat4,0) // extract row from matrix as a vector */
  template<typename T, const ushort c, const ushort r> inline glm::tvec<T,c> row(const glm::tmat<T,c,r>& m, ushort row) {
    assert(row < c);
    glm::tvec<T,c> v;
    for (ushort i = 0; i < c; i++)
      v[i] = m[i][row];
    return v;
  }
  /* glm::vec4 = glm::col(glm::mat4,3) // extract column from matrix as a vector */
  template<typename T, const ushort c, const ushort r> inline glm::tvec<T,r> col(const glm::tmat<T,c,r>& m, ushort col) {
    assert(col < r);
    return m[col];
  } 

  /* bool = glm::isIdentity(glm::mat4) */
  template<typename T, const ushort c, ushort r> inline bool isIdentity(const glm::tmat<T,c,r>& M) {
    for (ushort j = 0; j < c; j++)
      for (ushort i = 0; i < r; i++)
        if ((j == i && M[j][i] != glm::ONE) || (j != i && M[j][i] != glm::ZERO))
          return false;
    return true;
  }
  /* bool = glm::isIdentity(glm::quat) */
  template<typename T> inline bool isIdentity(const glm::tquat<T>& Q) { return (Q.w == glm::ONE && Q.x == glm::ZERO && Q.y == glm::ZERO && Q.z == glm::ZERO); }

  /* glm::mat4 = glm::asMatrix(glm::quat) */
  template<typename T> glm::tmat<T,4,4> asMatrix(const glm::tquat<T>& q) {
    // consts
    static constexpr const T ZERO {static_cast<T>(0)}; 
    static constexpr const T  ONE {static_cast<T>(1)}; 
    static constexpr const T  TWO {static_cast<T>(2)}; 
    // variables
    const T xx {q.x * q.x};
    const T yy {q.y * q.y};
    const T zz {q.z * q.z};
    // const T ww = q.w * q.w;
    const T xy {q.x * q.y};
    const T xz {q.x * q.z};
    const T xw {q.x * q.w};
    const T yz {q.y * q.z};
    const T yw {q.y * q.w};
    const T zw {q.z * q.w};
    // initializer
    return {
    /*m[0][0] = */ONE - TWO * (yy + zz),
    /*m[0][1] = */      TWO * (xy + zw), // -
    /*m[0][2] = */      TWO * (xz - yw), // +
    /*m[0][3] = */      ZERO,

    /*m[1][0] = */      TWO * (xy - zw), // +
    /*m[1][1] = */ONE - TWO * (xx + zz), 
    /*m[1][2] = */      TWO * (yz + xw), // -
    /*m[1][3] = */      ZERO,

    /*m[2][0] = */      TWO * (xz + yw), // -
    /*m[2][1] = */      TWO * (yz - xw), // +
    /*m[2][2] = */ONE - TWO * (xx + yy),
    /*m[2][3] = */      ZERO,

    /*m[3][0] = */      ZERO,
    /*m[3][1] = */      ZERO,
    /*m[3][2] = */      ZERO,
    /*m[3][3] = */       ONE};
  }
  
  /* glm::frustum = glm::asFrustum(glm::mat4) // convert matrix to a frustum (6 planes) */
  template<typename T> extern inline glm::frustum asFrustum(const glm::tmat<T,4,4>& M);
  
  template<typename T> sys::array<glm::tplane<T>,6> asPlanes(const glm::tmat<T,4,4>& PV) {
    sys::array<glm::tplane<T>,6> tPlanes;
    // extract rows
    const glm::tvec4<T> row0 {glm::row(PV, 0)};
    const glm::tvec4<T> row1 {glm::row(PV, 1)};
    const glm::tvec4<T> row2 {glm::row(PV, 2)};
    const glm::tvec4<T> row3 {glm::row(PV, 3)};
    // left
    tPlanes[EPlane::LEFT] = row3 + row0;
    tPlanes[EPlane::LEFT].normalize();
    // right
    tPlanes[EPlane::RIGHT] = row3 - row0;
    tPlanes[EPlane::RIGHT].normalize();
    // bottom 
    tPlanes[EPlane::BOTTOM] = row3 + row1;
    tPlanes[EPlane::BOTTOM].normalize();
    // top
    tPlanes[EPlane::TOP] = row3 - row1;
    tPlanes[EPlane::TOP].normalize();
    // near
    tPlanes[EPlane::NEAR] = row3 + row2;
    tPlanes[EPlane::NEAR].normalize();
    // far
    tPlanes[EPlane::FAR] = row3 - row2;
    tPlanes[EPlane::FAR].normalize();
    // return array
    return tPlanes;
  }
  
  /* populate a matrix with quaterion values */
  template<typename T> inline void quat2mat(const glm::tquat<T>& q, glm::tmat<T, 4, 4>& m) { m = q.asMatrix(); }
  /* extract matrix4x4 from a quaterion */
  template <typename T> glm::tmat<T,4,4> quat2mat(const glm::tquat<T>& q) { return q.asMatrix(); }
  
  /* glm::quat = glm::conjugate(glm::quat) // return the quaterion conjugate */
  template<typename T> glm::tquat<T> inline conjugate(const glm::tquat<T>& q) { return glm::tquat<T>(q.w, -q.x, -q.y, -q.z); }
  
// @todo inverse matrix
  template<typename T, const ushort c, const ushort r> glm::tmat<T,c,r> inverse(const glm::tmat<T,c,r>& M) {
    return glm::tmat<T,c,r>{};
  }
  /* glm::quat = glm::inverse(glm::quat) // return inversed quaternion */
  template<typename T> glm::tquat<T> inverse(const glm::tquat<T>& q) { glm::tquat<T> r{q}; r.inverse(); return r; }
  
  /* glm::mat4 = glm::matCompMult(mat4,mat4) // matrix x matrix component multiplication */
  template <typename T, const ushort c, const ushort r> inline glm::tmat<T,c,r> matCompMult(const glm::tmat<T,c,r>& m1, const glm::tmat<T,c,r>& m2) {
    glm::tmat<T,c,r> result;
    for(ushort j = 0; j < r; j++)
      for(ushort i = 0; i < c; i++) 
        result[i][j] = m1[i][j] * m2[i][j];
    return result;
  }
  
  /* glm::real = glm::halfSpace(glm::plane,glm::vec3) // < 0 (behind) // = 0 (on plane) // > 0 (front) */
  template<typename T> inline T halfSpace(const glm::tplane<T>& p, const glm::tvec3<T>& v) {
    // plane => a*x + b*y + c*z +d = 0
    // were (a,b,c) is the normal of the plane, & d is the distance from the origin.
    // if a point is on the plane then the equation = 0, if in front then > 0 (positive), if behind < 0 (negative)
    
    // plane's normal
    glm::tvec4<T> N {glm::tvec4<T>{p.n, T(0)}};
    // point on plane (where then normal starts pointing) //         * V (v in front of plane)
    glm::tvec4<T> P {p.n * p.d, T(1)};                    //    N ^ /
    // V as a 4D vector                                   //      |/
    glm::tvec4<T> V {v,T(1)};                             //  ----*-->*-
    // vector (direction) from plane to v                 //      P   V (v on the plane)
    glm::tvec4<T> D {P - V};
    // compare normal & vector to v // if 0 => v on plane, if > 0 => v in front of plane, if < 0 => v begind plane
    return glm::dot(N,D);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo glm::pitch // x axis // look up-down         // pitch = airplane goes up-dow
// @todo glm::yaw   // y axis // look left-right      // yaw = turn left-right
// @todo glm::roll  // z axis // tilt head left-right // roll = do a barrale roll = spin
  
  /* glm::mat4 = glm::rotate(a,x,y,z) // rotation matrix from axis and angle | R = cos*I + sin*[u]x + (1-cos)uXu | tensor product */
  template<typename T> inline tmat<T,4,4> rotate(const T& deg, const T& x, const T& y, const T& z) {
    // return glm::rotate(a, glm::tvec<T,3>{x,y,z});
    const T xx {x * x};
    const T yy {y * y};
    const T zz {z * z};
    const T xy {x * y};
    const T xz {x * z};
    const T yz {y * z};

    static const T ZERO {static_cast<T>(0)};
    static const T ONE  {static_cast<T>(1)};
    
    const T rad {glm::radians(deg)};               // float, (PI angle)
    const T c   {static_cast<T>(std::cos(rad))}; // float
    const T s   {static_cast<T>(std::sin(rad))}; // float
    const T omc {ONE - c};                       // one minus cos

    return glm::tmat<T,4,4>{glm::tvec<T,4>{xx * omc + c,     xy * omc + z * s, xz * omc - y * s, ZERO},
                            glm::tvec<T,4>{xy * omc - z * s, yy * omc + c,     yz * omc + x * s, ZERO},
                            glm::tvec<T,4>{xz * omc + y * s, yz * omc - x * s, zz * omc + c,     ZERO},
                            glm::tvec<T,4>{ZERO,             ZERO,             ZERO,              ONE}};
  }
  /* glm::mat4 = glm::rotate(deg, glm::vec3) // rotation matrix - vector */
  template<typename T> inline glm::tmat<T,4,4> rotate(const T& deg, const glm::tvec<T,3>& v) {
    return glm::rotate(deg, v.x, v.y, v.z);
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
  template<typename T> inline glm::tmat<T,4,4> rotate(const T& ax, const T& ay, const T& az) {
    return glm::rotate(ax, T(1), T(0), T(0)) * glm::rotate(ay, T(0), T(1), T(0)) * glm::rotate(az, T(0), T(0), T(1));
  }
  /* rotate vector around axis by angle theta */
  template<typename T> inline void rotate(glm::tvec<T,3>& v, const T& theta, const glm::tvec<T,3>& a) {
    //const T s = std::sin(radians(theta / T(2)));
    //const T c = std::cos(radians(theta / T(2)));
    
    glm::tquat<T> V {static_cast<T>(0), v.x, v.y, v.z};
    //quat R(a.x * s, a.y * s, a.z * s, c);
    glm::tquat<T> R {theta, a};
    glm::tquat<T> C {glm::conjugate(R)};
    glm::tquat<T> W {(R * V) * C};
    
    //sys::info << R << sys::endl;
    //sys::info << V << sys::endl;
    //sys::info << C << sys::endl;
    
    v.x = W.x;
    v.y = W.y;
    v.z = W.z;
  }
  /* return oritantion matrix from quaternion */
  template<typename T> inline glm::tmat<T,4,4> rotate(const glm::tquat<T>& Q) { return Q.asMatrix(); }
  /* rotate/orientate vector by quaternion */
  template<typename T,ushort n> inline glm::tvec<T,n>& rotate(glm::tvec<T,n>& v, const glm::tquat<T>& Q) { v = Q.asMatrix() * v; return v; }
  /* rotate/orientate vector by quaternion */
  template<typename T,ushort n> inline glm::tvec<T,n> rotate(const glm::tvec<T,n>& v, const glm::tquat<T>& Q) { return Q.asMatrix() * v; }
  /* rotate vector by quaternion */
  template<typename T> inline glm::tvec<T,3> rotate(const glm::tquat<T>& R, const glm::tvec<T, 3>& v) {
    glm::tquat<T> V {static_cast<T>(0), v.x, v.y, v.z};
    glm::tquat<T> C {glm::conjugate(R)};
    glm::tquat<T> W {(R * V) * C};
    return {W.x, W.y, W.z};
  }
  
  /* rotate vector around the X axis by a */
  template <typename T, const ushort n> inline glm::tvec<T,n> rotateX(const T& a, const glm::tvec<T,n>& vec) {
    glm::tvec<T,n> res(vec);
    const T rads = glm::radians(a);
    const T cosa = std::cos(rads);
    const T sina = std::cos(rads);
    
    res.y = vec.y * cosa - vec.z * sina;
    res.z = vec.y * sina + vec.z * cosa;
    
    return res;
  }
  /* rotate vector around the Y axis by a */
  template<typename T, const ushort n> inline glm::tvec<T,n> rotateY(const T& a, const glm::tvec<T,n>& vec) {
    glm::tvec<T,n> res(vec);
    const T rads = glm::radians(a);
    const T cosa = std::cos(rads);
    const T sina = std::cos(rads);
    // calc x & z
    res.x = vec.x * cosa + vec.z * sina;
    res.z =-vec.x * sina + vec.z * cosa;
    // done
    return res;
  }
  
  /* matrix-vector scaling - scalars */
  template<typename T> inline glm::tmat<T, 4, 4> scale(const T& x, const T& y, const T& z) {
    return glm::tmat<T,4,4>(glm::tvec<T,4>(   x, T(0), T(0), T(0)),
                            glm::tvec<T,4>(T(0),    y, T(0), T(0)),
                            glm::tvec<T,4>(T(0), T(0),    z, T(0)),
                            glm::tvec<T,4>(T(0), T(0), T(0), T(1))
    );
  }
  /* matrix-vector scaling - vector */
  template<typename T> inline glm::tmat<T, 4, 4> scale(const glm::tvec<T,3>& v) { return scale(v[0],v[1],v[2]); }
  /* matrix-vector scaling - vector */
  template<typename T> inline glm::tmat<T, 4, 4> scale(T s) { return scale(s, s, s); }
  
  /* glm::translate // create translation matrix from a direction vector */
  template<typename T> inline glm::tmat<T,4,4> translate(const glm::tvec<T,3>& v) {
    static const T ZERO {static_cast<T>(0)};
    static const T  ONE {static_cast<T>(1)};
    return glm::tmat<T,4,4>{glm::tvec<T,4>{ ONE, ZERO, ZERO, ZERO},    // 1 0 0 v0
                            glm::tvec<T,4>{ZERO,  ONE, ZERO, ZERO},    // 0 1 0 v1
                            glm::tvec<T,4>{ZERO, ZERO,  ONE, ZERO},    // 0 0 0 v2
                            glm::tvec<T,4>{v[0], v[1], v[2],  ONE}};   // 0 0 1 v3
  }
  /* glm::mat4& = glm::traslate(glm::mat4, glm::ved3) */
  template<typename T> glm::tmat<T,4,4>& translate(glm::tmat<T,4,4>& M, const glm::tvec3<T>& v) { M[3] = M[0]*v[0] + M[1]*v[1] + M[2]*v[2] + M[3]; return M; }
  
  /* @see CVector.hpp operator *(mat,vec) */
  template<typename T, ushort c, ushort r> inline glm::tvec<T,r>& transform(glm::tvec<T,r>& v, const glm::tmat<T,c,r>& M) { v = M * v; return v; }
  /* @see CVector.hpp operator *(mat,vec) */
  template<typename T, ushort c, ushort r> inline glm::tvec<T,r> transform(const glm::tvec<T,r>& v, const glm::tmat<T,c,r>& M) { return M * v; } 
  
  /* apply transform to vector */
  template<typename T, ushort n> inline glm::tvec<T,n>& transform(glm::tvec<T,n>& v, const glm::txform<T>& X) { v = X.asMatrix() * v; return v; }
  /* apply transform to vector */
  template<typename T, ushort n> inline glm::tvec<T,n> transform(const glm::tvec<T,n>& v, const glm::txform<T>& X) { return X.asMatrix() * v; }
  /* extern */
  template<typename T> extern glm::aabb transform(const glm::aabb& tAABB, const glm::txform<T>& tXform);
  
  /* vec3 = glm::reflect(vec3,vec3) // reflect vector relative to surface normal */
  template<typename T, const ushort n> inline glm::tvec<T,n> reflect(const glm::tvec<T,n>& I, const glm::tvec<T,n>& N) {
    // dot(N, I) - angle between vector & normal       //       /|2 * dot(I,N) * N 
    // 2 * dot(N, I) * N - resize normal               //    -I/ |
    return static_cast<T>(2) * glm::dot(I, N) * N - I; //     R\ |N/I
    // return I - T(2) * dot(N, I) * N;                //       \|/    
  }
  
// @todo glm::refract
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // @todo: glm::ortho(T left, T right = screen.width, T bottom = screen.height, T top, T near, T far) //
  template<typename T> glm::tmat<T,4,4> inline ortho(T left, T right, T bottom, T top, T near, T far) {
    return { T(2)/(right-left),          T(0),                        T(0),            T(0),
             T(0),                       T(2)/(top-bottom),           T(0),            T(0),
             T(0),                       T(0),                       -T(1)/(far-near), T(0),
             -(right+left)/(right-left), -(top+bottom)/(top-bottom), -near/(far-near), T(1) };
  } 
    
// @todo glm::frustum(T left, T right, T bottom, T top, T near, T far) // return mat4 // frustumRH_NO // right-hand negative z
  // if((right == left) || (top == bottom) || (near == far) || (near < T(0)) || (far < T(0)))
  //   return identity<T, 4>();
  // return CMatrix<T, 4, 4>(
  //   tvec<T, 4>((T(2) * near) / (right - left), T(0) ,                          (right + left) / (right - left), T(0)),
  //   tvec<T, 4>(T(0),                           (T(2) * near) / (top - bottom), (top + bottom) / (top - bottom), T(0)),
  //   tvec<T, 4>(T(0),                           T(0),                           -(far + near)  / (far - near),    -(T(2) * far * near) / (far - near)),
  //   tvec<T, 4>(T(0),                           T(0),                           -T(1),                           T(0))
  // );
    
  /* glm::mat4 P = glm::perspective(T fov, T width, T hight, T near, T far) // perspectiveFovRH_NO = right-hand & negative z */
  template<typename T> glm::tmat<T,4,4> inline perspective(T fov, T width, T height, T near, T far) {
    assert(width  > glm::ZERO);
    assert(height > glm::ZERO);
    assert(fov    > glm::ZERO);
    assert(far    > near);
    const T hrad  {glm::radians(fov) / glm::TWO}; // half radians
    const T m_h   {std::cos(hrad) / std::sin(hrad)}; // h // m11
    const T ratio {height / width};
    const T m_w   {m_h * ratio};                     // w // m00
    return { m_w,       glm::ZERO,  glm::ZERO,                      glm::ZERO,
             glm::ZERO, m_h,        glm::ZERO,                      glm::ZERO,
             glm::ZERO, glm::ZERO, -(far+near)/(far-near),          -glm::ONE,
             glm::ZERO, glm::ZERO, -(glm::TWO*far*near)/(far-near), glm::ZERO };
  }
  /* glm::mat4 P = glm::perspective() // P using fov, aspect ratio, near & far planes // perspectiveRH_NO = right-hand & negative z */
  template<typename T> glm::tmat<T,4,4> inline perspective(T fovy, T ratio, T near, T far) {
    assert(far > near);
    assert(ratio > glm::ZERO);
    const T thf {std::tan(glm::radians(fovy/glm::TWO))}; // tan half fov
// @todo: allow radians AND degrees
    const T m_h {glm::ONE / thf};
    const T m_w {glm::ONE / (ratio * thf)};
    return { m_w,       glm::ZERO, glm::ZERO,                       glm::ZERO,
             glm::ZERO, m_h,       glm::ZERO,                       glm::ZERO,
             glm::ZERO, glm::ZERO, -(far+near)/(far-near),          -glm::ONE,
             glm::ZERO, glm::ZERO, -(glm::TWO*far*near)/(far-near), glm::ZERO };
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
  
  /* glm::mat4 V = glm::lookat(vec3 pos/eye, vec3 target/center, vec3 up) // view(space) matrix // lookAtRH */
  template<typename T> inline glm::tmat<T,4,4> lookat(glm::tvec<T,3> p/*position,eye*/, glm::tvec<T,3> t/*target,center*/, glm::tvec<T,3> a/*up*/) {
    const glm::tvec<T,3> f{glm::normalize(t - p)};            // direction = position -> target 
    const glm::tvec<T,3> s{glm::normalize(glm::cross(f,a))};  // side = forward x up
    const glm::tvec<T,3> u{glm::cross(s,f)};                  // up - recomputed       //      c0   c1   c2   c3
    return { glm::tvec<T,4>{/* m.0   */s.x,/* m.1  */ u.x,/* m.2  */-f.x, glm::ZERO},  // r0 |  sx   sy   sz -(s*p) |
             glm::tvec<T,4>{/* m.4   */s.y,/* m.5  */ u.y,/* m.6  */-f.y, glm::ZERO},  // r1 |  ux   uy   uz -(u*p) |
             glm::tvec<T,4>{/* m.8   */s.z,/* m.9  */ u.z,/* m.10 */-f.z, glm::ZERO},  // r2 | -fx  -fy  -fz  (f*p) |
             glm::tvec<T,4>{-glm::dot(s,p),-glm::dot(u,p), glm::dot(f,p),  glm::ONE} };// r3 |   0    0    0      1 |
    //return M * glm::translate(-p);
  }
  
// @todo glm::unProject(vec3 window, mat4 modelview, mat4 perspective, vec4 viewport)
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
  
// @todo: implament this
  template<typename T> ECompare compare(const glm::tray<T>& r, const glm::plane& p) {
    return ECompare::OUTSIDE;
  }
  
  /* glm::ECompare = glm::compare(glm::aabb,glm::aabb) // aabb inside/outside/intersect another aabb */
  extern inline ECompare compare(const glm::aabb& lhs, const glm::aabb& rhs);
  
  /* glm::ECompare = glm::compare(glm::frustum, glm::aabb) // is aabb inside/outside/intersect the frustum */
  extern inline ECompare compare(const glm::frustum& lhs, const glm::aabb& rhs);
  
// @todo: compare vs classify
  
  /* glm::ECompare = glm::compare(glm::plane, glm::vec3) // find position of vector v relative to plane p */
  template<typename T> ECompare compare(const glm::tplane<T>& p, const glm::tvec3<T>& v) {
    glm::real d {glm::distance(p,v)};
    if (glm::lt(d,glm::ZERO))/*<0*/ return ECompare::BEHIND; // < 0 // NEGATIVE
    if (glm::eq(d,glm::ZERO))/*=0*/ return ECompare::INSIDE; // = 0 // ONPLANE
    /*if (glm::gt(d,T(0)))*/ /*>0*/ return ECompare::FRONT;  // > 0 // POSITIVE
  }
}

#endif //__glm_hpp__
