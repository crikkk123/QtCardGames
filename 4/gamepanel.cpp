#include "gamepanel.h"
#include "ui_gamepanel.h"

#include <QPainter>
#include <QRandomGenerator>

GamePanel::GamePanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GamePanel)
{
    ui->setupUi(this);

    ui->btnGroup->initButtons();
    ui->btnGroup->selectPanel(ButtonGroup::start);

    // 1、背景图
    int num = QRandomGenerator::global()->bounded(10);
    QString path = QString(":/images/background-%1.png").arg(num+1);
    m_bkImage.load(path);
    // 2、窗口的标题大小
    this->setWindowTitle("欢乐斗地主");
    this->setFixedSize(1000,650);
    // 3、实例化游戏控制类对象
    gameControlInit();

    // 4、玩家得分(更新)
    updatePlayerScore();

    // 5、切割游戏图片  :/images/card.png
    // 6、初始化游戏按钮
    // 7、初始化玩家在窗口的上下文环境（放牌的位置和头像显示的位置）
}

GamePanel::~GamePanel()
{
    delete ui;
}

void GamePanel::gameControlInit()
{
    m_gameCtl = new GameControl(this);  // 给m_gameCtl指定一个父对象作用是gamePanel这个窗口析构的时候会提前把m_gameCtl释放
    m_gameCtl->playerInit();    // 创建了三个玩家对象
    // 得到三个玩家的实例对象
    Robot* leftRobot = m_gameCtl->getLeftRobot();
    Robot* rightRobot = m_gameCtl->getRightRobot();
    UserPlayer* user = m_gameCtl->getUserPlayer();
    // 存储的顺序：左侧机器人、右侧机器人、当前玩家
    m_playList<<leftRobot<<rightRobot<<user;
}

void GamePanel::updatePlayerScore()
{
    ui->scorePanel->setScores(m_playList[0]->getScore(),
                              m_playList[1]->getScore(),
                              m_playList[2]->getScore());
}

void GamePanel::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_bkImage);
}

