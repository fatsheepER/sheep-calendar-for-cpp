#ifndef MONTHSWITCHERBUTTON_H
#define MONTHSWITCHERBUTTON_H

#include <QWidget>

class QLabel;
class QPushButton;

class MonthSwitcherButton : public QWidget
{
    Q_OBJECT
public:
    explicit MonthSwitcherButton(int initialMonth, QWidget *parent = nullptr);

signals:
    void monthHasChanged(int offset); // 前后切换
    void monthHasChangedBack(); // 回到当前

public slots:
    void setMonth(int yearIndex, int monthIndex);
    void onPrevButtonClicked();
    void onNextButtonClicked();
    void onCenterButtonClicked();

private:
    int currentMonth;
    QPushButton* prevButton;
    QPushButton* nextButton;
    QPushButton* centerButton;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MONTHSWITCHERBUTTON_H
