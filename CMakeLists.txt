cmake_minimum_required(VERSION 3.25)
project(P2pmessenger)

set(CMAKE_CXX_STANDARD 17)

add_executable(P2pmessenger
        main.cpp
        discovery.cpp
        peer.cpp
        ui.cpp
)

# Link Windows socket library
target_link_libraries(P2pmessenger ws2_32)
