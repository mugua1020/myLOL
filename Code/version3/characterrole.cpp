#include "characterrole.h"




// 战士，攻击力强
Warrior::Warrior(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 100; m_fullhp = 100;
    m_move = m_fullmove = 3;
    m_attrack = 70;
    m_armor =50;
    m_attrackable = 2;
    m_name = "剑圣";
    m_icon.load(WARRIOR_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE,this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}
// 刺客，行动力强
Assassin::Assassin(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 80; m_fullhp = 80;
    m_move = m_fullmove = 6;
    m_attrack = 100;
    m_armor =50;
    m_attrackable = 2;
    m_name = "阿卡丽";
    m_icon.load(ASSASSIN_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}
// 射手，攻击范围广
Shooter::Shooter(const int t_cellx, const int t_celly, const bool belong, QWidget* parent) :
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 80; m_fullhp = 80;
    m_move = m_fullmove = 4;
    m_attrack = 50;
    m_armor =20;
    m_attrackable = 4;
    m_name = "伊泽瑞尔";
    m_icon.load(SHOOTER_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}

// 法师， 攻击力强，攻击范围比较大
Master::Master(const int t_cellx, const int t_celly, const bool belong, QWidget* parent):
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 80; m_fullhp = 80;
    m_move = m_fullmove = 4;
    m_attrack = 50;
    m_armor =20;
    m_attrackable = 3;
    m_name = "见习小法师";
    m_icon.load(MASTER_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}

//坦克， 防御力强，血厚
Tank::Tank(const int t_cellx, const int t_celly, const bool belong, QWidget* parent):
    Character(t_cellx, t_celly, belong, parent)
{
    m_hp = 180; m_fullhp = 180;
    m_move = m_fullmove = 3;
    m_attrack = 30;
    m_armor =70;
    m_attrackable = 1;
    m_name = "龙龟";
    m_icon.load(TANK_PATH);
    setPixmap(m_icon);
    m_hpLabel = new HPLabel(m_hp, m_fullhp, m_belong, CELL_SIZE, this);
    m_propertyDlg = new CharacterProperty(m_name, m_fullhp, m_fullmove, m_attrack, m_attrackable, m_armor, parent);
    m_propertyDlg->hide();
}