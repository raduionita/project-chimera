#include "cym/ogl/ogl.hpp"

namespace cym::ogl {
  int OGL_VERSION_MAJOR = 0;
  int OGL_VERSION_MINOR = 0;
  int OGL_VERSION_1_0 = 0;
  int OGL_VERSION_1_1 = 0;
  int OGL_VERSION_1_2 = 0;
  int OGL_VERSION_1_3 = 0;
  int OGL_VERSION_1_4 = 0;
  int OGL_VERSION_1_5 = 0;
  int OGL_VERSION_2_0 = 0;
  int OGL_VERSION_2_1 = 0;
  int OGL_VERSION_3_0 = 0;
  int OGL_VERSION_3_1 = 0;
  int OGL_VERSION_3_2 = 0;
  int OGL_VERSION_3_3 = 0;
  int OGL_VERSION_4_0 = 0;
  int OGL_VERSION_4_1 = 0;
  int OGL_VERSION_4_2 = 0;
  int OGL_VERSION_4_3 = 0;
  int OGL_VERSION_4_4 = 0;
  int OGL_VERSION_4_5 = 0;
  int OGL_VERSION_4_6 = 0;
  
  void     version(int& major, int& minor) {
    // skip the line
    if (OGL_VERSION_MAJOR && OGL_VERSION_MINOR) {
      major = OGL_VERSION_MAJOR;
      minor = OGL_VERSION_MINOR;
      return;
    }
    
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        NULL
    };
    version = (const char*) ::glGetString(GL_VERSION);
    if (!version) return;
    
    
    for (int i = 0;  prefixes[i];  i++) {
      const size_t length = strlen(prefixes[i]);
      if (strncmp(version, prefixes[i], length) == 0) {
        version += length;
        break;
      }
    }
    
/* PR #18 */
#ifdef _MSC_VER
    sscanf_s(version, "%d.%d", &major, &minor);
#else
    sscanf(version, "%d.%d", &major, &minor);
#endif

    OGL_VERSION_MAJOR = major; 
    OGL_VERSION_MINOR = minor;
    OGL_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    OGL_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;
    OGL_VERSION_1_2 = (major == 1 && minor >= 2) || major > 1;
    OGL_VERSION_1_3 = (major == 1 && minor >= 3) || major > 1;
    OGL_VERSION_1_4 = (major == 1 && minor >= 4) || major > 1;
    OGL_VERSION_1_5 = (major == 1 && minor >= 5) || major > 1;
    OGL_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
    OGL_VERSION_2_1 = (major == 2 && minor >= 1) || major > 2;
    OGL_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
    OGL_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
    OGL_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;
    OGL_VERSION_3_3 = (major == 3 && minor >= 3) || major > 3;
    OGL_VERSION_4_0 = (major == 4 && minor >= 0) || major > 4;
    OGL_VERSION_4_1 = (major == 4 && minor >= 1) || major > 4;
    OGL_VERSION_4_2 = (major == 4 && minor >= 2) || major > 4;
    OGL_VERSION_4_3 = (major == 4 && minor >= 3) || major > 4;
    OGL_VERSION_4_4 = (major == 4 && minor >= 4) || major > 4;
    OGL_VERSION_4_5 = (major == 4 && minor >= 5) || major > 4;
    OGL_VERSION_4_6 = (major == 4 && minor >= 6) || major > 4;
    
    if (major > 4 || (major >= 4 && minor >= 6)) {
      major = OGL_VERSION_MAJOR = 4;
      minor = OGL_VERSION_MINOR = 6;
    }
  }
  
  SVersion version() {
    SVersion v;
    version(v.major,v.minor);
    return v;
  }
  
  static void load_v_1_0() { }
	static void load_v_1_1() { } 
	static void load_v_1_2() { } 
	static void load_v_1_3() { } 
	static void load_v_1_4() { } 
	static void load_v_1_5() { } 
	static void load_v_2_0() { } 
	static void load_v_2_1() { } 
	static void load_v_3_0() { } 
	static void load_v_3_1() { } 
	static void load_v_3_2() { } 
	static void load_v_3_3() { } 
	static void load_v_4_0() { } 
	static void load_v_4_1() { } 
	static void load_v_4_2() { } 
	static void load_v_4_3() { } 
	static void load_v_4_4() { } 
	static void load_v_4_5() { } 
	static void load_v_4_6() { } 
	
	static void load_exts() { }
  
  bool     load() {
    // check version
    version();
    // load functions
    load_v_1_0();
    load_v_1_1();
    load_v_1_2();
    load_v_1_3();
    load_v_1_4();
    load_v_1_5();
    load_v_2_0();
    load_v_2_1();
    load_v_3_0();
    load_v_3_1();
    load_v_3_2();
    load_v_3_3();
    load_v_4_0();
    load_v_4_1();
    load_v_4_2();
    load_v_4_3();
    load_v_4_4();
    load_v_4_5();
    load_v_4_6();
    // load extensions
    load_exts();
    // return status
    return true;
  }
}
