cmake_minimum_required(VERSION 3.16)

project(SD1 LANGUAGES CXX)

# Naudojame C++17 standarta.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dabartinis atminties matavimas pritaikytas Windows.
if(NOT WIN32)
    message(FATAL_ERROR "Si programos versija skirta Windows.")
endif()

# Failai, is kuriu kompiliuojama programa.
add_executable(SD1
    StudDB.cpp
    Studentas.cpp
    Failai.cpp
    Matavimai.cpp
)

# Biblioteka atminties matavimui.
target_link_libraries(SD1 PRIVATE Psapi)

# Saltinio failus skaitome kaip UTF-8.
if(MSVC)
    target_compile_options(SD1 PRIVATE /utf-8)
endif()