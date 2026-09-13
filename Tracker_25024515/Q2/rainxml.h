#ifndef RAINXML_H
#define RAINXML_H

#include <QString>
#include <QRegularExpression>
#include <QList>

class RainRecord;

class RainXml
{
public:
    static RainXml &getInstance();
    QString writeToXml(const QList<RainRecord *> &records) const;
    bool checkStationCode(const QString &stn) const;

    RainXml(const RainXml &) = delete;
    RainXml &operator=(const RainXml &) = delete;

private:
    RainXml();
    QRegularExpression re;
};

#endif
