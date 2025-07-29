#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QFile>

SearchDialog::SearchDialog(const QList<ServiceEntry> & entries, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
    ,allEntries(entries)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::setBackground()
{
    QPixmap bkgnd(":/img/img/52.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;                           
    palette.setBrush(QPalette::Window, bkgnd);   
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void SearchDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);        
    setBackground();                     
}

void SearchDialog::on_btnsearch_clicked()
{
    QString name = ui->namelineEdit->text().trimmed();   
    QString phone = ui->phonelineEdit->text().trimmed();
    QString model = ui->modellineEdit->text().trimmed();

    QString result;                                     

    // Loop through all stored service entries
    for (const ServiceEntry& entry : allEntries) {
        bool match = false;

        // Check each field for match 
        if (!name.isEmpty() && entry.name.contains(name, Qt::CaseInsensitive)) match = true;
        if (!phone.isEmpty() && entry.phone.contains(phone, Qt::CaseInsensitive)) match = true;
        if (!model.isEmpty() && entry.model.contains(model, Qt::CaseInsensitive)) match = true;

        if (match) {                            // If any field matched, build result string
            result += "Name: " + entry.name + "\n";
            result += "Phone: " + entry.phone + "\n";
            result += "Address: " + entry.address + "\n";
            result += "Vehicle No: " + entry.vehicleNumber + "\n";
            result += "Brand: " + entry.brand + "\n";
            result += "Model: " + entry.model + "\n";
            result += "Issue Date : " + entry.date + "\n";
            result += "Service Type: " + entry.serviceType + "\n";
            result += "Status: " + entry.status + "\n";
            result += "------------------------\n";
        }
    }

    if (result.isEmpty()) {              //if no matches found
        result = "No matching records found.";
    }

    ui->resulttextEdit->setPlainText(result);           // Display result in the UI text edit

}

void SearchDialog::loadDataFromFile()
{
    allEntries.clear();                         

    QFile file("services.csv");                  

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;                                   

    QTextStream in(&file);                      
    while (!in.atEnd()) {                      
        QString line = in.readLine();           
        QStringList parts = line.split(",");    

        if (parts.size() < 9) continue;          

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

        allEntries.append(entry);             
    }
    file.close();
}

void SearchDialog::showEvent(QShowEvent *event)
{
    loadDataFromFile();                     
    QDialog::showEvent(event);           
}

