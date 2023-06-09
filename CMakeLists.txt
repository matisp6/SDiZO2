cmake_minimum_required(VERSION 3.25)
project(SDiZO2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SDiZO2
        DrzewoSpinajace.cpp
        DrzewoSpinajace.h
        ElementListy.h
        Graf.cpp
        Graf.h
        Interfejs.cpp
        Interfejs.h
        Krawedz.h
        main.cpp
        Stos.cpp
        Stos.h Testy.cpp Testy.h)
