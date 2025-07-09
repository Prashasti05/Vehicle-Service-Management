#include "openingwindow.h"        // Include the header for OpeningWindow
#include "ui_openingwindow.h"     // Include the auto-generated UI header
#include"mainwindow.h"             // Include the MainWindow class


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
    MainWindow *mainWin =new MainWindow();      // Create MainWindow instance
    mainWin->show();                            //shows the main window
    this->close();                              // Close the opening window
}

