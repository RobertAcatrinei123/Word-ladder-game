#include "ui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UI ui;
    ui.start();

    return app.exec();
}
