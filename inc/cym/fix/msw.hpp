#ifndef __cym_fix_msw_hpp__
#define __cym_fix_msw_hpp__

#include <windows.h>

#include <map>

struct STATE {
  DWORD dwStyle{0};
  DWORD dwExStyle{0};
  RECT  rc{0};
};

/// returns previous state
/// returns current  state (if previous was not set)
inline STATE SwapWindowState(HWND hWnd) {
  assert(hWnd != NULL && "HWND is NULL");
  assert(::IsWindow(hWnd) != FALSE && "HWND is not a WINDOW");
  
  static std::map<HWND, STATE> states;
  
  STATE curr;
  curr.dwStyle   = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_STYLE));
  curr.dwExStyle = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_EXSTYLE));
  ::GetClientRect(hWnd, &curr.rc);
  
  auto it = states.find(hWnd);
  if (states.size() == 0 || it == states.end()) {    // not found // insert
    states.insert(std::pair<HWND,STATE>(hWnd, curr));
  } else {                                           // found // swap
    // read prev
    STATE  temp{it->second};
    STATE& prev{it->second};
    // store
    prev.dwStyle   = curr.dwStyle;
    prev.dwExStyle = curr.dwExStyle;
    prev.rc        = curr.rc;
    // return
    curr.dwStyle   = temp.dwStyle;
    curr.dwExStyle = temp.dwExStyle;
    curr.rc        = temp.rc;
  }
  
  return curr;
}

inline STATE GetWindowState(HWND hWnd) {
  STATE curr;
  curr.dwStyle   = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_STYLE));
  curr.dwExStyle = static_cast<DWORD>(::GetWindowLong(hWnd, GWL_EXSTYLE));
  ::GetClientRect(hWnd, &curr.rc);
  return curr;
}

#endif //__cym_fix_msw_hpp__
