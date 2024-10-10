cmake_minimum_required(VERSION 3.15)
project(RType)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/automate-vcpkg.cmake)

vcpkg_bootstrap()
vcpkg_install_packages(sfml)

set(CLIENT_INCLUDE_DIRS 
    r-type/client/include
    r-type/client/include/components
    r-type/client/include/events
    r-type/client/include/events/data
    r-type/client/include/systems
)
set(SERVER_INCLUDE_DIRS 
    r-type/server/include
    r-type/server/include/components
    r-type/server/include/events
    r-type/server/include/events/data
    r-type/server/include/systems
)

set(SHARED_INCLUDE_DIRS
    r-type/shared/include
    r-type/shared/include/components
    r-type/shared/include/events
    r-type/shared/include/events/data
    r-type/shared/include/systems
)

file(GLOB_RECURSE ENGINE_SOURCES
    "engine/src/components/*.cpp"
    "engine/src/core/*.cpp"
    "engine/src/core/entities/*.cpp"
    "engine/src/core/eventBus/*.cpp"
    "engine/src/events/*.cpp"
    "engine/src/systems/*.cpp"
)

add_library(engine SHARED ${ENGINE_SOURCES})

target_include_directories(engine PUBLIC
    engine/include
    engine/include/components
    engine/include/core
    engine/include/core/entities
    engine/include/core/eventBus
    engine/include/systems
    engine/include/events
    engine/include/events/data
)

file(GLOB_RECURSE SHARED_SOURCES
    "r-type/shared/src/*.cpp"
    "r-type/shared/src/components/*.cpp"
    "r-type/shared/src/events/*.cpp"
    "r-type/shared/src/systems/*.cpp"
    "r-type/shared/src/tools/*.cpp"
)

file(GLOB_RECURSE SERVER_SOURCES
    "r-type/server/src/*.cpp"
)

add_executable(r-type_server ${SERVER_SOURCES} ${SHARED_SOURCES})
target_include_directories(r-type_server PRIVATE ${SERVER_INCLUDE_DIRS} ${SHARED_INCLUDE_DIRS})
target_link_libraries(r-type_server PRIVATE engine)

file(GLOB_RECURSE CLIENT_SOURCES
    "r-type/client/src/*.cpp"
)

add_executable(r-type_client ${CLIENT_SOURCES} ${SHARED_SOURCES})
target_include_directories(r-type_client PRIVATE ${CLIENT_INCLUDE_DIRS} ${SHARED_INCLUDE_DIRS})
target_link_libraries(r-type_client PRIVATE engine)

file(GLOB_RECURSE SERVER_SOURCES_TEST "r-type/server/tests/*.cpp" "r-type/server/tests/*.hpp")
add_executable(r-type_server_test ${SERVER_SOURCES_TEST})
target_include_directories(r-type_server_test PRIVATE ${SERVER_INCLUDE_DIRS} ${GAME_INCLUDE_DIRS})
target_link_libraries(r-type_server_test PRIVATE engine)
add_test(NAME ServerTests COMMAND r-type_server_test)

file(GLOB_RECURSE CLIENT_SOURCES_TEST "r-type/client/tests/*.cpp" "r-type/client/tests/*.hpp")
add_executable(r-type_client_test ${CLIENT_SOURCES_TEST})
target_include_directories(r-type_client_test PRIVATE ${CLIENT_INCLUDE_DIRS} ${GAME_INCLUDE_DIRS})
target_link_libraries(r-type_client_test PRIVATE engine)
add_test(NAME ClientTests COMMAND r-type_client_test)

if(MSVC)
    target_compile_options(r-type_server PRIVATE /W4)
    target_compile_options(r-type_client PRIVATE /W4)
else()
    target_compile_options(r-type_server PRIVATE -std=c++20 -g -Wall)
    target_compile_options(r-type_client PRIVATE -std=c++20 -g -Wall)
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
        target_link_libraries(engine PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
    else()
        message(FATAL_ERROR "SFML not found!")
    endif()
endif()
