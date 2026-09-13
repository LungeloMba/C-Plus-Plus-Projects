#include "rainrecord.h"

RainRecord::RainRecord(const QString &station, const QDate &date, double mm, QObject *parent)
    : QObject(parent), stationCode(station), recordedDate(date), rainfallMm(mm)
{
}

QString RainRecord::station() const
{
    return stationCode;
}

QDate RainRecord::date() const
{
    return recordedDate;
}

double RainRecord::mm() const
{
    return rainfallMm;
}

QString RainRecord::getData() const
{
    return stationCode + ":" + recordedDate.toString("yyyyMMdd") + ":" + QString::number(rainfallMm, 'g', 15);
}
