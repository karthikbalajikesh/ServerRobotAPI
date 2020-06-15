cmake_minimum_required(VERSION 3.5.1)

# Cmake file for the Server Project. It will contain the following dependencies
# 1. Boost ASIO for TCP Comm
# 2. Boost Serial for Serial Comm
# 3. Threads for Boost ASIO
# 4. GUI Library
# 5. Optimisation Library (optional)

project(Server)

# Adding dependencies
#1. Threads
find_package(Threads REQUIRED)
set(LIBS ${CMAKE_THREAD_LIBS_INIT})

#2. Boost ASIO & Serialization
set(BOOSTPATH "/home/karthik/Downloads/boost_1_73_0/stage/lib/cmake")
set(BOOST_INCLUDE_DIR "/home/karthik/Downloads/boost_1_73_0")
set(BOOST_LIBRARY_DIR "/home/karthik/Downloads/boost_1_73_0/stage/lib")
set(CMAKE_PREFIX_PATH "${BOOSTPATH};${CMAKE_PREFIX_PATH}")
find_package(Boost 1.73 REQUIRED system serialization)
set(LIBS ${BOOST_LIBRARIES};${LIBS})


################ Compiler Settings ####################3
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_BUILD_TYPE "Release")
include_directories(${BOOST_INCLUDE_DIR})
include_directories(include)
link_directories(${BOOST_LIBRARY_DIR})
set(SERIAL "/home/karthik/Downloads/boost_1_73_0/stage/lib/libboost_serialization.so")
set(LIBS ${SERIAL};${LIBS})

file(GLOB PATHSOURCES src/PathPlanner/*.cpp)
file(GLOB TCPSOURCES src/Server/*.cpp)
file(GLOB BEHAVIORSOURCES src/Behavior/*.cpp)
set(LIBSOURCES ${PATHSOURCES};${TCPSOURCES};${BEHAVIORSOURCES})


############# Creating Shared Library #############
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../lib")
add_library(PathPlanner SHARED ${LIBSOURCES})



############# Adding Test FIle ################33333
file(GLOB CUSTOMLIBS lib/*.so)
set(LIBS ${CUSTOMLIBS};${LIBS})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

#1. Check Path planner
add_executable(check "test/main.cpp")
target_link_libraries(check ${LIBS})

#2. Check Server
add_executable(ServerTest "test/serverTest.cpp")
target_link_libraries(ServerTest ${LIBS})