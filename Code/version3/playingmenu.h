#ifndef PLAYINGMENU_H
#define PLAYINGMENU_H

#include "gamelabel.h"
#include "config.h"
#include <QWidget>
#include <QPushButton>

class PlayingMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PlayingMenu(QWidget *parent = nullptr);
protected:
    ClickLabel *m_button[3]; // 游戏菜单的三个选项
    QWidget *m_shadowDlg; // 阴影遮罩
signals:
    void restartGame()const ; // 重新开始游戏
    void exitGame()const ; // 退出游戏
};

class ResultMenu : public QWidget
{
    Q_OBJECT
public:
    ClickLabel *m_button[2]; // 结束菜单的三个选项
    HintLabel * m_resultLabel; // 游戏结果的hint
    QWidget *m_shadowDlg; // 阴影遮罩
public:
    explicit ResultMenu( QWidget *parent = nullptr);//蓝方获胜1 红方获胜0
    void setResult(const bool blueWinOrNot, const bool AIOpenOrNot);
signals:
    void restartGame(); // 重新开始游戏
    void exitGame(); // 退出游戏
};
#endif // PLAYINGMENU_H
