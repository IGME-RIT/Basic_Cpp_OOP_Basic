
if(WIN32)
cmake_minimum_required (VERSION 3.6)
else()
cmake_minimum_required (VERSION 3.0)
endif()

project(TestOOPBasics)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set (${PROJECT_NAME}._VERSION_MAJOR 1)
set (${PROJECT_NAME}._VERSION_MINOR 0)
set (${PROJECT_NAME}._VERSION_BUILD 0)

	
file(GLOB SOURCE_FILES "source/*.cpp")
file(GLOB HEADER_FILES "header/*.h")

source_group("source" FILES ${SOURCE_FILES})
source_group("header" FILES ${HEADER_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# vim: ts=4 sw=4 et
