#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui -> lblColor -> setStyleSheet("background-color: red;");
    ui -> lblState -> setStyleSheet("background-color: green;");
    ui -> lblState -> setText("State");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnPush_clicked()
{
    // colorIndex = (1+colorIndex)%3;

    // switch(colorIndex)
    // {
    // case 0:
    //     ui -> lblColor->setStyleSheet("background-color: red;");
    //     break;
    // case 1:
    //     ui->lblColor->setStyleSheet("background-color: green;");
    //     break;
    // case 2:
    //     ui->lblColor->setStyleSheet("background-color: blue;");
    //     break;
    // }

    static int cnt = 0;
    QStringList color = {"green","blue","red"};
    // QString s = QString("background-color: %1").arg(color[cnt%3]);
    QString s = QString("background-color:") + color[cnt%3];
    ui -> lblColor -> setStyleSheet(s);
    cnt++;

}


void MainWindow::on_btnCheckable_clicked(bool checked)
{
    if (checked)
    {
        ui->btnCheckable->setText("ON");
        ui->lblState->setStyleSheet("background-color: red;");
    }
    else
    {
        ui->btnCheckable->setText("OFF");
        ui->lblState->setStyleSheet("background-color: green;");
    }

    /*
    ui->btnCheckable->setText(checked?"ON":"OFF");
    ui->btnCheckable->setStyleSheet(QString("background-color: %1").arg(checked?"red":"green"));
    */
}

