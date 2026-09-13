#ifndef STATIONTHREAD_H
#define STATIONTHREAD_H

#include <QThread>
#include <QList>
#include <QString>

class RainRecord;

class StationThread : public QThread
{
    Q_OBJECT

public:
    StationThread(const QList<RainRecord *> &records, const QString &station, QObject *parent = nullptr);

signals:
    void foundStation(const QString &date, const QString &mm);
    void searchFinished();

protected:
    void run() override;

private:
    QList<RainRecord *> record;
    QString stationCode;
};

#endif
