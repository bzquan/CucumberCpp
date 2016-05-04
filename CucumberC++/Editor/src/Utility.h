#pragma once

#include <string>
#include <QString>

class Utility
{
public:
    Utility() = default;

    static bool fileExist(QString filePath);
    static std::wstring getDirFromFilepathWS (const QString& path);
    static QString getDirFromFilepath (const QString& path);
    static QString fileMine2FilePath(QString path_mime);
};
