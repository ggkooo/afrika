#include "UIStyleSheet.h"
#include "UITheme.h"

namespace ui {

using namespace theme;

QString StyleSheet::menuStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QMenu, QMenuBar {"
            "  background-color: %1;"
            "  color: %2;"
            "  border: 1px solid %3;"
            "  border-radius: %4px;"
            "}"
            "QMenu::item, QMenuBar::item {"
            "  padding: %5px %6px;"
            "}"
            "QMenu::item:selected, QMenuBar::item:selected {"
            "  background-color: %7;"
            "  color: %8;"
            "  border-radius: %4px;"
            "  margin: %9px %10px;"
            "}"
            "QMenu::separator { background-color: %3; height: 1px; margin: %11px 0px; }"
        ).arg(dark::BG_SECONDARY,
              dark::TEXT_PRIMARY,
              dark::BORDER_COLOR,
              QString::number(radius::MD),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_LG),
              dark::BG_TERTIARY,
              dark::ACCENT_COLOR,
              QString::number(spacing::PADDING_XS),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_SM));
    }

    return QString(
        "QMenu, QMenuBar {"
        "  background-color: %1;"
        "  color: %2;"
        "  border: 1px solid %3;"
        "  border-radius: %4px;"
        "}"
        "QMenu::item, QMenuBar::item {"
        "  padding: %5px %6px;"
        "}"
        "QMenu::item:selected, QMenuBar::item:selected {"
        "  background-color: %7;"
        "  color: %8;"
        "  border-radius: %4px;"
        "  margin: %9px %10px;"
        "}"
        "QMenu::separator { background-color: %3; height: 1px; margin: %11px 0px; }"
    ).arg("#ffffff",
          light::TEXT_PRIMARY,
          light::BORDER_COLOR,
          QString::number(radius::MD),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_LG),
          light::HOVER_BG,
          light::TEXT_PRIMARY,
          QString::number(spacing::PADDING_XS),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_SM));
}

QString StyleSheet::dialogStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QDialog, QMessageBox {"
            "  background-color: %1;"
            "  color: %2;"
            "}"
            "QLabel { color: %2; font-size: %3pt; }"
            "QLineEdit, QTextEdit, QCheckBox {"
            "  color: %2;"
            "  background-color: %4;"
            "  border: 1px solid %5;"
            "  border-radius: %6px;"
            "  padding: %7px %8px;"
            "  font-size: %3pt;"
            "}"
            "QLineEdit:focus, QTextEdit:focus {"
            "  border: 2px solid %9;"
            "}"
            "QPushButton {"
            "  background-color: %9;"
            "  color: %10;"
            "  border: none;"
            "  border-radius: %6px;"
            "  padding: %11px %12px;"
            "  font-weight: %13;"
            "  font-size: %3pt;"
            "}"
            "QPushButton:hover { background-color: %14; }"
            "QPushButton:pressed { background-color: %15; }"
        ).arg(dark::BG_PRIMARY,
              dark::TEXT_PRIMARY,
              QString::number(typography::FONT_SIZE_BODY),
              dark::BG_SECONDARY,
              dark::BORDER_COLOR,
              QString::number(radius::MD),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_MD),
              dark::ACCENT_COLOR,
              light::BG_PRIMARY,
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_LG),
              QString::number(typography::FONT_WEIGHT_MEDIUM),
              dark::ACCENT_HOVER,
              dark::BG_TERTIARY);
    }

    return QString(
        "QDialog, QMessageBox {"
        "  background-color: %1;"
        "  color: %2;"
        "}"
        "QLabel { color: %2; font-size: %3pt; }"
        "QLineEdit, QTextEdit, QCheckBox {"
        "  color: %2;"
        "  background-color: %4;"
        "  border: 1px solid %5;"
        "  border-radius: %6px;"
        "  padding: %7px %8px;"
        "  font-size: %3pt;"
        "}"
        "QLineEdit:focus, QTextEdit:focus {"
        "  border: 2px solid %9;"
        "}"
        "QPushButton {"
        "  background-color: %9;"
        "  color: %10;"
        "  border: none;"
        "  border-radius: %6px;"
        "  padding: %11px %12px;"
        "  font-weight: %13;"
        "  font-size: %3pt;"
        "}"
        "QPushButton:hover { background-color: %14; }"
        "QPushButton:pressed { background-color: %15; }"
    ).arg(light::BG_PRIMARY,
          light::TEXT_PRIMARY,
          QString::number(typography::FONT_SIZE_BODY),
          light::BG_SECONDARY,
          light::BORDER_COLOR,
          QString::number(radius::MD),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_MD),
          light::ACCENT_COLOR,
          light::BG_PRIMARY,
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_LG),
          QString::number(typography::FONT_WEIGHT_MEDIUM),
          light::ACCENT_HOVER,
          light::BG_TERTIARY);
}

