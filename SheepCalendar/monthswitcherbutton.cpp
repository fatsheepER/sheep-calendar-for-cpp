#include "monthswitcherbutton.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

MonthSwitcherButton::MonthSwitcherButton(int initialMonth, QWidget *parent)
    : QWidget{parent}
{
    monthLabel = new QLabel("某月", this);
    prevButton = new QPushButton("<", this);
    nextButton = new QPushButton(">", this);

    setMonth(initialMonth);
    prevButton->setStyleSheet("background-color: transparent;");
    prevButton->setFixedSize(35, 35);
    nextButton->setStyleSheet("background-color: transparent;");
    nextButton->setFixedSize(35, 35);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(prevButton);
    layout->addWidget(monthLabel);
    layout->addWidget(nextButton);
    layout->setContentsMargins(0, 0, 0, 0);  // 去掉布局边距
    layout->setSpacing(10);  // 设置按钮和标签之间的间距

    monthLabel->setAlignment(Qt::AlignCenter);
    monthLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // setFixedSize(115, 50);
    setStyleSheet("#MonthSwitchButton {background-color:#4d4d4d;color:#ffffff;border-radius:20px;}");

    connect(prevButton, &QPushButton::clicked, this, &MonthSwitcherButton::onPrevButtonClicked);
    connect(nextButton, &QPushButton::clicked, this, &MonthSwitcherButton::onNextButtonClicked);
}

void MonthSwitcherButton::setMonth(const int monthIndex)
{
    if (monthIndex <= 0 || monthIndex > 12)
    {
        currentMonth = -1;
        return;
    }

    currentMonth = monthIndex;

    QLocale locale(QLocale::Chinese, QLocale::China);
    QString monthName = locale.monthName(currentMonth);
    monthLabel->setText(monthName);
}

void MonthSwitcherButton::onPrevButtonClicked()
{
    emit monthHasChanged(-1);
}

void MonthSwitcherButton::onNextButtonClicked()
{
    emit monthHasChanged(1);
}

void MonthSwitcherButton::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
