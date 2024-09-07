#include "scfestival.h"
#include "LunarSolarConverter.h"

#include <QDate>

SCFestival::SCFestival(const QString _title, const QString _description, const QDate& _date, SCCalendarType _ct):
    SCEvent(_title, _description, _date),
    SCDayEvent(_title, _description, _date),
    SCRepeatingEvent(_title, _description, _date, SCRepeatingRule::Yearly),
    ct(_ct)
    { }

bool SCFestival::isOn(QDate &queryDate)
{
    // qDebug() << "SCFestival::isOn() called!";

    if (ct == SCCalendarType::Solar)
        return SCRepeatingEvent::isOn(queryDate);

    // 将 queryDate 转换为农历 判断月、日
    Solar sd;
    sd.solarDay = queryDate.day();
    sd.solarMonth = queryDate.month();
    sd.solarYear = queryDate.year();

    Lunar ld = SolarToLunar(sd);
    return (date.month() == ld.lunarMonth && date.day() == ld.lunarDay);
}

QJsonObject SCFestival::toJson() const
{
    QJsonObject json;

    json["type"] = "SCFestival";
    json["title"] = title;
    json["description"] = description;
    json["date"] = date.toString(Qt::ISODate);
    json["calendarType"] = static_cast<int>(ct);

    return json;
}

SCFestival *SCFestival::fromJson(const QJsonObject &json)
{
    QString title = json["title"].toString();
    QString description = json["description"].toString();
    QDate date = QDate::fromString(json["date"].toString(), Qt::ISODate);
    SCCalendarType ct = static_cast<SCCalendarType>(json["calendarType"].toInt());

    return new SCFestival(title, description, date, ct);
}
