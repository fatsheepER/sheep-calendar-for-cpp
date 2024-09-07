#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

#include "scevent.h"

class EventManager : public QObject
{
    Q_OBJECT
public:
    explicit EventManager(QObject *parent = nullptr);
    ~EventManager();

private:
    std::vector<SCEvent*> events;

public:
    std::vector<SCEvent*>& getEvents();
    void addEvent(SCEvent* event);
    void clearEvents();

public slots:
    void loadEventsFromJson(const QString filePath);
    void saveEventsToJson(const QString filePath);
};

#endif // EVENTMANAGER_H
