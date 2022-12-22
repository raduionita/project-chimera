#include "app/CApplication.hpp"

// DECLARE_APPLICATION(app::CApplication);

int main(int argc, char** argv) {
  app::CApplication exe;
  exe.exec(argc, argv);
  return 0;
}