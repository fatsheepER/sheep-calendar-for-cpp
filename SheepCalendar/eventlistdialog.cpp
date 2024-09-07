#include "eventlistdialog.h"

#include <QLabel>
#include <QPushButton>

EventListDialog::EventListDialog(std::vector<SCEvent*>& events, QWidget *parent)
    : QDialog(parent), events(events)
{
    layout = new QVBoxLayout(this);
    setWindowTitle("事件列表");
    setLayout(layout);

    setupUI(); // 可能叫 updateUI 会更好
}

void EventListDialog::setupUI()
{
    // 清空旧内容
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        // 每个项目都是一个 HBoxLayout，所以还有一个循环
        QLayout *subLayout = item->layout();
        if (subLayout)
        {
            QLayoutItem *subItem;
            while ((subItem = subLayout->takeAt(0)) != nullptr)
            {
                delete subItem->widget();
                delete subItem;
            }

            delete subLayout;
        }
        else // 可能有不是 layout 的组件
        {
            delete item->widget();
            delete item;
        }

        // delete item;
    }

    // 遍历添加事件
    for (int i = 0; i < events.size(); i++)
    {
        SCEvent *event = events[i];

        QHBoxLayout *rowLayout = new QHBoxLayout();
        layout->addLayout(rowLayout);

        QLabel *label = new QLabel(event->getTitle(), this);
        QPushButton *removeButton = new QPushButton("删除", this);
        rowLayout->addWidget(label);
        rowLayout->addStretch(); // 向两边对齐
        rowLayout->addWidget(removeButton);

        // 使用 lamda 表达式表示 slot
        connect(removeButton, &QPushButton::clicked,
                [this, i]() { removeEvent(i); });
    }
}

void EventListDialog::removeEvent(int index)
{
    if (index < 0 || index >= events.size())
    {
        qDebug() << "删除目标下标不合法！";
        return;
    }

    qDebug() << "Deleting index:" << index;

    events.erase(events.begin() + index);

    setupUI();
}
