#include "infodialog.h"
#include "ui_infodialog.h"
#include<QFile>
#include <QTextStream>
#include <QStringList>           // For handling lists of strings
#include"ServiceEntry.h"
#include <QMessageBox>

infodialog::infodialog(const QList<ServiceEntry> & entries, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::infodialog)

{
    ui->setupUi(this);
   // connect(ui->btnDelete, &QPushButton::clicked, this, &infodialog::on_btnDelete_clicked);

    ui->tableInfo->setSelectionMode(QAbstractItemView::SingleSelection);   // Allow only one row to be selected
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);    // Clicking a cell selects the entire row
    ui->tableInfo->clearSelection();                                       // Clear any existing selection

    loadDataFromFile();



    ui->tableInfo->setColumnCount(9);                                  //Set the number of col in table
    ui->tableInfo->setRowCount(entries.size());                        // Set initial row count based on list & also set headers
    ui->tableInfo->setHorizontalHeaderLabels({"Name", "Phone", "Address", "Vehicle No", "Brand", "Model", "Date", "Service", "Status"});

}

infodialog::~infodialog()
{
    delete ui;
}

void infodialog::setBackground()
{
    QPixmap bkgnd(":/img/img/17.jpg");      // Load bg img  & scale img to fit window
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;                                //create new palette
    palette.setBrush(QPalette::Window, bkgnd);      // brush image to  window bg
    this->setAutoFillBackground(true);              //enable fill bg
    this->setPalette(palette);                      //apply palette to dialog
}

void infodialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    setBackground();  // ← Update background size if window is resized
}


void infodialog::on_btnDelete_clicked()
{

    QItemSelectionModel *select=ui->tableInfo->selectionModel();  // Get selection model of table, which manages row/column selections.
   if(!select ||!select->hasSelection()){                        // Check if selection model exists AND if no row is selected,show warning
        QMessageBox::warning(this, " Delete Row ", "Please select a row to delete.");
       return;                                                  // Exit func early since there is nothing to delete
   }

   int row = select->currentIndex().row();                      // Retrieve row index of currently selected item
   if(row>=0){                                                  // Proceed only if row index is valid (non-negative
       QAbstractItemModel *model = ui->tableInfo->model();      // Access the data model
       model->removeRow(row);                                   // Remove specified row from model
       saveDataToFile();                             // Save the updated list to file

       emit serviceDataChanged();                   //Emit a signal to notify that data has changed
    }
}


void infodialog::saveDataToFile()
{
    QFile file("services.csv");                              //create a qfile obj
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {// Try opening file in write mode
        return;
    }
        QTextStream out(&file);                              //Create a text stream for writing to file

        int rowCount = ui->tableInfo->rowCount();            //get no of rows
        int colCount = ui->tableInfo->columnCount();         //ge no of columns

        for (int row = 0; row < rowCount; ++row) {           //loop rows
            QStringList rowData;                           //temp list to store all cell values (columns) of curr row
            bool isEmpty =true;                            //flag tracks whether curr row contains any non-empty cell

            for (int col = 0; col < colCount; ++col) {      //inner loop : go through each col of curr row
                QTableWidgetItem* item = ui->tableInfo->item(row, col); // Try to get item at posn (row, col).
                QString text =item ?item->text().trimmed():"";    // If item exists, extract its txt nd trim whitespace
                                                                 //If item is nullptr(empty cell), just assign an empty string

                if(!text.isEmpty())                   // If at least one cell in row is not empty, set flag to false
                    isEmpty =false;

                rowData <<text;                     // Append the text (even if empty) to the `rowData` list
            }
            if(!isEmpty)                           // If row is not completely empty, write it2 output stream.
            out << rowData.join(",") << "\n";      //join comma to make csv format file;`\n` moves to next line for next row.
        }

        file.close();
}

void infodialog::loadDataFromFile()
{
    QFile file("services.csv");                                 //create a qfile obj
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){     // Try opening file in read mode
        return;
    }

    ui->tableInfo->setRowCount(0);                            // Clear all rows before loading new data

    QTextStream in(&file);                                    // Create a text stream to read from file
    while (!in.atEnd()) {                                     // Loop through file until end
        QString line = in.readLine();                         // Read one line from the file
        QStringList parts = line.split(",");                  // Split the line by commas (CSV)


        int row = ui->tableInfo->rowCount();                  //get row cnt
        ui->tableInfo->insertRow(row);                        // Add a new row to the table

        for(int i=0;i<parts.size();++i){
            ui->tableInfo->setItem(row,i,new QTableWidgetItem(parts[i])); // Populate each cell in row

        }
    }
    file.close();
}







