cmake_minimum_required(VERSION 3.21)
project(Client)

set(CMAKE_CXX_STANDARD 14)

add_executable(Client Client.cpp targetver.h stdafx.h Server.cpp Server.h Main.cpp Main.h)
