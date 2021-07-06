cmake_minimum_required(VERSION 3.17)
project(WEndex)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Dependencies ###
add_subdirectory(dependencies)

### Main Targets ###
add_subdirectory(src)

