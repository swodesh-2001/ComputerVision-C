cmake_minimum_required(VERSION 3.13)

# Set the project name and version
project(open3d_practice)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find Open3D package
find_package(Open3D REQUIRED ,OpenCV REQUIRED)

if (Open3D_FOUND)
    message(STATUS "Open3D found. Version: ${Open3D_VERSION}")
else()
    message(FATAL_ERROR "Open3D not found.")
endif()

# Include Open3D headers
include_directories(${Open3D_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(3d_app main.cpp)

# Link Open3D libraries
target_link_libraries(3d_app ${Open3D_LIBRARIES} ${OpenCV_LIBRARIES})
