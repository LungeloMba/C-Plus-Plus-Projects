#include "stationthread.h"
#include "../Q1/rainrecord.h"

StationThread::StationThread(const QList<RainRecord *> &records, const QString &station, QObject *parent)
    : QThread(parent), record(records), stationCode(station)
{
}

void StationThread::run()
{
    for (RainRecord *r : record) {
        if (r && r->station() == stationCode)
            emit foundStation(r->date().toString("yyyy/MM/dd"), QString::number(r->mm(), 'g', 15));
    }
    emit searchFinished();
}
