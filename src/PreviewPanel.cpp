//
// Created by ancalagorn on 07.05.2026.
//

#include "PreviewPanel.h"

#include <imgui.h>

#include "Showcase.h"

void RenderPreviewPanel(ImGuiStyle& themeStyle) {
    (void)themeStyle;

    if (!ImGui::Begin("Preview")) {
        ImGui::End();
        return;
    }

    RenderShowcase();

    ImGui::End();
}
