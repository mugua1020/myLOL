#include "mainscene.h"
#include "config.h"
#include <QTime>
#include "gamescene.h"

/*  MainScene是关于首页的类，有几个按钮和选择、教程两个页面等变量 */

MainScene::MainScene(QWidget* parent) :
    QDialog(parent)
{
    // 初始配置
    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setMouseTracking(true);
    m_background.load(MAIN_SCENE_BACKGROUND_PATH);
    m_bgm = new QSound(BGM_PATH, this);
    m_bgm->setLoops(QSound::Infinite);
    m_bgm->play();

    // 设置三个按键
    QPixmap m_pixmap0 = QPixmap(MAIN_SCENE_GUIDE_BUTTON_PATH);
    QPixmap m_pixmap1 = QPixmap(MAIN_SCENE_ONE_PLAYER_BUTTON_PATH);
    QPixmap m_pixmap2 = QPixmap(MAIN_SCENE_TWO_PLAYERS_BUTTON_PATH);

    // 按键1：显示教程
    m_button[0] = new ClickLabel(400, 120, m_pixmap0, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[0]->setGeometry(610, 450, 400, 120);
    m_button[0]->raise();
    m_button[0]->show();

    // 按键2：人机模式
    m_button[1] = new ClickLabel(400, 120, m_pixmap1, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[1]->setGeometry(610, 600, 400, 120);
    m_button[1]->raise();
    m_button[1]->show();

    // 按键3：双人模式
    m_button[2] = new ClickLabel(400, 120, m_pixmap2, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[2]->setGeometry(610, 750, 400, 120);
    m_button[2]->raise();
    m_button[2]->show();

    m_guideScene = new GuideScene(this);

    // 按键1：显示教程
    connect(m_button[0], &ClickLabel::clicked, this, [=]() {
        zoom(m_button[0]);
        m_guideScene->show();
        this->hide();
        });

    // 按键2：人机模式
    connect(m_button[1], &ClickLabel::clicked, this, [=]() {
        zoom(m_button[1]);
        m_bgm->stop();
        m_lastGameMode = ONEPLAYER;
        createGameScene(ONEPLAYER);
        this->hide();
        });

    // 按键3：双人模式
    connect(m_button[2], &ClickLabel::clicked, this, [=]() {
        zoom(m_button[2]);
        m_bgm->stop();
        m_lastGameMode = TWOPLAYERS;
        createGameScene(TWOPLAYERS);
        this->hide();
        });
}

void MainScene::createGameScene(const int gameMode)
{
    // 下一关的函数
    m_gameScene = new GameScene(gameMode);

    // 处理游戏界面的退出信号
    connect(m_gameScene, &GameScene::exit, this, [=]() {
        m_gameScene->close();
        //delete gameScene;
        
        m_gameScene = nullptr;
        m_bgm->play();
        this->show();
        });

    // 处理游戏界面的重新开始游戏界面
    connect(m_gameScene, &GameScene::restart, this, [=]() {
        m_gameScene->close();
        //delete gameScene;
        
        m_gameScene = nullptr;
        createGameScene(m_lastGameMode);
        });
    m_gameScene->show();
    this->hide();
}


void MainScene::paintEvent(QPaintEvent*)
{
    // 画背景
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_background);
}
