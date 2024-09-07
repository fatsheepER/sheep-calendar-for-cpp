#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "datecellwidget.h"
#include "scevent.h"
#include "eventmanager.h"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);

signals:

public slots:
    void updateCalendar(int year, int month);
    void addEvent(SCEvent *event);
    void saveEventsToJson(const QString filePath);
    void editEventsInDialog();

private:
    QGridLayout *calendarLayout;
    QLabel* weekLabels[7];
    DateCellWidget* dayLabels[6][7];
    // std::vector<SCEvent*> events;
    EventManager manager;
private:

    void setupLayout(); // // 初始化布局
    void loadEventsFromJson(const QString filePath); // 从 Json 文件中读取 Event 对 events
};

#endif // CALENDARWIDGET_H
