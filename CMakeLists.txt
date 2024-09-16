cmake_minimum_required(VERSION 3.0)
project(RType)

include_directories(server client)
file(GLOB_RECURSE SERVER_SOURCES "server/src/*.cpp" "server/include/*.hpp")
file(GLOB_RECURSE SERVER_SOURCES_TEST "server/tests/*.cpp" "server/tests/*.hpp")
file(GLOB CLIENT_SOURCES "client/*.cpp" "client/*.hpp")
file(GLOB_RECURSE SERVER_SOURCES_TEST "client/tests/*.cpp" "client/tests/*.hpp")

add_executable(r-type_server ${SERVER_SOURCES})
add_executable(r-type_client  ${CLIENT_SOURCES})

target_compile_options(r-type_server PUBLIC -std=c++20 -Wall -Wfloat-conversion)
target_compile_options(r-type_client PUBLIC -std=c++20 -Wall -Wfloat-conversion)

find_package(GTest)

if(GTEST_FOUND)
  add_executable(unit_tests ${SERVER_SOURCES_TEST} ${SERVER_SOURCES})
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

  # linker options and library dependencies from it, by simply adding it as dependency.
  set_target_properties(example PROPERTIES ENABLE_EXPORTS on)

  target_link_libraries(unit_tests PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    example
  )

  target_include_directories(unit_tests PUBLIC
    ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
  )

endif()