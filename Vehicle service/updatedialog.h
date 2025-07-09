#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include "ServiceEntry.h"

namespace Ui {
class UpdateDialog;
}

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDialog(QWidget *parent = nullptr);
    ~UpdateDialog();

    void setEntries(const QList<ServiceEntry>& list);   
    QList<ServiceEntry>getUpdatedEntries();             

private slots:
    void on_updateButton_clicked(); 
    void on_entrycomboBox_currentIndexChanged(int index);     

private:
    Ui::UpdateDialog *ui;
    QList<ServiceEntry> entries;
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;              

};

#endif // UPDATEDIALOG_H
