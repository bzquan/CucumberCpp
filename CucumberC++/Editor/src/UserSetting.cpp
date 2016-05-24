/* The MIT License (MIT)
 * 
 * Copyright (c) 2016 Bingzhe Quan
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
    return s_Settings.value("compile/supportUnicode", true).toBool();
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
