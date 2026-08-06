#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->helloBtn, &QPushButton::clicked, this, &MainWindow::Print_Hello);
    connect(ui->worldBtn, &QPushButton::clicked, this, &MainWindow::Print_World);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Print_Hello(){
    ui->chMessage->setText("Hello");
}

void MainWindow::Print_World(){
    ui->chMessage->setText("World");
}


// void MainWindow::on_helloBtn_clicked()
// {
//     ui -> chMessage -> setText("Hello");
// }



// void MainWindow::on_worldBtn_clicked()
// {
//     ui -> chMessage -> setText("World");
// }

