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
    QPushButton *testButton;
    MonthSwitcherButton *monthSwitcher;
    CalendarWidget *calendar;

private:
    QDate currentDate;
    std::vector<SCEvent*> events;

signals:
    void dateHasChanged(int year, int month);

public slots:
    void changeDate(int offset);
    void onTestButtonClicked();

private:
    void setupCurrentDate();
    void loadEventsFromJson(const QString filePath);
    void saveTestDataToJson(const QString filePath);
};
#endif // MAINWINDOW_H
