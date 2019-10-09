#ifndef __sys_cmemory_hpp__
#define __sys_cmemory_hpp__

namespace sys {
  class CMemoryManager {
    // usage: (64byte aligned)
    // buffer data;
    // byte*  temp = new byte[1000+63]           // create big chung of memory + padding
    // data.pointer = temp+63;                   // assign & offset pointer by 63bytes
    // data.address = data.address & (-(int)64); // back to the front
  };
  
  
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
