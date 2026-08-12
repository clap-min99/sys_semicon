#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    ui->lblName->setText(name);
   // connect(this, SIGNAL(send_hobby(QString)), parent, SLOT(receive_hobby(QString)));
}

MyDialog::~MyDialog()
{
    delete ui;
}

QString MyDialog::get_data()
{
    QString str = QString("Hobby:");
    int one_or_more = 0;
    if(ui->chkFishing->isChecked())
    {
        one_or_more++;
        str.append(" Fishing");
    }
    if(ui->chkSurfing->isChecked())
    {
        one_or_more++;
        str.append(" Surfing");
    }
    if(ui->chkTraveling->isChecked())
    {
        one_or_more++;
        str.append(" Traveling");
    }
    if(one_or_more == 0)
    {
        str.append(" None");
    }
    return str;
}

void MyDialog::on_btnOK_clicked()
{


    accept();
}


void MyDialog::on_btnCancel_clicked()
{
    reject();
}

