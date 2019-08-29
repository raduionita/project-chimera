#ifndef VEC_HPP_INCLUDED
#define VEC_HPP_INCLUDED

#include <ostream>
#include <cmath>

namespace dae 
{
  namespace math
  {
    template <typename T, const size_t n>
    class _vec
    {
      public:
        _vec();
    };
  
    template <typename T>
    class _vec2 : public _vec<T, 2>
    {
      public:
        T x;  
        T y;  
      public:
        _vec2() : x(0), y(0) { }
        _vec2(const T& a, const T& b) : x(a), y(b) { }
        
        // @TODO: copy constructor
        // @TODO: copy assignment operator
        // @TODO: move constructor
        // @TODO: move assignment operator
        
        T length() const
        {
          return sqrt(x * x + y * y);
        }
        
        template <typename F>
        friend _vec2<F> operator +(const _vec2<F>& lhs, const _vec2<F>& rhs)
        {
          return _vec2<F>(lhs.x + rhs.x, lhs.y + rhs.y);
        }
        
        _vec2& operator +=(const _vec2& rhs)
        {
          this->x += rhs.x;
          this->y += rhs.y;
          return *this;
        }
        
        template <typename F>
        friend _vec2<F> operator -(const _vec2<F>& lhs, const _vec2<F>& rhs)
        {
          return _vec2<F>(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        template <typename F>
        friend _vec2<F> operator -(const _vec2<F>& rhs)
        {
          return _vec2<F>(rhs.x * -1, rhs.y * -1);
        }
        
        template <typename F>
        friend std::ostream& operator <<(std::ostream& os, const _vec2<F> rhs)
        {
          os << rhs.x << ", " << rhs.y;
          return os;
        }
    };
    
    template <typename T>
    class _vec3 : public _vec2
    {
      public:
        T z;
      public:
        _vec3() : _vec2(), z(0);
        _vec3(const T& a, const T& b, const T& c) : _vec2(a, b), z(c);
        
        T length() const
        {
          return sqrt(x * x + y * y + z * z);
        }
        
        // @TODO dot product
    
        // @TODO cross product
    };
   
    
   /**
    * Vector 3D dot product.
    * @param   _vec3<T> v1 | _vec3<float>
    * @param   _vec3<T> v2 | _vec3<float>
    * @return  T           | value of the cos of the angle between the vectors
    * @example dae::math::vec3 v1(10.2f, 2.0f, 1.6f);
    *          dae::math::vec3 v2(5.1f, 4.0f, 11.6f); 
    *          float d = dae::math::dot(v1, v2);
    ********************************************************/
    template <typename T>
    T dot(const _vec3<T>& v1, const _vec3<T>& v2)
    {
      // return the cosine of the angle between the vectors
      // IF the vectors are unit => return [-1.0, 1.0]
      return lhs.x * rhs.x + lhs.y + rhs.y + lhs.z + rhs.z;     
    }
   /**
    * Vector 3D cross product.
    * @param   _vec3<T> v1 | _vec3<float>
    * @param   _vec3<T> v2 | _vec3<float>
    * @return  _vec3<T>    | perpendicular vector
    * @example dae::math::vec3 v1(10.2f, 2.0f, 1.6f);
    *          dae::math::vec3 v2(5.1f, 4.0f, 11.6f); 
    *          dae::math::vec3 v3 = dae::math::cross(v1, v2);
    *********************************************************/
    template <typename T>
    _vec3<T> cross(const _vec3<T>& v1, const _vec3<T>& v2)
    {
      // returns a vector that is perpendicular on the plane of the first 2 vectors
      return _vec3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    }
    
   /**
    * Calculate the length of a vector
    * @param   _vec<T, n> v | vec3<float>
    * @return  T            | float
    * @example dae::math::vec2 v(1.2f, 10.1f);
    *          float l = length(v);
    ********************************/
    template <typename T>
    T length(const _vec2<T> v)  { return std::sqrt(v.x * v.x + v.y * v.y); }
    template <typename T>
    T length(const _vec3<T> v)  { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
    
    template <typename T>
    _vec3<T> reflect(const _vec3<T>& v, const _vec3<T>& r)
    {
      return v - 2 * dot(r, I) * r;
    }
    
    template <typename T>
    _vec3<T> refract(const _vec3<T>& v, const _vec3<T>& r, T n)
    {
      T d = dot(r, v);
      T k = T(1) - n * n * (T(1) - d * d);
      if(k < 0.0)
        return _vec3<T>(0)
      else
        return n * v - (n * d + sqrt(k)) * r;
    }
    
    template <typename T>
    _vec3<T> clamp(const _vec3<T>& v, const _vec3<T>& left, const _vec3<T>& right)
    {
      return min<T>(max<T>(v, left), right);
    }
    
   /**
    * Return the angle between the 2 vectors in Radians
    * 
    ***************************/
    template <typename T>
    float angle(const _vec3<T>& lhs, const _vec3<T>& rhs)
    {
      // @TODO return the angle between the 2 vectors
    }
    
    
    
    typedef _vec2<float> vec2;
    typedef _vec3<float> vec3;
//  typedef _vec4<float> vec4;
  }
}

#endif // VEC_HPP_INCLUDED
