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


void MainWindow::on_btnEdit_clicked()
{
    QString str = QString("Name: %1").arg(ui->editName->text());
    MyDialog *dlg = new MyDialog(this, str);

    dlg->setAttribute(Qt::WA_DeleteOnClose);
    connect(dlg, &QDialog::accepted, this,[=](){receive_hobby(dlg->get_data())};
    // int r = dlg->exec();
    // if (r==QDialog::Accepted)
    // {
    //     ui->lblHobby->setText(dlg->get_data());
    // }
        dlg->open();
}

void MainWindow::receive_hobby(QString str)
{
    qDebug() << "receive_hobby" << str;
    ui->lblHobby->setText(str);    
}
