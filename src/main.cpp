#include "app/CApplication.hpp"
#include "cym/sys/CPointer.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << log::end;
  cym::sys::CPointer<app::CApplication> app{new app::CApplication()};
  INT result = app->exec();
  return result;
}  
