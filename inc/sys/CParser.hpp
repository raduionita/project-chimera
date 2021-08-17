#ifndef __sys_cparser_hpp__
#define __sys_cparser_hpp__

#include "sys/sys.hpp"
#include "sys/CFile.hpp"
#include "sys/CException.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <cstdio>
#include <cstring>

#define USE_REFS 1
#define USE_EVENTS 0

namespace sys {
  inline uint taglen(const char* src) { uint i {0}; while (isalnum(src[i]) || src[i] == '_') i++; return i; }
  
  inline uint attrlen(const char* src) { uint i {0}; /* @todo: attribute length */ return i; }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CParser { };
  
  class CXMLParser : public CParser {
    public:
      enum EFlag : uint { OWNER = 1, };
      
      struct SQuery {
        
      };
      
      struct SStream {
        const char* from {nullptr};
        char* last       {nullptr};
        const uint  size {0};
              bool  good {true};   
        // ctors
        SStream(char* f, uint s) : from{f}, last{f}, size{s} { }
        // friends
        friend std::ostream& operator <<(std::ostream& out, const SStream& view);
        // operators
        SStream& operator >>(int &i) {
          // -1 +100
          uint n {0};
          while (!(last + n - from >= size) && !(::isdigit(last[n]) || (last[n] == '+' && n == 0) || (last[n] == '-' && n == 0)))
            n++;
          // advance
          last += n;
          // reset counter
          n = 0;
          // read each float simbol - + 0123456789 e .
          while (!(last + n - from >= size) && (::isdigit(last[n]) || (last[n] == '+' && n == 0) || (last[n] == '-' && n == 0)))
            n++;
          // write float
          if (n > 0) 
            i = ::atoi(last);
          // advance internal pointer
          last += n;
          // good? = data was extracted?
          good = n > 0;
          // continue
          return *this;
        }
        SStream& operator >>(float &f) { 
          // -1.0 +1 3.52434 1.0e-10 7.00000 3.14159e+000
          uint n {0};
          // skip non-floats
          while (!(last + n - from >= size) && !(::isdigit(last[n]) || (last[n] == 'e' && n > 0) || last[n] == '+' || last[n] == '-' || last[n] == '.'))
            n++;
          // advance
          last += n;
          // reset counter
          n = 0;
          // read each float simbol - + 0123456789 e .
          while (!(last + n - from >= size) && (::isdigit(last[n]) || (last[n] == 'e' && n > 0) || last[n] == '+' || last[n] == '-' || last[n] == '.'))
            n++;
          // write float
          if (n > 0) 
            f = ::atof(last);
          // advance internal pointer
          last += n;
          // done
          good = n > 0;
          // continue
          return *this;
        }
        SStream& operator >>(std::pair<float*,uint> p) {
          for (uint i = 0; i < p.second; i++)
            *this >> p.first[i];
          return *this;
        }
        // casts
        operator bool() const { return good; }
      };
      
      struct SView {
        // fields
        char* from {nullptr}; 
        uint  size {0}; 
        // friends
        friend std::ostream& operator <<(std::ostream& out, const SView& view);
        // operators
        bool operator ==(const SView& view)    { return  (view.size == size) && strncmp(from, view.from, view.size); }
        bool operator ==(const char tValue[]) { return  (strlen(tValue) == size) &&  strncmp(from, tValue, strlen(tValue)); }
        bool operator !=(const char tValue[]) { return !(strlen(tValue) == size) || !strncmp(from, tValue, strlen(tValue)); }
        // metgofs
        SStream     toStream() const { return {from, size}; }
        std::string toString() const { return {from, size}; }
      };
  
      struct SNode { 
        SNode() = default;
        virtual ~SNode() = default;
      };
      
      struct SElement;
      
