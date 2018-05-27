#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



   w.initializeWidgets();
    //QString fileName = QFileDialog::getOpenFileName(nullptr, "Open", "");

    w.show();

    return a.exec();
}
