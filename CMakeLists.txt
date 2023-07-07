cmake_minimum_required(VERSION 3.12)
project(mandelbroat-glfw VERSION 0.1.0)

add_executable(main 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/VertexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/IndexBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/VertexBufferLayout.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Shaders.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/Utils.cpp
    )

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib)

target_link_libraries(main PRIVATE Xrandr Xi Xxf86vm X11) # Linux X11 required
target_link_libraries(main PRIVATE GLEW) # GLEW
target_link_libraries(main PRIVATE EGL GL GLU OpenGL) # OpenGL required
target_link_libraries(main PRIVATE glfw3) # GLFW

add_custom_command(
    TARGET main POST_BUILD 
    COMMAND  rm -r ${CMAKE_CURRENT_BINARY_DIR}/res && cp -r ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM)