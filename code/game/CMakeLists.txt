cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp ../engine/src/Systems/Graphics/shader.cpp ../engine/include/engine/Systems/Graphics/shader.h ../engine/src/Systems/FileManager/FileManager.cpp ../engine/include/engine/Systems/FileManager/FileManager.h ../engine/src/Systems/Graphics/mesh.cpp ../engine/include/engine/Systems/Graphics/mesh.h ../engine/include/engine/Systems/Graphics/Components/Model.h ../engine/src/Systems/Graphics/GraphicsSystem.cpp ../engine/include/engine/Systems/Graphics/Scene.h ../engine/src/Systems/InputSystem/InputManager.cpp ../engine/include/engine/Systems/Input/InputManager.h ../engine/src/Systems/Graphics/Utils/TransformUtils.cpp ../engine/include/engine/Systems/Graphics/Components/Transform.h ../engine/src/Tools/Grid.cpp ../engine/include/engine/Tools/Grid.h ../engine/src/Tools/CubicNode.cpp ../engine/include/engine/Tools/CubicNode.h ../engine/include/engine/Tools/Node.h src/ShipController.cpp src/ShipController.h)

set(EXE_FILE Game)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

