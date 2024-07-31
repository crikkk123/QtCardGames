#ifndef ROBOTGRAPLORD_H
#define ROBOTGRAPLORD_H

#include <QThread>
#include "robot.h"

class RobotGrapLord : public QThread
{
    Q_OBJECT
public:
    explicit RobotGrapLord(Robot* player,QObject *parent = nullptr);

protected:
    void run();
signals:

private:
    Robot* m_player;
};

#endif // ROBOTGRAPLORD_H
