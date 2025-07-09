#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H
#include"ServiceEntry.h"

#include <QDialog>
#include"ServiceEntry.h"                // Include the definition of ServiceEntry
//#include <QVector>
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
    void serviceEntryAdded(const ServiceEntry &entry);        // Signal emitted when new service is added


private:
    Ui::addservicedialog *ui;
    void setBackground();                                   // Helper function to set bg img

protected:
    void resizeEvent(QResizeEvent *event)override;          // Handle resizing of the dialog
};                                                    //automatically calls whenever  window/dialog is resized by user

#endif // ADDSERVICEDIALOG_H
