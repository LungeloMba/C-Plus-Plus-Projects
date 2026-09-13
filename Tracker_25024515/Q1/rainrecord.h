#ifndef RAINRECORD_H
#define RAINRECORD_H

#include <QObject>
#include <QDate>
#include <QString>

class RainRecord : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ getData)

public:
    RainRecord(const QString &station, const QDate &date, double mm, QObject *parent = nullptr);
    QString station() const;
    QDate date() const;
    double mm() const;

private:
    QString getData() const;
    QString stationCode;
    QDate recordedDate;
    double rainfallMm;
};

#endif
