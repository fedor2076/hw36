#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
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

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    s.exec();
}

void MainWindow::on_messageEdit_returnPressed()
{
    on_allSendButton_clicked();
}

void MainWindow::on_allSendButton_clicked()
{

}

void MainWindow::on_privateSendButton_clicked()
{

}

void MainWindow::on_actionchose_client_triggered()
{
createClient();
}

void MainWindow::on_actionexit_triggered()
{

}

void MainWindow::showEvent(QShowEvent* event)
{
    ui->statusbar->showMessage("connect");
}
