#include "characterlabel.h"

/* 此文件包含与人物相关的几种widgets
 * 分别包含人物属性栏CharacterProperty、人物操作选择栏CharacterSelection和血量条HPLabel
 * 以下是他们的初始化和相关方法的内容
 */

// 人物属性栏：依附于主窗体
CharacterProperty::CharacterProperty(QString name, int fullhp, int fullmove, int attrack, int attrackable,int armor, QWidget* parent) :
    QLabel(parent),
    m_name(name),
    m_fullhp(fullhp),
    m_fullmove(fullmove),
    m_attrack(attrack),
    m_attrackable(attrackable),
    m_armor(armor)
    
{
    // 初始设定
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setMouseTracking(true);
    setFixedSize(CELL_SIZE*3, CELL_SIZE*3);
    setPixmap(QPixmap(":/pic/dlg.png"));

    // 属性栏各种属性
    
    m_nameLabel.setText(m_name);
    m_hpLabel1.setText("血量");
    m_hpLabel2.setText(QString::number(m_fullhp) + "/" + QString::number(m_fullhp));
    m_moveLabel1.setText("行动力");
    m_moveLabel2.setText(QString::number(m_fullmove) + "/" + QString::number(m_fullmove));
    m_attrackLabel1.setText("攻击力");
    m_attrackLabel2.setText(QString::number(m_attrack));
    m_attrackableLabel1.setText("攻击范围");
    m_attrackableLabel2.setText(QString::number(m_attrackable));
    m_armorLabel1.setText("护甲");
    m_armorLabel2.setText(QString::number(m_armor));

    // 将属性加入layout
    m_layout.addWidget(&m_nameLabel, 0, 0);
    m_layout.addWidget(&m_hpLabel1, 1, 0);
    m_layout.addWidget(&m_hpLabel2, 1, 1);
    m_layout.addWidget(&m_moveLabel1, 2, 0);
    m_layout.addWidget(&m_moveLabel2, 2, 1);
    m_layout.addWidget(&m_attrackLabel1, 3, 0);
    m_layout.addWidget(&m_attrackLabel2, 3, 1);
    m_layout.addWidget(&m_attrackableLabel1, 4, 0);
    m_layout.addWidget(&m_attrackableLabel2, 4, 1);
    m_layout.addWidget(&m_armorLabel1, 5, 0);
    m_layout.addWidget(&m_armorLabel2, 5, 1);
    m_layout.setVerticalSpacing(0);
    setLayout(&m_layout);
}
// 更新属性栏数据
void CharacterProperty::updateData(const int hp, const int move1, const int localCellx, const int localCelly)
{
    bool ishidden = isHidden();
    // 寻找属性栏显示位置
    int x = 0;
    if ((localCellx - 1) * CELL_SIZE - CELL_SIZE*3 >= 0)
        x = (localCellx - 1) * CELL_SIZE - CELL_SIZE*3;
    else
        x = (localCellx - 1) * CELL_SIZE + 32;
    move(x, (localCelly - 1) * CELL_SIZE);
    // 更新数据
    m_hpLabel2.setText(QString::number(hp) + "/" + QString::number(m_fullhp));
    m_moveLabel2.setText(QString::number(move1) + "/" + QString::number(m_fullmove));
    if (ishidden)hide();
    else show();
}

BaseProperty::BaseProperty(QString name, int fullhp, int armor, QWidget* parent):
    QLabel(parent),
    m_name(name),
    m_fullhp(fullhp),
    m_armor(armor)
{
    // 初始设定
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setMouseTracking(true);
    setFixedSize(CELL_SIZE*3, CELL_SIZE*3);
    setPixmap(QPixmap(":/pic/dlg.png"));


    // 各个属性
    m_nameLabel.setText(m_name);
    m_hpLabel1.setText("血量");
    m_hpLabel2.setText(QString::number(m_fullhp) + "/" + QString::number(m_fullhp));
    m_armorLabel1.setText("护甲");
    m_armorLabel2.setText(QString::number(m_armor));

    // 将属性加入layout
    m_layout.addWidget(&m_nameLabel, 0, 0);
    m_layout.addWidget(&m_hpLabel1, 1, 0);
    m_layout.addWidget(&m_hpLabel2, 1, 1);
    m_layout.addWidget(&m_armorLabel1, 2, 0);
    m_layout.addWidget(&m_armorLabel2, 2, 1);
    m_layout.setVerticalSpacing(0);
    setLayout(&m_layout);
}

void BaseProperty::updateData(const int hp, const int localCellx, const int localCelly)
{
    bool ishidden = isHidden();
    // 寻找属性栏显示位置
    int x = 0;
    if ((localCellx - 1) * CELL_SIZE - CELL_SIZE*3 >= 0)
        x = (localCellx - 1) * CELL_SIZE - CELL_SIZE*3;
    else
        x = (localCellx - 1) * CELL_SIZE + 32;
    move(x, (localCelly - 1) * CELL_SIZE);
    // 更新数据
    m_hpLabel2.setText(QString::number(hp) + "/" + QString::number(m_fullhp));
    if (ishidden)hide();
    else show();
}

// 人物操作选择栏：依附于主窗体
CharacterSelection::CharacterSelection(QWidget* parent) :
    QLabel(parent)
{
    // 为三个操作按键设置layout
    m_layout = new QVBoxLayout;
    m_moveButton = new QPushButton;
    m_attrackButton = new QPushButton;
    m_skipButton = new QPushButton;
    setFixedSize(90, 90);
    // 设置文字
    m_moveButton->setText("移动");
    m_attrackButton->setText("攻击");
    m_skipButton->setText("跳过");
    m_layout->addWidget(m_moveButton);
    m_layout->addWidget(m_attrackButton);
    m_layout->addWidget(m_skipButton);
    m_layout->setSpacing(0);
    setLayout(m_layout);
}
// 更新人物操作栏信息，也即更新显示位置
void CharacterSelection::updateData(const int localCellx, const int localCelly)
{
    bool ishidden = isHidden();
    move((localCellx - 1) * CELL_SIZE + 64, (localCelly - 1) * CELL_SIZE - 10);
    if (ishidden)hide();
    else
    {
        show();
        raise();
    }
}

// 人物血条：依附于人物身上
HPLabel::HPLabel(const int hp, const int totalhp, const bool belong, const int size, QWidget* parent) :
    QLabel(parent), SIZE(size), m_hp(hp), m_totalhp(totalhp), m_belong(belong)
{

}
// 更新血量
void HPLabel::reset(const int t_hp, const int t_totalhp, const bool t_belong)
{
    m_hp = t_hp;
    if (m_hp < 0) m_hp = 0;
    m_totalhp = t_totalhp;
    m_belong = t_belong;
}
// 绘制血量
void HPLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (m_belong == YOURS)// 蓝方蓝血
        painter.setBrush(QColor(117, 27, 19));
    else // 红方红血
        painter.setBrush(QColor(36, 169, 255));
    painter.drawRect(0, 0, (1.0 * m_hp / m_totalhp) * SIZE, HP_HEIGHT); // 血槽内容
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, SIZE, HP_HEIGHT); // 血槽边框
    painter.setPen(Qt::NoPen);
}
