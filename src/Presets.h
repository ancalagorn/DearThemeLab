#pragma once
#include <imgui.h>

struct ThemePreset {
    const char* name;
    void (*apply)(ImGuiStyle& style);
};

extern const ThemePreset g_presets[];
extern const int         g_presetCount;

// Applies preset by index. Safe to call with any index in [0, g_presetCount).
void ApplyPreset(int index, ImGuiStyle& style);
