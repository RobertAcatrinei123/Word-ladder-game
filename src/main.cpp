#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include "service.h"

int main(int argc, char *argv[])
{
    // QApplication app(argc, argv);

    // QMainWindow mainWindow;
    // mainWindow.setWindowTitle("My Qt App");
    // mainWindow.setGeometry(100, 100, 400, 300);

    // QLabel *label = new QLabel("Hello, Qt!", &mainWindow);
    // label->setAlignment(Qt::AlignCenter);
    // mainWindow.setCentralWidget(label);

    // mainWindow.show();

    // return app.exec();

    Service service;
    service.initGraph("dictionary.txt");
}
