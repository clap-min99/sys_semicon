#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Eval.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnGrpDisp,
            QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this,
            &MainWindow::Make_String);
    // Eval eval;
    // QString expr = "12+34";
    // double res = eval.Evaluate(expr.toStdString());
    // QString qstr = QString("%1").arg(res);
    // expr.append("=");
    // expr.append(qstr);
    // qDebug() << expr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Make_String(QAbstractButton *btn)
{
    expr.append(btn->text());
    ui->lblResult->setText(expr);
}

void MainWindow::on_btnCancel_clicked()
{
    // expr.clear();
    expr = "";
    ui->lblResult->setText("0");
}

void MainWindow::on_btnBackspace_clicked()
{
    expr.chop(1);
    ui->lblResult->setText(expr);
}

// void MainWindow::appendToExpr(const QString &s)
// {
//     expr += s;
//     ui->lblResult->setText(expr);
// }

void MainWindow::on_btnEqual_clicked()
{
    Eval eval;
    double res = eval.Evaluate(expr.toStdString());
    QString qstr = QString("%1").arg(res);
    expr.append("=");
    expr.append(qstr);
    ui->lblResult->setText(expr);
    expr="";
    // expr = QString::number(res);
    // ui->lblResult->setText(expr);
}

// void MainWindow::on_btn0_clicked() { appendToExpr("0"); }
// void MainWindow::on_btn1_clicked() { appendToExpr("1"); }
// void MainWindow::on_btn2_clicked() { appendToExpr("2"); }
// void MainWindow::on_btn3_clicked() { appendToExpr("3"); }
// void MainWindow::on_btn4_clicked() { appendToExpr("4"); }
// void MainWindow::on_btn5_clicked() { appendToExpr("5"); }
// void MainWindow::on_btn6_clicked() { appendToExpr("6"); }
// void MainWindow::on_btn7_clicked() { appendToExpr("7"); }
// void MainWindow::on_btn8_clicked() { appendToExpr("8"); }
// void MainWindow::on_btn9_clicked() { appendToExpr("9"); }
// void MainWindow::on_btnOpen_clicked()  { appendToExpr("("); }
// void MainWindow::on_btnClose_clicked() { appendToExpr(")"); }
// void MainWindow::on_btnPlus_clicked()  { appendToExpr("+"); }
// void MainWindow::on_btnMinus_clicked() { appendToExpr("-"); }
// void MainWindow::on_btnMul_clicked()   { appendToExpr("*"); }
// void MainWindow::on_btnDiv_clicked()   { appendToExpr("/"); }
// void MainWindow::on_btnPoint_clicked() { appendToExpr("."); }




// void MainWindow::on_btnMul_windowIconTextChanged(const QString &iconText)
// {

// }

