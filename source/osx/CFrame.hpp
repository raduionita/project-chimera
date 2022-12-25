#ifndef __osx_cframe_hpp__
#define __osx_cframe_hpp__

#ifdef PLATFORM_MACOS

#include "osx/CWindow.hpp"

#include <objc/runtime.h>
#include <objc/message.h>
#include <Carbon/Carbon.h>

#define cls objc_getClass
#define sel sel_getUid
#define msg ((id (*)(id, SEL, ...))objc_msgSend)
#define cls_msg ((id (*)(Class, SEL, ...))objc_msgSend)

namespace osx {
  typedef enum NSApplicationActivationPolicy {
      NSApplicationActivationPolicyRegular   = 0,
      NSApplicationActivationPolicyAccessory = 1,
      NSApplicationActivationPolicyERROR     = 2,
  } NSApplicationActivationPolicy;

  typedef enum NSWindowStyleMask {
    NSWindowStyleMaskBorderless     = 0,
    NSWindowStyleMaskTitled         = 1 << 0,
    NSWindowStyleMaskClosable       = 1 << 1,
    NSWindowStyleMaskMiniaturizable = 1 << 2,
    NSWindowStyleMaskResizable      = 1 << 3,
  } NSWindowStyleMask;

  typedef enum NSBackingStoreType {
    NSBackingStoreBuffered = 2,
  } NSBackingStoreType;

  class CFrame : public CWindow {
    public:
      CFrame();
      ~CFrame();
  };
} // namespace osx

#endif // PLATFORM_MACOS

#endif // __osx_cframe_hpp__