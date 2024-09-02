#include "screpeatingevent.h"

// SCRepeatingEvent::SCRepeatingEvent() {}

bool SCRepeatingEvent::isOn(QDate& queryDate)
{
    switch (rule)
    {
    case SCRepeatingRule::Yearly:
        return (date.month() == queryDate.month() && date.day() == queryDate.day());
    case SCRepeatingRule::Monthly:
        return (date.day() == queryDate.day());
    case SCRepeatingRule::Weekly:
        return (date.dayOfWeek() == queryDate.dayOfWeek());
    case SCRepeatingRule::Daily:
        return true;
    }

    return false;
}

QJsonObject SCRepeatingEvent::toJson() const
{
    QJsonObject json;

    json["type"] = "SCRepeatingEvent";
    json["title"] = title;
    json["description"] = description;
    json["date"] = date.toString(Qt::ISODate);
    json["repeatingRule"] = static_cast<int>(rule); // ?

    return json;
}

SCRepeatingEvent *SCRepeatingEvent::fromJson(const QJsonObject &json)
{
    QString title = json["title"].toString();
    QString description = json["description"].toString();
    QDate date = QDate::fromString(json["date"].toString(), Qt::ISODate);
    SCRepeatingRule rule = static_cast<SCRepeatingRule>(json["repeatingRule"].toInt());

    return new SCRepeatingEvent(title, description, date, rule);
}
