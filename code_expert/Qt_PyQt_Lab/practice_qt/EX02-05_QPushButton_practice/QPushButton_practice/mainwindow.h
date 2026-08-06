#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_btnPush_clicked();

    void on_btnCheckable_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    int colorIndex = 0;
};
#endif // MAINWINDOW_H
