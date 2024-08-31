#ifndef SCEVENT_H
#define SCEVENT_H

class QString {};
class QDate {};
class QDateTime {};
class SCReminder {};

class SCEvent
{
private:
    QString title;
    QString description;
    QDate date;

public:
    SCEvent();

public:
    virtual bool isOn(QDateTime&) = 0;
    virtual void setDate(QDate&) = 0;
};

#endif // SCEVENT_H
