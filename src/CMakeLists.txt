add_executable(DearThemeLab
    main.cpp
    App.cpp
    PreviewPanel.cpp
    Showcase.cpp
    EditorPanel.cpp
    Exporter.cpp
)

if(APPLE)
    target_compile_definitions(DearThemeLab PRIVATE GL_SILENCE_DEPRECATION)
endif()

target_link_libraries(DearThemeLab PRIVATE imgui nfd::nfd)
