cmake_minimum_required(VERSION 2.6)

project(BattleshipContest CXX)

set(BC_SOLUTION_ROOT_DIR "${CMAKE_SOURCE_DIR}")
message(STATUS "Solution root directory : ${BC_SOLUTION_ROOT_DIR}")

include_directories("${BC_SOLUTION_ROOT_DIR}/include")
set(BC_CURRENT_SOURCES
  "src/ParseCmdOptions.cpp"
  "src/ShipFactory.cpp"
  "src/Rules.cpp"
  "src/Cell.cpp"
  "src/Grid.cpp"
  "src/main.cpp"
)

add_executable("battleshipContest" ${BC_CURRENT_SOURCES})

