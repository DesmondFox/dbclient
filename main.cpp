#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("DBClient");
    a.setOrganizationName("Alexey R.");
    a.setApplicationVersion("0.0.1");
    a.setApplicationDisplayName("DBClient");

    MainWindow w;
    w.show();

    return a.exec();
}
