#ifndef CHARACTERROLE_H
#define CHARACTERROLE_H

#include "character.h"

// 战士
class Warrior: public Character
{
public:
    Warrior(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};
// 刺客
class Assassin: public Character
{
public:
    Assassin(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};
// 射手
class Shooter: public Character
{
public:
    Shooter(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};

//法师
class Master: public Character
{
public:
    Master(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};

//坦克
class Tank: public Character
{
public:
    Tank(const int t_cell_x, const int t_cell_y, const bool belong, QWidget* parent = nullptr);
};
#endif // CHARACTERROLE_H
