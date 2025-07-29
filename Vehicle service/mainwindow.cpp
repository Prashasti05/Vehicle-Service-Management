#include "mainwindow.h"                     
#include "ui_mainwindow.h"                    
#include "addservicedialog.h"
#include "ServiceEntry.h"
#include<QFile>
#include "infodialog.h"
#include <QTextStream>
#include "updatedialog.h"
#include "searchdialog.h"
#include <QString>
#include <QDate>

#include <QPixmap>                          
#include <QPalette>                         
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadDataFromFile();
    updateServiceCounts();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackground()
{
    QPixmap bkgnd(":/img/img/19.jpg");     
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;                            
    palette.setBrush(QPalette::Window, bkgnd);  
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);         
    setBackground();                    
}

void MainWindow::on_btnadd_clicked()
{
    addservicedialog dialog(this);            

    connect(&dialog, &addservicedialog::serviceEntryAdded, this,[this](const ServiceEntry &entry){
        entries.append(entry);               
    });
    dialog.exec();                           
    updateServiceCounts();                  
}


void MainWindow::on_btncustomerinfo_clicked()
{
    infodialog *dialog = new infodialog(entries, this);     

   connect(dialog, &infodialog::serviceDataChanged, this, &MainWindow::updateServiceCounts);

    dialog->exec();                                  
    delete dialog;                                    
}

QList<ServiceEntry> MainWindow::loadDataFromFile()
{
    QList<ServiceEntry> list;                       
    QFile file("services.csv");                    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
        return list;                                       

    QTextStream in(&file);                          

    while (!in.atEnd()) {                           
        QString line = in.readLine();               
        QStringList parts = line.split(",");        
        if (parts.size() >= 9) {                   
            ServiceEntry entry;
            entry.name = parts[0];
            entry.phone = parts[1];
            entry.address = parts[2];
            entry.vehicleNumber = parts[3];
            entry.brand = parts[4];
            entry.model = parts[5];
            entry.date = parts[6];
            entry.serviceType = parts[7];
            entry.status=parts[8];

            list.append(entry);                   
        }
    }
    file.close();

    entries =list;                               
    return list;                                
}

void MainWindow::saveDataToFile()
{
    QFile file("services.csv");               
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))   
        return;                            

    QTextStream out(&file);                 
   
    for (const ServiceEntry &entry : entries) {
        out << entry.name << "," << entry.phone << "," << entry.address << ","
            << entry.vehicleNumber << "," << entry.brand << "," << entry.model << ","
            << entry.date << "," << entry.serviceType << "," << entry.status << "\n";
    }
    file.close();
}

void MainWindow::on_btnupdate_clicked()
{
    QList<ServiceEntry> updatedList=loadDataFromFile();    

    UpdateDialog dialog(this);                            
    dialog.setEntries(updatedList);                     

    if(dialog.exec()==QDialog::Accepted){
        entries=dialog.getUpdatedEntries();              

        saveDataToFile();                                 
        loadDataFromFile();                              
        updateServiceCounts();                           
    }
}

void MainWindow::on_btnsearch_clicked()
{
    SearchDialog dialog(entries, this);  
    dialog.exec();                       
}

void MainWindow::on_btnShowTotal_clicked()
{
    int count =0;                                               
    QString today=QDate::currentDate().toString("yyyy-MM-dd");    
    for(const ServiceEntry &entry :entries){              
        if(entry.date ==today)                             
            count++;
    }
}


void MainWindow::updateServiceCounts()
{
    QFile file("services.csv");                                 
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))        
        return;

    QTextStream in(&file);                                    
    int total = 0, completed = 0, pending = 0;       

    while (!in.atEnd()) {                                    
        QString line = in.readLine();                         
        QStringList fields = line.split(",");                
        if (fields.size() < 9) continue;                    

        QString status = fields[8].trimmed();            
        total++;                                           

        if (status.compare("Completed", Qt::CaseInsensitive) == 0)
            completed++;                                     
        else if (status.compare("Pending", Qt::CaseInsensitive) == 0)
            pending++;                                     
    }

    file.close();

    // Update by setting QLineEdits
    ui->lineEdittotal->setText(QString::number(total));
    ui->lineEditcompleted->setText(QString::number(completed));
    ui->lineEditpending->setText(QString::number(pending));
}

void MainWindow::on_btnexit_clicked()
{
    QApplication::quit();        
}

