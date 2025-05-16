#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("My Qt App");
    mainWindow.setGeometry(100, 100, 400, 300); // x, y, width, height

    QLabel *label = new QLabel("Hello, Qt!", &mainWindow);
    label->setAlignment(Qt::AlignCenter);
    mainWindow.setCentralWidget(label);

    mainWindow.show();

    return app.exec();
}
