#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);

    connect(this, &MyDialog::accepted, this, &MyDialog::dlg_accepted);
    connect(this,  &MyDialog::rejected, this, &MyDialog::dlg_rejected);
    connect(this, &MyDialog::finished, this, &MyDialog::dlg_finished);
}


MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::dlg_accepted()
{
    qDebug() << "accpeted";
}

void MyDialog::dlg_rejected()
{
    qDebug() << "rejected";
}

void MyDialog::dlg_finished(int result)
{
    qDebug() << "finished" << result;
}


void MyDialog::on_btnAccept_clicked()
{
    accept();
}


void MyDialog::on_btnReject_clicked()
{
    reject();
}


void MyDialog::on_btnDone_clicked()
{
    done(10);
}

