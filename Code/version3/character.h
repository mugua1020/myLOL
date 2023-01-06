#ifndef CHARACTER_H
#define CHARACTER_H

#include "config.h"
#include "characterlabel.h"
#include <QWidget>
#include "animation.h"

class Character: public QLabel
{
    Q_OBJECT

public:
    enum CHARACTERSTATE{BEGIN, FINDPATH, FINDATTRACK, END, DEAD};
    Character(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
protected:
    QPixmap m_icon; // 人物图标
    QString m_name; // 人物名称
    QVBoxLayout *m_layout;
    HPLabel *m_hpLabel; // 血条
public:
    int m_hp, m_fullhp, m_move,m_fullmove,m_attrack, m_attrackable, m_armor; // 人物各项属性
    bool m_belong; //人物归属，见枚举变量BELONGING
    bool m_attrackedOrNot;// 攻击为1，未攻击为0
    CharacterProperty *m_propertyDlg; // 人物属性栏
    CharacterSelection *m_selectionDlg; // 人物操作选择栏
    int m_characterState; // 人物状态，见CHARACTERSTATE枚举变量
    int m_cellx, m_celly; //  全局位置
    
    MoveAnimation *m_mover; // 移动动画播放器
    AttrackAnimation *m_attracker; // 攻击动画播放器
public:
    // void setLabel();
    // 鼠标进入，弹出人物属性栏
    void enterEvent(QEvent *)override;
    // 鼠标移出，关闭人物属性栏
    void leaveEvent(QEvent *)override;
    // 给予路径，调动MoveAnimation播放移动的动画
    void movePos(const int steps, const std::vector<int>&path);
public slots:
    // 人物需要移动，连接到GameScene的寻路显示上
    void moveAction();
    // 人物需要攻击，连接到GameScene的攻击显示上
    void attrackAction();
    // 跳过选择，向GameScene说明有人结束
    void skipAction();
    // 被攻击时伤害结算，attrack是被攻击的攻击点数
    void attrackedEvent(const int attrack);
    // 需要更新数据时，发射数据更新信号
    void updateInfo()const ;
signals:
    // 人物移动
    void characterMoveAction(Character*)const ;
    // 人物进攻
    void characterAttrackAction(Character*)const ;
    // 基本信息改变
    void infoChanged()const ;
    // 人物被攻击
    void beAttracked(int attrack)const ;
    // 人物去世
    void dieOneCharacter(Character*)const ;
    // 人物结束当前回合
    void endOneCharacter(Character*)const ;
    // 需要发送HintLabel
    void submitHint(QString)const ;
    // 隐藏“取消”键
    void hideCancelButton()const ;
    // 重绘主屏幕
    void repaintScreen()const ;
};

#endif // CHARACTER_H
