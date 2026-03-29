#ifndef UISTYLESHEET_H
#define UISTYLESHEET_H

#include <QString>

namespace ui {

class StyleSheet {
public:
    static QString toolbarStyle(bool darkMode);
    static QString urlbarStyle(bool darkMode);
    static QString tabbarStyle(bool darkMode);
    static QString tabCloseButtonStyle(bool darkMode);
    static QString menuStyle(bool darkMode);
    static QString dialogStyle(bool darkMode);
    static QString mainWindowStyle(bool darkMode);
    static QString buttonStyle(bool darkMode);
};

}

#endif // UISTYLESHEET_H
