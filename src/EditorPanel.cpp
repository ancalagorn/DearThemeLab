//
// Created by ancalagorn on 10.05.2026.
//

#include "EditorPanel.h"

#include <string>
#include <nfd.h>
#include <imgui.h>

#include "Exporter.h"

// ── export state (persists across frames) ─────────────────────────────────────
static ExportOptions s_exportOpts;
static std::string s_exportCode;
static char s_funcNameBuf[64] = "ApplyTheme";
static char s_nsBuf[64] = "";

// ── colors filter ─────────────────────────────────────────────────────────────
static ImGuiTextFilter s_colorFilter;

// ── helpers ───────────────────────────────────────────────────────────────────

static void Tip(const char* text) {
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) ImGui::SetTooltip("%s", text);
}

// ── section renderers ─────────────────────────────────────────────────────────

static void RenderMainSection(ImGuiStyle& s) {
    ImGui::SliderFloat2("WindowPadding", reinterpret_cast<float*>(&s.WindowPadding), 0.0f, 20.0f);
    Tip("Padding inside a window.");

    ImGui::SliderFloat2("FramePadding", reinterpret_cast<float*>(&s.FramePadding), 0.0f, 20.0f);
    Tip("Padding inside a framed rectangle (button, input, etc.).");

    ImGui::SliderFloat2("CellPadding", reinterpret_cast<float*>(&s.CellPadding), 0.0f, 20.0f);
    Tip("Padding within a table cell.");

    ImGui::SliderFloat2("ItemSpacing", reinterpret_cast<float*>(&s.ItemSpacing), 0.0f, 20.0f);
    Tip("Horizontal and vertical spacing between widgets.");

    ImGui::SliderFloat2("ItemInnerSpacing", reinterpret_cast<float*>(&s.ItemInnerSpacing), 0.0f, 20.0f);
    Tip("Spacing within a composed widget (label inside a slider, etc.).");

    ImGui::SliderFloat2("TouchExtraPadding", reinterpret_cast<float*>(&s.TouchExtraPadding), 0.0f, 10.0f);
    Tip("Expand reactive bounding box for touch-based systems.");

    ImGui::SliderFloat("IndentSpacing", &s.IndentSpacing, 0.0f, 30.0f);
    Tip("Horizontal indentation when entering a tree node.");

    ImGui::SliderFloat("ScrollbarSize", &s.ScrollbarSize, 1.0f, 20.0f);
    Tip("Width of the vertical scrollbar and height of the horizontal one.");

    ImGui::SliderFloat("GrabMinSize", &s.GrabMinSize, 1.0f, 20.0f);
    Tip("Minimum width/height of a grab box for sliders and scrollbars.");
}

static void RenderBordersSection(ImGuiStyle& s) {
    ImGui::SliderFloat("WindowBorderSize", &s.WindowBorderSize, 0.0f, 2.0f);
    Tip("Thickness of border around windows.");

    ImGui::SliderFloat("ChildBorderSize", &s.ChildBorderSize, 0.0f, 2.0f);
    Tip("Thickness of border around child windows.");

    ImGui::SliderFloat("PopupBorderSize", &s.PopupBorderSize, 0.0f, 2.0f);
    Tip("Thickness of border around popup and tooltip windows.");

    ImGui::SliderFloat("FrameBorderSize", &s.FrameBorderSize, 0.0f, 2.0f);
    Tip("Thickness of border around frames (inputs, buttons, etc.).");

    ImGui::SliderFloat("TabBorderSize", &s.TabBorderSize, 0.0f, 2.0f);
    Tip("Thickness of border around the top of tab items.");
}

