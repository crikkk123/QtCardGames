#ifndef ROBOTPLAYHAND_H
#define ROBOTPLAYHAND_H

#include <QThread>
#include "robot.h"

class RobotPlayHand : public QThread
{
    Q_OBJECT
public:
    explicit RobotPlayHand(Robot* player,QObject *parent = nullptr);

signals:

protected:
    void run() override;

private:
    Robot* m_player;
};

#endif // ROBOTPLAYHAND_H
