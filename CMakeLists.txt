cmake_minimum_required(VERSION 3.0.0)
project(chimera VERSION 0.1.0)

set(LOGGER ON)
set(BENCHMARK OFF)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lgdi32 -lcomctl32 -lcomdlg32 -lopengl32 ${CMAKE_CSS_STANDARD_LIBRARIES}") # -lwsock32 -lws2_32
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binary)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# CMAKE_CURRENT_BINARY_DIR
file(COPY ${CMAKE_CURRENT_LIST_DIR}/assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

include_directories(source)

link_directories(vendor)
link_directories(binary)

file(GLOB CYM "source/sys/*.cpp" "source/glm/*.cpp" "source/cym/*.cpp" "source/win/*.cpp")
file(GLOB APP "source/app/*.cpp" "source/main.cpp")

add_compile_definitions(CONTEXT_OPENGL)

# LOGGER
if(LOGGER)
  message(STATUS "Logger=ON")
  add_compile_definitions(LOGGER)
else()
  message(STATUS "Logger=OFF")
  list(FILTER CYM EXCLUDE REGEX ".*CLogger\\.cpp$")
endif()

# BENMRK
if(BENCHMARK)
  message(STATUS "Benchmark=ON")
  add_compile_definitions(BENCHMARK)
else()
  message(STATUS "Benchmark=OFF")
  list(FILTER CYM EXCLUDE REGEX ".*CBenchmark\\.cpp$")
endif()

add_library(cym ${CYM})
add_executable(app ${APP})

target_link_libraries(app cym) 