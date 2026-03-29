#include "UIStyleSheet.h"
#include "UITheme.h"

namespace ui {

using namespace theme;

QString StyleSheet::tabbarStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QTabBar::tab {"
            "  background-color: %1;"
            "  color: %2;"
            "  padding: %3px %4px %3px %5px;"
            "  margin: 0px;"
            "  border: none;"
            "  font-size: %6pt;"
            "  font-weight: %7;"
            "  min-height: %8px;"
            "  margin-top: 4px;"
            "}"
            "QTabBar::tab:selected {"
            "  background-color: %9;"
            "  color: %10;"
            "  margin-top: 0px;"
            "}"
            "QTabBar::tab:!selected:hover {"
            "  background-color: %11;"
            "}"
            "QTabBar {"
            "  background-color: %12;"
            "  border-bottom: 1px solid %13;"
            "}"
        ).arg(dark::TAB_INACTIVE_BG,
              dark::TEXT_PRIMARY,
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_LG),
              QString::number(spacing::PADDING_MD),
              QString::number(typography::FONT_SIZE_BODY),
              QString::number(typography::FONT_WEIGHT_MEDIUM),
              QString::number(spacing::TAB_HEIGHT),
              dark::TAB_ACTIVE_BG,
              dark::TEXT_PRIMARY,
              dark::HOVER_BG,
              dark::BG_SECONDARY,
              dark::BORDER_COLOR);
    }

    return QString(
        "QTabWidget::tab-bar {"
        "  alignment: left;"
        "  background-color: %1;"
        "}"
        "QTabBar {"
        "  background-color: %1;"
        "  border-bottom: 1px solid %2;"
        "}"
        "QTabBar::scroller {"
        "  background-color: %1;"
        "  width: 22px;"
        "}"
        "QTabBar::tab {"
        "  background-color: %3;"
        "  color: %4;"
        "  padding: %5px %6px %5px %7px;"
        "  margin: 4px 4px 0px 0px;"
        "  border: 1px solid transparent;"
        "  border-top-left-radius: 8px;"
        "  border-top-right-radius: 8px;"
        "  font-size: %8pt;"
        "  font-weight: %9;"
        "  min-height: %10px;"
        "  min-width: 108px;"
        "  max-width: 190px;"
        "}"
        "QTabBar::tab:selected {"
        "  background-color: %11;"
        "  color: %12;"
        "  border-color: %2;"
        "  border-bottom-color: %11;"
        "}"
        "QTabBar::tab:!selected:hover {"
        "  background-color: %13;"
        "  color: %12;"
        "}"
        "QTabBar QToolButton {"
        "  background-color: %1;"
        "  border: none;"
        "  color: %12;"
        "  width: 22px;"
        "}"
        "QTabBar QToolButton:hover {"
        "  background-color: %13;"
        "  border-radius: 6px;"
        "}"
    ).arg(light::BG_PRIMARY,
          light::BORDER_COLOR,
          light::TAB_INACTIVE_BG,
          light::TEXT_SECONDARY,
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_LG),
          QString::number(spacing::PADDING_MD),
          QString::number(typography::FONT_SIZE_BODY),
          QString::number(typography::FONT_WEIGHT_MEDIUM),
          QString::number(spacing::TAB_HEIGHT),
          light::TAB_ACTIVE_BG,
          light::TEXT_PRIMARY,
          light::HOVER_BG);
}

QString StyleSheet::tabCloseButtonStyle(bool darkMode)
{
    if (darkMode) {
        return QString(
            "QPushButton {"
            "  border: none;"
            "  background-color: transparent;"
            "  padding: %1px %2px;"
            "  margin: 0px %3px 0px %4px;"
            "  font-size: %5pt;"
            "  font-weight: %6;"
            "  color: %7;"
            "  min-width: 20px;"
            "  min-height: 20px;"
            "}"
            "QPushButton:hover {"
            "  background-color: %8;"
            "  border-radius: %9px;"
            "  color: %10;"
            "}"
            "QPushButton:pressed { "
            "  background-color: %11;"
            "  color: %12;"
            "}"
        ).arg(QString::number(spacing::PADDING_XS),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_SM),
              QString::number(spacing::PADDING_SM),
              QString::number(typography::FONT_SIZE_BODY),
              QString::number(typography::FONT_WEIGHT_MEDIUM),
              dark::TEXT_SECONDARY,
              dark::BG_TERTIARY,
              QString::number(radius::SM),
              dark::TEXT_PRIMARY,
              dark::ACCENT_COLOR,
              light::BG_PRIMARY);
    }

    return QString(
        "QPushButton {"
        "  border: none;"
        "  background-color: transparent;"
        "  padding: %1px %2px;"
        "  margin: 0px %3px 0px %4px;"
        "  font-size: %5pt;"
        "  font-weight: %6;"
        "  color: %7;"
        "  min-width: 22px;"
        "  min-height: 22px;"
        "  border-radius: %9px;"
        "}"
        "QPushButton:hover {"
        "  background-color: %8;"
        "  color: %10;"
        "}"
        "QPushButton:pressed { "
        "  background-color: %11;"
        "  color: %12;"
        "}"
    ).arg(QString::number(spacing::PADDING_XS),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_SM),
          QString::number(spacing::PADDING_SM),
          QString::number(typography::FONT_SIZE_BODY),
          QString::number(typography::FONT_WEIGHT_MEDIUM),
          light::TEXT_SECONDARY,
          light::BG_TERTIARY,
          QString::number(radius::SM),
          light::TEXT_PRIMARY,
          light::ACCENT_COLOR,
          light::BG_PRIMARY);
}

}
