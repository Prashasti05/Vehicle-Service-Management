#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
//#include <QVector>
#include<QTableWidget>
#include "ServiceEntry.h"

namespace Ui {
class infodialog;
}

class infodialog : public QDialog
{
    Q_OBJECT

public:
    explicit infodialog( const QList<ServiceEntry> & entries, QWidget *parent = nullptr);
    ~infodialog();


private slots:
    void on_btnDelete_clicked();

signals:
    void serviceDataChanged();         //signal that notifies when service data is changed(e.g.after deletion).

private:
    Ui::infodialog *ui;
    QList<ServiceEntry> entries;        //Stores the list of service entries

    void saveDataToFile();             //Helper func to save/load entries list to/from a file
    void loadDataFromFile();
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;   //resize bg when window is resized
};

#endif // INFODIALOG_H
