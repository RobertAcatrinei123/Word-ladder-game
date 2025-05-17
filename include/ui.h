#pragma once

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "service.h"

class UI
{
private:
    static constexpr QRect defaultGeometry{150, 150, 500, 500};
    Service service;
    void initGraph(const std::string &filename);
    QMainWindow *menuWindow(QRect geometry = defaultGeometry);
    QMainWindow *autoWindow(QRect geometry = defaultGeometry);
    QMainWindow *playWindow(QRect geometry = defaultGeometry);
    QMainWindow *analyticsWindow(QRect geometry = defaultGeometry);

public:
    void start();
};