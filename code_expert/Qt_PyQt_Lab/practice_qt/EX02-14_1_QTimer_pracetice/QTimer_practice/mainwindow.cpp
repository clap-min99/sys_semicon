#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tick = 0;
    mode = 1;
    rstatus = false;
    gstatus = false;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::time_tick);
    // connect(sender, &SenderClass::signalName, receiver, &ReceiverClass::slotName);
    connect(ui->btnCase1, &QPushButton::clicked, this, [=](){change_mode(1);});
    connect(ui->btnCase2, &QPushButton::clicked, this, [=](){change_mode(2);});
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_tick()
{
    tick++;
    if(tick % mode==0)
    {
        rstatus = !rstatus;
    }
    if(tick % (mode+1) == 0)
    {
        gstatus = !gstatus;
    }
    led_control(rstatus, gstatus);
}

void MainWindow::led_control(bool red, bool green)
{
    if (red==true) ui->lblRedLED -> setStyleSheet("background-color:red");
    else ui->lblRedLED ->setStyleSheet("background-color:black");

    if (green==true) ui->lblGreenLED -> setStyleSheet("background-color:green");
    else ui->lblGreenLED ->setStyleSheet("background-color:black");
}


void MainWindow::change_mode(int m)
{
    mode = m;
    tick = 0;
    rstatus = false;
    gstatus = false;
    led_control(rstatus, gstatus);
    timer->start(500);
}

// void MainWindow::on_btnCase1_clicked()
// {
//     mode = 1;
//     tick = 0;
//     rstatus = false;
//     gstatus = false;
//     led_control(rstatus, gstatus);
//     timer->start(500);
// }

// void MainWindow::on_btnCase2_clicked()
// {
//     mode = 2;
//     tick = 0;
//     rstatus = false;
//     gstatus = false;
//     led_control(rstatus, gstatus);
//     timer->start(500);
// }
