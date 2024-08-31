#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtWidgets>

#include "monthswitcherbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Sheep Calendar v0.0.1");
    setMinimumSize(800, 600);
    updateDate();

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 主布局将界面分为上下两部分
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    // 上部分包括年份，月份切换，显示模式切换和星期指示条
    QWidget *topWidget = new QWidget(centralWidget);
    QVBoxLayout *topLayout = new QVBoxLayout(centralWidget);
    topLayout->setSpacing(5);
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);

    // 年份显示
    yearLabel = new QLabel(QString::number(currentYear));
    yearLabel->setStyleSheet("font-size: 45px; font-weight: bold;");
    yearLabel->setAlignment(Qt::AlignRight);
    topLayout->addWidget(yearLabel);

    // 月份切换
    QHBoxLayout *monthSwitcherLayout = new QHBoxLayout(centralWidget);
    topLayout->addLayout(monthSwitcherLayout);
    monthSwitcher = new MonthSwitcherButton(currentMonth, topWidget);
    monthSwitcher->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    monthSwitcherLayout->addStretch();
    monthSwitcherLayout->addWidget(monthSwitcher);

    topLayout->addStretch();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDate()
{
    QDate currentDate = QDate::currentDate();
    currentYear = currentDate.year();
    currentMonth = currentDate.month();
    currentDay = currentDate.day();
}
