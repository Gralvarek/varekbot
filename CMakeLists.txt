cmake_minimum_required(VERSION 2.8)

include_directories("include/slacking")

find_package(CURL)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(".")

set (SOURCES_EXAMPLES
    main.cpp
)

set (TARGETS_EXAMPLES
    main
)

foreach( name ${TARGETS_EXAMPLES} )
    add_executable(${name} ${name}.cpp)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD 11)
    set_property(TARGET ${name} PROPERTY CXX_STANDARD_REQUIRED ON)
    target_link_libraries(${name} ${CURL_LIBRARIES})
endforeach()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -pedantic")

if ("${CMAKE_MAJOR_VERSION}${CMAKE_MINOR_VERSION}" LESS 31)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")

add_definitions(-DSLACKING_VERBOSE_OUTPUT=1)
