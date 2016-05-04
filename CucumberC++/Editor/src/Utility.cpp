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
