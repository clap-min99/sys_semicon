#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include "camerathread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void handle_data(const QImage &image);

    void on_btnTakeAPicture_clicked();

private:
    Ui::MainWindow *ui;
    CameraThread *camera_thread;
    QImage m_last_frame;
    int m_photo_count = 0;
};
#endif // MAINWINDOW_H