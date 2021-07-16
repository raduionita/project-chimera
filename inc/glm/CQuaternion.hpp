#ifndef __glm_cquaternion_hpp__
#define __glm_cquaternion_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
#include "glm/CMatrix.hpp"

namespace glm {
  template<typename T> class CQuaternion {
      typedef CQuaternion<T> type;
      typedef T              data_type;
      // consts
      static constexpr const T ZERO {static_cast<T>(0)}; 
      static constexpr const T  ONE {static_cast<T>(1)}; 
      static constexpr const T  TWO {static_cast<T>(2)}; 
    public:
      union { T data[4]; struct { T w; T x; T y; T z; }; };
    public:
      CQuaternion() : w{ONE}, x{ZERO}, y{ZERO}, z{ZERO} { }
      CQuaternion(const T s) : w(s), x{ZERO}, y{ZERO}, z{ZERO} { }
      CQuaternion(const T w, const T x, const T y, const T z) : w(w), x(x), y(y), z(z) { }
      /* unit quaterion from a 3D vector */
      CQuaternion(const glm::tvec<T,3>& v) : x{v.x}, y{v.y}, z{v.z} {
        // this is a unit quat - compute w // w*w + x*x + y*y + z*z = 1
        T t = ONE - (v.x*v.x) - (v.y*v.y) - (v.z*v.z);
        w = t < ZERO ? ZERO : -(T)std::sqrt(t);
      }
      /* quaterion from pitch, yaw, roll */
      CQuaternion(const T pitch, const T yaw, const T roll) {
        T half {static_cast<T>(0.5)};
        T p {glm::radians(pitch * half)};
        T y {glm::radians(yaw   * half)};
        T r {glm::radians(roll  * half)};
        
        T sinp {static_cast<T>(std::sin(p))};
        T siny {static_cast<T>(std::sin(y))};
        T sinr {static_cast<T>(std::sin(r))};
        T cosp {static_cast<T>(std::cos(p))};
        T cosy {static_cast<T>(std::cos(y))};
        T cosr {static_cast<T>(std::cos(r))};
        
        w = cosr * cosp * cosy + sinr * sinp * siny;
        x = sinr * cosp * cosy - cosr * sinp * siny;
        y = cosr * sinp * cosy + sinr * cosp * siny;
        z = cosr * cosp * siny - sinr * sinp * cosy;
        
        normalize();
      }
    public:
      /* quat = quat */
      CQuaternion& operator =(const CQuaternion& that) {
        if (this != &that) {
          w = that.w;
          x = that.x;
          y = that.y;
          z = that.z;
        }
        return *this;
      }
      /* quat = s // scalar */
      CQuaternion& operator =(const T& s) { w = s; x = y = z = ZERO; return *this; }
      /* quat = vec3 */
      CQuaternion& operator =(const glm::tvec<T,3>& v) {
        x = v.x; y = v.y; z = v.z;
        // this is a unit quat - compute w // w*w + x*x + y*y + z*z = 1
        T t = ONE - (v.x*v.x) - (v.y*v.y) - (v.z*v.z);
        w = t < ZERO ? ZERO : -(T)std::sqrt(t);
        return *this;
      }
    public:
      /* quat[i] */
      T&       operator [](uint i)       { assert(i >= 0 && i < 4); return data[i]; }
      /* const quat[i] */
      const T& operator [](uint i) const { assert(i >= 0 && i < 4); return data[i]; }
    public:
      /* quat = quat + quat */
      CQuaternion   operator + (const CQuaternion& rhs) const { return CQuaterion(w + rhs.w, x + rhs.x, y + rhs.y, z + rhs.z); }
      /* quat += quat */
      CQuaternion&  operator +=(const CQuaternion& rhs) { w += rhs.w; x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
      /* quat = quat - quat */
      CQuaternion   operator - (const CQuaternion& rhs) const { return CQuaternion(w - rhs.w, x - rhs.x, y - rhs.y, z - rhs.z); }
      /* quat -= quat */
      CQuaternion&  operator -=(const CQuaternion& rhs) { w -= rhs.w; x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
      /* = -quat */
      CQuaternion   operator - () const { return CQuaternion(-w, -x, -y, -z); }
      /* quat = quat * s */
      CQuaternion   operator * (const T s) const { return CQuaternion(w * s, x * s, y * s, z * s); }
      /* quat *= s */
      CQuaternion&  operator *=(const T s) { w *= s; x *= s; y *= s; z *= s; return *this; }    
      /* quat = quat * quat */
      CQuaternion   operator * (const CQuaternion& q) const {
        return CQuaternion<T>((w * q.w) - (x * q.x) - (y * q.y) - (z * q.z),
                              (w * q.x) + (x * q.w) + (y * q.z) - (z * q.y),
                              (w * q.y) - (x * q.z) + (y * q.w) + (z * q.x),
                              (w * q.z) + (x * q.y) - (y * q.x) + (z * q.w));
      }
      /* quat *= quat */
      CQuaternion&  operator *=(const CQuaternion& rhs) { *this = *this * rhs; return *this; }
      /* quat = quat * vec4 */
      CQuaternion   operator * (const CVector<T,4>& v) const{
        return CQuaternion<T>((w * v.w) - (x * v.x) - (y * v.y) - (z * v.z),   // w
                              (w * v.x) + (x * v.w) + (y * v.z) - (z * v.y),   // x
                              (w * v.y) - (x * v.z) + (y * v.w) + (z * v.x),   // y
                              (w * v.z) + (x * v.y) - (y * v.x) + (z * v.w));  // z
      }
      /* vec3 = quat * vec3 */
      CVector<T,3>  operator * (const CVector<T,3>& v) const {
        CVector<T, 3> vn = glm::normalize(v);
        // quat from vec3 
        CQuaternion<T> V(ZERO, vn.x, vn.y, vn.z);
        CQuaternion<T> C = glm::inverse(*this);
        CQuaternion<T> R = *this * (V * C);
        // return vector
        return CVector<T,3>(R.x, R.y, R.z);
        // glm alternative
        // const glm::tvec<T,3>   u{x,y,z}; // quat-vector
        // const glm::tvec<T,3>  uv{glm::cross(u,v)};
        // const glm::tvec<T,3> uuv{glm::cross(u,uv)};
        // return v + static_cast<T>(2) * ((uv * w) + uuv);
      }
      /* quat = quat / s */
      CQuaternion   operator / (const T s) const { return CQuaternion(w / s, x / s, y / s, z / s); }
      /* quat /= s */
      CQuaternion&  operator /=(const T s) { w /= s; x /= s; y /= s; z /= s; return *this; }
    public:
      /* vec4 = quat */
      operator       CVector<T, 4>() { return CVector<T, 4>(x, y, z, w); }
      /* const vec4 = quat */
      operator const CVector<T, 4>() const { return CVector<T, 4>(x, y, z, w); }
      /* float* = (float*)(quat) */
      explicit operator         T*() { return (T*)(&data[0]); }
      /* const float* = (const float*)(quat) */
      explicit operator const   T*() const { return (const T*)(&data[0]); }
    public:
      /* bool = quat == quat */
      bool operator == (const CQuaternion& rhs) const { return (w == rhs.w) && (x == rhs.x) && (y == rhs.y) && (z == rhs.z); }
      /* bool = quat != quat */
      bool operator != (const CQuaternion& rhs) const { return (w != rhs.w) || (x != rhs.x) || (y != rhs.y) || (z != rhs.z); }
    public:
      /* length (pythagora's) */
      T length() const { return std::sqrt(w*w + x*x + y*y + z*z); }
      /* normalize (like a vector), lenght should be 1 after this */
      void normalize() {
        T ll {w*w + x*x + y*y + z*z};
        
        if (std::fabs(ll) > std::numeric_limits<T>::epsilon() && std::fabs(ll - ONE) > std::numeric_limits<T>::epsilon()) {
          T l {std::sqrt(ll)};
          w /= l; x /= l; y /= l; z /= l;
        }
      }
      /* make this quat a conjugate of itself quat(w,-x,-y,-z) */
      void conjugate() { x = -x; y = -y; z = -z; }
      /* inverse = conjugate & normalize */
      void inverse() { conjugate(); normalize(); }
      /* as matrix */
      glm::tmat<T,4,4> toMatrix() const {
        // temps
        const T xx {x * x};
        const T yy {y * y};
        const T zz {z * z};
        //const T ww {w * w};
        const T xy {x * y};
        const T xz {x * z};
        const T xw {x * w};
        const T yz {y * z};
        const T yw {y * w};
        const T zw {z * w};
        // return initializer
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
      /* @todo: return angle to axis */
      T getAxisAngle() const {
        const T scale = std::sqrt(x * x + y * y + z * z);
        const glm::tvec3<T>& axis(x / scale, y / scale, z / scale);
        const T angle = std::acos(w) * static_cast<T>(2);
        return angle;
      }
      /* to rotation */
      inline glm::tvec3<T> toRotation() const {
        const T t0  {TWO * (w*x + y*z)};
        const T t1  {ONE - TWO*(x*x + y*y)};
        const T r   {std::atan2(t0,t1)};
        T t2  {TWO * (w*y - z*x)};
          t2 = t2 >  ONE ?  ONE : t2;
          t2 = t2 < -ONE ? -ONE : t2;
        const T p   {std::asin(t2)};
        const T t3  {TWO * (w*z + x*y)};
        const T t4  {ONE - TWO * (y*y + z*z)};
        const T y   {std::atan2(t3,t4)};
        return {p,y,r};
      }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> glm::tquat<T> operator * (const T& s, const glm::tquat<T>& q) { return q * s; }
  
  template <typename T> glm::tquat<T> operator / (const T& s, const glm::tquat<T>& q) { return glm::tquat<T>(s / q.w, s / q.x, s / q.y, s / q.z); }
  
  template <typename T> glm::tvec<T,4> operator *(const glm::tquat<T>& q, const glm::tvec<T,4>& v) {
    return glm::tvec<T,4>(q * glm::tvec<T,3>(v), v.w);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const glm::tquat<T>& q) {
    std::ostringstream oss;
    oss << "q(" << q.w << ',' << q.x << ',' << q.y << ',' << q.z << ')';
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }
  
  template <typename T> std::ostream& operator <<(std::ostream& out, const glm::tquat<T>& q) {
    return out << "q("<< q.w << ',' << q.x << ',' << q.y << ',' << q.z << ')';
  }
}

#endif //__glm_cquaternion_hpp__
