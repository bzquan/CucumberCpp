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

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "StrUtility.h"
#include "Utility.h"

bool Utility::fileExist(QString filePath)
{
    QFile file(filePath);
    return file.exists();
}

std::wstring Utility::getDirFromFilepathWS(const QString& path)
{
    return getDirFromFilepath(path).toStdWString();
}

QString Utility::getDirFromFilepath(const QString& path)
{
    QFileInfo file_info(path);
    QDir dir = file_info.absoluteDir();
    QString dirStr = dir.absolutePath();
    dirStr.append('/');

    QString nativeDir = QDir::toNativeSeparators(dirStr);
    return nativeDir;
}

QString Utility::fileMine2FilePath(QString path_mime)
{
    std::wstring path = path_mime.toStdWString();
    std::wstring prefix{ L"file:///" };
    if (StrUtility::startWith(path, prefix))
    {
        path.erase(0, prefix.length());
    }

    return QString::fromStdWString(path);
}
