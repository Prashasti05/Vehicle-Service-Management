#ifndef OPENINGWINDOW_H                
#define OPENINGWINDOW_H

#include <QDialog>                   

namespace Ui {                      
class OpeningWindow;
}

class OpeningWindow : public QDialog     
{
    Q_OBJECT

public:
    explicit OpeningWindow(QWidget *parent = nullptr);
    ~OpeningWindow();

private slots:

    void on_schedulebtn_clicked();   

private:
    Ui::OpeningWindow *ui;            

};

#endif // OPENINGWINDOW_H
