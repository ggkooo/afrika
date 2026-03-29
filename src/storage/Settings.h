#ifndef SETTINGS_H
#define SETTINGS_H

#include <QUrl>

QUrl loadHomepageOrDefault();
void saveSettingsHomepage(const QUrl &home);
void applyDarkMode(bool enable);

extern bool darkMode;

// Expose session path for session persistence
QString sessionPath();

#endif // SETTINGS_H