      struct SAttribute { 
        SView     name; 
        SView     value;
#ifdef USE_REFS
        SElement* ref {nullptr};
#endif // USE_REF
        // operators
        bool operator ==(const SAttribute attr) { return value == attr.value; }
        bool operator ==(const char tValue[])   { return value == tValue; }
        bool operator !=(const char tValue[])   { return value != tValue; }
        bool operator ==(bool tValue)           { return toBool() == tValue; }
        bool operator !=(bool tValue)           { return toBool() != tValue; }
        bool operator ==(int tValue)            { return toInt() == tValue; }
        bool operator !=(int tValue)            { return toInt() != tValue; }
        bool operator ==(long tValue)           { return toLong() == tValue; }
        bool operator !=(long tValue)           { return toLong() != tValue; }
        bool operator ==(float tValue)          { return toFloat() == tValue; }
        bool operator !=(float tValue)          { return toFloat() != tValue; }
        bool operator ==(double tValue)         { return toDouble() == tValue; }
        bool operator !=(double tValue)         { return toDouble() != tValue; }
        // casts
        operator bool() const { return toBool(); }
        // value converters
        bool                               toBool() const   { return value.size != 0 && !strncmp(value.from,"false",5); }
        int                                toInt() const    { return ::atoi(value.from); }
        long                               toLong() const   { return ::atol(value.from); }
        float                              toFloat() const  { return static_cast<float>(::atof(value.from)); }
        double                             toDouble() const { return ::atof(value.from); }
        sys::string                        toString() const { return std::string(value.from,value.size); }
        sys::pair<sys::string,sys::string> toPair() const   { return {std::string(name.from,name.size), std::string(value.from,value.size)}; }
      };
      
      struct SCdata : SNode { };
      
      struct SComment : SNode { SView value; };
      
      struct SText : SNode { 
        SView value;
        SStream     toStream() const { return {value.from, value.size}; }
        std::string toString() const { return {value.from, value.size}; }
        // converters
        int                                toInt()   const    { return ::atoi(value.from); }
        float                              toFloat() const    { return static_cast<float>(::atof(value.from)); }
        // friends
        friend std::ostream& operator <<(std::ostream& out, const SText& text);
      };
      
