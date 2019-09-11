#include "app/CApplication.hpp"
#include "cym/CPointer.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  log::dbg << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << log::end;
  cym::CPointer<app::CApplication> app{new app::CApplication()};
  INT result = app->exec();
  return result;
}  
