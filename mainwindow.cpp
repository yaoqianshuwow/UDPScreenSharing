#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QBuffer>
#include <QImageReader>
#include<windows.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadsize = 10;
    server = new UDPServer[threadsize];

    for(int i=0;i<threadsize;i++){
        // 在服务器端，连接信号到槽函数
        //connect(&server[i], &UDPServer::pixReceived, this, &MainWindow::displaypix, Qt::QueuedConnection);
        connect(&server[i], &UDPServer::pixReceived, ui->openGLWidget, &OurOpenglWidget::pixshow);
        server[i].startServer(12345+i);
        server[i].start();
    }
    // connect(ui->openGLWidget,&OurOpenglWidget::pressevent,this,&MainWindow::presseventsolt);
    // connect(ui->openGLWidget,&OurOpenglWidget::moveevent,this,&MainWindow::moveeventsolt);
    // connect(ui->openGLWidget,&OurOpenglWidget::releaseevent,this,&MainWindow::releaseeventsolt);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendClearButton_clicked()
{
   // ui->SendEdit->clear();
}


void MainWindow::on_ClearButton_clicked()
{
   // ui->RecieveEdit->clear();

}


void MainWindow::on_fillwindowaction_triggered()
{

}

