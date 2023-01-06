#ifndef ANIMATION_H
#define ANIMATION_H

#include "config.h"
#include <QObject>
#include <QWidget>

class MoveAnimation :public QWidget
{
    Q_OBJECT

public:
    MoveAnimation(QWidget *parent=nullptr);
public:
    // 移动固定一格的动画，用QPropertyAnimation写成
    void moveOneCell(QWidget* object, const int direction, const int duration = ANIMATION_DURATION);
    // 按照path移动的整体动画，用QTimer延时调用moveOneCell函数
    void moveAlongPath(QWidget* object, const std::vector<int>&);
signals:
    void widgetDown()const ; // 人物上移
    void widgetUp()const ; // 人物下移
    void widgetRight()const ; // 人物右移
    void widgetLeft()const ; // 人物左移
    void moveOneCellFinished()const ; // moveOneCell函数执行结束
    void animationFinished()const ; // 动画开始执行
    void animationStarted()const ; // moveAlongPath函数执行结束
};

class AttrackAnimation :public QWidget
{
    Q_OBJECT

public:
    AttrackAnimation(QWidget *parent = nullptr);
public:
    // 攻击某格敌人的动画
    void startMove(QWidget* object, const int beginx, const int beginy, const int endx, const int endy, const int duration = ANIMATION_DURATION);
signals:
    void animationFinished()const ; // 动画开始执行
    void animationStarted()const ; // 动画执行结束
};

// 弹跳动画声明
void zoom(QWidget*);

#endif // ANIMATION_H
