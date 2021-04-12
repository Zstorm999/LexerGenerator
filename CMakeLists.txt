cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

project(LexerGenerator VERSION 0.2.0)

set(SRCS 
    source/dfa.cpp
    source/dfatransition.cpp
    source/nfa.cpp
    source/nfagraph.cpp)

set(TESTSRCS 
    test/testautomaton.hpp
    test/simpleDFATest.cpp
    test/transitionsTest.cpp
    test/ioDFATest.cpp
    test/graphTest.cpp)

set(HEADERS
    includes/dfa.hpp
    includes/dfatransition.hpp
    includes/nfa.hpp
    includes/nfagraph.hpp)

include_directories(includes)

add_executable(AppBuild main.cpp ${SRCS} ${HEADERS})
add_executable(TestBuild ${SRCS} ${HEADERS} ${TESTSRCS})

add_library(LexerGenerator STATIC ${SRCS} ${HEADERS})


target_link_libraries(TestBuild gtest_main)
add_test(NAME LexerGenerator_test COMMAND TestBuild)