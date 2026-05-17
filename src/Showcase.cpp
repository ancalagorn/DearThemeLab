//
// Created by ancalagorn on 08.05.2026.
//

#include "Showcase.h"

#include <cmath>
#include <cstdio>

#include <imgui.h>

// ── persistent state ─────────────────────────────────────────────────────────
static float  s_dragFloat    = 1.5f;
static int    s_dragInt      = 42;
static float  s_sliderFloat  = 0.5f;
static int    s_sliderInt    = 3;
static float  s_sliderFloat3[3] = {0.2f, 0.5f, 0.8f};
static char   s_inputBuf[128]   = "Hello, theme!";
static char   s_inputMulti[256] = "Line one\nLine two\nLine three";
static int    s_inputInt     = 7;
static float  s_inputFloat   = 3.14f;
static bool   s_checkbox     = true;
static bool   s_checkboxB    = false;
static int    s_radio        = 0;
static float  s_color3[3]    = {0.6f, 0.2f, 0.8f};
static float  s_color4[4]    = {0.2f, 0.6f, 0.4f, 0.9f};
static int    s_comboItem    = 1;
static int    s_listItem     = 0;
static bool   s_treeSelected[4] = {};
static int    s_selectedRow  = 1;
static float  s_progress     = 0.65f;
static bool   s_modalOpen    = false;

static const char* s_comboItems[] = {"Option Alpha", "Option Beta", "Option Gamma", "Option Delta"};
static const char* s_listItems[] = {"Item One", "Item Two", "Item Three", "Item Four", "Item Five"};

// ── helpers ───────────────────────────────────────────────────────────────────

// Renders a colored square swatch inline, then a label — useful to show a
// widget in its normal, hovered, and active states side by side.
static void ShowButtonStates() {
    ImGuiStyle& s = ImGui::GetStyle();

    // Draw three colored rects representing each button state colour
    constexpr ImVec2 sz(20.0f, 20.0f);
    ImDrawList* dl = ImGui::GetWindowDrawList();

    auto rect = [&](const ImGuiCol col, const char* label) {
        const ImVec2 p = ImGui::GetCursorScreenPos();
        dl->AddRectFilled(p, {p.x + sz.x, p.y + sz.y}, ImGui::ColorConvertFloat4ToU32(s.Colors[col]));
        ImGui::Dummy(sz);
        ImGui::SameLine();
        ImGui::TextUnformatted(label);
        ImGui::SameLine(0, 16.0f);
    };

    rect(ImGuiCol_Button,        "Normal");
    rect(ImGuiCol_ButtonHovered, "Hovered");
    rect(ImGuiCol_ButtonActive,  "Active");
    ImGui::NewLine();
}

