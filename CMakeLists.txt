cmake_minimum_required(VERSION 3.20)

project(TuringMachine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(turing-machine src/main.cpp
    src/machine.h src/machine.cpp
    src/parser.h src/parser.cpp
)

include(GNUInstallDirs)
install(TARGETS turing-machine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
