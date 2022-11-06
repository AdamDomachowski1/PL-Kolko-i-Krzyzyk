# CMakeList.txt: projekt CMake dla elementu OX, do³¹cz Ÿród³o i zdefiniuj
# tutaj logikê specyficzn¹ dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("OX")

# Dodaj Ÿród³o do pliku wykonywalnego tego projektu.
add_executable (OX "main.cpp" "plansza.h" "SI.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OX PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
