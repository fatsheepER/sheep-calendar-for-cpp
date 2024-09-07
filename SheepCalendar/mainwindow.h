#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "monthswitcherbutton.h"
#include "calendarwidget.h"
#include "scevent.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// ui stuff
private:
    Ui::MainWindow *ui;
    QLabel *yearLabel;
    QLabel *clockLabel;
    QTimer *clockTimer;
    QTimer *dateCheckTimer;
    MonthSwitcherButton *monthSwitcher;
    CalendarWidget *calendar;
    QPushButton *addButton;
    QPushButton *saveButton;
    QPushButton *editButton;

private:
    QDate currentDate; // 当前展示的日期
    QDate lastCheckedDate; // 上一次日期检查时的日期 只要月份不变就不会更新

signals:
    void dateHasChanged(int year, int month);
    void newEventCreated(SCEvent *event);
    void saveEvents(const QString filePath);
    void editEvents();

public slots:
    void updateClock();
    void checkDateChange();
    void changeDate(int offset);
    void changeDateBack();
    void onAddButtonClicked();
    void onSaveButtonClicked();
    void onEditButtonClicked();

private:
    void setupCurrentDate();
};
#endif // MAINWINDOW_H
