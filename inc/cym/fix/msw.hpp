#ifndef __cym_fix_msw_hpp__
#define __cym_fix_msw_hpp__

#include <windef.h>

#include <map>

struct STATE {
  DWORD dwStyle{0};
  DWORD dwExStyle{0};
  RECT  rc;
};

WINBOOL SwapWindowState(HWND hWnd, STATE* pState) {
  static std::map<HWND, STATE*> states;
  
  // @todo: try to find STATE for HWND
  
  // @todo: IF not found 
    // @todo: insert 
    // @todo: return FALSE
  // @todo: ELSE // found
    // @todo: swap: get prev STATE in temp
    // @todo:       store new state
    // @todo:       pState = temp
    // @todo: return TRUE
  
  
  return TRUE;
}


#endif //__cym_fix_msw_hpp__
