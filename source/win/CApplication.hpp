#ifndef __win_capplication_hpp__
#define __win_capplication_hpp__

#include "sys/CApplication.hpp"
#include "sys/CException.hpp"
#include "sys/CLogger.hpp"
#include "win/win.hpp"
#include "win/CFrame.hpp"

namespace win {
  template<typename T> class TApplication : public sys::CApplication, public T {
    // or typename std::enable_if<std::is_base_of<CWindow, T>::value, void>::type
      static_assert(std::is_base_of<CWindow, T>::value, "T must be derived from CWindow");
    protected:
      static TApplication* sInstance;
      bool                 mRunning {true}; // TODO: atomic bool
    public:
      inline        bool          isRunning() const { return mRunning; }
      static inline TApplication* getInstance() { return sInstance; }
    public:
      // start
      virtual int exec() override {
        try {
          init();
          // try to loop
          try {
            loop();
          } catch (sys::CException& ex) {
            // TODO
          }
          // cleanup
          free();
          // exit
          quit(0);
          // last inputs
          poll();
          // done
          return 0;
        } catch (sys::CException& e) {
          // TODO: log error
          return -1;
        }
      }

      void init() {
        T::init();
        onInit();
      }

      void free() {
        T::free();
        onFree();
      }

      void loop() {
        while (mRunning) {
          tick();
        }
      }

      void tick() {
        onTick(0);
      }

      void quit(int nCode=0) {
        mRunning = false;
      }

      bool poll() {
        return false;
      }

      // events
      virtual void onInit() { }
      virtual void onTick(int=0) { mRunning = false; }
      virtual void onFree() { }
  };

  template<typename T> TApplication<T>* TApplication<T>::sInstance{nullptr};

  class CApplication : public TApplication<CFrame> {
    public:
      CApplication();
  };
} // namespace win

#undef DECLARE_APPLICATION
#define DECLARE_APPLICATION(CLS)                                                                                       \
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {                      \
  LOGTAG("   ::WinMain(HINSTANCE,HINSTANCE,LPSTR,int)");                                                               \
  LOGNFO("::" << hInstance << " INIT");                                                                                \
  try {                                                                                                                \
    CLS app;                                                                                                           \
    INT result = app.exec();                                                                                           \
    LOGNFO("::" << hInstance << " EXIT");                                                                              \
    return result;                                                                                                     \
  } catch (sys::CException& ex) {                                                                                      \
    LOGERR("::FATAL! " << ex);                                                                                         \
    return -1;                                                                                                         \
  }                                                                                                                    \
}

#endif //__win_capplication_hpp__