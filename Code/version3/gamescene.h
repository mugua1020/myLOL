#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "gamemap.h"
#include "character.h"
#include "config.h"
#include "algorithm.h"
#include "gamelabel.h"
#include "aicontroller.h"
#include "animation.h"
#include "playingmenu.h"
#include "base.h"

class GameScene : public QDialog
{
    Q_OBJECT
public:
    enum GAMESTATE{BEGIN,FINDPATH,FINDATTRACK,AI,END};
    explicit GameScene(const int gameMode = ONEPLAYER, QWidget *parent = nullptr);
    ~GameScene();
protected:
    FindPathAlgorithm moveAl, attrackAl; // 移动可行域和攻击可行域的算法类
    void paintEvent(QPaintEvent*)override; // 绘制函数
    void mouseMoveEvent(QMouseEvent*)override; // 鼠标移动函数
    void mousePressEvent(QMouseEvent*)override; // 鼠标点击函数
    bool eventFilter(QObject*, QEvent*)override; // 对Character事件过滤
    void setScreenMoveTimer();  // 设置屏幕移动判断的QTimer
    void setButton(); // 设置屏幕右下角四个按钮
    void createCharacter(); // 初始创建人物
    void createBase();  //创建双方基地
    void ReliveCharacter(int id); //复活序号为id的人物
    void updateMousePosition(QMouseEvent*);
    void nextRound(const int last); // 到达下一局，进行初始化
    void AIRound()const ; // 启动AI回合
    void AIMoveCharacter(const int id); // 调用aicontroller以完成ai回合
    
protected:
    GameMap m_map; // GameMap数据
    
    int m_mousex, m_mousey; // 当前鼠标坐标（地图上的像素）
    int m_mouseCellx, m_mouseCelly; // 当前鼠标坐标（地图上的格子）
    
    Character * m_character[10], *m_nowCharacter; // 储存人物和当前人物
    Base *YoursBase, *MineBase, *EnemyBase;
    int m_game_number;  //记录到第几轮游戏
    int m_character_relive[10];
    int m_characterNum; // 人物总数
    int m_gameState; // 当前游戏状态，详见GAMESTATE枚举变量
    int m_aliveNum[2]; // 场上存活人物总数，0、1参考BELONGING枚举变量
    int m_roundNum[2]; // 本局剩余可行人数，0、1参考BELONGING枚举变量
    bool m_roundBelonged; // 本局属于何方，0、1参考BELONGING枚举变量
    bool m_AIOpenOrNot; // AI是否开启
    ClickLabel *m_cancelButton, *m_skipButton, *m_menuButton, *m_musicButton; // 屏幕右下角四个按钮
    HintLabel *m_hint; // 提示框
    AIController *m_aiController; // AI控制者
    QSound *m_bgm, *m_attrackSound, *m_clickSound; // 各种音乐音效
    MoveAnimation *m_animation; // 移动动画管理器
    PlayingMenu *m_playingMenu; // 游戏菜单
    ResultMenu *m_resultMenu; // 游戏结果菜单
    

signals:
    
    void myLoss()const ; void myWin()const ; // 输赢信号
    void restart()const ; void exit()const ; // 重新开始游戏/退出信号
public slots:
    void redrawCharacter()const ; // 重绘人物
    void redrawBase()const; //重绘基地
    void characterMoveEvent(Character*); // 人物坐标移动
    void characterAttrackEvent(Character*); // 处理人物攻击事件
    void endOneCharacterEvent(Character*); // 处理人物回合结束事件
    void dieOneCharacterEvent(Character*); // 处理人物死亡事件
    void dieOneBaseEvent(Base*); //处理基地死亡事件
    void receiveHint(const QString str)const ; // 给出提示框
};
#endif // GAMESCENE_H
