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

inline void SetDefaultFont(HWND hWnd) {
  ::SendMessage(hWnd, WM_SETFONT, (WPARAM)::GetStockObject(DEFAULT_GUI_FONT), (LPARAM)true);
}

inline std::string GetLastErrorString() {
  DWORD errid = ::GetLastError();
  if (errid == 0) return std::string();
  LPSTR buffer = nullptr;
  const DWORD size = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errid, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);
  std::string errmsg(buffer, size);
  ::LocalFree(buffer);
  return errmsg;
}

#endif //__cym_fix_msw_hpp__
