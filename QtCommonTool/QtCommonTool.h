#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtCommonTool.h"

class QtCommonTool : public QMainWindow
{
    Q_OBJECT

public:
    QtCommonTool(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtCommonToolClass ui;
};
