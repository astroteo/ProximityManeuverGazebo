cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cholessy_wiltshire_gazebo_plugins)

# Specify C++17 standard
add_definitions(-std=c++17)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS})

######################################################################## Boost
find_package( Boost  COMPONENTS system REQUIRED )

######################################################################## Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/include)

link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

MESSAGE("GAZEBO @@@")
MESSAGE(${GAZEBO_LIBRARY_DIRS})

######################################################################### 3DTLib
set(3DTlib_DIR /usr/local/Cellar/3DTlib/lib)

find_package(3DTlib REQUIRED)
include_directories(${3DTLIB_INCLUDE_DIR})

MESSAGE("FOUND 3DTLIB @@@")
MESSAGE(${3DTLIB_INCLUDE_DIRS})


################################################################ Gazebo messages
include_directories(
                    ${SDF_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_BINARY_DIR}/msgs)

link_directories(${GAZEBO_LIBRARY_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/msgs)
add_subdirectory(msgs)


##################################################[World Plugin] Link an Compile
add_library(cholessy_wiltshire SHARED cholessy_wiltshire.cc )
target_link_libraries(cholessy_wiltshire ${GAZEBO_LIBRARIES})

################################################[Physics Plugin] Link an Compile
