cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp ../engine/src/GraphicsEngine/shader.cpp ../engine/include/engine/GraphicsEngine/shader.h ../engine/src/FileManager/FileManager.cpp ../engine/include/engine/FileManager/FileManager.h ../engine/src/GraphicsEngine/mesh.cpp ../engine/include/engine/GraphicsEngine/mesh.h ../engine/include/engine/GraphicsEngine/Components/Model.h ../engine/src/GraphicsEngine/Systems/GraphicsSystem.cpp ../engine/include/engine/GraphicsEngine/Scene.h ../engine/src/InputSystem/InputManager.cpp ../engine/include/engine/InputSystem/InputManager.h ../engine/src/GraphicsEngine/Components/Transform.cpp ../engine/include/engine/GraphicsEngine/Components/Transform.h ../engine/src/Tools/Grid.cpp ../engine/include/engine/Tools/Grid.h ../engine/src/Tools/CubicNode.cpp ../engine/include/engine/Tools/CubicNode.h ../engine/include/engine/Tools/Node.h src/ShipController.cpp src/ShipController.h)

set(EXE_FILE Game)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

