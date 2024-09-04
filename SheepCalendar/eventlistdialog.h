#ifndef EVENTLISTDIALOG_H
#define EVENTLISTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

#include "scevent.h"

class EventListDialog : public QDialog
{
    Q_OBJECT
public:
    EventListDialog(std::vector<SCEvent*>& events, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    std::vector<SCEvent*>& events;

    void setupUI();

private slots:
    void removeEvent(int index); // 删除某一事件
};

#endif // EVENTLISTDIALOG_H
