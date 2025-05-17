#include "ui.h"

void UI::initGraph(const std::string &filename)
{
    service.initGraph(filename);
}

void UI::start()
{
    initGraph("dictionary.txt");
    menuWindow()->show();
}

QMainWindow *UI::menuWindow(QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Word Ladder");
    window->setGeometry(geometry);

    QWidget *centralWidget = new QWidget(window);
    window->setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addStretch(1);

    QLabel *label = new QLabel("Welcome to Word Ladder!", centralWidget);
    layout->addWidget(label, 0, Qt::AlignCenter);

    QPushButton *automaticButton = new QPushButton("Automatic mode", centralWidget);
    QObject::connect(automaticButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = autoWindow(window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(automaticButton, 0, Qt::AlignCenter);

    QPushButton *playButton = new QPushButton("Play mode", centralWidget);
    QObject::connect(playButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = playWindow(window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(playButton, 0, Qt::AlignCenter);

    QPushButton *analyticsButton = new QPushButton("Analytics", centralWidget);
    QObject::connect(analyticsButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = analyticsWindow(window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(analyticsButton, 0, Qt::AlignCenter);

    layout->addStretch(1);

    return window;
}

QMainWindow *UI::autoWindow(QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Automatic Mode");
    window->setGeometry(geometry);

    return window;
}

QMainWindow *UI::playWindow(QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Play Mode");
    window->setGeometry(geometry);

    return window;
}

QMainWindow *UI::analyticsWindow(QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Analytics");
    window->setGeometry(geometry);

    return window;
}