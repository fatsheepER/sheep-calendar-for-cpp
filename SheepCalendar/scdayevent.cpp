#include "scdayevent.h"

// SCDayEvent::SCDayEvent() {}

bool SCDayEvent::isOn(QDate &queryDate)
{
    return date == queryDate;
}

QJsonObject SCDayEvent::toJson() const
{
    QJsonObject json;
    json["type"] = "SCDayEvent";
    json["title"] = title;
    json["description"] = description;
    json["date"] = date.toString(Qt::ISODate);

    return json;
}

SCDayEvent *SCDayEvent::fromJson(const QJsonObject &json)
{
    QString title = json["title"].toString();
    QString description = json["description"].toString();
    QDate date = QDate::fromString(json["date"].toString(), Qt::ISODate);
    return new SCDayEvent(title, description, date);
}
