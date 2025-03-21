#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab14_oop.h"

class lab14_oop : public QMainWindow
{
    Q_OBJECT

public:
    lab14_oop(QWidget *parent = nullptr);
    ~lab14_oop();

private:
    Ui::lab14_oopClass ui;
};
