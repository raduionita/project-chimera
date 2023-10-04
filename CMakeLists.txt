cmake_minimum_required(VERSION 3.0.0)
project(chimera VERSION 0.1.0)

# definitions
include(${CMAKE_CURRENT_SOURCE_DIR}/CMakeDefs.txt)

set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lgdi32 -lcomctl32 -lcomdlg32 -lopengl32 ${CMAKE_CSS_STANDARD_LIBRARIES}") # -lwsock32 -lws2_32
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

#file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

include_directories(source)

link_directories(vendor)
link_directories(output)

file(GLOB CYM "source/glm/*.cpp" "source/sys/*.cpp" "source/win/*.cpp" "source/nix/*.cpp" "source/osx/*.cpp" "source/uix/*.cpp" "source/cym/*.cpp")
file(GLOB APP "source/app/*.cpp" "source/main.cpp") 
#file(GLOB APP "source/main.cpp") 

add_library(cym ${CYM})
add_executable(app ${APP})

add_compile_definitions(LOGGER)
target_compile_definitions(app PRIVATE PLATFORM_MACOS)

target_link_libraries(app cym) 