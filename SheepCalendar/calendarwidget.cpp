#include "calendarwidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QStringList>
#include <QString>
#include <QDate>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

CalendarWidget::CalendarWidget(QWidget *parent)
    : QWidget{parent}
{
    setupLayout();
    loadEventsFromJson("testData.json");
    updateCalendar(QDate::currentDate().year(), QDate::currentDate().month());
}

void CalendarWidget::updateCalendar(int year, int month)
{
    QDate firstDayOfMonth = QDate(year, month, 1);

    int startColumn = firstDayOfMonth.dayOfWeek() % 7;
    int daysInMonth = firstDayOfMonth.daysInMonth();
    int day = 1;

    // 清空之前的日期
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            dayLabels[row][col]->clear();
        }
    }

    // 填充日期和事件 暂时还没有完成事件类的设计
    for (int row = 0; row < 6; row++)
    {
        for (int col = startColumn; col < 7; col++)
        {
            if (day > daysInMonth)
                return;

            QDate cellDate = QDate(year, month, day);

            // 设置日期
            dayLabels[row][col]->setDate(day);


            // 设定日期字体风格
            bool isToday = (cellDate == QDate::currentDate());
            dayLabels[row][col]->setLabelStyle(isToday);

            // 遍历事件 检测
            for (SCEvent* eve: events)
            {
                if (eve->isOn(cellDate))
                {
                    qDebug() << "Adding event!";
                    // 后期应当修改为 cell 储存 event*，供小窗口访问
                    dayLabels[row][col]->addEvent(eve->getTitle());
                }
            }

            // 向上对齐 还得专门写个方法 烦
            dayLabels[row][col]->addStretch();

            // 仅作示范用：添加几个固定事件 后期删除
            // dayLabels[row][col]->addEvent("农历新年");
            // dayLabels[row][col]->addEvent("高级程序语言设计 王琼");
            // dayLabels[row][col]->addEvent("生日");

            day++;
        }
        startColumn = 0; // 重置列，从下周的第一天开始
    }
}

void CalendarWidget::setupLayout()
{
    calendarLayout = new QGridLayout(this);

    QStringList days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // 初始化星期指示条
    for (int i = 0; i < 7; i++)
    {
        weekLabels[i] = new QLabel(days[i], this);
        weekLabels[i]->setStyleSheet("font-size: 18px; font-weight: bold;");
        weekLabels[i]->setAlignment(Qt::AlignRight);
        weekLabels[i]->setMinimumHeight(20);
        calendarLayout->addWidget(weekLabels[i], 0, i);
    }

    // 在行的底部添加一条水平线
    QFrame *hLine = new QFrame(this);
    hLine->setFrameShape(QFrame::HLine); // 设置为水平线
    hLine->setFrameShadow(QFrame::Sunken); // 设置阴影样式（可选）
    calendarLayout->addWidget(hLine, 0, 0, 1, 7);

    // 初始化日期 最多 6 行 7 列
    for (int row = 0; row < 6; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            dayLabels[row][col] = new DateCellWidget(this);
            dayLabels[row][col]->setMinimumSize(50, 40);
            dayLabels[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            calendarLayout->addWidget(dayLabels[row][col], row + 1, col);
        }

        // 行底部水平线
        calendarLayout->addWidget(hLine, row + 1, 0, 1, 7); // 添加水平线，跨越所有7列
    }

    setLayout(calendarLayout);
}

void CalendarWidget::loadEventsFromJson(const QString filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "打开文件失败";
        return;
    }

    QByteArray fileData = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonArray eventsArray = doc.array();

    for (const QJsonValue &value: eventsArray)
    {
        QJsonObject json = value.toObject();
        SCEvent *event = SCEvent::fromJson(json);
        if (event)
        {
            events.emplace_back(event);
            qDebug() << event->getTitle();
        }
    }

    qDebug() << "读取文件成功！";

    file.close();
}
