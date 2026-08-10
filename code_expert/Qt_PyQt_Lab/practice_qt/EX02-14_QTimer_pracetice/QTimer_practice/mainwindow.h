#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void onTick();
    void on_btnCase1_clicked();
    void on_btnCase2_clicked();

private:
    Ui::MainWindow *ui;
    QTimer timer;
    int t = 0, redMs= 500, greenMs=1000;
    void reset(int r, int g);
};
#endif // MAINWINDOW_H
