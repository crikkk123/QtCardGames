#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QMainWindow>
#include "gamecontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GamePanel; }
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();

    // 初始化游戏控制类信息
    void gameControlInit();
    // 更新分数面板的分数
    void updatePlayerScore();

protected:
    void paintEvent(QPaintEvent* ev);

private:
    Ui::GamePanel *ui;
    QPixmap m_bkImage;  // 背景图片
    GameControl* m_gameCtl;
    QVector<Player*> m_playList;
};
#endif // GAMEPANEL_H
