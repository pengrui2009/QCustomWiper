#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->cbx_wipermode->addItem("关闭", QVariant("DEFAULT"));
    ui->cbx_wipermode->addItem("模式A", QVariant("MODEA"));
    ui->cbx_wipermode->addItem("模式B", QVariant("MODEB"));
    ui->cbx_wipermode->addItem("模式C", QVariant("MODEC"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cbx_wipermode_currentIndexChanged(const QString &arg1)
{
    QString value = ui->cbx_wipermode->currentData().toString();

    if (value == "DEFAULT")
    {
        ui->widget->setWiperMode(QCustomWiper::WIPERMODE_DEFAULT);
    } else if (value == "MODEA") {
        ui->widget->setWiperMode(QCustomWiper::WIPERMODE_A);
    } else if (value == "MODEB") {
        ui->widget->setWiperMode(QCustomWiper::WIPERMODE_B);
    } else if (value == "MODEC") {
        ui->widget->setWiperMode(QCustomWiper::WIPERMODE_C);
    }
}
