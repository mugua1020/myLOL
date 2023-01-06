#include "base.h"


Base::Base(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    QLabel(parent),m_belong(belong),ALIVE(true),
    m_cellx(t_cellx), m_celly(t_celly)
    
{
    // 初始设定
    setAttribute(Qt::WA_MouseNoMask, true);

    m_layout = new QVBoxLayout(this);

    // 当人物信息改变时，血条、人物属性和操作选择框的所有信息都要改变
    connect(this, &Base::infoChanged, [=]() {
        // 按顺序，raise有次序
        if (ALIVE == false)
        {
            m_propertyDlg->close();
            hide();
        }
        m_propertyDlg->updateData(m_hp, m_cellx, m_celly);
        m_hpLabel->reset(m_hp, m_fullhp, belong);
        m_hpLabel->repaint();
        });

    connect(this, &Base::beAttracked, this, &Base::attrackedEvent);


}
// 鼠标进入，弹出人物属性栏
void Base::enterEvent(QEvent*)
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
void Base::leaveEvent(QEvent*)
{
    if (m_propertyDlg->isHidden() == false)
        m_propertyDlg->hide();
}



// 被攻击时，attrack是被攻击的攻击点数
void Base::attrackedEvent(const int attrack)
{
    // 扣血
    m_hp -= int(m_armor/100.0 * attrack);

    // 判断是否死亡
    if (m_hp <= 0)
    {
        ALIVE = false;
        hide();
        emit dieOneBase(this);
    }

    // 扣血条
    QLabel* tempLabel = new QLabel(parentWidget());
    tempLabel->setAttribute(Qt::WA_DeleteOnClose);
    tempLabel->setStyleSheet("color:rgb(255,40,0); font:bold; font-size:20px;");
    tempLabel->setText(QString("-%1").arg(attrack));
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

// 需要更新数据时，发射数据更新信号
void Base::updateInfo() const
{
    emit infoChanged();
}

Egg::Egg(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent):
    Base(t_cell_x, t_cell_y, belong, parent)
{
    m_hp=200; m_fullhp=200;
    m_armor = 60;
    m_name = "旦旦";
    m_icon.load(EGG_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new BaseProperty(m_name, m_fullhp, m_armor, parent);
    m_propertyDlg->hide();

}
