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

    QWidget *centralWidget = new QWidget(window);
    window->setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch(1);

    QLabel *label = new QLabel("Name:", centralWidget);
    layout->addWidget(label, 0, Qt::AlignCenter);

    QLineEdit *nameEdit = new QLineEdit(centralWidget);
    layout->addWidget(nameEdit, 0, Qt::AlignCenter);

    QLabel *label2 = new QLabel("Number of letters:", centralWidget);
    layout->addWidget(label2, 0, Qt::AlignCenter);

    QComboBox *letterCountComboBox = new QComboBox(centralWidget);
    letterCountComboBox->addItems(letterCountList);
    layout->addWidget(letterCountComboBox, 0, Qt::AlignCenter);

    QPushButton *playButton = new QPushButton("Start", centralWidget);
    QObject::connect(playButton, &QPushButton::clicked, [window, this, nameEdit, letterCountComboBox]()
                     {
        if (nameEdit->text().isEmpty())
        {
            QMessageBox::warning(window, "Warning", "Please enter a name.");
            return;
        }
        std::string name = nameEdit->text().toStdString();
        int letterCount = letterCountComboBox->currentText().toInt();

        service.initGraph("dictionary" + std::to_string(letterCount) + ".txt");

        auto words = service.getStartEndWords();
        std::string startWord = words.first;
        std::string endWord = words.second;

        std::vector<std::string> ladder;
        ladder.push_back(startWord);
        ladder.push_back("?");
        ladder.push_back(endWord);

        auto newWindow = playingWindow(name, ladder,false, window->geometry());

        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
    layout->addWidget(playButton, 0, Qt::AlignCenter);

    layout->addStretch(1);

    return window;
}

QMainWindow *UI::playingWindow(const std::string &name, std::vector<std::string> ladder, bool hint, QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Playing");
    window->setGeometry(geometry);

    QWidget *centralWidget = new QWidget(window);
    window->setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addStretch(1);

    QWidget *ladderWidget = WordLadderWidget(ladder, centralWidget, hint);
    layout->addWidget(ladderWidget, 0, Qt::AlignCenter);

    layout->addStretch(1);

    QLabel *label = new QLabel("Enter next word", centralWidget);
    layout->addWidget(label, 0, Qt::AlignCenter);

    QLineEdit *wordEdit = new QLineEdit(centralWidget);
    layout->addWidget(wordEdit, 0, Qt::AlignCenter);

    QPushButton *submitButton = new QPushButton("Submit", centralWidget);
    QObject::connect(submitButton, &QPushButton::clicked, [window, this, name, ladderWidget, wordEdit]() {});
    layout->addWidget(submitButton, 0, Qt::AlignCenter);

    if (!hint)
    {
        QPushButton *hintButton = new QPushButton("Hint", centralWidget);
        QObject::connect(hintButton, &QPushButton::clicked, [window, this, ladderWidget, name, ladder]()
                         {
        auto newWindow = playingWindow(name, ladder, true, window->geometry());
        if (window->isFullScreen()) {
            newWindow->showFullScreen();
        } else {
            newWindow->show();
        }
        window->close(); });
        layout->addWidget(hintButton, 0, Qt::AlignCenter);
    }

    QPushButton *backButton = new QPushButton("Back", centralWidget);
    QObject::connect(backButton, &QPushButton::clicked, [window, this]()
                     {
        QMainWindow *newWindow = playWindow(window->geometry());
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

QMainWindow *UI::analyticsWindow(QRect geometry)
{
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Analytics module");
    window->setGeometry(geometry);

    return window;
}

QWidget *UI::WordLadderWidget(std::vector<std::string> words, QWidget *parent, bool hint)
{
    QWidget *widget = new QWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    int n = words.size();
    int k;

    if (hint)
    {
        auto path = service.getShortestPath(words[n - 3], words[n - 1]);
        std::string w1 = path[0], w2 = path[1];

        for (int i = 0; i < w1.size(); i++)
        {
            if (w1[i] != w2[i])
            {
                k = i;
                break;
            }
        }
    }

    std::reverse(words.begin(), words.end());

    for (int i = 0; i < words.size(); i++)
    {
        if ((i == 2) && hint)
        {
            auto richText = QString("%1<font color='red'>%2</font>%3").arg(QString::fromStdString(words[i].substr(0, k))).arg(words[i][k]).arg(QString::fromStdString(words[i].substr(k + 1)));
            QLabel *label = new QLabel(richText, widget);
            layout->addWidget(label, 0, Qt::AlignCenter);
        }
        else
        {
            QLabel *label = new QLabel(QString::fromStdString(words[i]), widget);
            layout->addWidget(label, 0, Qt::AlignCenter);
        }
    }

    return widget;
}