static void RenderRoundingSection(ImGuiStyle& s) {
    ImGui::SliderFloat("WindowRounding", &s.WindowRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for regular windows.");

    ImGui::SliderFloat("ChildRounding", &s.ChildRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for child windows.");

    ImGui::SliderFloat("FrameRounding", &s.FrameRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for framed elements.");

    ImGui::SliderFloat("PopupRounding", &s.PopupRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for popup windows.");

    ImGui::SliderFloat("ScrollbarRounding", &s.ScrollbarRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for the scrollbar grab.");

    ImGui::SliderFloat("GrabRounding", &s.GrabRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding for the slider/scrollbar grab box.");

    ImGui::SliderFloat("TabRounding", &s.TabRounding, 0.0f, 12.0f);
    Tip("Radius of corner rounding on the top of tab items.");
}

static void RenderAlignmentSection(ImGuiStyle& s) {
    ImGui::SliderFloat2("WindowTitleAlign", reinterpret_cast<float *>(&s.WindowTitleAlign), 0.0f, 1.0f, "%.2f");
    Tip("Alignment for title bar text. (0,0.5) = left-center.");
    ImGui::SliderFloat2("ButtonTextAlign", reinterpret_cast<float *>(&s.ButtonTextAlign), 0.0f, 1.0f, "%.2f");
    Tip("Alignment of button text when the button is larger than the text.");
    ImGui::SliderFloat2("SelectableTextAlign", reinterpret_cast<float *>(&s.SelectableTextAlign), 0.0f, 1.0f, "%.2f");
    Tip("Alignment of selectable text — usually (0,0.5).");

    // WindowMenuButtonPosition: None / Left / Right
    static const char* dirNames[] = {"None", "Left", "Right"};
    int dirIdx = (s.WindowMenuButtonPosition == ImGuiDir_None) ? 0 :
                 (s.WindowMenuButtonPosition == ImGuiDir_Left) ? 1 : 2;
    if (ImGui::Combo("WindowMenuButtonPosition", &dirIdx, dirNames, 3)) {
        s.WindowMenuButtonPosition = (dirIdx == 0) ? ImGuiDir_None :
                                     (dirIdx == 1) ? ImGuiDir_Left : ImGuiDir_Right;
    }
    Tip("Which side of the title bar the collapse/close button appears on.");
}

static void RenderRenderingSection(ImGuiStyle& s) {
    ImGui::SliderFloat("Alpha", &s.Alpha, 0.2f, 1.0f, "%.2f");
    Tip("Global alpha applied to everything rendered by Dear ImGui.");

    ImGui::SliderFloat("DisabledAlpha", &s.DisabledAlpha, 0.0f, 1.0f, "%.2f");
    Tip("Additional alpha multiplier applied by BeginDisabled().");

    ImGui::Checkbox("AntiAliasedLines", &s.AntiAliasedLines);
    Tip("Enable anti-aliased lines and borders.");

    ImGui::Checkbox("AntiAliasedLinesUseTex", &s.AntiAliasedLinesUseTex);
    Tip("Use textures for anti-aliased lines where possible (faster).");

    ImGui::Checkbox("AntiAliasedFill", &s.AntiAliasedFill);
    Tip("Enable anti-aliasing on filled shapes (circles, etc.).");
}

static void RenderColorsSection(ImGuiStyle& s) {
    s_colorFilter.Draw("Filter##colors", -1.0f);
    ImGui::BeginChild("##colorlist", {0.0f, 320.0f}, ImGuiChildFlags_Borders);

    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        const char* name = ImGui::GetStyleColorName(i);
        if (!s_colorFilter.PassFilter(name)) continue;
        ImGui::PushID(i);
        ImGui::ColorEdit4(
            "##col",
            reinterpret_cast<float*>(&s.Colors[i]),
            ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel
        );
        ImGui::SameLine();
        ImGui::TextUnformatted(name);
        ImGui::PopID();
    }

    ImGui::EndChild();
}

static void RenderExportSection(ImGuiStyle& themeStyle) {
    bool changed = false;
    changed |= ImGui::InputText("Function Name", s_funcNameBuf, sizeof(s_funcNameBuf));
    Tip("Name of the generated C++ function.");
    changed |= ImGui::InputText("Namespace", s_nsBuf, sizeof(s_nsBuf));
    Tip("Optional C++ namespace. Leave blank for none.");
    changed |= ImGui::Checkbox("Include Comments",   &s_exportOpts.includeComments);
    Tip("Emit section comments in the generated code.");
    changed |= ImGui::Checkbox("Only Changed Values", &s_exportOpts.onlyChanged);
    Tip("Only emit values that differ from the StyleColorsDark baseline.");
    changed |= ImGui::SliderInt("Float Precision", &s_exportOpts.floatPrecision, 1, 4);
    Tip("Number of decimal places for float literals (e.g. 2 → 0.50f).");

    // Regenerate code every frame when the export section is open — the
    // function is pure string-building with no I/O so it's fast enough.
    s_exportOpts.functionName  = s_funcNameBuf;
    s_exportOpts.namespaceName = s_nsBuf;
    s_exportCode = GenerateThemeCode(themeStyle, s_exportOpts);
    (void)changed;

    ImGui::InputTextMultiline(
        "##codeprev",
        const_cast<char*>(s_exportCode.c_str()),
        s_exportCode.size() + 1,
        {-1.0f, 200.0f},
        ImGuiInputTextFlags_ReadOnly
    );

    if (ImGui::Button("Copy to Clipboard")) ImGui::SetClipboardText(s_exportCode.c_str());

    ImGui::SameLine();

    if (ImGui::Button("Save to File...")) {
        nfdchar_t* outPath = nullptr;
        nfdresult_t result = NFD_SaveDialog("cpp", nullptr, &outPath);
        if (result == NFD_OKAY && outPath) {
            FILE* f = fopen(outPath, "w");
            if (f) {
                fwrite(s_exportCode.c_str(), 1, s_exportCode.size(), f);
                fclose(f);
            }
            free(outPath);
        }
    }
}

void RenderEditorPanel(ImGuiStyle& themeStyle) {
    if (!ImGui::Begin("Editor")) {
        ImGui::End();
        return;
    }

    if (ImGui::CollapsingHeader("Main")) RenderMainSection(themeStyle);
    if (ImGui::CollapsingHeader("Borders")) RenderBordersSection(themeStyle);
    if (ImGui::CollapsingHeader("Rounding")) RenderRoundingSection(themeStyle);
    if (ImGui::CollapsingHeader("Alignment")) RenderAlignmentSection(themeStyle);
    if (ImGui::CollapsingHeader("Rendering")) RenderRenderingSection(themeStyle);
    if (ImGui::CollapsingHeader("Colors")) RenderColorsSection(themeStyle);
    if (ImGui::CollapsingHeader("Export")) RenderExportSection(themeStyle);

    ImGui::End();
}
