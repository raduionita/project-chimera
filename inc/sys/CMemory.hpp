#ifndef __sys_cmemory_hpp__
#define __sys_cmemory_hpp__

namespace sys {
  class CMemory /*Allocator*/ {
    private:
      // obj_ptr data
      // int     cursor
    public:
      CMemory();
      // data = ::malloc(sizeof(object)*64);
      // cursor = 0;
      
      ~CMemory();
      // free(data)
      
      void* alloc(); // -> obj_ptr
      // if cursor < 64 
      //   cursor++
      //   return &data[cursor-1]
      // else
      //   return null;
      
      void free();
      // if cursor > 0
      //   cursor--;
      
      void defrag();
  };
}

#endif //__sys_cmemory_hpp__