      struct SElement : SNode { 
      // fields
        SView                   name; 
        SView                   id; 
        std::vector<SAttribute> attributes; 
        std::vector<SElement*>  children; 
        SElement*               parent {nullptr}; // nullptr = only root 
        SText                   text;
      // ctor/dtor
        ~SElement() { for (auto it = children.begin(); it != children.end(); ++it) { delete *it; *it = nullptr; } }
      // operators  
        inline SElement* operator [](uint i)             const { return children[i]; }
        inline SElement* operator [](const char tName[]) const { 
          for (auto& child : children) 
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) 
              return child; 
          return nullptr; 
        }
      // friends  
        friend std::ostream& operator <<(std::ostream& out, const SElement& elem);
      // methods
        SAttribute* attribute(const char tAttribute[]) {
          for (auto& attribute : attributes)
            if ((strlen(tAttribute) == attribute.name.size) && strncmp(attribute.name.from, tAttribute, strlen(tAttribute)))
              return &attribute;
          return nullptr;
        }
        SElement* child(const char tName[]) {
          // SYS_LOG_NFO("sys::SElement::attach(const char["<< strlen(tName) <<"]{"<< tName << "})::" << name);
          for (auto& child : children) 
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) 
              return child; 
          return nullptr;
        }
        std::vector<SElement*> findByName(const char tName[]) {
          std::vector<SElement*> all;
          // for all children
          for (const auto& child : children) {
            // if attach is named
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) {
              all.push_back(child);
            }
            // search children of children
            std::vector<SElement*> out = child->findByName(tName);
            all.insert(all.end(),out.begin(),out.end());
          }
          // return found elements named 
          return all;
        }
        SElement* findOneByName(const char tName[]) {
          // SYS_LOG_NFO("sys::SElement::findOneByName(const char["<< strlen(tName) <<"]{"<< tName << "})::" << name);
          for (const auto& child : children)
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName)))
              return child;
          SElement* tFound {nullptr};
          for (const auto& child : children)
            if ((tFound = child->findOneByName(tName)) != nullptr)
              return tFound;
          return nullptr;
        }
        SElement* findById(const char tId[]) {
          short i {0};
          // in case id starts w/ # // id="#some"
          if (tId[0] == '#')
            i++;
          for (auto child : children)
            if ((strlen(tId)-i == child->id.size) && strncmp(child->id.from, tId+i, strlen(tId)-i))
              return child;
          SElement* tFound {nullptr};
          for (auto child : children)
            if ((tFound = child->findById(tId+i)) != nullptr)
              return tFound;
          return nullptr;
        }
        SElement* findById(const SView& tId) {
          uint i {0};
          // in case id starts w/ # // id="#some"
          if (tId.from[0] == '#')
            i++;
          for (auto child : children)
            if ((tId.size-i == child->id.size) && strncmp(child->id.from, tId.from+i, tId.size-i))
              return child;
          SElement* tFound {nullptr};
          for (auto child : children)
            if ((tFound = child->findById(tId)) != nullptr)
              return tFound;
          return nullptr;
        }
        SElement* findOneByAttributeValue(const sys::string& tValue) {
          for (const auto& child : children)
            for (const auto& attribute : child->attributes)
              if ((tValue.size() == attribute.value.size) && strncmp(attribute.value.from, tValue.data(), tValue.size()))
                return child;
          SElement* tFound {nullptr};
            for (const auto& child : children)
              if ((tFound = child->findOneByAttributeValue(tValue)) != nullptr)
              return tFound;
          return nullptr;
        }
        SElement* findOneByAttributeValue(const char (&tValue)[]) {
          for (const auto& child : children)
            for (const auto& attribute : child->attributes)
              if ((strlen(tValue) == attribute.value.size) && strncmp(attribute.value.from, tValue, strlen(tValue)))
                return child;
          SElement* tFound {nullptr};
            for (const auto& child : children)
              if ((tFound = child->findOneByAttributeValue(tValue)) != nullptr)
              return tFound;
          return nullptr;
        }
        SElement* findOneByAttributeValue(const SView& tValue) {
          for (const auto& child : children)
            for (const auto& attribute : child->attributes)
              if ((tValue.size == attribute.value.size) && strncmp(attribute.value.from, tValue.from, tValue.size))
                return child;
          SElement* tFound {nullptr};
            for (const auto& child : children)
              if ((tFound = child->findOneByAttributeValue(tValue)) != nullptr)
              return tFound;
          return nullptr;
        }
        uint      countByName(const char tName[]) {
          uint tTotal {0};
          for (const auto& child : children) {
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName)))
              tTotal++;
            tTotal += child->countByName(tName);
          }
          return tTotal;
        }
      };
      
      struct STree {
      // fields
        uint                       flags {0};
        char*                      source {nullptr};
        SView                      type;
        SElement*                  root {nullptr};
        std::vector<SAttribute>    attributes;
        std::map<SView*,SElement*> index;  // @todo: replace w/ indices a map of indices, where u index stuff by something, id/tag...
      // ctor/dtor
        ~STree() { if (root) { delete root; root = nullptr; } if ((flags & OWNER) && (source)) { delete [] source; source = nullptr; } }
      // operators
        inline SElement* operator [](int i)              const { return root->children[i]; }
        inline SElement* operator [](const char tName[]) const { 
          for (auto& child : root->children) 
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) 
              return child; 
          return nullptr; 
        }
      // friends
        friend std::ostream& operator <<(std::ostream& out, const STree& tree);
      // methods
        SElement* child(const char tName[]) {
          for (auto& child : root->children) 
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) 
              return child; 
          return nullptr;
        }
        SElement* findById(const char id[]) {
          short i {0};
          // in case id starts w/ # // id="#some"
          if (id[0] == '#')
            i++;
          for (auto it = index.begin(); it != index.end(); ++it)
            if ((it->first->size == strlen(id)-i) && strncmp(it->first->from, id+i, strlen(id)-i))
              return it->second;
          return nullptr;
        }
        SElement* findById(const SView& id) {
          uint i {0};
          // in case id starts w/ # // id="#some"
          if (id.from[0] == '#')
            i++;
          for (auto it = index.begin(); it != index.end(); ++it)
            if ((it->first->size == id.size-i) && strncmp(it->first->from, id.from+i, id.size-i))
              return it->second;
          return nullptr;
        }
        std::vector<SElement*> findByName(const char tName[]) {
          std::vector<SElement*> all;
          // test root
          if ((strlen(tName) == root->name.size) && strncmp(root->name.from, tName, strlen(tName)))
            all.push_back(root);
          // then root's children
          for (const auto& child : root->children) {
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName))) {
              all.push_back(child);
            }
            std::vector<SElement*> out = child->findByName(tName);
            all.insert(all.end(),out.begin(),out.end());
          }
          
          return all; 
        }
        SElement* findOneByName(const char tName[]) {
          if ((strlen(tName) == root->name.size) && strncmp(root->name.from, tName, strlen(tName))) {
            return root;
          } else {
            for (auto child : root->children)
              if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName)))
                return child;
            SElement* tFound {nullptr};
            for (auto child : root->children)
              if ((tFound = child->findOneByName(tName)) != nullptr)
                return tFound;
            return nullptr;
          } 
        }
        uint countByName(const char tName[]) {
          uint tTotal {0};
          if ((strlen(tName) == root->name.size) && strncmp(root->name.from, tName, strlen(tName)))
            tTotal++;
          for (const auto& child : root->children)
            if ((strlen(tName) == child->name.size) && strncmp(child->name.from, tName, strlen(tName)))
              tTotal++;
            tTotal += root->countByName(tName);
          return tTotal;
        }
      };
    protected:
