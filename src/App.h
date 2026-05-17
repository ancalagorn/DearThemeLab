//
// Created by ancalagorn on 05.05.2026.
//

#pragma once

#include "imgui.h"

class App {
public:
    ImGuiStyle g_editorStyle;
    ImGuiStyle g_themeStyle;

    void Init();
    void OnFrame();

private:
    bool m_firstFrame = true;
    void SetupInitialDockLayout(ImGuiID dockspace_id);
};
