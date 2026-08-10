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


void MainWindow::on_btnGetOpenFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this, "Open File", "/home/willtek", "all (*.*);; text (*.txt)");
    if(filename.isNull()) return;
    QString s = QFileInfo(filename).fileName();
    ui->lblOpenFileName->setText(filename);

    QString dir = QFileDialog::getExistingDirectory(this, "캡션", "/home/wiltek");
    // qDebug() << dir;

}


void MainWindow::on_btnGetSaveFile_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
                this, "Save File", "/home/willtek", "all (*.*);; text (*.txt)");
    if(filename.isNull()) return;
    ui->lblSaveFileName->setText(filename);
}

