#include "eventeditordialog.h"
#include "scdayevent.h"
#include "screpeatingevent.h"
#include "scfestival.h"
#include "screpeatingrule.h"
#include "sccalendartype.h"

#include <QVBoxLayout>
#include <QLabel>

EventEditorDialog::EventEditorDialog(QWidget *parent): QDialog(parent)
{
    setupUI();

    connect(eventTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &EventEditorDialog::changeEventType);
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

SCEvent *EventEditorDialog::createEvent()
{
    QString title = titleEdit->text();
    QString description = descriptionEdit->toPlainText();
    QDate date = dateEdit->date();

    int typeIndex = eventTypeComboBox->currentIndex();
    if (typeIndex == 0) // 全天事件
    {
        return new SCDayEvent(title, description, date);
    }
    else if (typeIndex == 1) // 重复事件
    {
        int repeatingRuleIndex = repeatingRuleComboBox->currentIndex();
        SCRepeatingRule rule = static_cast<SCRepeatingRule>(repeatingRuleIndex);
        return new SCRepeatingEvent(title, description, date, rule);
    }
    else if (typeIndex == 2) // 节日
    {
        int calendarTypeIndex = calendarTypeComboBox->currentIndex();
        SCCalendarType type = static_cast<SCCalendarType>(calendarTypeIndex);
        return new SCFestival(title, description, date, type);
    }

    qDebug() << "OH NO!";
    return nullptr; // 不会吧
}

void EventEditorDialog::setupUI()
{
    setWindowTitle("创建新事件");

    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);

    // 事件类型
    eventTypeComboBox = new QComboBox(this);
    eventTypeComboBox->addItems({"全天时间", "重复事件", "节日"});
    layout->addWidget(new QLabel("事件类型"));
    layout->addWidget(eventTypeComboBox);

    // 标题
    titleEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("标题", this));
    layout->addWidget(titleEdit);

    // 描述
    descriptionEdit = new QTextEdit(this);
    layout->addWidget(new QLabel("描述", this));
    layout->addWidget(descriptionEdit);

    // 日期
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    layout->addWidget(new QLabel("日期", this));
    layout->addWidget(dateEdit);

    // 重复规则 - 重复事件/节日
    repeatingRuleComboBox = new QComboBox(this);
    repeatingRuleComboBox->addItems({"每年", "每月", "每周", "每日"});
    repeatingRuleLabel = new QLabel("重复规则", this);
    layout->addWidget(repeatingRuleLabel);
    layout->addWidget(repeatingRuleComboBox);

    // 历法 - 节日
    calendarTypeComboBox = new QComboBox(this);
    calendarTypeComboBox->addItems({"公历", "农历"});
    calendarTypeLabel = new QLabel("历法");
    layout->addWidget(calendarTypeLabel);
    layout->addWidget(calendarTypeComboBox);

    // 保存 取消
    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    saveButton = new QPushButton("保存", this);
    cancelButton = new QPushButton("取消", this);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    // 默认是全天事件 所以隐藏两个下拉框
    repeatingRuleComboBox->hide();
    repeatingRuleLabel->hide();
    calendarTypeComboBox->hide();
    calendarTypeLabel->hide();
}

void EventEditorDialog::changeEventType(int index)
{
    if (index == 0) // 全天事件
    {
        repeatingRuleComboBox->hide();
        repeatingRuleLabel->hide();
        calendarTypeComboBox->hide();
        calendarTypeLabel->hide();
    }
    else if (index == 1) // 重复事件
    {
        repeatingRuleComboBox->show();
        repeatingRuleLabel->show();
        calendarTypeComboBox->hide();
        calendarTypeLabel->hide();
    }
    else if (index == 2) // 节日
    {
        repeatingRuleComboBox->hide();
        repeatingRuleLabel->hide();
        calendarTypeComboBox->show();
        calendarTypeLabel->show();
    }
}
