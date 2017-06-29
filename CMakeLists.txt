cmake_minimum_required(VERSION 3.7)
project(EX4_LATEST_)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Company.cpp Company.h Enigma.cpp Enigma.h EscapeRoom.c EscapeRoom.h
        EscapeRoomWrapper.cpp EscapeRoomWrapper.h Exceptions.h KidsRoom.cpp KidsRoom.h
        list.h mtmtest.h ScaryRoom.cpp ScaryRoom.h tests/KidsRoom_test.cpp)
add_executable(EX4_LATEST_ ${SOURCE_FILES})