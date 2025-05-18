#include "ui.h"

void UI::start()
{
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
        service.initGraph("dictionary4.txt");
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

    QWidget *centralWidget = new QWidget(window);
    window->setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch(1);

    auto words = service.getWords();
    QStringList wordList;
    for (const auto &word : words)
    {
        wordList.append(QString::fromStdString(word));
    }

    QLabel *label = new QLabel("Start:", centralWidget);
    layout->addWidget(label, 0, Qt::AlignCenter);
    QComboBox *startComboBox = new QComboBox(centralWidget);
    startComboBox->addItems(wordList);
    layout->addWidget(startComboBox, 0, Qt::AlignCenter);

    label = new QLabel("End:", centralWidget);
    layout->addWidget(label, 0, Qt::AlignCenter);
    QComboBox *endComboBox = new QComboBox(centralWidget);
    endComboBox->addItems(wordList);
    layout->addWidget(endComboBox, 0, Qt::AlignCenter);

    QPushButton *playButton = new QPushButton("Start", centralWidget);
    QObject::connect(playButton, &QPushButton::clicked, [window, this, startComboBox, endComboBox]()
                     {
        std::string startWord = startComboBox->currentText().toStdString();
        std::string endWord = endComboBox->currentText().toStdString();

        auto newWindow = autoLadderWindow(startWord,endWord, window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(playButton, 0, Qt::AlignCenter);

    QPushButton *backButton = new QPushButton("Back", centralWidget);
    QObject::connect(backButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = menuWindow(window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(backButton, 0, Qt::AlignCenter);

    layout->addStretch(1);

    return window;
}

QMainWindow *UI::autoLadderWindow(std::string start, std::string end, QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Automatic Ladder");
    window->setGeometry(geometry);

    QWidget *centralWidget = new QWidget(window);
    window->setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch(1);

    auto ladder = service.getShortestPath(start, end);

    QWidget *ladderWidget = WordLadderWidget(ladder, centralWidget);
    layout->addWidget(ladderWidget, 0, Qt::AlignCenter);
    QPushButton *backButton = new QPushButton("Back", centralWidget);
    QObject::connect(backButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = autoWindow(window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(backButton, 0, Qt::AlignCenter);

    layout->addStretch(1);

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

QWidget *UI::WordLadderWidget(std::vector<std::string> words, QWidget *parent)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    std::reverse(words.begin(), words.end());
    for (const auto &word : words)
    {
        QLabel *label = new QLabel(QString::fromStdString(word), widget);
        layout->addWidget(label, 0, Qt::AlignCenter);
    }

    return widget;
}