#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ServiceEntry.h"
//#include <QVector>
#include <QList>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //QList<ServiceEntry> entries;

private slots:
    void on_btnadd_clicked();
    void on_btncustomerinfo_clicked();
    void on_btnupdate_clicked();
    void on_btnsearch_clicked();
    void on_btnShowTotal_clicked();
    void on_btnexit_clicked();

private:
    Ui::MainWindow *ui;

    void updateServiceCounts();                   // helper func to update total no of service
    QList<ServiceEntry> entries;                  //actual data list holding all service records

    QList<ServiceEntry> loadDataFromFile();       // Function to load entries from CSV
    void saveDataToFile();                        // Function to write entries to CSV
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;

};
#endif // MAINWINDOW_H
