cmake_minimum_required(VERSION 3.0.0)
project(chimera VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lgdi32 -lcomctl32 -lcomdlg32 -lopengl32 ${CMAKE_CSS_STANDARD_LIBRARIES}") # -lwsock32 -lws2_32
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

add_compile_definitions(CYM_CONTEXT_OPENGL)

include_directories(source)

link_directories(vendors)
link_directories(binary)

# file(GLOB CYM "src/sys/*.cpp" "src/glc/*.cpp" "src/ogl/*.cpp" "src/cym/*.cpp" "src/uix/*.cpp")
file(GLOB APP "source/app/*.cpp" "source/main.cpp") 

# add_library(cym ${CYM})
add_executable(app ${APP})

# target_link_libraries(app cym) 