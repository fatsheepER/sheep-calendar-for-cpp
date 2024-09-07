#include "datecellwidget.h"

#include <QLabel>
#include <QVBoxLayout>

DateCellWidget::DateCellWidget(QWidget *parent)
    : QWidget{parent}
{
    dateLabel = new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(dateLabel);
    setLayout(layout);
}

void DateCellWidget::setDate(int date)
{
    dateLabel->setText(QString::number(date));
}


void DateCellWidget::addEvent(QString event)
{
    QLabel *eventLabel = new QLabel(event, this);
    layout->addWidget(eventLabel);
}

void DateCellWidget::addStretch()
{
    layout->addStretch();
}

void DateCellWidget::setLabelStyle(bool isToday)
{
    if (isToday)
    {
        dateLabel->setStyleSheet("color: #E34F41; font-size: 20px; font-weight: bold;");
    }
    else
    {
        dateLabel->setStyleSheet("font-size: 20px;");
    }
}

void DateCellWidget::clear()
{
    // 清空日期文字
    dateLabel->clear();

    // 清空所有事件
    QLayoutItem *child;
    while ( (child = layout->takeAt(1)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}
