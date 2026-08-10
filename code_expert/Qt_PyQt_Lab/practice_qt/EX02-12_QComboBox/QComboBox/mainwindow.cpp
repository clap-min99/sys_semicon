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


void MainWindow::on_cboActivate_activated(int index)
{
    qDebug() << "activated" << index << ":" << ui->cboActivate;
}


void MainWindow::on_cboHighlight_highlighted(int index)
{
    qDebug() << "highlighted" << index;
}


void MainWindow::on_cboEditableFalse_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index;
}


void MainWindow::on_cboEditableFalse_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableFalse_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_currentIndexChanged(int index)
{
    qDebug() << "currentIndexChanged" << index;
}


void MainWindow::on_cboEditableTrue_currentTextChanged(const QString &arg1)
{
    qDebug() << "currentTextChanged" << arg1;
}


void MainWindow::on_cboEditableTrue_editTextChanged(const QString &arg1)
{
    qDebug() << "editTextChanged" << arg1;
}

void MainWindow::on_btnAct_clicked()
{
    // 하나의 아이템 추가
    // ui->comboBox->addItem("사과");

    // 여러개 아이템 추가 - additem
    // QStringList list = {"사과", "바나나", "수박"};
    // ui->comboBox->addItems(list);

    // // 기존 아이템 선택
    // ui->comboBox->setCurrentText("수박");

    // // 선택된 아이템들의 텍스트 획득
    // qDebug() << "선택된 아이템: " << ui->cboActivate->currentText();

    // 아이템 삭제
    ui->cboActivate->removeItem(0);
    int index = ui->cboHighlight->findText("item0");
    ui->cboHighlight->removeItem(index);
}

