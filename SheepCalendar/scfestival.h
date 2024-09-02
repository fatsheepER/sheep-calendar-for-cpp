#ifndef SCFESTIVAL_H
#define SCFESTIVAL_H

#include "scdayevent.h"
#include "screpeatingevent.h"
#include "sccalendartype.h"


class SCFestival : public SCDayEvent, public SCRepeatingEvent
{
public:
    SCFestival(const QString _title, const QString _description, const QDate& _date, SCCalendarType _ct);

    // SCEvent interface
public:
    bool isOn(QDate &) override;

private:
    SCCalendarType ct;

    // SCEvent interface
public:
    QJsonObject toJson() const override;
    static SCFestival* fromJson(const QJsonObject &json);
};

#endif // SCFESTIVAL_H
