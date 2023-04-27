cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
if(LINUX)
    set(CMAKE_CXX_COMPILER "clang++")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(WebCore)

set(WEBCORE_VERSION_MAJOR 0)
set(WEBCORE_VERSION_MINOR 1)

set(SOURCES
    src/HttpStatus.cpp
    src/HttpMethod.cpp
    src/Router.cpp
    src/Request.cpp
    src/Response.cpp
    src/App.cpp
    src/Logger.cpp
)

set(HEADERS
    include/WebCore/WebCore.h
    include/WebCore/HttpStatus.h
    include/WebCore/HttpMethod.h
    include/WebCore/HttpHeader.h
    include/WebCore/Router.h
    include/WebCore/Request.h
    include/WebCore/Response.h
    include/WebCore/App.h
    include/WebCore/Utils/Logger.h
)

set(TESTS
    tests/Router_test.cpp
)

set(EXAMPLE
    example/main.cpp
    example/App.cpp
)

add_library(WebCore ${SOURCES} ${HEADERS})

target_include_directories(WebCore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_precompile_headers(WebCore
    PRIVATE
        src/Common.h
)

if(WIN32)
    target_link_libraries(WebCore
        PRIVATE
            wsock32
            ws2_32
    )
endif()

target_compile_options(WebCore
PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

enable_testing()

foreach(test_src ${TESTS})
    get_filename_component(test_name ${test_src} NAME_WE)

    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} WebCore)

    add_test(
        NAME
            ${test_name}
        COMMAND
            ${test_name}
    )
endforeach()

add_executable(example_WebCore ${EXAMPLE})
target_link_libraries(example_WebCore WebCore)
