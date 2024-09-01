#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtWidgets>

#include "monthswitcherbutton.h"
#include "calendarwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Sheep Calendar v0.0.1");
    setMinimumSize(800, 600);

    // 初始化日期为当前日期
    setupCurrentDate();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

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

    // 月份切换
    QHBoxLayout *monthSwitcherLayout = new QHBoxLayout();
    topLayout->addLayout(monthSwitcherLayout);
    monthSwitcher = new MonthSwitcherButton(currentDate.month(), topWidget);
    monthSwitcher->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    monthSwitcherLayout->addStretch(); // 整体向右对齐
    monthSwitcherLayout->addWidget(monthSwitcher);

    // topLayout->addStretch(); // 上半部分结束

    // 日历部分
    calendar = new CalendarWidget(centralWidget);
    mainLayout->addWidget(calendar, 3);
    // calendar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    // 信号连接
    connect(monthSwitcher, &MonthSwitcherButton::monthHasChanged,
            this, &MainWindow::changeDate);

    connect(this, &MainWindow::dateHasChanged, monthSwitcher,
            &MonthSwitcherButton::setMonth);

    connect(this, &MainWindow::dateHasChanged,
            calendar, &CalendarWidget::updateCalendar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeDate(int offset)
{
    currentDate = currentDate.addMonths(offset);

    // 更新年份 以后应该转到 monthSwitcher
    yearLabel->setText(QString::number(currentDate.year()));

    emit dateHasChanged(currentDate.year(), currentDate.month());
}

void MainWindow::setupCurrentDate()
{
    // 将日期设置为当前月份的第一天 更稳妥
    currentDate = QDate::currentDate().addDays(1 - QDate::currentDate().day());

    // 执行此步时其他 widget 还没有完成初始化，所以不用 emit
}
