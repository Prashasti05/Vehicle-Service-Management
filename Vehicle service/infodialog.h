#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
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
    void serviceDataChanged();         

private:
    Ui::infodialog *ui;
    QList<ServiceEntry> entries;        

    void saveDataToFile();             
    void loadDataFromFile();
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;   
};

#endif // INFODIALOG_H
