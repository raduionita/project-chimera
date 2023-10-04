#ifndef __cym_cmessage_hpp__
#define __cym_cmessage_hpp__

#include "cym/cym.hpp"

namespace cym {
  using PMessage = sys::ptr<CMessage>;

  class CMessage {

  };

  class CMessageSupervisor {
    private:
      // ??type?? mGraph;
    public:
      static void submit() {

      }
  };
} // namespace cym


#endif //__cym_cmessage_hpp__

// message graph:
// app.
//   .view
//     .screens
//       .id
//         .layers
//           .id
//   .root
//     .scenes
//       .id
//         .nodes
//           .id