#ifdef PLATFORM_MACOS

#include "osx/CFrame.hpp"

namespace osx {
  CFrame::CFrame() {
    LOGDBG("osx::CFrame::CFrame()");

    id app = cls_msg(cls("NSApplication"), sel("sharedApplication"));

    msg(app, sel("setActivationPolicy:"), NSApplicationActivationPolicyRegular);

    struct CGRect frameRect = {0, 0, 600, 500};

    id win = msg(cls_msg(cls("NSWindow"), sel("alloc")),
                 sel("initWithContentRect:styleMask:backing:defer:"),
                 frameRect,
                 NSWindowStyleMaskTitled|NSWindowStyleMaskClosable|NSWindowStyleMaskResizable,
                 NSBackingStoreBuffered,
                 false);

    msg(win, sel("setTitle:"), cls_msg(cls("NSString"), sel("stringWithUTF8String:"), "Pure C App"));

    msg(win, sel("makeKeyAndOrderFront:"), nil);

    msg(app, sel("activateIgnoringOtherApps:"), true);

    msg(app, sel("run"));
  }
  CFrame::~CFrame() {
    LOGDBG("osx::CFrame::~CFrame()");
  }
} // namespace osx 

#endif // PLATFORM_MACOS