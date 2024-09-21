cmake_minimum_required(VERSION 3.15)
project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    message(STATUS "Configuring for Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(SFML_STATIC_LIBRARIES TRUE)
elseif(UNIX)
    message(STATUS "Configuring for Unix-based system")
endif()

if(DEFINED ENV{VCPKG_ROOT})
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
    include("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
    include("/opt/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(WARNING "VCPKG_ROOT environment variable not defined, please modify the previous path")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CLIENT_INCLUDE_DIRS r-type/client/include)
set(SERVER_INCLUDE_DIRS r-type/server/include)

file(GLOB_RECURSE ENGINE_SOURCES
    "engine/source/components/*.cpp"
    "engine/source/core/*.cpp"
    "engine/source/renderer/*.cpp"
    "engine/source/systems/*.cpp"
)

add_library(engine SHARED ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC
    engine/include
    engine/include/components
    engine/include/core
    engine/include/renderer
    engine/include/systems
)

file(GLOB_RECURSE SERVER_SOURCES "r-type/server/src/*.cpp")
add_executable(r-type_server ${SERVER_SOURCES})
target_include_directories(r-type_server PRIVATE ${SERVER_INCLUDE_DIRS})
target_link_libraries(r-type_server PRIVATE engine)

file(GLOB_RECURSE CLIENT_SOURCES "r-type/client/src/*.cpp")
add_executable(r-type_client ${CLIENT_SOURCES})
target_include_directories(r-type_client PRIVATE ${CLIENT_INCLUDE_DIRS})
target_link_libraries(r-type_client PRIVATE engine)

file(GLOB_RECURSE SERVER_SOURCES_TEST "r-type/server/tests/*.cpp" "r-type/server/tests/*.hpp")
add_executable(r-type_server_test ${SERVER_SOURCES_TEST})
target_link_libraries(r-type_server_test engine)
add_test(NAME ServerTests COMMAND r-type_server_test)

file(GLOB_RECURSE CLIENT_SOURCES_TEST "r-type/client/tests/*.cpp" "r-type/client/tests/*.hpp")
add_executable(r-type_client_test ${CLIENT_SOURCES_TEST})
target_link_libraries(r-type_client_test engine)
add_test(NAME ClientTests COMMAND r-type_client_test)

if(MSVC)
    target_compile_options(r-type_server PRIVATE /W4)
    target_compile_options(r-type_client PRIVATE /W4)
else()
    target_compile_options(r-type_server PRIVATE -std=c++20 -Wall)
    target_compile_options(r-type_client PRIVATE -std=c++20 -Wall)
endif()

install(TARGETS engine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY engine/include/ DESTINATION include)

enable_testing()

add_custom_target(re
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
)

add_custom_target(build_server
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_server
)

add_custom_target(build_client
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_client
)

add_custom_target(re_server
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/r-type_server
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_server
)

add_custom_target(re_client
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/r-type_client
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_client
)

# SFML
if(WIN32)
    find_package(SFML COMPONENTS system window graphics network audio  REQUIRED)

    if(SFML_FOUND)
        message(STATUS "SFML found: ${SFML_LIBRARIES}.")
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()

    if(SFML_STATIC_LIBRARIES)
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
        target_link_libraries(r-type_client PRIVATE opengl32 freetype winmm gdi32)
    endif()

else()
    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
    if(SFML_FOUND)
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()
endif()
