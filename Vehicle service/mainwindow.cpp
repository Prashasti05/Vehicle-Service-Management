#include "mainwindow.h"                      // Includes the MainWindow class header
#include "ui_mainwindow.h"                    // Includes UI definition
#include "addservicedialog.h"
#include "ServiceEntry.h"
#include<QFile>
#include "infodialog.h"
#include <QTextStream>
#include "updatedialog.h"
#include "searchdialog.h"
#include <QString>
#include <QDate>

#include <QPixmap>                          // For background img
#include <QPalette>                         // For setting img
#include <QResizeEvent>
//#include <QPainter>                          // For painting custom graphics (bg)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadDataFromFile();
    updateServiceCounts();

   //setBackground();
   // connect(ui->btnadd , &QPushButton::clicked,this, &MainWindow::on_btnadd_clicked);
   // connect(ui->btncustomerinfo,&QPushButton::clicked,this, &MainWindow::on_btncustomerinfo_clicked);
   // connect(ui->btnsearch, &QPushButton::clicked, this, &MainWindow::on_btnsearch_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackground()
{
    QPixmap bkgnd(":/img/img/19.jpg");      //add img from resource nd scale it
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;                            //loads and sets img using palette and pixmap
    palette.setBrush(QPalette::Window, bkgnd);   //to apply full size img behind dialog
    this->setAutoFillBackground(true);
    this->setPalette(palette);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);         // Call base class implementation
    setBackground();                     // Resize bg img to match new size

}


void MainWindow::on_btnadd_clicked()
{
    addservicedialog dialog(this);            // create instance of add service dialog

    // Connect custom signal from dialog to a lambda function to add entry to list
    connect(&dialog, &addservicedialog::serviceEntryAdded, this,[this](const ServiceEntry &entry){
        entries.append(entry);               // Append the new service entry to the list
    });
    dialog.exec();                           // Show dialog and wait until user closes it

    updateServiceCounts();                  // Refresh totals on main screen
}


void MainWindow::on_btncustomerinfo_clicked()
{
    infodialog *dialog = new infodialog(entries, this);     // Create instance of InfoDialog

   // Connect signal to automatically update counts when data is changed in InfoDialog
   connect(dialog, &infodialog::serviceDataChanged, this, &MainWindow::updateServiceCounts);

    dialog->exec();                                   // Show InfoDialog
    delete dialog;                                    // Delete the dialog after closing (heap cleanup)

}

QList<ServiceEntry> MainWindow::loadDataFromFile()
{
    QList<ServiceEntry> list;                       // Temporary list to hold read entries
    QFile file("services.csv");                     //take qfile obj to open csv file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //open in read only mode
        return list;                                        // If file can't open, return empty list


    QTextStream in(&file);                          // Create a text stream to read lines

    while (!in.atEnd()) {                           //untill it reaches last of file
        QString line = in.readLine();               // Read a single line
        QStringList parts = line.split(",");        // Split the line into values
        if (parts.size() >= 9) {                    // Ensure line has all required fields
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

            list.append(entry);                   // Add to the temporary list
        }
    }
    file.close();

    entries =list;                               // Copy temporary list to member variable
    return list;                                 //return list
}

void MainWindow::saveDataToFile()
{
    QFile file("services.csv");               //take qfile obj to open csv file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))   //open in write only mode
        return;                             //if file not open,abort

    QTextStream out(&file);                 // Text stream for writing lines
     // Write each entry as a comma-separated line
    for (const ServiceEntry &entry : entries) {
        out << entry.name << "," << entry.phone << "," << entry.address << ","
            << entry.vehicleNumber << "," << entry.brand << "," << entry.model << ","
            << entry.date << "," << entry.serviceType << "," << entry.status << "\n";
    }
    file.close();
}


void MainWindow::on_btnupdate_clicked()
{
    QList<ServiceEntry> updatedList=loadDataFromFile();     // Reload entries from file

    UpdateDialog dialog(this);                            // Create UpdateDialog
    dialog.setEntries(updatedList);                       // Provide it with current data

     // If user accepts the dialog (e.g., clicked update)
    if(dialog.exec()==QDialog::Accepted){
        entries=dialog.getUpdatedEntries();              // Retrieve updated list

        saveDataToFile();                                 //save changes ti file
        loadDataFromFile();                               //reload data
        updateServiceCounts();                            //refresh count display
    }
}

void MainWindow::on_btnsearch_clicked()
{
    SearchDialog dialog(entries, this);  // Pass current entries to search dialog
    dialog.exec();                       // Show dialog
}

void MainWindow::on_btnShowTotal_clicked()
{
    int count =0;                                                // Count of today's entries
    QString today=QDate::currentDate().toString("yyyy-MM-dd");     // Get current date as string
    for(const ServiceEntry &entry :entries){               //run a loop for all entries
        if(entry.date ==today)                               // If service date is today
            count++;
    }
}

// Function to update total/completed/pending counts nd display in QLineEdits
void MainWindow::updateServiceCounts()
{
    QFile file("services.csv");                                  //take qfile obj to open csv file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))        //open in read only mode
        return;

    QTextStream in(&file);                                     //Create a QTextStream to read text from file.
    int total = 0, completed = 0, pending = 0;       //Initialize counters for total, completed,nd pending services

    while (!in.atEnd()) {                                     //Read the file line by line untill end
        QString line = in.readLine();                         //read one line from file
        QStringList fields = line.split(",");                // Split the line into values
        if (fields.size() < 9) continue;                     // Skip the line if it doesn't have enough fields

        QString status = fields[8].trimmed();            //Extract and trim the "status" field (9th column, index 8)
        total++;                                              // Count this line as a valid service entry

        //Check the value of status (case-insensitive comparison)
        if (status.compare("Completed", Qt::CaseInsensitive) == 0)
            completed++;                                     // Increment completed count if status is "Completed"
        else if (status.compare("Pending", Qt::CaseInsensitive) == 0)
            pending++;                                      // Increment pending count if status is "Pending"
    }

    file.close();

    // Update by setting QLineEdits
    ui->lineEdittotal->setText(QString::number(total));
    ui->lineEditcompleted->setText(QString::number(completed));
    ui->lineEditpending->setText(QString::number(pending));
}

void MainWindow::on_btnexit_clicked()
{
    QApplication::quit();        //to exit the application
}

