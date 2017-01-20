cmake_minimum_required(VERSION 3.6)
project(SteamStatus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(SteamStatus ${SOURCE_FILES})
include_directories(/home/marz/steamworks/sdk/public/steam/)
target_link_libraries(SteamStatus ${CMAKE_CURRENT_SOURCE_DIR}/libsteam_api.so)