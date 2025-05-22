# CMakeList.txt: projekt CMake dla elementu university_db-minproject, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (university_db-minproject "university_db-minproject.cpp" "university_db-minproject.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET university_db-minproject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
