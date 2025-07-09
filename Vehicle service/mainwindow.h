#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ServiceEntry.h"
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

private slots:
    void on_btnadd_clicked();
    void on_btncustomerinfo_clicked();
    void on_btnupdate_clicked();
    void on_btnsearch_clicked();
    void on_btnShowTotal_clicked();
    void on_btnexit_clicked();

private:
    Ui::MainWindow *ui;

    void updateServiceCounts();                  
    QList<ServiceEntry> entries;                  

    QList<ServiceEntry> loadDataFromFile();      
    void saveDataToFile();                        
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;

};
#endif // MAINWINDOW_H
