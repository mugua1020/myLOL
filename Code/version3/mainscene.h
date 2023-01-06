#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "gamescene.h"
#include "gamelabel.h"

#include "guidescene.h"
#include <QWidget>

class MainScene :public QDialog
{
public:
    explicit MainScene(QWidget* parent = nullptr);
protected:
    GameScene* m_gameScene;
    GuideScene *m_guideScene; // 教程场景
    QPixmap m_background; // 主页图片
    ClickLabel *m_button[3]; // 主页上三个选择案件
    int m_lastGameMode;
    QSound *m_bgm;
protected:
    void paintEvent(QPaintEvent*)override;
    void createGameScene(const int gameMode);
};

#endif // MAINSCENE_H
