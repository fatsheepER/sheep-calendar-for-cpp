#ifndef SCEVENT_H
#define SCEVENT_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class SCEvent
{
protected:
    QString title;
    QString description;
    QDate date;

public:
    SCEvent(const QString _title, const QString& _description, const QDate& _date): title(_title)
        , description(_description), date(_date) {}
    virtual ~SCEvent() = default;
public:
    virtual bool isOn(QDate&) = 0; // 具体判断各种事件是否在该日期上发生

public:
    virtual QJsonObject toJson() const = 0;
    static SCEvent* fromJson(const QJsonObject& jsonObj); // 使用静态方法 根据type字段判断使用哪一种

public:
    // getter
    QString getTitle() { return title; }
    QString getDescription() { return description; }
    QDate getDate() { return date; }

    // setter
    void setTitle(const QString _title) { title = _title; }
    void setDescription(const QString _description) { description = _description; }
    void setDate(const QDate& _date) { date = _date; }; // 在 Schedule 中会有所不同?
    void setDate(int year, int month, int day) { date = QDate(year, month, day); }
};

#endif // SCEVENT_H
