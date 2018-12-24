#specify the minimum version for CMake
cmake_minimum_required(VERSION 3.11)

project(FrontEnd)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Modules)

set(SOURCE_FILES src/main.cpp src/FrontEnd.cpp src/systems.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)


include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

add_executable(FrontEnd ${SOURCE_FILES})

target_link_libraries(FrontEnd ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})


