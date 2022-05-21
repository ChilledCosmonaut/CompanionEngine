cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp src/shader.cpp src/shader.h ../engine/src/FileManager/FileManager.cpp ../engine/include/FileManager/FileManager.h ../engine/src/FileManager/std_image.cpp ../engine/src/GraphicsEngine/camera.cpp ../engine/include/GraphicsEngine/camera.h ../engine/src/GraphicsEngine/mesh.cpp ../engine/include/GraphicsEngine/mesh.h ../engine/src/GraphicsEngine/Model.cpp ../engine/include/GraphicsEngine/Model.h ../engine/src/GraphicsEngine/Scene.cpp ../engine/include/GraphicsEngine/Scene.h ../engine/src/InputSystem/InputManager.cpp ../engine/include/InputSystem/InputManager.h ../engine/src/GraphicsEngine/Transform.cpp ../engine/include/GraphicsEngine/Transform.h ../engine/src/Tools/Grid.cpp ../engine/include/Tools/Grid.h ../engine/src/Tools/CubicNode.cpp ../engine/include/Tools/CubicNode.h ../engine/src/Tools/Node.cpp ../engine/include/Tools/Node.h src/ShipController.cpp src/ShipController.h)

set(EXE_FILE Game)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

