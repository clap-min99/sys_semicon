#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::onTick);
    timer.start(500);
    reset(500, 1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset(int r, int g)
{
    redMs = r; greenMs = g; t = 0;
    ui->lblRedLED->setStyleSheet("background:black");
    ui->lblGreenLED->setStyleSheet("background:black");
}

void MainWindow::onTick()
{
    t += 500;
    if (t % redMs == 0)
        ui->lblRedLED->setStyleSheet(
            ui->lblRedLED->styleSheet() == "background:black"
                ? "background:red" : "background:black");
    if (t % greenMs == 0)
        ui->lblGreenLED->setStyleSheet(
            ui->lblGreenLED->styleSheet() == "background:black"
                ? "background:green" : "background:black");
}

void MainWindow::on_btnCase1_clicked() { reset(500, 1000); }
void MainWindow::on_btnCase2_clicked() { reset(1000, 1500); }