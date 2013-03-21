cmake_minimum_required(VERSION 2.6)

project(BattleshipContest CXX)

set(BC_LIBRARY "battleshipLib")
set(BC_GAME "battleshipContest")

set(BC_SOLUTION_ROOT_DIR "${CMAKE_SOURCE_DIR}")
message(STATUS "Solution root directory : ${BC_SOLUTION_ROOT_DIR}")

include_directories("${BC_SOLUTION_ROOT_DIR}/include")
set(BC_CURRENT_SOURCES
  "src/Engine.cpp"
  "src/EngineSender.cpp"
  "src/EngineReceiver.cpp"
  "src/Controller.cpp"
  "src/ParseCmdOptions.cpp"
  "src/ShipFactory.cpp"
  "src/Rules.cpp"
  "src/Cell.cpp"
  "src/Grid.cpp"
  "src/Game.cpp"
)

add_library(${BC_LIBRARY} SHARED ${BC_CURRENT_SOURCES})

set(BC_GAME_SOURCES
  "src/main.cpp"
)
add_executable(${BC_GAME} ${BC_GAME_SOURCES} )
target_link_libraries(${BC_GAME} ${BC_LIBRARY})


if (MARAT_ALGO_COMPILE)
  set(MARAT_ALGO "maratAlgo")
  set(MARAT_SRC
    "marat/main.cpp"
  )
  
  add_executable(${MARAT_ALGO} ${MARAT_SRC})
  target_link_libraries(${MARAT_ALGO} ${BC_LIBRARY})
endif (MARAT_ALGO_COMPILE)
