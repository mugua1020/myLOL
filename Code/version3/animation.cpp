#include "animation.h"
#include <QObject>

/*  此文件包含MoveAnimation和AttrackAnimation两个类
 *  分别完成人物的移动和攻击动画
 *  此外，zoom函数具有让QWidget表现出弹跳效果的功能
 */


MoveAnimation::MoveAnimation(QWidget* parent) :QWidget(parent)//上0 下1 左2 右3
{
}
// 移动固定一格的动画，用QPropertyAnimation写成
void MoveAnimation::moveOneCell(QWidget* object, const int direction,const int duration)
{
    // 开始格子
    int beginx = object->x();
    int beginy = object->y();
    // 结束格子
    int endx = beginx;
    int endy = beginy;

    // 计算结束格子
    switch (direction)
    {
    case LEFT:  endx -= CELL_SIZE; emit widgetLeft(); break;
    case RIGHT: endx += CELL_SIZE; emit widgetRight(); break;
    case UP: endy -= CELL_SIZE; emit widgetUp(); break;
    case DOWN: endy += CELL_SIZE; emit widgetDown(); break;
    }

    // 制作动画
    QPropertyAnimation* animation = new QPropertyAnimation(object, "geometry");
    animation->setStartValue(QRect(beginx, beginy, 64, 64));
    animation->setEndValue(QRect(endx, endy, 64, 64));
    animation->setDuration(duration);
    animation->start();
    emit moveOneCellFinished();
}
// 按照path移动的整体动画，用QTimer延时调用moveOneCell函数
void MoveAnimation::moveAlongPath(QWidget* object, const std::vector<int>& path)
{
    int duration = ANIMATION_DURATION;

    // 发送动画开始信号
    emit animationStarted();

    // 延时移动
    for (ull i = 0; i < path.size(); i++)
    {
        QTimer::singleShot(i * (1.5 * duration), this, [=]() {
            moveOneCell(object, path[i], duration);
            });
    }

    // 发送动画结束信号
    QTimer::singleShot((path.size()) * 1.5 * duration, this, [=]() {
        emit animationFinished();
        });
}
AttrackAnimation::AttrackAnimation(QWidget* parent) :
    QWidget(parent)
{
}
// 攻击某格敌人的动画
void AttrackAnimation::startMove(QWidget* object, const int begincellx, const int begincelly, const int endcellx, const int endcelly, const int duration)
{
    // 发送开始信号
    emit animationStarted();

    // 开始格子
    int beginx = (begincellx - 1) * CELL_SIZE;
    int beginy = (begincelly - 1) * CELL_SIZE;
    // 结束格子
    int endx = (endcellx - 1) * CELL_SIZE;
    int endy = (endcelly - 1) * CELL_SIZE;

    // 用QSequentialAnimationGroup串联前进和返回两个动画
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
    // 前进动画
    QPropertyAnimation* animation1 = new QPropertyAnimation(object, "geometry");
    animation1->setStartValue(QRect(beginx, beginy, CELL_SIZE, CELL_SIZE));
    animation1->setEndValue(QRect(endx, endy, CELL_SIZE, CELL_SIZE));
    animation1->setDuration(duration);
    group->addAnimation(animation1);
    // 返回动画
    QPropertyAnimation* animation2 = new QPropertyAnimation(object, "geometry");
    animation2->setEndValue(QRect(beginx, beginy, CELL_SIZE, CELL_SIZE));
    animation2->setStartValue(QRect(endx, endy, CELL_SIZE, CELL_SIZE));
    animation2->setDuration(duration);
    group->addAnimation(animation2);

    group->start();

    // 延时发射结束信号
    QTimer::singleShot(duration * 2, this, [=]() {
        emit animationFinished();
        });
}

// 弹跳动画
void zoom(QWidget* widget)
{
    int x = widget->x();
    int y = widget->y();

    // 用QSequentialAnimationGroup串联下降和上升两个动画
    QSequentialAnimationGroup* group = new QSequentialAnimationGroup;
    // 下降动画
    QPropertyAnimation* animation = new QPropertyAnimation(widget, "geometry");
    animation->setDuration(ZOOM_DURATION);
    animation->setStartValue(QRect(x, y, widget->width(), widget->height()));
    animation->setEndValue(QRect(x, y + 10, widget->width(), widget->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 上升动画
    group->addAnimation(animation);
    animation->setEndValue(QRect(x, y, widget->width(), widget->height()));
    animation->setStartValue(QRect(x, y + 10, widget->width(), widget->height()));
    group->addAnimation(animation);
    group->start();

    // 延迟保证动画效果
    //QTimer::singleShot(ZOOM_DURATION * 2, widget, [=]() {Sleep(100); });
}
