#ifndef SCDAYEVENT_H
#define SCDAYEVENT_H

#include "scevent.h"

class SCDayEvent :virtual public SCEvent
{
public:
    SCDayEvent(const QString _title, const QString _description, const QDate& _date):
        SCEvent(_title, _description, _date) {}

    // SCEvent interface
public:
    bool isOn(QDate &) override;

    QJsonObject toJson() const override;
    static SCDayEvent* fromJson(const QJsonObject &json);
};

#endif // SCDAYEVENT_H
