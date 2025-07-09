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

    void setEntries(const QList<ServiceEntry>& list);   // Setter for the list of entries to be updated
    QList<ServiceEntry>getUpdatedEntries();             // Getter to retrieve updated entries

private slots:
   // void on_searchButton_clicked();
    void on_updateButton_clicked(); 
    void on_entrycomboBox_currentIndexChanged(int index);     // Triggers when new entry is selected in combo box

private:
    Ui::UpdateDialog *ui;

    QList<ServiceEntry> entries;
    void setBackground();

protected:
    void resizeEvent(QResizeEvent *event)override;              // Handles window resizing

};

#endif // UPDATEDIALOG_H