QString StyleSheet::buttonStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QPushButton {"
            "  background-color: %1;"
            "  color: %2;"
            "  border: none;"
            "  border-radius: %3px;"
            "  padding: %4px %5px;"
            "  font-size: %6pt;"
            "  font-weight: %7;"
            "  min-height: 32px;"
            "}"
            "QPushButton:hover { background-color: %8; }"
            "QPushButton:pressed { background-color: %9; }"
            "QPushButton:focus { outline: 2px solid %1; outline-offset: 2px; }"
        ).arg(dark::ACCENT_COLOR,
              light::BG_PRIMARY,
              QString::number(radius::MD),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_LG),
              QString::number(typography::FONT_SIZE_BODY),
              QString::number(typography::FONT_WEIGHT_MEDIUM),
              dark::ACCENT_HOVER,
              dark::BG_TERTIARY);
    }

    return QString(
        "QPushButton {"
        "  background-color: %1;"
        "  color: %2;"
        "  border: none;"
        "  border-radius: %3px;"
        "  padding: %4px %5px;"
        "  font-size: %6pt;"
        "  font-weight: %7;"
        "  min-height: 32px;"
        "}"
        "QPushButton:hover { background-color: %8; }"
        "QPushButton:pressed { background-color: %9; }"
        "QPushButton:focus { outline: 2px solid %1; outline-offset: 2px; }"
    ).arg(light::ACCENT_COLOR,
          light::BG_PRIMARY,
          QString::number(radius::MD),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_LG),
          QString::number(typography::FONT_SIZE_BODY),
          QString::number(typography::FONT_WEIGHT_MEDIUM),
          light::ACCENT_HOVER,
          light::BG_TERTIARY);
}

QString StyleSheet::mainWindowStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QMainWindow, QWidget { "
            "  background-color: %1; "
            "  color: %2; "
            "}"
            "QTabWidget::pane { "
            "  border: none; "
            "  background-color: %1; "
            "}"
            "QScrollBar:vertical { "
            "  background-color: %3; "
            "  width: 12px; "
            "  border: none; "
            "}"
            "QScrollBar::handle:vertical { "
            "  background-color: %4; "
            "  border-radius: 6px; "
            "  min-height: 20px; "
            "}"
            "QScrollBar::handle:vertical:hover { "
            "  background-color: %5; "
            "}"
        ).arg(dark::BG_PRIMARY,
              dark::TEXT_PRIMARY,
              dark::BG_SECONDARY,
              dark::BG_TERTIARY,
              dark::BORDER_COLOR);
    }

    return QString(
        "QMainWindow, QWidget { "
        "  background-color: %1; "
        "  color: %2; "
        "}"
        "QTabWidget::pane { "
        "  border: none; "
        "  background-color: %1; "
        "}"
        "QTabWidget { "
        "  background-color: %1; "
        "}"
        "QScrollBar:vertical { "
        "  background-color: %3; "
        "  width: 12px; "
        "  border: none; "
        "}"
        "QScrollBar::handle:vertical { "
        "  background-color: %4; "
        "  border-radius: 6px; "
        "  min-height: 20px; "
        "}"
        "QScrollBar::handle:vertical:hover { "
        "  background-color: %5; "
        "}"
    ).arg(light::BG_PRIMARY,
          light::TEXT_PRIMARY,
          light::BG_SECONDARY,
          light::BG_TERTIARY,
          light::BORDER_COLOR);
}

}
