#include "UIStyleSheet.h"
#include "UITheme.h"

namespace ui {

using namespace theme;

QString StyleSheet::toolbarStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QToolBar {"
            "  background-color: %1;"
            "  border: none;"
            "  border-bottom: 1px solid %2;"
            "  spacing: %3px;"
            "  padding: %4px %5px;"
            "  min-height: %6px;"
            "}"
            "QToolButton {"
            "  color: %7;"
            "  background-color: transparent;"
            "  border: none;"
            "  padding: %8px;"
            "  border-radius: %9px;"
            "  font-size: %10pt;"
            "  min-width: %11px;"
            "  min-height: %11px;"
            "}"
            "QToolButton:hover {"
            "  background-color: %12;"
            "}"
            "QToolButton:pressed { background-color: %13; }"
            "QToolButton::menu-indicator {"
            "  image: none;"
            "  width: 0px;"
            "}"
            "QToolBar::separator { width: 0px; }"
        ).arg(dark::TOOLBAR_BG,
              dark::BORDER_COLOR,
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_MD),
              QString::number(spacing::TOOLBAR_HEIGHT),
              dark::TEXT_PRIMARY,
              QString::number(spacing::PADDING_XS),
              QString::number(radius::SM),
              QString::number(typography::FONT_SIZE_BODY),
              QString::number(spacing::BUTTON_SIZE),
              dark::HOVER_BG,
              dark::BG_TERTIARY);
    }

    return QString(
        "QToolBar {"
        "  background-color: %1;"
        "  border: none;"
        "  border-bottom: 1px solid %2;"
        "  spacing: %3px;"
        "  padding: %4px %5px;"
        "  min-height: %6px;"
        "}"
        "QToolButton {"
        "  color: %7;"
        "  background-color: transparent;"
        "  border: 1px solid transparent;"
        "  padding: %8px;"
        "  border-radius: %9px;"
        "  font-size: %10pt;"
        "  min-width: %11px;"
        "  min-height: %11px;"
        "}"
        "QToolButton:hover {"
        "  background-color: %12;"
        "  border-color: %2;"
        "}"
        "QToolButton:pressed { background-color: %13; border-color: %2; }"
        "QToolButton::menu-indicator {"
        "  image: none;"
        "  width: 0px;"
        "}"
        "QToolBar::separator { width: 0px; }"
    ).arg(light::TOOLBAR_BG,
          light::BORDER_COLOR,
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_MD),
          QString::number(spacing::TOOLBAR_HEIGHT),
          light::TEXT_PRIMARY,
          QString::number(spacing::PADDING_XS),
          QString::number(radius::SM),
          QString::number(typography::FONT_SIZE_BODY),
          QString::number(spacing::BUTTON_SIZE),
          light::HOVER_BG,
          light::BG_TERTIARY);
}

QString StyleSheet::urlbarStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QLineEdit {"
            "  background-color: %1;"
            "  color: %2;"
            "  border: 1px solid %3;"
            "  border-radius: %4px;"
            "  padding: %5px %6px;"
            "  font-size: %7pt;"
            "  selection-background-color: %8;"
            "}"
            "QLineEdit:focus {"
            "  border: 2px solid %8;"
            "  padding: %5px %9px;"
            "  background-color: %1;"
            "}"
        ).arg(dark::BG_TERTIARY,
              dark::TEXT_PRIMARY,
              dark::BORDER_COLOR,
              QString::number(radius::MD),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_MD),
              QString::number(typography::FONT_SIZE_BODY),
              dark::ACCENT_COLOR,
              QString::number(spacing::PADDING_MD - 1));
    }

    return QString(
        "QLineEdit {"
        "  background-color: %1;"
        "  color: %2;"
        "  border: 1px solid %3;"
        "  border-radius: %4px;"
        "  padding: %5px %6px;"
        "  font-size: %7pt;"
        "  selection-background-color: %8;"
        "}"
        "QLineEdit:focus {"
        "  border: 2px solid %8;"
        "  padding: %5px %9px;"
        "  background-color: %10;"
        "}"
    ).arg("#ffffff",
          light::TEXT_PRIMARY,
          light::BORDER_COLOR,
          QString::number(radius::MD),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_MD),
          QString::number(typography::FONT_SIZE_BODY),
          light::ACCENT_COLOR,
          QString::number(spacing::PADDING_MD - 1),
          light::BG_PRIMARY);
}

}
