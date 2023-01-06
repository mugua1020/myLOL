#include "character.h"
#include "algorithm.h"

/* 此文件包含与人物角色有关的方法
 * 包含人物各种活动和控制三种人物面板（characterlabel.h）等过程
 */

Character::Character(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    QLabel(parent),m_belong(belong),m_attrackedOrNot(false),m_characterState(BEGIN),
    m_cellx(t_cellx), m_celly(t_celly)
    
{
    // 初始设定
    setAttribute(Qt::WA_MouseNoMask, true);

    // 关于移动、攻击动画的信号和槽
    m_mover = new MoveAnimation;
    m_attracker = new AttrackAnimation;
    connect(m_mover, &MoveAnimation::widgetDown, this, [=]() {m_celly++; });
    connect(m_mover, &MoveAnimation::widgetUp, this, [=]() {m_celly--; });
    connect(m_mover, &MoveAnimation::widgetRight, this, [=]() {m_cellx++; });
    connect(m_mover, &MoveAnimation::widgetLeft, this, [=]() {m_cellx--; });
    connect(m_mover, &MoveAnimation::animationFinished, this, [=]() {emit infoChanged(); });
    m_layout = new QVBoxLayout(this);
    // 操作选择框
    m_selectionDlg = new CharacterSelection(parent);
    m_selectionDlg->hide();

    // 当人物信息改变时，血条、人物属性和操作选择框的所有信息都要改变
    connect(this, &Character::infoChanged, [=]() {
        // 按顺序，raise有次序
        if (m_characterState == DEAD)
        {
            m_propertyDlg->close();
            m_selectionDlg->close();
            hide();
        }
        m_propertyDlg->updateData(m_hp, m_move, m_cellx, m_celly);
        m_selectionDlg->updateData(m_cellx, m_celly);
        m_hpLabel->reset(m_hp, m_fullhp, belong);
        m_hpLabel->repaint();
        });

    // 操作选择框的各个操作按钮
    connect(m_selectionDlg->m_moveButton, &QPushButton::clicked,
        this, &Character::moveAction);
    connect(m_selectionDlg->m_attrackButton, &QPushButton::clicked,
        this, &Character::attrackAction);
    connect(m_selectionDlg->m_skipButton, &QPushButton::clicked,
        this, &Character::skipAction);
    connect(this, &Character::beAttracked, this, &Character::attrackedEvent);


}
// 鼠标进入，弹出人物属性栏
void Character::enterEvent(QEvent*)
{
    if (m_propertyDlg->isHidden() == true)
    {
        m_propertyDlg->show();
        m_propertyDlg->raise();
        // 延时关闭
        QTimer::singleShot(1500, this, [=]() {
            m_propertyDlg->hide();
            });
    }
}
// 鼠标移出，关闭人物属性栏
void Character::leaveEvent(QEvent*)
{
    if (m_propertyDlg->isHidden() == false)
        m_propertyDlg->hide();
}
// 人物需要移动，连接到GameScene的寻路显示上
void Character::moveAction()
{
    if (m_selectionDlg->isHidden() == false)
        m_selectionDlg->hide();
    m_characterState = FINDPATH;
    emit characterMoveAction(this);
}
// 人物需要攻击，连接到GameScene的攻击显示上
void Character::attrackAction()
{
    if (m_attrackedOrNot)
    {
        emit submitHint("本回合已攻击过");
        emit hideCancelButton();
        return;
    }
    if (m_selectionDlg->isHidden() == false)
        m_selectionDlg->hide();
    m_characterState = FINDATTRACK;
    emit characterAttrackAction(this);
}
// 被攻击时，attrack是被攻击的攻击点数
void Character::attrackedEvent(const int attrack)
{
    // 扣血
    m_hp -= int(m_armor/100.0 * attrack);

    // 判断是否死亡
    if (m_hp <= 0)
    {
        m_characterState = DEAD;
        hide();
        emit dieOneCharacter(this);
    }

    // 扣血条
    QLabel* tempLabel = new QLabel(parentWidget());
    tempLabel->setAttribute(Qt::WA_DeleteOnClose);
    if(attrack>0){
        tempLabel->setStyleSheet("color:rgb(117, 27, 19); font:bold; font-size:20px;");
        tempLabel->setText(QString("-%1").arg(attrack));
    }
    else{
        tempLabel->setStyleSheet("color:rgb(36, 169, 255); font:bold; font-size:20px;");
        tempLabel->setText(QString("+%1").arg(-attrack));
    }
    
    tempLabel->show();
    tempLabel->raise();
    // 扣血条上浮并停留的动画
    QPropertyAnimation* animation = new QPropertyAnimation(tempLabel, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect((m_cellx - 1) * CELL_SIZE + CELL_SIZE / 4, (m_celly - 1) * CELL_SIZE - 30, tempLabel->width(), tempLabel->height()));
    animation->setEndValue(QRect((m_cellx - 1) * CELL_SIZE + CELL_SIZE / 4, (m_celly - 1) * CELL_SIZE - 30 - 30, tempLabel->width(), tempLabel->height()));
    animation->start();

    emit infoChanged();
    QTimer::singleShot(1500, this, [=]() {tempLabel->close(); });
}
// 跳过选择，向GameScene说明有人结束
void Character::skipAction()
{
    m_characterState = END;
    m_selectionDlg->hide();
    emit endOneCharacter(this);
}
// 需要更新数据时，发射数据更新信号
void Character::updateInfo() const
{
    emit infoChanged();
}
// 给予路径，调动MoveAnimation播放移动的动画
void Character::movePos(const int steps, const std::vector<int>&path)
{
    m_selectionDlg->hide();
    m_move -= steps;
    m_mover->moveAlongPath(this, path);
    updateInfo();
}
