#ifndef __mem_hpp__
#define __mem_hpp__

namespace mem {
  template<typename T> class TPointer;
  template<typename T> class TReference;

  template<typename T> using ref = TReference<T>;
  template<typename T> using ptr = TPointer<T>;

} // namespace mem

#endif //__mem_hpp__
