#include "addservicedialog.h"
#include "ui_addservicedialog.h"
#include"ServiceEntry.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
//#include <QFileDialog>
#include <QPixmap>
#include <QPalette>


addservicedialog::addservicedialog(QWidget *parent)
    : QDialog(parent)                     // Call parent constructor
    , ui(new Ui::addservicedialog)        // Create UI instance
{
    ui->setupUi(this);
    setBackground();                      //set bg img

  //  connect(ui->btnsave , &QPushButton::clicked,this, &QDialog::accept);
  // connect(ui->btncancel,&QPushButton::clicked,this, &QDialog::reject);
}

addservicedialog::~addservicedialog()
{
    delete ui;
}
//-----------------Function to set bg image of dialog----------------
void addservicedialog::setBackground()
{
    QPixmap bkgnd(":/img/img/18.jpg");       // Load image to qpixmap
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation); // Scale it to window size

    QPalette palette;                                     // Create new palette
    palette.setBrush(QPalette::Window, bkgnd);            // Set img as window bg
    this->setAutoFillBackground(true);                    // Enable bg filling
    this->setPalette(palette);                            //apply palette to window
}

//-------------called when the window is resized------------------------
void addservicedialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);                   // Call base class implementation
    setBackground();                               // Resize bg img to match new size
}


void addservicedialog::on_btnsave_clicked() {
    ServiceEntry s;                                 // Create a ServiceEntry obj
    s.name = ui->namelineEdit->text();
    s.phone = ui->phonelineEdit->text();
    s.address = ui->addresslineEdit->text();           //get all fields input
    s.vehicleNumber = ui->vehiclenolineEdit->text();
    s.brand = ui->brandlineEdit->text();  
    s.model = ui->modellineEdit->text();
    s.date = ui->servicedate->date().toString("yyyy-MM-dd");
    s.serviceType = ui->servicecomboBox->currentText();
    s.status = ui->statuscomboBox->currentText();

    QFile file("services.csv");                            //To save in File-create a QFile obj
    if (file.open(QIODevice::Append | QIODevice::Text)) {       //open in append mode
        QTextStream out(&file);                              // Create output stream linked wid file
            out << s.name << "," << s.phone << "," << s.address << ","
                << s.vehicleNumber << "," << s.brand << "," << s.model << ","
                << s.date <<","<< s.serviceType << "," << s.status <<  "\n";  //writes data to file
        file.close();
    }

    emit serviceEntryAdded(s);                     // Emit custom signal to notify parent
    accept();
}

void addservicedialog::on_btncancel_clicked()
{
    reject();                             // Close dialog with cancel
}

