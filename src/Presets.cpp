//
// Theme presets — each function writes a complete ImGuiStyle from scratch so
// the result is always fully defined regardless of the previous state.
//

#include "Presets.h"
#include <imgui.h>

// ── DTL Dark ──────────────────────────────────────────────────────────────────
// A polished dark theme with blue accents, soft rounding, and low visual noise.
static void Preset_DTLDark(ImGuiStyle& s)
{
    // Structure
    s.WindowPadding      = ImVec2(12.0f, 12.0f);
    s.FramePadding       = ImVec2(8.0f,  4.0f);
    s.CellPadding        = ImVec2(6.0f,  4.0f);
    s.ItemSpacing        = ImVec2(8.0f,  6.0f);
    s.ItemInnerSpacing   = ImVec2(6.0f,  4.0f);
    s.TouchExtraPadding  = ImVec2(0.0f,  0.0f);
    s.IndentSpacing      = 20.0f;
    s.ScrollbarSize      = 12.0f;
    s.GrabMinSize        = 8.0f;

    // Borders
    s.WindowBorderSize   = 1.0f;
    s.ChildBorderSize    = 1.0f;
    s.PopupBorderSize    = 1.0f;
    s.FrameBorderSize    = 0.0f;
    s.TabBorderSize      = 0.0f;

    // Rounding
    s.WindowRounding     = 6.0f;
    s.ChildRounding      = 4.0f;
    s.FrameRounding      = 4.0f;
    s.PopupRounding      = 4.0f;
    s.ScrollbarRounding  = 4.0f;
    s.GrabRounding       = 4.0f;
    s.TabRounding        = 4.0f;

    // Alignment
    s.WindowTitleAlign        = ImVec2(0.0f, 0.5f);
    s.WindowMenuButtonPosition = ImGuiDir_Left;
    s.ButtonTextAlign         = ImVec2(0.5f, 0.5f);
    s.SelectableTextAlign     = ImVec2(0.0f, 0.0f);

    // Rendering
    s.Alpha                    = 1.0f;
    s.DisabledAlpha            = 0.45f;
    s.AntiAliasedLines         = true;
    s.AntiAliasedLinesUseTex   = true;
    s.AntiAliasedFill          = true;

    // Colors
    ImVec4* c = s.Colors;
    c[ImGuiCol_Text]                   = ImVec4(0.92f, 0.92f, 0.95f, 1.00f);
    c[ImGuiCol_TextDisabled]           = ImVec4(0.40f, 0.40f, 0.46f, 1.00f);
    c[ImGuiCol_WindowBg]               = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
    c[ImGuiCol_ChildBg]                = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    c[ImGuiCol_PopupBg]                = ImVec4(0.11f, 0.11f, 0.14f, 0.98f);
    c[ImGuiCol_Border]                 = ImVec4(0.22f, 0.22f, 0.28f, 1.00f);
    c[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    c[ImGuiCol_FrameBg]                = ImVec4(0.14f, 0.14f, 0.18f, 1.00f);
    c[ImGuiCol_FrameBgHovered]         = ImVec4(0.20f, 0.20f, 0.26f, 1.00f);
    c[ImGuiCol_FrameBgActive]          = ImVec4(0.24f, 0.24f, 0.30f, 1.00f);
    c[ImGuiCol_TitleBg]                = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    c[ImGuiCol_TitleBgActive]          = ImVec4(0.10f, 0.12f, 0.18f, 1.00f);
    c[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.07f, 0.07f, 0.09f, 0.75f);
    c[ImGuiCol_MenuBarBg]              = ImVec4(0.10f, 0.10f, 0.13f, 1.00f);
    c[ImGuiCol_ScrollbarBg]            = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    c[ImGuiCol_ScrollbarGrab]          = ImVec4(0.26f, 0.26f, 0.34f, 1.00f);
    c[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.34f, 0.34f, 0.44f, 1.00f);
    c[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.40f, 0.40f, 0.52f, 1.00f);
    c[ImGuiCol_CheckMark]              = ImVec4(0.40f, 0.66f, 1.00f, 1.00f);
    c[ImGuiCol_SliderGrab]             = ImVec4(0.32f, 0.58f, 0.96f, 1.00f);
    c[ImGuiCol_SliderGrabActive]       = ImVec4(0.44f, 0.68f, 1.00f, 1.00f);
    c[ImGuiCol_Button]                 = ImVec4(0.20f, 0.36f, 0.64f, 1.00f);
    c[ImGuiCol_ButtonHovered]          = ImVec4(0.28f, 0.46f, 0.78f, 1.00f);
    c[ImGuiCol_ButtonActive]           = ImVec4(0.16f, 0.30f, 0.56f, 1.00f);
    c[ImGuiCol_Header]                 = ImVec4(0.20f, 0.36f, 0.64f, 0.75f);
    c[ImGuiCol_HeaderHovered]          = ImVec4(0.28f, 0.46f, 0.78f, 0.90f);
    c[ImGuiCol_HeaderActive]           = ImVec4(0.16f, 0.30f, 0.56f, 1.00f);
    c[ImGuiCol_Separator]              = ImVec4(0.22f, 0.22f, 0.28f, 1.00f);
    c[ImGuiCol_SeparatorHovered]       = ImVec4(0.32f, 0.58f, 0.96f, 0.80f);
    c[ImGuiCol_SeparatorActive]        = ImVec4(0.32f, 0.58f, 0.96f, 1.00f);
    c[ImGuiCol_ResizeGrip]             = ImVec4(0.32f, 0.58f, 0.96f, 0.18f);
    c[ImGuiCol_ResizeGripHovered]      = ImVec4(0.32f, 0.58f, 0.96f, 0.60f);
    c[ImGuiCol_ResizeGripActive]       = ImVec4(0.32f, 0.58f, 0.96f, 0.90f);
    c[ImGuiCol_Tab]                    = ImVec4(0.12f, 0.12f, 0.16f, 1.00f);
    c[ImGuiCol_TabHovered]             = ImVec4(0.28f, 0.46f, 0.78f, 0.90f);
    c[ImGuiCol_TabActive]              = ImVec4(0.20f, 0.36f, 0.64f, 1.00f);
    c[ImGuiCol_TabUnfocused]           = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
    c[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.22f, 0.40f, 1.00f);
    c[ImGuiCol_DockingPreview]         = ImVec4(0.32f, 0.58f, 0.96f, 0.70f);
    c[ImGuiCol_DockingEmptyBg]         = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);
    c[ImGuiCol_PlotLines]              = ImVec4(0.40f, 0.66f, 1.00f, 1.00f);
    c[ImGuiCol_PlotLinesHovered]       = ImVec4(0.60f, 0.82f, 1.00f, 1.00f);
    c[ImGuiCol_PlotHistogram]          = ImVec4(0.32f, 0.58f, 0.96f, 1.00f);
    c[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.44f, 0.68f, 1.00f, 1.00f);
    c[ImGuiCol_TableHeaderBg]          = ImVec4(0.12f, 0.12f, 0.16f, 1.00f);
    c[ImGuiCol_TableBorderStrong]      = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);
    c[ImGuiCol_TableBorderLight]       = ImVec4(0.16f, 0.16f, 0.22f, 1.00f);
    c[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    c[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.03f);
    c[ImGuiCol_TextSelectedBg]         = ImVec4(0.32f, 0.58f, 0.96f, 0.35f);
    c[ImGuiCol_DragDropTarget]         = ImVec4(0.40f, 0.66f, 1.00f, 0.90f);
    c[ImGuiCol_NavHighlight]           = ImVec4(0.32f, 0.58f, 0.96f, 1.00f);
    c[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    c[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.18f);
    c[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.06f, 0.06f, 0.10f, 0.70f);
}

// ── ImGui built-in wrappers ───────────────────────────────────────────────────
static void Preset_ImGuiDark(ImGuiStyle& s)    { ImGui::StyleColorsDark(&s);    }
static void Preset_ImGuiLight(ImGuiStyle& s)   { ImGui::StyleColorsLight(&s);   }
static void Preset_ImGuiClassic(ImGuiStyle& s) { ImGui::StyleColorsClassic(&s); }

// ── preset table ─────────────────────────────────────────────────────────────
const ThemePreset g_presets[] = {
    { "DTL Dark",     Preset_DTLDark     },
    { "ImGui Dark",   Preset_ImGuiDark   },
    { "ImGui Light",  Preset_ImGuiLight  },
    { "ImGui Classic",Preset_ImGuiClassic},
};
const int g_presetCount = sizeof(g_presets) / sizeof(g_presets[0]);

void ApplyPreset(int index, ImGuiStyle& style)
{
    if (index >= 0 && index < g_presetCount)
        g_presets[index].apply(style);
}
