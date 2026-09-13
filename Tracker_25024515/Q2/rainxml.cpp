#include "rainxml.h"
#include "../Q1/rainrecord.h"
#include <QXmlStreamWriter>

RainXml::RainXml()
    : re("^([A-Z])[a-z]{2}\\1[1-9][0-9]{2}$")
{
}

RainXml &RainXml::getInstance()
{
    static RainXml instance;
    return instance;
}

bool RainXml::checkStationCode(const QString &stn) const
{
    return re.match(stn).hasMatch();
}

QString RainXml::writeToXml(const QList<RainRecord *> &records) const
{
    QString xmlOutput;
    QXmlStreamWriter writer(&xmlOutput);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("rainRecord");

    for (const RainRecord *r : records) {
        if (!r || !checkStationCode(r->station()))
            continue;

        writer.writeStartElement("rain");
        writer.writeAttribute("date", r->date().toString("yyyy/MM/dd"));
        writer.writeTextElement("station", r->station());
        writer.writeTextElement("mm", QString::number(r->mm(), 'g', 15));
        writer.writeEndElement();
    }

    writer.writeEndElement();
    writer.writeEndDocument();
    return xmlOutput;
}
