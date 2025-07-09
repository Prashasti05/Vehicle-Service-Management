#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H
#include"ServiceEntry.h"

#include <QDialog>
#include"ServiceEntry.h"               
#include <QString>

namespace Ui {
class addservicedialog;
}

class addservicedialog : public QDialog
{
    Q_OBJECT

public:
    explicit addservicedialog(QWidget *parent = nullptr);
    ~addservicedialog();

private slots:
    void on_btnsave_clicked();
    void on_btncancel_clicked();

signals:
    void serviceEntryAdded(const ServiceEntry &entry);       

private:
    Ui::addservicedialog *ui;
    void setBackground();                                  

protected:
    void resizeEvent(QResizeEvent *event)override;          
};                                                   

#endif // ADDSERVICEDIALOG_H
