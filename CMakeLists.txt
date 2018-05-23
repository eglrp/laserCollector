cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++11)
project(dataCollector)


# third_parties
# cereal
include_directories(third_parties/cereal/include)
# velodyne
add_subdirectory(third_parties/VelodyneHDL)
include_directories(third_parties/VelodyneHDL)

include_directories(common)
add_subdirectory(common)
##

add_subdirectory(collectLaser)
