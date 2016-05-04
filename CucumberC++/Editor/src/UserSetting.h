#ifndef USERSETTING_H
#define USERSETTING_H

#include <QRect>
#include <QString>
#include <QSettings>
#include <QFont>

class UserSetting
{
public:
    UserSetting() = default;

    static QRect mainWindowRect();
    static void mainWindowRect(QRect rect);

    static QString lastUsedFile();
    static QString lastDir();
    static void setLastUsedFile(QString file);

    static QStringList recentFiles();
    static void recentFiles(QStringList files);

    static bool supportUnicode();
    static void supportUnicode(bool flag);

    static QFont font();
    static void font(QFont font);

private:
    static const QString organization;
    static const QString application;
    static QSettings s_Settings;
};

#endif // USERSETTING_H
