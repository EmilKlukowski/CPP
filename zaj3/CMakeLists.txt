cmake_minimum_required(VERSION 3.22)
project(untitled)

set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

FetchContent_Declare(
        fmt                                                         #jaka biblioteka
        GIT_REPOSITORY https://github.com/fmtlib/fmt                #skad bedzie pobrana   ||| NIE mozna dodawac kolejne bibl po spacji
        GIT_TAG a33701196adfad74917046096bf5a2aa0ab0bb50            #numer commita, wersja  ||| Najlepiej stworzyc nowy FetchContent_Declare
)

FetchContent_MakeAvailable(fmt)                                        #fetch content pobiera ||| mozna dodawac kolejne bibl po spacji

add_executable(untitled main.cpp)
target_link_libraries(untitled fmt)                                    #target link eksportuje do projektu ||| mozna dodawac kolejne bibl po spacji
