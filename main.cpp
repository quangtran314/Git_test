#include "mainwindow/mainwindow.h"

#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Resource);
    QCoreApplication::setOrganizationName("quangtran");
    QCoreApplication::setApplicationName(GAME_NAME);
    QCoreApplication::setApplicationVersion(GAME_VERSION);

    qsrand(QTime::currentTime().msec());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
