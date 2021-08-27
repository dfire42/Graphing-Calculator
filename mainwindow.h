#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <vector>
#include "header/Interpreter.hpp"

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DrawButton_clicked();

    void on_EquationList_currentIndexChanged(const QString &arg1);

    void on_DeleteLine_clicked();   // deletes a lines

    void on_EnterEquation_returnPressed();  // adds a new line

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
