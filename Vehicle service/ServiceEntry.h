#ifndef SERVICEENTRY_H
#define SERVICEENTRY_H

#include <QString>

struct ServiceEntry {
    QString name;
    QString phone;
    QString address;
    QString vehicleNumber;
    QString brand;
    QString model;
    QString date;
    QString serviceType;
    QString status;
};

#endif // SERVICEENTRY_H
