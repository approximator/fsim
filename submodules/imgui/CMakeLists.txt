add_library(imgui
    imgui.cpp
    imgui_widgets.cpp
    imgui_draw.cpp
    imgui_demo.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC .)
target_compile_definitions(imgui PRIVATE "-DIMGUI_IMPL_OPENGL_LOADER_GLAD")
target_link_libraries(imgui PRIVATE glad glfw)
