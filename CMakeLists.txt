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
    set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")
else()
    message(WARNING "VCPKG_ROOT environment variable not defined, skipping vcpkg integration")
endif()

set(CLIENT_INCLUDE_DIRS r-type/client/include)
set(ENGINE_INCLUDE_DIRS engine)

include_directories(${ENGINE_INCLUDE_DIRS} r-type)

file(GLOB_RECURSE SERVER_SOURCES "r-type/server/src/*.cpp" "r-type/server/include/*.hpp")
file(GLOB_RECURSE CLIENT_SOURCES "r-type/client/src/*.cpp")
file(GLOB_RECURSE ENGINE_SOURCES "engine/*.cpp" "engine/*.hpp")
file(GLOB_RECURSE SERVER_SOURCES_TEST "r-type/server/tests/*.cpp" "r-type/server/tests/*.hpp")
file(GLOB_RECURSE CLIENT_SOURCES_TEST "r-type/client/tests/*.cpp" "r-type/client/tests/*.hpp")

add_executable(r-type_server ${SERVER_SOURCES})
add_executable(r-type_client ${CLIENT_SOURCES})

add_library(engine STATIC ${ENGINE_SOURCES})

target_link_libraries(r-type_server PRIVATE engine)
target_link_libraries(r-type_client PRIVATE engine)

target_include_directories(r-type_server PRIVATE ${SERVER_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})
target_include_directories(r-type_client PRIVATE ${CLIENT_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})

if(MSVC)
    target_compile_options(r-type_server PRIVATE /W4)
    target_compile_options(r-type_client PRIVATE /W4)
else()
    target_compile_options(r-type_server PRIVATE -std=c++20 -Wall)
    target_compile_options(r-type_client PRIVATE -std=c++20 -Wall)
endif()

enable_testing()

add_executable(r-type_server_test ${SERVER_SOURCES_TEST})
target_link_libraries(r-type_server_test engine)
add_test(NAME ServerTests COMMAND r-type_server_test)

add_executable(r-type_client_test ${CLIENT_SOURCES_TEST})
target_link_libraries(r-type_client_test engine)
add_test(NAME ClientTests COMMAND r-type_client_test)

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

if(WIN32)
    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

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
    find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
    if(SFML_FOUND)
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()
endif()
