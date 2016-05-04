#include <QDesktopWidget>
#include <QApplication>
#include <QtPlugin>
#include <QRect>

#include "UserSetting.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    QRect rect = UserSetting::mainWindowRect();
    mainWindow.move(rect.x(), rect.y());
    mainWindow.resize(rect.width(), rect.height());

    mainWindow.show();

    return app.exec();
}
