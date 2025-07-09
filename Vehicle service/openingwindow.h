#ifndef OPENINGWINDOW_H                // Include guard to prevent multiple inclusions
#define OPENINGWINDOW_H

#include <QDialog>                   // declare Qdialog Base class

namespace Ui {                      // Forward declaration of  openwindow class in ui namespace
class OpeningWindow;
}

class OpeningWindow : public QDialog     // Inherits from QDialog
{
    Q_OBJECT

public:
    explicit OpeningWindow(QWidget *parent = nullptr);
    ~OpeningWindow();

private slots:


    void on_schedulebtn_clicked();   //get started button

private:
    Ui::OpeningWindow *ui;            // Pointer to the UI

};

#endif // OPENINGWINDOW_H
