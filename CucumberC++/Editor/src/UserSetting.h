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
