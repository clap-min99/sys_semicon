#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QAbstractButton>
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
    void on_btnEqual_clicked();
    void on_btnBackspace_clicked();
    void on_btnCancel_clicked();
    void Make_String(QAbstractButton *btn);
private:
    Ui::MainWindow *ui;
    QString expr = "";
};

#endif // MAINWINDOW_H
