#pragma once

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include "service.h"

class UI
{
private:
    static inline QStringList letterCountList{"4"};
    static constexpr QRect defaultGeometry{150, 150, 500, 500};
    Service service;
    QMainWindow *menuWindow(QRect geometry = defaultGeometry);
    QMainWindow *autoWindow(QRect geometry = defaultGeometry);
    QMainWindow *autoLadderWindow(std::string start, std::string end, QRect geometry = defaultGeometry);
    QMainWindow *playWindow(QRect geometry = defaultGeometry);
    QMainWindow *playingWindow(const std::string &name, std::vector<std::string> ladder, bool hint = false, QRect geometry = defaultGeometry);
    QMainWindow *analyticsWindow(QRect geometry = defaultGeometry);
    QWidget *WordLadderWidget(std::vector<std::string> words, QWidget *parent = (QWidget *)nullptr, bool hint = false);

public:
    void start();
};