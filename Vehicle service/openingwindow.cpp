#include "openingwindow.h"        
#include "ui_openingwindow.h"    
#include"mainwindow.h"             


OpeningWindow::OpeningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OpeningWindow)
{
    ui->setupUi(this);
}

OpeningWindow::~OpeningWindow()
{
    delete ui;
}


void OpeningWindow::on_schedulebtn_clicked()
{
    MainWindow *mainWin =new MainWindow();     
    mainWin->show();                            
    this->close();                              
}

