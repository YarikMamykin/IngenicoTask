cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/clients)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/server)

find_package(Threads REQUIRED)

set(SOURCES 
  ${CMAKE_CURRENT_SOURCE_DIR}/clients/Client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/clients/ClientsDataQueue.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
