#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "datecellwidget.h"

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);

signals:

public slots:
    void updateCalendar(int year, int month);

private:
    QGridLayout *calendarLayout;
    QLabel* weekLabels[7];
    DateCellWidget* dayLabels[6][7];

    void setupLayout();
};

#endif // CALENDARWIDGET_H
