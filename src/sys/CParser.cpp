#include "sys/CParser.hpp"

namespace sys {
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::ostream& operator <<(std::ostream& out, const CXMLParser::STree& tree) {
    out << tree.type << std::endl;
    for (auto it = tree.attributes.begin(); it != tree.attributes.end(); ++it) {
      out << ".attributes[" << it->name << "]=" << it->value << std::endl;
    }
    if (tree.root)  {
      out << *tree.root;
    }
    return out;
  }
  
  std::ostream& operator <<(std::ostream& out, const CXMLParser::SElement& element) {
    out << element.name << std::endl;
    for (auto it = element.attributes.begin(); it != element.attributes.end(); ++it) {
      out << ".attributes[" <<  it->name << "]=" << it->value << std::endl;
    }
    
    out << ".text=" << element.text.value << std::endl; 
    
    out << ".children=" << std::endl;
    for (auto& child : element.children) {
      out << *child;
    }
    return out;
  }
  
  std::ostream& operator <<(std::ostream& out, const CXMLParser::SView& view) {
    return out.write(view.from,view.size);
  }
  
  std::ostream& operator <<(std::ostream& out, const CXMLParser::SStream& stream) {
    return out.write(stream.last,stream.size - (stream.last - stream.from));
  }
  
  std::ostream& operator <<(std::ostream& out, const CXMLParser::SText& text) {
    return out.write(text.value.from,text.value.size);
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
