#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnExec_clicked()
{/*
    MyDialog *dlg = new MyDialog(this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);    // 메모리정리 방법 1
    int r = dlg->exec();
    qDebug() << "exec return" << r;*/
    // delete dlg;                             // 메모리정리 방법 2

    // stack에 로컬로 정의
    MyDialog dlg(this);
    int r = dlg.exec();
    if(r == MyDialog::Accepted)
    {
        qDebug() << "accept complete";
    }
    qDebug() << "exec return" << r;
}


void MainWindow::on_btnOpen_clicked()
{
    MyDialog *dlg = new MyDialog(this);
    dlg->open();
    qDebug() << "open return";
}


void MainWindow::on_btnShow_clicked()
{
    MyDialog *dlg = new MyDialog(this);
    dlg->show();
    qDebug() << "show return";

}

