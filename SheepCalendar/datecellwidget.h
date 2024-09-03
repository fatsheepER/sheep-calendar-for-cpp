#ifndef DATECELLWIDGET_H
#define DATECELLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class DateCellWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateCellWidget(QWidget *parent = nullptr);

signals:

private:
    QLabel *dateLabel;
    QVBoxLayout* layout;

public:
    void setDate(int date); // 设置日期
    void addEvent(QString event); // 添加新的事件
    void addStretch(); // 添加弹簧 向上对齐
    void setLabelStyle(bool isToday); // 设置日期风格 如果是今天就粗体标红
    void clear(); // 清空自己的信息
};

#endif // DATECELLWIDGET_H
