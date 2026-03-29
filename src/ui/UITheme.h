#ifndef UITHEME_H
#define UITHEME_H

#include <QString>

namespace ui {
namespace theme {

// Light mode with solid ice-white surfaces
namespace light {
constexpr const char* BG_PRIMARY = "#f8fbfd";         // Ice white
constexpr const char* BG_SECONDARY = "#f3f7fa";       // Toolbar surface
constexpr const char* BG_TERTIARY = "#edf2f6";        // Soft raised surface
constexpr const char* TEXT_PRIMARY = "#1f2933";       // Deep neutral
constexpr const char* TEXT_SECONDARY = "#6b7683";     // Secondary neutral
constexpr const char* BORDER_COLOR = "#d9e3ea";       // Soft divider
constexpr const char* ACCENT_COLOR = "#2f6fdd";       // Refined blue
constexpr const char* ACCENT_HOVER = "#255fc0";       // Deeper blue
constexpr const char* TOOLBAR_BG = "#f7fafc";         // Main toolbar
constexpr const char* HOVER_BG = "#eef4f8";           // Hover fill
constexpr const char* TAB_ACTIVE_BG = "#ffffff";      // Active tab
constexpr const char* TAB_INACTIVE_BG = "#f1f5f8";    // Inactive tab
}

// Google Chrome Dark Mode (Official colors)
namespace dark {
constexpr const char* BG_PRIMARY = "#121212";         // Chrome dark background
constexpr const char* BG_SECONDARY = "#202124";       // Chrome dark toolbar
constexpr const char* BG_TERTIARY = "#292a2d";        // Chrome dark tab inactive
constexpr const char* TEXT_PRIMARY = "#e8eaed";       // Chrome dark text
constexpr const char* TEXT_SECONDARY = "#9aa0a6";     // Chrome dark hint
constexpr const char* BORDER_COLOR = "#3c4043";       // Chrome dark separator
constexpr const char* ACCENT_COLOR = "#8ab4f8";       // Google Material Blue Light
constexpr const char* ACCENT_HOVER = "#aecbfa";       // Google Material Blue Lighter
constexpr const char* TOOLBAR_BG = "#202124";         // Chrome dark toolbar
constexpr const char* HOVER_BG = "#292a2d";           // Chrome dark hover
constexpr const char* TAB_ACTIVE_BG = "#202124";      // Chrome dark active tab
constexpr const char* TAB_INACTIVE_BG = "#292a2d";    // Chrome dark inactive tab
}

// Modern Sizing & Spacing (Chrome-style compact spacing)
namespace spacing {
constexpr int TOOLBAR_HEIGHT = 46;      // Compact toolbar height
constexpr int TAB_HEIGHT = 30;          // Compact tab height
constexpr int PADDING_XS = 4;
constexpr int PADDING_SM = 6;
constexpr int PADDING_MD = 10;
constexpr int PADDING_LG = 14;
constexpr int PADDING_XL = 20;
constexpr int ICON_SIZE = 18;           // Compact icon size
constexpr int BUTTON_SIZE = 28;         // Compact toolbar button size
}

// Modern Border Radius
namespace radius {
constexpr int NONE = 0;
constexpr int SM = 6;
constexpr int MD = 8;
constexpr int LG = 12;
constexpr int PILL = 24;
}

// Modern Typography
namespace typography {
constexpr int FONT_SIZE_BODY = 12;          // Body text
constexpr int FONT_SIZE_SMALL = 11;         // Small text
constexpr int FONT_SIZE_LARGE = 14;         // Large text
constexpr int FONT_WEIGHT_NORMAL = 400;
constexpr int FONT_WEIGHT_MEDIUM = 500;
constexpr int FONT_WEIGHT_SEMIBOLD = 600;
}

}
}

#endif // UITHEME_H
