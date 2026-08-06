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


void MainWindow::on_helloBtn_clicked()
{
    ui -> chMessage -> setText("Hello");
}



void MainWindow::on_worldBtn_clicked()
{
    ui -> chMessage -> setText("World");
}

