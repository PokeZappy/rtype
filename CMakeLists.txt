cmake_minimum_required(VERSION 3.15)
project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/auto-vcpkg.cmake)
vcpkg_add_package(sfml)

set(CLIENT_INCLUDE_DIRS
    r-type/client/include
    r-type/client/include/components
    r-type/client/include/events
    r-type/client/include/events/data
    r-type/client/include/systems)

set(SERVER_INCLUDE_DIRS
    r-type/server/include
    r-type/server/include/components
    r-type/server/include/events
    r-type/server/include/events/data
    r-type/server/include/systems)

set(SHARED_INCLUDE_DIRS
    r-type/shared/include
    r-type/shared/include/components
    r-type/shared/include/cross
    r-type/shared/include/events
    r-type/shared/include/events/data
    r-type/shared/include/systems)

file(GLOB_RECURSE ENGINE_SOURCES
    "engine/src/components/*.cpp"
    "engine/src/core/*.cpp"
    "engine/src/core/entities/*.cpp"
    "engine/src/core/eventBus/*.cpp"
    "engine/src/events/*.cpp"
    "engine/src/systems/*.cpp")

add_library(engine STATIC ${ENGINE_SOURCES})
set_target_properties(engine PROPERTIES
    IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/lib/engine.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/include/libengine")

target_include_directories(engine PUBLIC
    engine/include
    engine/include/components
    engine/include/core
    engine/include/core/entities
    engine/include/core/eventBus
    engine/include/systems
    engine/include/events
    engine/include/events/data)

file(GLOB_RECURSE SHARED_SOURCES
    "r-type/shared/src/*.cpp"
    "r-type/shared/src/components/*.cpp"
    "r-type/shared/src/events/*.cpp"
    "r-type/shared/src/systems/*.cpp"
    "r-type/shared/src/tools/*.cpp")

file(GLOB_RECURSE SERVER_SOURCES "r-type/server/src/*.cpp")

add_executable(r-type_server ${SERVER_SOURCES} ${SHARED_SOURCES})
target_include_directories(r-type_server PRIVATE ${SERVER_INCLUDE_DIRS} ${SHARED_INCLUDE_DIRS})
target_link_libraries(r-type_server PRIVATE engine)

file(GLOB_RECURSE CLIENT_SOURCES "r-type/client/src/*.cpp")

add_executable(r-type_client ${CLIENT_SOURCES} ${SHARED_SOURCES})
target_include_directories(r-type_client PRIVATE ${CLIENT_INCLUDE_DIRS} ${SHARED_INCLUDE_DIRS})
target_link_libraries(r-type_client PRIVATE engine)

file(GLOB_RECURSE SERVER_SOURCES_TEST "r-type/server/tests/*.cpp" "r-type/server/tests/*.hpp")
add_executable(r-type_server_test ${SERVER_SOURCES_TEST})
#target_link_libraries(r-type_server_test engine)
add_test(NAME ServerTests COMMAND r-type_server_test)

file(GLOB_RECURSE CLIENT_SOURCES_TEST "r-type/client/tests/*.cpp" "r-type/client/tests/*.hpp")
add_executable(r-type_client_test ${CLIENT_SOURCES_TEST})
#target_link_libraries(r-type_client_test engine)
add_test(NAME ClientTests COMMAND r-type_client_test)

if(MSVC)
#    target_compile_options(r-type_server PRIVATE /W4)
#    target_compile_options(r-type_client PRIVATE /W4)
else()
    target_compile_options(r-type_server PRIVATE -std=c++20 -g -Wall)
    target_compile_options(r-type_client PRIVATE -std=c++20 -g -Wall)
endif()

install(TARGETS engine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(DIRECTORY engine/include/ DESTINATION include)

enable_testing()

add_custom_target(re
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR})

add_custom_target(build_server
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_server)

add_custom_target(build_client
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_client)

add_custom_target(re_server
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/r-type_server
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_server)

add_custom_target(re_client
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/r-type_client
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target r-type_client)

# SFML
if(WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg/installed/x64-windows/share")
    include_directories("${CMAKE_BINARY_DIR}/vcpkg/installed/x64-windows/include")
    find_package(SFML COMPONENTS system window graphics audio  REQUIRED)

    if(SFML_FOUND)
        message(STATUS "SFML found: ${SFML_LIBRARIES}.")
        target_link_libraries(engine PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio ws2_32)
        target_link_libraries(r-type_server PRIVATE sfml-system sfml-window sfml-graphics sfml-audio ws2_32)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()
else()
    set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg/installed/x64-linux/share")
    include_directories("${CMAKE_BINARY_DIR}/vcpkg/installed/x64-linux/include")
    find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
    if(SFML_FOUND)
        target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
        target_link_libraries(engine PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()
endif()