#ifdef USE_EVENTS
      std::vector<std::function<void(SElement*)>>                        _on_element;
      std::map<std::string, std::function<void(SElement*)>>              _on_element_name;
      std::map<std::string, std::function<void(SElement*)>>              _on_id;
#ifdef USE_REFS
      std::map<std::string, std::function<void(SAttribute*,SElement*)>> _on_ref;
#endif // USE_REF
      std::map<std::string, std::function<void(SAttribute*,SElement*)>> _on_attribute;
      std::map<std::string, std::function<void(SAttribute*,SElement*)>> _on_attribute_value;
#endif // USE_REF
    public:
      // events
      void onElement(std::function<void(SElement*)>&& f) {
#ifdef USE_EVENTS
        _on_element.push_back(std::move(f));
#endif // USE_REF 
      }
      void onElement(const char* name, std::function<void(SElement*)>&& f) {
#ifdef USE_EVENTS
        _on_element_name.insert(std::pair{name, std::move(f)});
#endif // USE_REF
      }
      void onId(const char* id, std::function<void(SElement*)>&& f) { 
#ifdef USE_EVENTS
        _on_id.insert(std::pair(id,std::move(f)));
#endif // USE_REF
      }
      void onRef(const char* ref, std::function<void(SAttribute*,SElement*)>&& f) {
#ifdef USE_EVENTS
#ifdef USE_REFS
        _on_ref.insert(std::pair(ref,std::move(f)));
#endif // USE_REF
#endif // USE_REF
      }
      void onAttribute(const char* attr, std::function<void(SAttribute*,SElement*)>&& f) {
#ifdef USE_EVENTS
        _on_attribute.insert(std::pair(attr, std::move(f)));
#endif // USE_EVENTS
      }
      void onAttribute(const char* attr, const char* val, std::function<void(SAttribute*,SElement*)>&& f) {
#ifdef USE_EVENTS
      _on_attribute_value.insert(std::pair(std::string(attr).append(val), std::move(f)));
#endif // USE_EVENTS
    }
    public:
      STree* parse(FILE* f, uint flags = 0) { throw sys::exception("NOT IMPLEMENTED", __FILE__, __LINE__); }
      STree* parse(sys::CFile& file, uint flags = 0) {
        std::streamsize len = file.size();
        char* src           = new char[len+1];
        
        file.read(src,len);
        
        src[len] = '\0';
        
        return parse(src, flags | CXMLParser::OWNER);
      }
      STree* parse(sys::CFile::stream_type& fs, uint flags = 0) { 
        fs.seekg(0, fs.end);
        size_t len = fs.tellg();
        fs.seekg(0, fs.beg);
        
        char* src = new char[len+1];
        
        fs.read(src,len);
        
        src[len] = '\0';
        
        return parse(src, flags | CXMLParser::OWNER);
      }
      
      STree* parse(const char* source, uint flags = 0) { 
        STree* tTree    = new STree{flags};
        char*  tPointer = tTree->source = const_cast<char*>(source);
        
        SElement* tCurrent = nullptr;
        SElement* tParent  = nullptr;
        
#ifdef USE_REFS
        std::vector<SAttribute*> tRefs; // id=>element
        std::vector<SAttribute*> tIDS;  // 
#endif // USE_REF
        
        while (*tPointer) { // if not EOF
          if (tPointer[0] == '\n' || tPointer[0] == '\r' || tPointer[0] == '\t' || tPointer[0] == ' ') {
            tPointer += 1;
            
            continue;
          } else if (tPointer[0] == '<' && tPointer[1] == '?') { // xml:tag
            tPointer += 1;
            
            // span to next > // not including
            uint nLength = charspn(tPointer, '>');   // value
            // span to next alpha-numeric
            uint i = alnumspn(tPointer/*until alphanum*/);
            uint j {0};
            
            // tag // from when alpha num starts
            tTree->type.from = tPointer + i;
            // tag // to where tag ends
            tTree->type.size = taglen(tPointer + i);
            
            i += tTree->type.size;
            
            // attributes
            while((i + (j = alnumspn(tPointer + i/*until alphanum*/))) < nLength) {
              i += j;
              SAttribute tAttribute;
              
              tAttribute.name = {tPointer + i, charspn(tPointer + i, '=')};
              
              i += tAttribute.name.size; 
              i += 2; // ="
              
              tAttribute.value = {tPointer + i, charspn(tPointer + i, '"')};
              
              tTree->attributes.push_back(tAttribute);
              
              // pass end of value
              i += tAttribute.value.size; 
              i += 1; // "
            }
            
            tPointer += i;
            tPointer += 2; // ? + >
            
            continue;
          } else if (tPointer[0] == '<' && tPointer[1] != '/') { // tag:start
            tPointer += 1;
            
            // parent = previous current
            tParent  = tCurrent;
            // new current
            tCurrent = new SElement;
            tCurrent->parent = tParent;
            
            // span to next > // not including
            uint nLength = charspn(tPointer, '>');   // value
            // span to next alpha-numeric
            uint i = alnumspn(tPointer/*until alphanum*/);;
            uint j {0};
            
            // tag // from when alpha num starts
            tCurrent->name.from = tPointer + i;
            // tag // to where tag ends
            tCurrent->name.size = taglen(tPointer + i);
          
            i += tCurrent->name.size;
            
            // if i cannot pass the length of the tag
            while((i + (j = alnumspn(tPointer + i/*until alphanum*/))) < nLength) { // attributes
              i += j;
              
              tCurrent->attributes.push_back({});
              SAttribute* tAttribute = &tCurrent->attributes.back();
              
              // attribute // from when alpha num starts -> until =
              tAttribute->name = {tPointer + i, charspn(tPointer + i, '=')};
              
              i += tAttribute->name.size; 
              i += 2; // ="
              
              // attribute.value // from where we at, until "
              tAttribute->value = {tPointer + i, charspn(tPointer + i, '"')};
              
#ifdef USE_EVENTS
              for (auto it = _on_attribute.begin(); it != _on_attribute.end(); ++it) {
                if ((it->first.size() == tAttribute->name.size) && strncmp(it->first.c_str(), tAttribute->name.from, tAttribute->name.size)) {
                  it->second(tAttribute,tCurrent);
                }
              }
              
              for (auto it = _on_attribute_value.begin(); it != _on_attribute_value.end(); ++it) {
                std::string tKey {std::string(tAttribute->name.from, tAttribute->name.size).append(tAttribute->value.from, tAttribute->value.size)};
                if ((tKey.size() == it->first.size()) && strncmp(it->first.c_str(), tKey.c_str(), tKey.size())) {
                  it->second(tAttribute,tCurrent);
                }
              }
#endif // USE_EVENTS
              
#ifdef USE_REFS
              // find ref
              if (tAttribute->value.from[0] == '#') {
                // like source="#someid"
                tAttribute->ref = tTree->findById(tAttribute->value);
                if (tAttribute->ref == nullptr) {
                  tRefs.push_back(tAttribute);
                }
              }
#endif // USE_REF
              
              // remeber element id=
              if (strncmp(tAttribute->name.from, "id", 2)) {
                tCurrent->id = tAttribute->value;
                
                tTree->index[&tCurrent->id] = tCurrent;
                
#ifdef USE_EVENTS
                for (auto it = _on_id.begin(); it != _on_id.end(); ++it) {
                  if ((it->first.size() == tAttribute->value.size) && strncmp(tAttribute->value.from, it->first.c_str(), it->first.size()))
                    it->second(tCurrent);
                }
#endif // USE_EVENTS
#ifdef USE_REFS
                // fill refs
                for (auto it = tRefs.begin(); it != tRefs.end(); ++it) {
                  if ((tAttribute->value.size == (*it)->value.size-1) && strncmp(tAttribute->value.from, (*it)->value.from+1, (*it)->value.size-1)) {
                    (*it)->ref = tCurrent;
#ifdef USE_EVENTS
                    for (auto jt = _on_ref.begin(); jt != _on_ref.end(); ++jt) {
                      if ((jt->first.size() == tAttribute->value.size) && strncmp(tAttribute->value.from, jt->first.c_str(), jt->first.size())) {
                        jt->second(tAttribute, tCurrent);
                      }
                    }
#endif // USE_EVENTS
                  }
                }
#endif // USE_REF
              }
              
              // pass end of value
              i += tAttribute->value.size;
              // pass "
              i += 1; 
            }
            
            // set up root
            if (tTree->root == nullptr) {
              tTree->root = tCurrent;
            }
            
            // add attach to parent (like current element to root)
            if (tParent) {
              tParent->children.push_back(tCurrent);
            }
            
            // advance
            tPointer += i;
            
#ifdef USE_EVENTS
            for (auto& f : _on_element) {
              f(tCurrent);
            }
            for (auto it = _on_element_name.begin(); it != _on_element_name.end(); ++it) {
              if ((it->first.size() == tCurrent->name.size) && strncmp(it->first.c_str(), tCurrent->name.from, tCurrent->name.size)) 
                it->second(tCurrent);
            }
#endif // USE_EVENTS
            
            // tag closes itself 
            if (tPointer[0] == '/') {
              tPointer += 1;
              tCurrent = tCurrent->parent;
            }
            
            // pass > 
            tPointer += 1;
            
            continue;
          } else if (tPointer[0] == '<' && tPointer[1] == '/') { // tag:end
            // pass </
            tPointer += 2;
            
            // span to next > //  not including
            uint nLength = charspn(tPointer, '>');   
            uint i {0};
            
            // if current is null => bad close - close more then u should
            if (tCurrent == nullptr) {
              throw std::string(tPointer, nLength).append(" bad close!");
            }
            
            if (!strncmp(tPointer, tCurrent->name.from, tCurrent->name.size)) {
              throw std::string(tPointer-2, nLength+3).append(" close mismatch!");
            }
            
            // closing by reverting current to the previous parent
            tCurrent = tCurrent->parent;
            
            // unnecessary, but might be usefull later
            i += nLength;
            
            // advance
            tPointer += i;
            
            // pass >
            tPointer += 1;
            
            continue;
          } else if (tPointer[0] != '<') {
            
            uint nLength = charspn(tPointer, '<');   // value
            
            tCurrent->text.value.from = tPointer;
            tCurrent->text.value.size = nLength;
            
            tPointer += nLength;
            
            continue;
          }
          
          tPointer++;
        }
    // parsed
        return tTree;
      }
  };
}

#endif //__sys_cparser_hpp__
