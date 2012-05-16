project(Pianobar-QT)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Pianobar-QT_SRCS Pianobar-QT.cpp main.cpp)
qt4_automoc(${Pianobar-QT_SRCS})
add_executable(Pianobar-QT ${Pianobar-QT_SRCS})
target_link_libraries(Pianobar-QT ${QT_QTCORE_LIBRARY})