// ── main showcase ─────────────────────────────────────────────────────────────
void RenderShowcase() {
    // ── Text & Labels ─────────────────────────────────────────────────────────
    ImGui::SeparatorText("Text & Labels");
    ImGui::Text("Normal text");
    ImGui::SameLine(200); ImGui::TextDisabled("Disabled text");
    ImGui::TextColored({0.4f, 0.8f, 0.4f, 1.0f}, "Colored text (green)");
    ImGui::BulletText("Bullet item one");
    ImGui::BulletText("Bullet item two");
    ImGui::LabelText("Label", "Value string");
    ImGui::TextWrapped("Wrapped text: this line is intentionally long so it wraps "
                       "around inside the panel to show how the theme handles it.");

    // ── Buttons ───────────────────────────────────────────────────────────────
    ImGui::SeparatorText("Buttons");
    ImGui::Button("Button");  ImGui::SameLine();
    ImGui::SmallButton("Small");  ImGui::SameLine();
    ImGui::ArrowButton("##arr_l", ImGuiDir_Left);  ImGui::SameLine();
    ImGui::ArrowButton("##arr_r", ImGuiDir_Right);
    ImGui::SameLine(0, 16.0f);
    ImGui::Button("Wide Button", {120.0f, 0.0f});

    // Disabled state
    ImGui::BeginDisabled();
    ImGui::Button("Disabled Button");  ImGui::SameLine();
    ImGui::SmallButton("Disabled Small");
    ImGui::EndDisabled();

    // State colour swatches (no hover simulation needed — swatches show colours)
    ShowButtonStates();

    // ── Checkboxes & Radio Buttons ────────────────────────────────────────────
    ImGui::SeparatorText("Checkboxes & Radio Buttons");
    ImGui::Checkbox("Checked",   &s_checkbox);  ImGui::SameLine(150);
    ImGui::Checkbox("Unchecked", &s_checkboxB);
    ImGui::BeginDisabled();
    bool tmp = true;
    ImGui::Checkbox("Disabled checked", &tmp);
    ImGui::EndDisabled();

    ImGui::RadioButton("Radio A", &s_radio, 0);  ImGui::SameLine();
    ImGui::RadioButton("Radio B", &s_radio, 1);  ImGui::SameLine();
    ImGui::RadioButton("Radio C", &s_radio, 2);

    // ── Drag Controls ─────────────────────────────────────────────────────────
    ImGui::SeparatorText("Drag Controls");
    ImGui::DragFloat("DragFloat",  &s_dragFloat, 0.01f, -10.0f, 10.0f, "%.2f");
    ImGui::DragInt  ("DragInt",    &s_dragInt,   0.25f, 0, 100);
    ImGui::DragFloat3("DragFloat3", s_sliderFloat3, 0.005f, 0.0f, 1.0f, "%.3f");

    // ── Slider Controls ───────────────────────────────────────────────────────
    ImGui::SeparatorText("Slider Controls");
    ImGui::SliderFloat("SliderFloat",  &s_sliderFloat, 0.0f, 1.0f, "%.2f");
    ImGui::SliderInt  ("SliderInt",    &s_sliderInt,   0, 10);
    ImGui::SliderFloat3("SliderFloat3", s_sliderFloat3, 0.0f, 1.0f, "%.2f");
    ImGui::BeginDisabled();
    float dis = 0.3f;
    ImGui::SliderFloat("Disabled Slider", &dis, 0.0f, 1.0f);
    ImGui::EndDisabled();

    // ── Input Fields ──────────────────────────────────────────────────────────
    ImGui::SeparatorText("Input Fields");
    ImGui::InputText("InputText", s_inputBuf, sizeof(s_inputBuf));
    ImGui::InputInt("InputInt", &s_inputInt);
    ImGui::InputFloat("InputFloat", &s_inputFloat, 0.1f, 1.0f, "%.2f");
    ImGui::InputTextMultiline("InputMultiline", s_inputMulti, sizeof(s_inputMulti), {-1.0f, 60.0f});
    ImGui::BeginDisabled();
    char disInput[32] = "Read-only";
    ImGui::InputText("Disabled Input", disInput, sizeof(disInput));
    ImGui::EndDisabled();

    // ── Color Pickers ─────────────────────────────────────────────────────────
    ImGui::SeparatorText("Color Pickers");
    ImGui::ColorEdit3("ColorEdit3", s_color3);
    ImGui::ColorEdit4(
        "ColorEdit4",
        s_color4,
        ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_PickerHueWheel
    );
    ImGui::ColorButton(
        "ColorButton##cb",
        {s_color4[0], s_color4[1], s_color4[2], s_color4[3]},
        ImGuiColorEditFlags_AlphaPreview
    );

    // ── Combo & List Box ──────────────────────────────────────────────────────
    ImGui::SeparatorText("Combo & List Box");
    ImGui::Combo("Combo", &s_comboItem, s_comboItems, 4);
    ImGui::ListBox("ListBox", &s_listItem, s_listItems, 5, 4);

    // ── Selectables & Trees ───────────────────────────────────────────────────
    ImGui::SeparatorText("Selectables & Trees");

    // Selectables
    for (int i = 0; i < 3; i++) {
        char lbl[32]; snprintf(lbl, sizeof(lbl), "Selectable %d", i + 1);
        if (ImGui::Selectable(lbl, s_treeSelected[i])) s_treeSelected[i] = !s_treeSelected[i];
    }

    // Tree
    if (ImGui::TreeNode("Tree Root")) {
        if (ImGui::TreeNode("Branch A")) {
            ImGui::BulletText("Leaf A1");
            ImGui::BulletText("Leaf A2");
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Branch B")) {
            ImGui::BulletText("Leaf B1");
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }

    if (ImGui::CollapsingHeader("Collapsing Header")) {
        ImGui::Text("Content revealed by collapsing header.");
        ImGui::Text("Another line of content here.");
        ImGui::SliderFloat("Inner Slider", &s_sliderFloat, 0.0f, 1.0f);
    }

    // ── Tables ────────────────────────────────────────────────────────────────
    ImGui::SeparatorText("Table");
    static const char* tbl_headers[] = {"Name", "Score", "Status"};
    static const char* tbl_data[][3] = {
        {"Alpha", "98", "Active"},
        {"Beta", "74", "Idle"},
        {"Gamma", "55", "Error"},
        {"Delta", "100", "Active"},
    };
    if (ImGui::BeginTable("##showcase_table", 3,
            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
            ImGuiTableFlags_Sortable | ImGuiTableFlags_Resizable
    )) {
        for (auto* h : tbl_headers) ImGui::TableSetupColumn(h);
        ImGui::TableHeadersRow();

        for (int r = 0; r < 4; r++) {
            ImGui::TableNextRow();
            if (r == s_selectedRow)
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImGuiCol_Header));

            ImGui::TableSetColumnIndex(0);
            if (ImGui::Selectable(tbl_data[r][0], r == s_selectedRow, ImGuiSelectableFlags_SpanAllColumns))
                s_selectedRow = r;

            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(tbl_data[r][1]);
            ImGui::TableSetColumnIndex(2);
            ImGui::TextUnformatted(tbl_data[r][2]);
        }
        ImGui::EndTable();
    }

    // ── Tab Bar ───────────────────────────────────────────────────────────────
    ImGui::SeparatorText("Tab Bar");
    if (ImGui::BeginTabBar("##showcase_tabs")) {
        if (ImGui::BeginTabItem("Tab One")) { ImGui::Text("Content of Tab One.");   ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Tab Two")) { ImGui::Text("Content of Tab Two.");   ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Tab Three")) { ImGui::Text("Content of Tab Three."); ImGui::EndTabItem(); }
        if (ImGui::BeginTabItem("Tab Four")) { ImGui::Text("Content of Tab Four.");  ImGui::EndTabItem(); }
        ImGui::EndTabBar();
    }

    // ── Menus ─────────────────────────────────────────────────────────────────
    // Use popup-based menus — they exercise the same theme colours as a real
    // menu bar (Header, PopupBg, MenuItem colours, separators, etc.).
    ImGui::SeparatorText("Menus");
    if (ImGui::Button("File##menu"))  ImGui::OpenPopup("##menu_file");
    ImGui::SameLine();
    if (ImGui::Button("Edit##menu"))  ImGui::OpenPopup("##menu_edit");
    ImGui::SameLine();
    if (ImGui::Button("View##menu"))  ImGui::OpenPopup("##menu_view");

    if (ImGui::BeginPopup("##menu_file")) {
        ImGui::MenuItem("New", "Ctrl+N");
        ImGui::MenuItem("Open", "Ctrl+O");
        ImGui::MenuItem("Save", "Ctrl+S");
        ImGui::Separator();
        ImGui::MenuItem("Exit");
        ImGui::EndPopup();
    }
    if (ImGui::BeginPopup("##menu_edit")) {
        ImGui::MenuItem("Undo", "Ctrl+Z");
        ImGui::MenuItem("Redo", "Ctrl+Y");
        ImGui::Separator();
        ImGui::MenuItem("Cut", "Ctrl+X");
        ImGui::MenuItem("Copy", "Ctrl+C");
        ImGui::MenuItem("Paste", "Ctrl+V");
        ImGui::EndPopup();
    }
    if (ImGui::BeginPopup("##menu_view")) {
        static bool s_showGrid = true;
        ImGui::MenuItem("Show Grid", nullptr, &s_showGrid);
        ImGui::MenuItem("Zoom In", "Ctrl++");
        ImGui::MenuItem("Zoom Out", "Ctrl+-");
        ImGui::EndPopup();
    }

    // ── Progress Bar & Plots ──────────────────────────────────────────────────
    ImGui::SeparatorText("Progress Bar & Plots");
    ImGui::ProgressBar(s_progress, {-1.0f, 0.0f});
    ImGui::SliderFloat("Progress##ctrl", &s_progress, 0.0f, 1.0f);

    // PlotLines: sine wave
    static float sineData[64];
    static bool  sineFilled = false;
    if (!sineFilled) {
        for (int i = 0; i < 64; i++) sineData[i] = std::sin(static_cast<float>(i) * 0.2f);
        sineFilled = true;
    }
    ImGui::PlotLines(
        "PlotLines",
        sineData,
        64,
        0,
        nullptr,
        -1.2f,
        1.2f,
        {-1.0f, 50.0f}
    );

    // PlotHistogram: ramp
    static float histData[16];
    static bool  histFilled = false;
    if (!histFilled) {
        for (int i = 0; i < 16; i++) histData[i] = static_cast<float>(i + 1) / 16.0f;
        histFilled = true;
    }
    ImGui::PlotHistogram(
        "PlotHistogram",
        histData,
        16,
        0,
        nullptr,
        0.0f,
        1.0f,
        {-1.0f, 50.0f}
    );

    // ── Tooltips ──────────────────────────────────────────────────────────────
    ImGui::SeparatorText("Tooltips");
    ImGui::Text("Hover for tooltip ->");
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::Text("This is a tooltip.");
        ImGui::Text("It can span multiple lines.");
        ImGui::EndTooltip();
    }

    // ── Popups & Modals ───────────────────────────────────────────────────────
    ImGui::SeparatorText("Popups & Modals");
    if (ImGui::Button("Open Popup")) ImGui::OpenPopup("##ctx_popup");
    ImGui::SameLine();
    if (ImGui::Button("Open Modal...")) { s_modalOpen = true; ImGui::OpenPopup("Info##modal"); }

    if (ImGui::BeginPopup("##ctx_popup")) {
        ImGui::MenuItem("Action One");
        ImGui::MenuItem("Action Two");
        ImGui::Separator();
        ImGui::MenuItem("Action Three");
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal("Info##modal", &s_modalOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("This is a modal dialog.\nTheme affects all controls inside.");
        ImGui::Separator();
        ImGui::SliderFloat("Modal Slider", &s_sliderFloat, 0.0f, 1.0f);
        ImGui::Spacing();
        if (ImGui::Button("OK", {120.0f, 0.0f})) { s_modalOpen = false; ImGui::CloseCurrentPopup(); }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", {120.0f, 0.0f})) { s_modalOpen = false; ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }

    // ── Child Windows ─────────────────────────────────────────────────────────
    ImGui::SeparatorText("Child Windows");
    ImGui::BeginChild("##scroll_child", {-1.0f, 80.0f}, ImGuiChildFlags_Borders);
    for (int i = 0; i < 20; i++)
        ImGui::Text("Scrollable line %d — check scrollbar and border styling", i + 1);
    ImGui::EndChild();

    // Nested child
    ImGui::BeginChild("##outer_child", {-1.0f, 80.0f}, ImGuiChildFlags_Borders);
    ImGui::Text("Outer child");
    ImGui::BeginChild("##inner_child", {-1.0f, 40.0f}, ImGuiChildFlags_Borders);
    ImGui::Text("Inner child (nested)");
    ImGui::EndChild();
    ImGui::EndChild();

    // ── Separator styles ──────────────────────────────────────────────────────
    ImGui::SeparatorText("Separators");
    ImGui::Text("Above a Separator():");
    ImGui::Separator();
    ImGui::Text("Below the separator.");
    ImGui::Spacing();
    ImGui::Spacing();
}
