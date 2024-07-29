#ifndef BGMCONTROL_H
#define BGMCONTROL_H

#include <QObject>

class BGMControl : public QObject
{
    Q_OBJECT
public:
    explicit BGMControl(QObject *parent = nullptr);

signals:
};

#endif // BGMCONTROL_H
