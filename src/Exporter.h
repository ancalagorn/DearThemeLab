//
// Created by ancalagorn on 13.05.2026.
//

#pragma once

#include <string>

struct ImGuiStyle;

struct ExportOptions {
    std::string functionName = "ApplyTheme";
    std::string namespaceName;
    bool includeComments = true;
    bool onlyChanged = false;
    int floatPrecision = 2;
};

std::string GenerateThemeCode(const ImGuiStyle& style, const ExportOptions& opts);
