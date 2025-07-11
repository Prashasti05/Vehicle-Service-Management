#include "infodialog.h"
#include "ui_infodialog.h"
#include<QFile>
#include <QTextStream>
#include <QStringList>           
#include"ServiceEntry.h"
#include <QMessageBox>

infodialog::infodialog(const QList<ServiceEntry> & entries, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::infodialog)

{
    ui->setupUi(this);
   
    ui->tableInfo->setSelectionMode(QAbstractItemView::SingleSelection);   
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);    
    ui->tableInfo->clearSelection();                                       

    loadDataFromFile();

    ui->tableInfo->setColumnCount(9);                                  
    ui->tableInfo->setRowCount(entries.size());                        
    ui->tableInfo->setHorizontalHeaderLabels({"Name", "Phone", "Address", "Vehicle No", "Brand", "Model", "Date", "Service", "Status"});
}

infodialog::~infodialog()
{
    delete ui;
}

void infodialog::setBackground()
{
    QPixmap bkgnd(":/img/img/17.jpg");      
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;                                
    palette.setBrush(QPalette::Window, bkgnd);      
    this->setAutoFillBackground(true);             
    this->setPalette(palette);                     
}

void infodialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    setBackground();  
}


void infodialog::on_btnDelete_clicked()
{
    QItemSelectionModel *select=ui->tableInfo->selectionModel();  
   if(!select ||!select->hasSelection()){                        
        QMessageBox::warning(this, " Delete Row ", "Please select a row to delete.");
       return;                                                 
   }
   int row = select->currentIndex().row();                     
   if(row>=0){                                                 
       QAbstractItemModel *model = ui->tableInfo->model();      
       model->removeRow(row);                                 
       saveDataToFile();                            

       emit serviceDataChanged();                
    }
}


void infodialog::saveDataToFile()
{
    QFile file("services.csv");                              
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
        QTextStream out(&file);                              

        int rowCount = ui->tableInfo->rowCount();            
        int colCount = ui->tableInfo->columnCount();        

        for (int row = 0; row < rowCount; ++row) {           
            QStringList rowData;                          
            bool isEmpty =true;                           

            for (int col = 0; col < colCount; ++col) {      
                QTableWidgetItem* item = ui->tableInfo->item(row, col); 
                QString text =item ?item->text().trimmed():"";    
                                                                 
                if(!text.isEmpty())                   
                    isEmpty =false;

                rowData <<text;                     
            }
            if(!isEmpty)                           
            out << rowData.join(",") << "\n";      
        }

        file.close();
}

void infodialog::loadDataFromFile()
{
    QFile file("services.csv");                                 
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){    
        return;
    }

    ui->tableInfo->setRowCount(0);                          

    QTextStream in(&file);                                   
    while (!in.atEnd()) {                                     
        QString line = in.readLine();                         
        QStringList parts = line.split(",");                  


        int row = ui->tableInfo->rowCount();                 
        ui->tableInfo->insertRow(row);                        

        for(int i=0;i<parts.size();++i){
            ui->tableInfo->setItem(row,i,new QTableWidgetItem(parts[i]));

        }
    }
    file.close();
}







