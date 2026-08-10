#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>

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


void MainWindow::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "/home/willtek/work/practice_qt/images",
        "JPEG (*.jpg *.jpeg);;PNG (*.png)"
        );

    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        ui->lblImage->setPixmap(pixmap.scaled(ui->lblImage->size(), Qt::KeepAspectRatio));
    }
}


void MainWindow::on_btnOpen_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open File",
        "/home/willtek/work/practice_qt/images",
        "JPEG (*.jpg *.jpeg);;PNG (*.png)"
        );

    if (!fileName.isEmpty()) {
        QPixmap pixmap(fileName);
        QLabel *label = new QLabel;
        label->setPixmap(pixmap);
        label->resize(pixmap.size());
        ui->scrollArea->setWidget(label);
        ui->scrollArea->setWidgetResizable(false);
    }
}

