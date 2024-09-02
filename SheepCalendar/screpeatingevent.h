#ifndef SCREPEATINGEVENT_H
#define SCREPEATINGEVENT_H

#include "scevent.h"
#include "screpeatingrule.h"

class SCRepeatingEvent: virtual public SCEvent
{
public:
    SCRepeatingEvent(const QString _title, const QString _description, const QDate& _date, SCRepeatingRule _rule):
        SCEvent(_title, _description, _date), rule(_rule) {}

protected:
    SCRepeatingRule rule;

    // SCEvent interface
public:
    bool isOn(QDate &) override;
    QJsonObject toJson() const override;
    static SCRepeatingEvent* fromJson(const QJsonObject &json);
};

#endif // SCREPEATINGEVENT_H
