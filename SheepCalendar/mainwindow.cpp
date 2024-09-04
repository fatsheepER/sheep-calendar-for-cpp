#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtWidgets>

#include "monthswitcherbutton.h"
#include "calendarwidget.h"
#include "scevent.h"
#include "screpeatingevent.h"
#include "scfestival.h"
#include "screpeatingrule.h"
#include "sccalendartype.h"
#include "eventeditordialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Sheep Calendar v0.0.1");
    setMinimumSize(800, 650);

    // 初始化日期为当前日期
    setupCurrentDate();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 设置日期定时检查
    dateCheckTimer = new QTimer(this);
    dateCheckTimer->start(60000);

    // 主布局将界面分为上下两部分
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // 上部分包括年份，月份切换，显示模式切换和星期指示条
    QWidget *topWidget = new QWidget(centralWidget);
    QVBoxLayout *topLayout = new QVBoxLayout(topWidget);
    topLayout->setSpacing(5);
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget, 0); // 不伸张

    // 年份显示
    yearLabel = new QLabel(QString::number(currentDate.year()), topWidget);
    yearLabel->setStyleSheet("font-size: 45px; font-weight: bold;");
    yearLabel->setAlignment(Qt::AlignRight);
    topLayout->addWidget(yearLabel);

    // 添加事件 编辑 保存 || 月份切换
    QHBoxLayout *monthSwitcherLayout = new QHBoxLayout();
    topLayout->addLayout(monthSwitcherLayout);

    // 添加事件
    addButton = new QPushButton("添加事件", topWidget);
    monthSwitcherLayout->addWidget(addButton);

    // 打开编辑列表
    editButton = new QPushButton("编辑");
    monthSwitcherLayout->addWidget(editButton);

    // 保存至 Json 文件
    saveButton = new QPushButton("保存", topWidget);
    monthSwitcherLayout->addWidget(saveButton);

    // 月份切换
    monthSwitcher = new MonthSwitcherButton(currentDate.month(), topWidget);
    monthSwitcher->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    monthSwitcherLayout->addStretch(); // 整体向右对齐
    monthSwitcherLayout->addWidget(monthSwitcher);

    // 数字时钟
    clockLabel = new QLabel(this);
    clockLabel->setAlignment(Qt::AlignRight);
    clockTimer = new QTimer(this);
    clockTimer->start(1000); // 每秒更新一次
    topLayout->addWidget(clockLabel);

    // 上半部分结束

    // 日历部分
    calendar = new CalendarWidget(centralWidget);
    mainLayout->addWidget(calendar, 3);
    // calendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // 信号连接
    // 前/后切换月份
    connect(monthSwitcher, &MonthSwitcherButton::monthHasChanged,
            this, &MainWindow::changeDate);

    // 回到当前月
    connect(monthSwitcher, &MonthSwitcherButton::monthHasChangedBack,
            this, &MainWindow::changeDateBack);

    // 更新 switcher 的显示月份
    connect(this, &MainWindow::dateHasChanged, monthSwitcher,
            &MonthSwitcherButton::setMonth);

    // 更新 calendar 内容
    connect(this, &MainWindow::dateHasChanged,
            calendar, &CalendarWidget::updateCalendar);

    // 点击新建事件
    connect(addButton, &QPushButton::clicked,
            this, &MainWindow::onAddButtonClicked);

    // 向 calendar 新增事件
    connect(this, &MainWindow::newEventCreated,
            calendar, &CalendarWidget::addEvent);

    // 点击保存
    connect(saveButton, &QPushButton::clicked,
            this, &MainWindow::onSaveButtonClicked);

    // 向文件保存
    connect(this, &MainWindow::saveEvents,
            calendar, &CalendarWidget::saveEventsToJson);

    // 点击编辑
    connect(editButton, &QPushButton::clicked,
            this, &MainWindow::onEditButtonClicked);

    // 在 dialog 中编辑
    connect(this, &MainWindow::editEvents,
            calendar, &CalendarWidget::editEventsInDialog);

    // 更新文字时间
    connect(clockTimer, &QTimer::timeout,
            this, &MainWindow::updateClock);

    // 检查日期变更 自动翻页
    connect(dateCheckTimer, &QTimer::timeout,
            this, &MainWindow::checkDateChange);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClock()
{
    QString currentTime = QTime::currentTime().toString("HH:mm:ss");
    clockLabel->setText(currentTime);
}

void MainWindow::checkDateChange()
{
    if (QDate::currentDate().month() != lastCheckedDate.month())
    {
        changeDateBack(); // 正好可以复用
    }
}

void MainWindow::changeDate(int offset)
{
    currentDate = currentDate.addMonths(offset);

    // 更新年份 转到 monthSwitcher 会更好？
    yearLabel->setText(QString::number(currentDate.year()));

    emit dateHasChanged(currentDate.year(), currentDate.month());
}

void MainWindow::changeDateBack()
{
    currentDate = QDate::currentDate();

    yearLabel->setText(QString::number(currentDate.year()));

    emit dateHasChanged(currentDate.year(), currentDate.month());
}

void MainWindow::onAddButtonClicked()
{
    EventEditorDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) // 用户选择保存
    {
        SCEvent *event = dialog.createEvent();
        if (event)
        {
            emit newEventCreated(event);
        }
    }
}

void MainWindow::onSaveButtonClicked()
{
    emit saveEvents("testData.json");
}

void MainWindow::onEditButtonClicked()
{
    emit editEvents();
}

void MainWindow::setupCurrentDate()
{
    // 将日期设置为当前月份的第一天 更稳妥
    currentDate = QDate::currentDate().addDays(1 - QDate::currentDate().day());
    lastCheckedDate = currentDate;
}
