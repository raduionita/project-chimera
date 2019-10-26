#ifndef __cregistry_hpp__
#define __cregistry_hpp__

#include <vector>

namespace ogl {
  template <typename T> class CEntry;
  
  template <typename T> class CRegistry {
    friend class CEntry<T>;
    
    public:
    std::vector<T*> mEntries;
  
    protected:
    CRegistry();
    virtual ~CRegistry();
  
    public:
    bool insert(T*);
    bool remove(T*);
  };
  
  template <typename T> class CEntry {
    friend class CRegistry<T>;
    
    private:
    T* mEntry{nullptr};
    
    public:
    CEntry();
    virtual ~CEntry();
  };
}

#endif //__cregistry_hpp__
