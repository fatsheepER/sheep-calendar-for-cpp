#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "monthswitcherbutton.h"
#include "calendarwidget.h"

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

private:
    Ui::MainWindow *ui;
    QLabel *yearLabel;
    MonthSwitcherButton *monthSwitcher;
    CalendarWidget *calendar;

private:
    QDate currentDate;

signals:
    void dateHasChanged(int year, int month);

public slots:
    void changeDate(int offset);

private:
    void setupCurrentDate();
};
#endif // MAINWINDOW_H
