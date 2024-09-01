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
    void monthHasChanged(int offset);

public slots:
    void setMonth(int yearIndex, int monthIndex);
    void onPrevButtonClicked();
    void onNextButtonClicked();

private:
    int currentMonth;
    QLabel* monthLabel;
    QPushButton* prevButton;
    QPushButton* nextButton;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // MONTHSWITCHERBUTTON_H
