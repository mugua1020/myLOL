#include "playingmenu.h"

/* 此文件包含PlayingMenu和ResultMenu两个类
 * PlayingMenu显示游戏进行中的菜单
 * ResultMenu显示游戏结束后的菜单
 */

PlayingMenu::PlayingMenu(QWidget* parent) : QWidget(parent)
{
    // 设置默认值
    setWindowFlags(Qt::WindowCloseButtonHint);
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_shadowDlg = new QWidget(this);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");
    m_shadowDlg->setStyleSheet(str);
    m_shadowDlg->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 设置三个按钮
    QPixmap returnPixmap = QPixmap(":/pic/back_to_game.png");
    QPixmap restartPixmap = QPixmap(":/pic/restart.png");
    QPixmap exitPixmap = QPixmap(":/pic/exit_game.png");

    returnPixmap = returnPixmap.scaled(300, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    restartPixmap = restartPixmap.scaled(300, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    exitPixmap = exitPixmap.scaled(300, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    m_button[0] = new ClickLabel(300, 120, returnPixmap, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[1] = new ClickLabel(300, 120, restartPixmap, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[2] = new ClickLabel(300, 120, exitPixmap, this, ClickLabel::TRANSPARENTSTYLE);

    for (int i = 0; i < 3; i++)
    {
        m_button[i]->setGeometry(650, 200 + 200 * i, 300, 120);
        m_button[i]->raise();
    }

    // 按下第一个按钮：继续游戏
    connect(m_button[0], &ClickLabel::clicked, this, &PlayingMenu::hide);
    // 按下第二个按钮：发送重新开始游戏信号
    connect(m_button[1], &ClickLabel::clicked, this, [=]() {emit restartGame(); });
    // 按下第三个按钮：发送退出游戏信号
    connect(m_button[2], &ClickLabel::clicked, this, [=]() {emit exitGame(); });
}

ResultMenu::ResultMenu(QWidget* parent) :
    QWidget(parent)
{
    // 设置三个按钮
    QPixmap restartPixmap = QPixmap(":/pic/restart.png");
    QPixmap exitPixmap = QPixmap(":/pic/exit_game.png");
    

    restartPixmap = restartPixmap.scaled(200, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    exitPixmap = exitPixmap.scaled(200, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    m_button[0] = new ClickLabel(200, 80, restartPixmap, this, ClickLabel::TRANSPARENTSTYLE);
    m_button[1] = new ClickLabel(200, 80, exitPixmap, this, ClickLabel::TRANSPARENTSTYLE);
    
    for (int i = 0; i < 2; i++)
    {
        m_button[i]->setGeometry(700, 500 + 150 * i, 200, 80);
        m_button[i]->raise();
    }
    // 按下第一个按钮：重新开始游戏
    connect(m_button[0], &ClickLabel::clicked, this, [=]() {emit restartGame(); });
    // 按下第二个按钮：退出游戏
    connect(m_button[1], &ClickLabel::clicked, this, [=]() {emit exitGame(); });
    
}
// 显示结果
void ResultMenu::setResult(const bool blueWinOrNot, const bool AIOpenOrNot)
{
    setFixedSize(1600, 960);
    // 加阴影遮罩
    m_shadowDlg = new QWidget(this);
    QString str("QWidget{background-color:rgba(0,0,0,0.6);}");
    m_shadowDlg->setStyleSheet(str);
    m_shadowDlg->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    m_resultLabel = new HintLabel(this, 540, 200);

    // 显示按钮
    for (int i = 0; i < 2; i++)
        m_button[i]->raise();
    // 显示提示框
    if (AIOpenOrNot)
    {
        if (blueWinOrNot)
            m_resultLabel->setText("您获胜了！");
        else
            m_resultLabel->setText("您失败了！");
    }
    else
    {
        if (blueWinOrNot)
            m_resultLabel->setText("蓝方获胜");
        else
            m_resultLabel->setText("红方获胜");
    }
    m_resultLabel->show();
}
