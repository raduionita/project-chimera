#ifndef MATH_HPP_INCLUDED
#define MATH_HPP_INCLUDED

#include <cmath>

namespace dae 
{
  namespace math
  {
    template <typename T, const size_t n>
    class _mat
    {
      private:
        T* data;
      public:
        float& operator [](size_t x);
        
        static _mat<T, n> identity()
        {
          // return indentity matrix
        }
    };
    
    template <typename T, size_t n>
    _mat::operator [](size_t x) 
    {
      return 12.3f;
    }
    
    
    _mat4<T> translate(T x, Ty, Tz)
    {
    
    }
    
    _mat4<T> translate(const _vec3<T>& v)
    {
    
    }
    
    _mat4<T> rotate(T angle_x, T angle_y, T angle_z)
    {
    
    }
    
    _mat4<T> rotate(T angle, T x, T y, T z)
    {
    
    }
    
    _mat4<T> rotaet(T angle, const _vec3<T>& v)
    {
    
    }
    
    _mat4<T> scale(T x, T y, T z) 
    {
    
    }
    
    _mat4<T> scale(const _vec3<T>& v)
    {
    
    }
    
    _mat4 scale(T x)
    {
    
    }
    
    
    typedef _mat<float, 3> mat3;
    typedef _mat<float, 4> mat4;
  }
}
#endif // MATH_HPP_INCLUDED
