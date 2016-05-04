#include "string"
#include "UserSetting.h"

using namespace std;

const QString UserSetting::organization{"Quan"};
const QString UserSetting::application{"Cucumber/C++"};

QSettings UserSetting::s_Settings(organization, application);

QRect UserSetting::mainWindowRect()
{
    return s_Settings.value("mainwindow/rect", QRect(200, 200,860, 640)).toRect();
}

void UserSetting::mainWindowRect(QRect rect)
{
    s_Settings.setValue("mainwindow/rect", rect);
}

QString UserSetting::lastUsedFile()
{
    return s_Settings.value("file/lastUsedFile", "").toString();
}

QStringList UserSetting::recentFiles()
{
    return s_Settings.value("file/recentFiles", "").toStringList();
}

void UserSetting::recentFiles(QStringList files)
{
    s_Settings.setValue("file/recentFiles", files);
}

QString UserSetting::lastDir()
{
    wstring dir = lastUsedFile().toStdWString();
    size_t last = dir.find_last_of(L'/');
    if (last != wstring::npos)
    {
        dir.erase(last, dir.length() - last);
        return QString::fromStdWString(dir);
    }
    else
    {
        return QString();
    }
}

void UserSetting::setLastUsedFile(QString file)
{
    s_Settings.setValue("file/lastUsedFile", file);
}

bool UserSetting::supportUnicode()
{
    return s_Settings.value("compile/supportUnicode", false).toBool();
}


void UserSetting::supportUnicode(bool flag)
{
    s_Settings.setValue("compile/supportUnicode", flag);
}

QFont UserSetting::font()
{
    return s_Settings.value("edit/font", QFont("Courier", 10)).value<QFont>();
}

void UserSetting::font(QFont font)
{
    s_Settings.setValue("edit/font", font);
}
