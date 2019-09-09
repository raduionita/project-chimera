#include "app/CApplication.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  log::nfo << "   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)::" << hInstance << log::end;
  auto app   = new app::CApplication();
  INT result = app->exec();
  delete app;
  return result;
}  
