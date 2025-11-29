cmake_minimum_required(VERSION 3.16)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
project(ksmaxis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
	add_compile_options(/utf-8)
endif()

file(GLOB_RECURSE KSMAXIS_SOURCES src/*.cpp)
add_library(ksmaxis STATIC ${KSMAXIS_SOURCES})

target_include_directories(ksmaxis PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
	target_link_libraries(ksmaxis PRIVATE dinput8 dxguid)
elseif(APPLE)
	find_library(IOKIT_FRAMEWORK IOKit REQUIRED)
	find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)
	target_link_libraries(ksmaxis PRIVATE ${IOKIT_FRAMEWORK} ${COREFOUNDATION_FRAMEWORK})
elseif(UNIX)
	find_package(X11 REQUIRED)
	if(NOT X11_Xi_FOUND)
		message(FATAL_ERROR "X11 XInput extension not found")
	endif()
	target_link_libraries(ksmaxis PRIVATE X11::X11 X11::Xi)
endif()

target_compile_features(ksmaxis PUBLIC cxx_std_20)

option(KSMAXIS_BUILD_EXAMPLE "Build example application" ON)

if(KSMAXIS_BUILD_EXAMPLE)
	add_executable(ksmaxis_example example/main.cpp)
	target_link_libraries(ksmaxis_example PRIVATE ksmaxis)
endif()
