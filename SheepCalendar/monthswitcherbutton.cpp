#include "monthswitcherbutton.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDate>

MonthSwitcherButton::MonthSwitcherButton(int initialMonth, QWidget *parent)
    : QWidget{parent}
{
    centerButton = new QPushButton("某月", this);
    prevButton = new QPushButton("<", this);
    nextButton = new QPushButton(">", this);

    setMonth(QDate::currentDate().year(), initialMonth);
    centerButton->setStyleSheet("background-color: transparent;");
    centerButton->setFixedSize(70, 35);

    prevButton->setStyleSheet("background-color: transparent;");
    prevButton->setFixedSize(35, 35);
    nextButton->setStyleSheet("background-color: transparent;");
    nextButton->setFixedSize(35, 35);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(prevButton);
    layout->addWidget(centerButton);
    layout->addWidget(nextButton);
    layout->setContentsMargins(0, 0, 0, 0);  // 去掉布局边距
    layout->setSpacing(10);  // 设置按钮和标签之间的间距

    setStyleSheet("#MonthSwitchButton {background-color:#4d4d4d;color:#ffffff;border-radius:20px;}");

    connect(prevButton, &QPushButton::clicked, this, &MonthSwitcherButton::onPrevButtonClicked);
    connect(nextButton, &QPushButton::clicked, this, &MonthSwitcherButton::onNextButtonClicked);
    connect(centerButton, &QPushButton::clicked, this, &MonthSwitcherButton::onCenterButtonClicked);
}

void MonthSwitcherButton::setMonth(int yearIndex, int monthIndex)
{
    Q_UNUSED(yearIndex);

    if (monthIndex <= 0 || monthIndex > 12)
    {
        currentMonth = -1;
        return;
    }

    currentMonth = monthIndex;

    // 通过本地化获取月份的中文名 是不是很聪明
    QLocale locale(QLocale::Chinese, QLocale::China);
    QString monthName = locale.monthName(currentMonth);
    centerButton->setText(monthName);
}

void MonthSwitcherButton::onPrevButtonClicked()
{
    emit monthHasChanged(-1);
}

void MonthSwitcherButton::onNextButtonClicked()
{
    emit monthHasChanged(1);
}

void MonthSwitcherButton::onCenterButtonClicked()
{
    emit monthHasChangedBack();
}

void MonthSwitcherButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
