cmake_minimum_required(VERSION 3.16)

project(cps2linux LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cps2linux main.cpp)
target_compile_options(cps2linux PRIVATE -Wno-unsafe-buffer-usage)

include(GNUInstallDirs)
install(TARGETS cps2linux
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
