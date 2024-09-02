#include "scevent.h"
#include "scdayevent.h"
#include "screpeatingevent.h"
#include "scfestival.h"

SCEvent* SCEvent::fromJson(const QJsonObject &json)
{
    QString type = json["type"].toString();

    // 根据类型选择具体转换方法
    if (type == "SCDayEvent")
    {
        return SCDayEvent::fromJson(json);
    }
    else if (type == "SCRepeatingEvent")
    {
        return SCRepeatingEvent::fromJson(json);
    }
    else if (type == "SCFestival")
    {
        return SCFestival::fromJson(json);
    }
    else
    {
        qDebug() << "未能识别事件类型！";
        return nullptr;
    }
}
