#ifndef __cym_uix_sarea_hpp__
#define __cym_uix_sarea_hpp__

#include <windef.h>

namespace cym { namespace uix {
  struct SRect; 
  
  struct SArea {
    static constexpr int DEFAULT = -1;
    union {int data[4]; struct {int x, y, w, h;};};
    SArea(int v = DEFAULT) : x(v), y(v), w(v), h(v) { }
    SArea(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }
    operator       RECT()  const;
    operator const RECT()  const;
    operator       SRect() const; 
    operator const SRect() const; 
  };
  
  SArea::operator       RECT()  const { return RECT{x,y,x+w,y+h}; }
  SArea::operator const RECT()  const { return RECT{x,y,x+w,y+h}; }
  SArea::operator       SRect() const { return SRect{x,y,x+w,y+h}; }
  SArea::operator const SRect() const { return SRect{x,y,x+w,y+h}; }
}}

#endif //__cym_uix_sarea_hpp__
