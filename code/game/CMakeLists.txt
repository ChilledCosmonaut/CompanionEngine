cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp src/Systems/ShipController.cpp src/Systems/ShipController.h src/Components/ShipMovementSettings.h src/ControlGroups/Spaceship/SpaceShipControls.h src/ControlGroups/Spaceship/SpaceShipControls.cpp src/Systems/EnemyController.h src/Systems/EnemyController.cpp src/Systems/AsteroidVectorField.h src/Systems/AsteroidVectorField.cpp)

set(EXE_FILE Game)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

