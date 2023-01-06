#ifndef CHARACTERLABEL_H
#define CHARACTERLABEL_H

#include <QLabel>
#include "config.h"

class CharacterProperty: public QLabel
{
    Q_OBJECT
public:
    explicit CharacterProperty(QString name, int fullhp, int fullmove, int attrack, int attrackable, int armor, QWidget* parent);

protected:
    QString m_name;
    int m_fullhp;
    int m_fullmove;
    int m_attrack;
    int m_attrackable;
    int m_armor;

public:
    QGridLayout m_layout;
    QLabel m_nameLabel, m_hpLabel1, m_hpLabel2, m_moveLabel1, m_moveLabel2, 
    m_attrackLabel1, m_attrackLabel2, m_attrackableLabel1, m_attrackableLabel2,
    m_armorLabel1, m_armorLabel2;
    // 更新属性栏数据
    void updateData(const int hp, const int move, const int localCellx, const int localCelly);

};

class BaseProperty: public QLabel
{
    Q_OBJECT
public:
    explicit BaseProperty(QString name, int fullhp, int armor, QWidget* parent);

protected:
    QString m_name;
    int m_fullhp;
    int m_armor;

public:
    QGridLayout m_layout;
    QLabel m_nameLabel, m_hpLabel1, m_hpLabel2,
    m_armorLabel1, m_armorLabel2;
    void updateData(const int hp, const int localCellx, const int localCelly);

};

class CharacterSelection: public QLabel
{
    Q_OBJECT
public:
    explicit CharacterSelection(QWidget* parent = nullptr);
public:
    QVBoxLayout *m_layout;
    QPushButton *m_moveButton, *m_attrackButton, *m_skipButton; // 操作栏上三个按钮
    // 更新操作栏数据
    void updateData(const int localCellx, const int localCelly); // 更新数据
};

class Character;
class HPLabel: public QLabel
{
    Q_OBJECT
public:
    int SIZE;
    explicit HPLabel(const int hp, const int totalhp, const bool belong, const int size, QWidget* parent = nullptr);
public:
    int m_hp, m_totalhp, m_belong; // 血量值
    void reset(const int hp, const int totalhp, const bool belong); //重置血量值
    void paintEvent(QPaintEvent*)override; // 绘制
};

#endif // CHARACTERLABEL_H
