//
// Created by ancalagorn on 05.05.2026.
//

#include "App.h"

#include <imgui.h>
#include <imgui_internal.h>

#include "PreviewPanel.h"
#include "EditorPanel.h"

void App::Init() {
    g_editorStyle = ImGui::GetStyle();

    // Start the theme from ImGui's Dark baseline
    ImGui::StyleColorsDark(&g_themeStyle);
}

void App::OnFrame() {
    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(
        0,
        nullptr,
        ImGuiDockNodeFlags_PassthruCentralNode
    );

    if (m_firstFrame) {
        m_firstFrame = false;
        SetupInitialDockLayout(dockspace_id);
    }

    // Editor renders with the editor style (no swap needed — it's the default)
    RenderEditorPanel(g_themeStyle);

    // Swap to the theme under design for the Preview panel only
    ImGui::GetStyle() = g_themeStyle;
    RenderPreviewPanel(g_themeStyle);
    // Always restore — unconditional, even if RenderPreviewPanel returned early
    ImGui::GetStyle() = g_editorStyle;
}

void App::SetupInitialDockLayout(ImGuiID dockspace_id) {
    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

    ImGuiID editor_id, preview_id;
    // Right 40% Editor, left 60% Preview
    ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.4f, &editor_id, &preview_id);
    ImGui::DockBuilderDockWindow("Editor",  editor_id);
    ImGui::DockBuilderDockWindow("Preview", preview_id);
    ImGui::DockBuilderFinish(dockspace_id);
}
