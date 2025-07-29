#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QMessageBox>

UpdateDialog::UpdateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::setBackground()
{
    QPixmap bkgnd(":/img/img/5.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void UpdateDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    setBackground();  
}

void UpdateDialog::setEntries(const QList<ServiceEntry>& list)
{
    entries = list;                          
    ui->entrycomboBox->clear();             

    for (const auto &entry : entries) {      
        ui->entrycomboBox->addItem(entry.name); 
    }

    if (!entries.isEmpty()) {                       
        ui->entrycomboBox->setCurrentIndex(0);        
        on_entrycomboBox_currentIndexChanged(0);      
    }
}

QList<ServiceEntry> UpdateDialog::getUpdatedEntries()
{
    return entries;                     
}

void UpdateDialog::on_updateButton_clicked()
{
    int index = ui->entrycomboBox->currentIndex();         
    if (index >= 0 && index < entries.size()) {           

        entries[index].name = ui->namelineEdit->text();
        entries[index].phone = ui->phonelineEdit->text();   
        entries[index].address = ui->addresslineEdit->text();
        entries[index].vehicleNumber = ui->vehiclelineEdit->text();
        entries[index].brand = ui->brandlineEdit->text();
        entries[index].model = ui->modellineEdit->text();
        entries[index].serviceType = ui->servicecomboBox->currentText();
        entries[index].status = ui->statuscomboBox->currentText();

        QMessageBox::information(this, "Success", "Service entry updated.");
        accept();                                          
    }
}

void UpdateDialog::on_entrycomboBox_currentIndexChanged(int index)
{

    if (index >= 0 && index < entries.size()) {       
        
        ui->namelineEdit->setText(entries[index].name);
        ui->phonelineEdit->setText(entries[index].phone);
        ui->addresslineEdit->setText(entries[index].address);
        ui->vehiclelineEdit->setText(entries[index].vehicleNumber);
        ui->brandlineEdit->setText(entries[index].brand);
        ui->modellineEdit->setText(entries[index].model);
        ui->servicecomboBox->setCurrentText(entries[index].serviceType);
        ui->statuscomboBox->setCurrentText(entries[index].status);
    }
}

