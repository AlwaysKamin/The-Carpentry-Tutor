#  minimum required cmake version: 3.1.0
cmake_minimum_required(VERSION 3.1.0)

project(cmake-build-debug/CarpentryTutor)

# Save the command line compile commands in the build output
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


# Make project require C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


elseif (COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif ()

find_library(REALSENSE2_FOUND realsense2 HINTS ${LIBRARY_DIR} REQUIRED)
if (NOT REALSENSE2_FOUND)
    SET(REALSENSE2_FOUND "realsense2")
    message(WARN "Failed to find_library(realsense2)")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}/bin)

add_subdirectory(lib/imgui)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

if (APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
endif (APPLE)

# getting-started
add_executable(CarpentryTutor src/main.cpp src/window.cpp include/window.h)
include_directories(include)
target_link_libraries(CarpentryTutor
        ${REALSENSE2_FOUND}
        imgui
        ${OPENGL_LIBRARIES}
        glfw
        ${GLEW_LIBRARIES})

add_executable(GuiTesting spike/GuiTesting/GuiTesting.cpp)
include_directories(GuiTesting ${ADDITIONAL_INCLUDE_DIRS} include lib/imgui)
target_link_libraries(
        GuiTesting
        imgui
        ${OPENGL_LIBRARIES}
        glfw
        ${GLEW_LIBRARIES}
)

add_executable(modelingTest spike/modelingTest/modelingTest.cpp)
include_directories(modelingTest ${ADDITIONAL_INCLUDE_DIRS} include lib/imgui)
target_link_libraries(
        modelingTest
        imgui
        ${OPENGL_LIBRARIES}
        glfw
        ${GLEW_LIBRARIES}
)


add_executable(distanceTest spike/distanceTest/distanceTest.cpp)
include_directories(distanceTest ${ADDITIONAL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} include lib/imgui)
target_link_libraries(
        distanceTest
        ${OpenCV_LIBS}
        ${REALSENSE2_FOUND}
        ${GLFW_LIBRARIES})
set_target_properties(distanceTest PROPERTIES FOLDER Examples)


install(
        TARGETS

        CarpentryTutor

        RUNTIME DESTINATION
        ${CMAKE_HOME_DIRECTORY}/bin
)