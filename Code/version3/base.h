#ifndef BASE_H
#define BASE_H

#include <QLabel>
#include <QWidget>
#include "config.h"
#include "characterlabel.h"


class Base: public QLabel
{
    Q_OBJECT

public:
    Base(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);

protected:
    QPixmap m_icon; // 基地图标
    QString m_name; // 基地名称
    QVBoxLayout *m_layout;
    HPLabel *m_hpLabel; // 血条

public:
    int m_hp, m_fullhp, m_armor;    //基地的血量和护甲属性
    bool m_belong;
    BaseProperty *m_propertyDlg;    //基地属性栏
    bool ALIVE;
    int m_cellx, m_celly;

public:
    void setLabel();
    // 鼠标进入，弹出属性栏
    void enterEvent(QEvent *)override;
    // 鼠标移出，关闭属性栏
    void leaveEvent(QEvent *)override;

public slots:
    // 被攻击时伤害结算，attrack是被攻击的攻击点数
    void attrackedEvent(const int attrack);
    // 需要更新数据时，发射数据更新信号
    void updateInfo()const ;

signals:
    // 基本信息改变
    void infoChanged()const ;
    // 被攻击
    void beAttracked(int attrack)const ;
    // 基地毁坏
    void dieOneBase(Base*)const ;
    // 重绘主屏幕
    void repaintScreen()const ;
};

class Egg: public Base
{
public:
    Egg(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);

};


#endif // BASE_H
