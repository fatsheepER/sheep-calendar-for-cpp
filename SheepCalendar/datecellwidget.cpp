#include "datecellwidget.h"

#include <QLabel>
#include <QVBoxLayout>

DateCellWidget::DateCellWidget(QWidget *parent)
    : QWidget{parent}
{
    dateLabel = new QLabel(this);
    dateLabel->setStyleSheet("font-size: 20px;");
    layout = new QVBoxLayout(this);
    layout->addWidget(dateLabel);
    setLayout(layout);
}

void DateCellWidget::setDate(int date)
{
    dateLabel->setText(QString::number(date));
}

// 暂时使用 QString，未来会使用 QEvent 代替
void DateCellWidget::addEvent(QString event)
{
    QLabel *eventLabel = new QLabel(event, this);
    layout->addWidget(eventLabel);
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
