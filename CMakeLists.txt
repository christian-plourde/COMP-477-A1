#When using this template, all you need to do is change the name of the project (the second line)

cmake_minimum_required(VERSION 3.3)
project(COMP_477_A1_PROBLEM_1)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES problem_1.cpp Loaders/ShaderLoader.cpp Loaders/ObjectLoader.cpp Controls/KeyboardControls.cpp Utilities/Lights/Light.cpp Utilities/Window/Window.cpp Utilities/Objects/MVP.cpp Utilities/Shading/Shader.cpp Utilities/Shading/Uniform.cpp Utilities/Objects/Object.cpp Utilities/ErrorHandling/ErrorHandlingFunction.cpp Utilities/Objects/ObjectContainer.cpp Utilities/ShadowMapping/DepthMap.cpp Utilities/ShadowMapping/DepthMapLight.cpp Utilities/Lights/SpotLight.cpp Utilities/Camera/Camera.cpp Utilities/Objects/BoundingBox.cpp Utilities/Timing/Timestep.cpp)
set(SOURCE_FILES_2 problem_2.cpp Loaders/ShaderLoader.cpp Loaders/ObjectLoader.cpp Controls/KeyboardControls.cpp Utilities/Lights/Light.cpp Utilities/Window/Window.cpp Utilities/Objects/MVP.cpp Utilities/Shading/Shader.cpp Utilities/Shading/Uniform.cpp Utilities/Objects/Object.cpp Utilities/ErrorHandling/ErrorHandlingFunction.cpp Utilities/Objects/ObjectContainer.cpp Utilities/ShadowMapping/DepthMap.cpp Utilities/ShadowMapping/DepthMapLight.cpp Utilities/Lights/SpotLight.cpp Utilities/Camera/Camera.cpp Utilities/Objects/BoundingBox.cpp Utilities/Timing/Timestep.cpp Utilities/Timing/GradualTranslation.cpp Utilities/Timing/Interpolator.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLM/glm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include)
find_library(GLFW_LIBRARIES NAMES glfw3 PATHS "${CMAKE_CURRENT_SOURCE_DIR}/GLFW/lib-mingw-w64")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GLEW/include/GL)
find_library(GLEW_LIBRARIES NAMES glew32 PATHS "${CMAKE_CURRENT_SOURCE_DIR}/GLEW/lib")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
add_executable(COMP_477_A1_PROBLEM_2 ${SOURCE_FILES_2})

# Linking GLFW and OGL
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})
target_link_libraries(COMP_477_A1_PROBLEM_2 ${OPENGL_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})