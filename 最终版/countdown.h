#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QTimer>
#include <QWidget>

class CountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CountDown(QWidget *parent = nullptr);

    void showCountDown();
    void stopCountDown();

signals:
    void notMuchTime();
    void Cardtimeout();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    QPixmap m_clock;
    QPixmap m_number;
    QTimer* m_timer;
    int m_count;        // 倒计时的总时长
};

#endif // COUNTDOWN_H
