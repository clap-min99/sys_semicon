#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "mythread.h"

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


    void on_btnStart_clicked();

    void on_btnStop_clicked();
    void handle_command(int cmd);


private:
    Ui::MainWindow *ui;
    MyThread *myThread;
};
#endif // MAINWINDOW_H
