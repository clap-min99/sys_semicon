#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect(ui->clearBtn, SIGNAL(clicked()), ui -> hellolbl, SLOT(clear()));
    connect(ui->clearBtn, &QPushButton::clicked, ui->hellolbl, &QLabel::clear);
}

MainWindow::~MainWindow()
{
    delete ui;
}

