#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QMessageBox>

UpdateDialog::UpdateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
   // QList<ServiceEntry> getUpdatedEntries();
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
    setBackground();  // ← Update bg size on window resize
}



void UpdateDialog::setEntries(const QList<ServiceEntry>& list)
{
    entries = list;                          // Store the entries
    ui->entrycomboBox->clear();              // Clear existing combo box items

    for (const auto &entry : entries) {       //iterate in each entries
        ui->entrycomboBox->addItem(entry.name); //Adds it as an item to entrycomboBox, which allows users to select from dropdown menu.
    }

    if (!entries.isEmpty()) {                       //Checks if the list is not empty
        ui->entrycomboBox->setCurrentIndex(0);        // Select first item in combobox by default
        on_entrycomboBox_currentIndexChanged(0);       // Load its data into form
    }
}

QList<ServiceEntry> UpdateDialog::getUpdatedEntries()
{
    return entries;                      // Return updated entries
}

void UpdateDialog::on_updateButton_clicked()
{
    int index = ui->entrycomboBox->currentIndex();         // Get selected entry index
    if (index >= 0 && index < entries.size()) {            //Ensures selected index is within bounds of entries list

        entries[index].name = ui->namelineEdit->text();
        entries[index].phone = ui->phonelineEdit->text();    //Takes data entered by user in various input fields in form
        entries[index].address = ui->addresslineEdit->text();//and Updates selected entry (entries[index]) with new data.
        entries[index].vehicleNumber = ui->vehiclelineEdit->text();
        entries[index].brand = ui->brandlineEdit->text();
        entries[index].model = ui->modellineEdit->text();
        entries[index].serviceType = ui->servicecomboBox->currentText();
        entries[index].status = ui->statuscomboBox->currentText();

        QMessageBox::information(this, "Success", "Service entry updated.");
        accept();                                          // Close dialog and return with success
    }
}

void UpdateDialog::on_entrycomboBox_currentIndexChanged(int index)
{

    if (index >= 0 && index < entries.size()) {        //checks if the selected index is within valid range:
        // Populate form fields and sets selected entry's data
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

