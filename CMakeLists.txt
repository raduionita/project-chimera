cmake_minimum_required(VERSION 3.12)
project(cpp:chimera)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lgdi32 -lcomctl32 -lcomdlg32 -lopengl32 ${CMAKE_CSS_STANDARD_LIBRARIES}") # -lwsock32 -lws2_32
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

#add_compile_definitions(GLC_DEBUG)
add_compile_definitions(UIX_PLATFORM_WINDOWS)
add_compile_definitions(UIX_EVENT_HANDLE=1)
add_compile_definitions(UIX_EVENT_APPLICATION=0)
add_compile_definitions(UIX_EVENT_PROPAGATE=1)
add_compile_definitions(UIX_EVENT_MOUSEMOVE=0)
add_compile_definitions(SYS_LOGGER=1)
add_compile_definitions(SYS_LOGGER_INFO)
add_compile_definitions(SYS_LOGGER_COUT)
add_compile_definitions(APP_BUILD=APP_EDIT)

include_directories(inc)

link_directories(lib)

file(GLOB CYM "src/sys/*.cpp" "src/glc/*.cpp" "src/ogl/*.cpp" "src/cym/*.cpp" "src/uix/*.cpp")
file(GLOB APP "src/app/*.cpp")

add_library(cym ${CYM})
add_executable(app ${APP})

target_link_libraries(app cym) # libgdi32.a libopengl32.a
