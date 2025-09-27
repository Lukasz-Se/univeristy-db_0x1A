cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("University_database")

set(ProjectFilesToCompile

src/Person.cpp
src/Student.cpp
src/Employee.cpp
src/pesel.cpp
src/db.cpp
src/peselBirthDateParser.cpp
src/PersonsGenerator.cpp
src/PeselGenerator.cpp
 "src/main.cpp")

set(TestFilesToCompile
src/ut/test_2.cpp

src/Person.cpp
src/Student.cpp
src/Employee.cpp
src/pesel.cpp
src/db.cpp
src/peselBirthDateParser.cpp
src/PersonsGenerator.cpp
src/PeselGenerator.cpp
)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${ProjectFilesToCompile} )

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${PROJECT_NAME}-ut
  ${TestFilesToCompile})

target_link_libraries(
  ${PROJECT_NAME}-ut
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)