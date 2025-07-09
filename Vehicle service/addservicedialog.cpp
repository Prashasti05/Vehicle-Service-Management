#include "addservicedialog.h"
#include "ui_addservicedialog.h"
#include"ServiceEntry.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QPixmap>
#include <QPalette>


addservicedialog::addservicedialog(QWidget *parent)
    : QDialog(parent)                     
    , ui(new Ui::addservicedialog)       
{
    ui->setupUi(this);
    setBackground();                      

}

addservicedialog::~addservicedialog()
{
    delete ui;
}
//-----------------Function to set bg image of dialog----------------
void addservicedialog::setBackground()
{
    QPixmap bkgnd(":/img/img/18.jpg");       
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation);

    QPalette palette;                                     
    palette.setBrush(QPalette::Window, bkgnd);            
    this->setAutoFillBackground(true);                   
    this->setPalette(palette);                            
}

//-------------func call when window is resized------------------------
void addservicedialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);                   
    setBackground();                               
}

void addservicedialog::on_btnsave_clicked() {
    ServiceEntry s;                                 
    s.name = ui->namelineEdit->text();
    s.phone = ui->phonelineEdit->text();
    s.address = ui->addresslineEdit->text();           
    s.vehicleNumber = ui->vehiclenolineEdit->text();
    s.brand = ui->brandlineEdit->text();  
    s.model = ui->modellineEdit->text();
    s.date = ui->servicedate->date().toString("yyyy-MM-dd");
    s.serviceType = ui->servicecomboBox->currentText();
    s.status = ui->statuscomboBox->currentText();

    QFile file("services.csv");                            
    if (file.open(QIODevice::Append | QIODevice::Text)) {       
        QTextStream out(&file);                              
            out << s.name << "," << s.phone << "," << s.address << ","
                << s.vehicleNumber << "," << s.brand << "," << s.model << ","
                << s.date <<","<< s.serviceType << "," << s.status <<  "\n";  
        file.close();
    }

    emit serviceEntryAdded(s);                     
    accept();
}

void addservicedialog::on_btncancel_clicked()
{
    reject();                            
}

