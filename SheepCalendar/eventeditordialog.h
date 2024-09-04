#ifndef EVENTEDITORDIALOG_H
#define EVENTEDITORDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QLabel>

#include "scevent.h"

class EventEditorDialog : public QDialog
{
    Q_OBJECT
public:
    EventEditorDialog(QWidget *parent = nullptr);

private:
    QComboBox *eventTypeComboBox;
    QLineEdit *titleEdit;
    QTextEdit *descriptionEdit;
    QDateEdit *dateEdit;
    QComboBox *repeatingRuleComboBox;
    QLabel *repeatingRuleLabel;
    QComboBox *calendarTypeComboBox;
    QLabel *calendarTypeLabel;
    QPushButton *saveButton;
    QPushButton *cancelButton;

public:
    SCEvent* createEvent(); // 根据当前填写的内容创建新的习惯 可能加一点空值检查会更好

private:
    void setupUI();

private slots:
    void changeEventType(int index); // 根据下拉框的事件类型 index 决定展示哪些编辑框
};

#endif // EVENTEDITORDIALOG_H
