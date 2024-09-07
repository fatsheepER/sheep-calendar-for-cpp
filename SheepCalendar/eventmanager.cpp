#include "eventmanager.h"

EventManager::EventManager(QObject *parent)
    : QObject{parent}
{

}

EventManager::~EventManager()
{
    if (!events.empty())
    {
        for (SCEvent *event: events)
        {
            delete event;
        }
    }
}

std::vector<SCEvent *> &EventManager::getEvents()
{
    return events;
}

void EventManager::addEvent(SCEvent *event)
{
    events.emplace_back(event);
}

void EventManager::clearEvents()
{
    events = {};
}

void EventManager::loadEventsFromJson(const QString filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "打开文件失败";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray eventsArray = doc.array();

    for (const QJsonValue &value: eventsArray)
    {
        QJsonObject json = value.toObject();
        SCEvent *event = SCEvent::fromJson(json);
        if (event)
        {
            events.emplace_back(event);
            qDebug() << event->getTitle();
        }
    }

    qDebug() << "读取文件成功！";

    file.close();
}

void EventManager::saveEventsToJson(const QString filePath)
{
    // 创建 Json 数组
    QJsonArray jsonArray;
    for (SCEvent *eve: events)
    {
        jsonArray.append(eve->toJson());
    }

    // 创建 Json 文档
    QJsonDocument jsonDocument(jsonArray);

    // 写入路径
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "无法写入目标路径！";
        return;
    }

    file.write(jsonDocument.toJson());
    file.close();

    qDebug() << "数据保存成功！";
}
