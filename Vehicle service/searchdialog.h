#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "ServiceEntry.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(const QList<ServiceEntry> & entries, QWidget *parent = nullptr);
    ~SearchDialog();

private slots:
    void on_btnsearch_clicked();

private:
    Ui::SearchDialog *ui;
    QList<ServiceEntry> allEntries;

    void setBackground();
    void loadDataFromFile();

protected:
    void resizeEvent(QResizeEvent *event)override;    
    void showEvent(QShowEvent *event)override;        
};

#endif // SEARCHDIALOG_H
