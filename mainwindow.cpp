#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MouseClick.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timerClickConnection = connect(timer, &QTimer::timeout, this, &mouseLeftClick);
    this->setWindowTitle("AutoClicker");
}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
    delete ui;
}


void MainWindow::on_pushButton_clicked()//start
{

    if(timer->isActive()){
        timer->stop();
    }
    //timer->start((int)(ui->doubleSpinBox->value() * 1000));
    timer->setInterval((int)(ui->doubleSpinBox->value() * 1000));
    //std::cout<<"starting timer with "<<(int)(ui->doubleSpinBox->value() * 1000)<<"millis"<<std::endl;
    timer->start();
    this->setWindowTitle("AutoClicker(Running)");
}

void MainWindow::on_pushButton_2_clicked()//stop
{
    if(timer->isActive()){
        timer->stop();
    }
    this->setWindowTitle("AutoClicker");
}

void MainWindow::on_pushButton_3_clicked()//quit
{
    qApp->quit();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    disconnect(timerClickConnection);
    if(arg1 == "Left"){
        timerClickConnection = connect(timer, &QTimer::timeout, this, &mouseLeftClick);
    }else if(arg1 == "Right"){
        timerClickConnection = connect(timer, &QTimer::timeout, this, &mouseRightClick);
    }
}
